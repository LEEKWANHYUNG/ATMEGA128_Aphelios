#include "lcd.h"

// LCD 시간 지연 함수입니다. 명렁을 IR레지스터에 쓰고나면 40us 또는 1.64ms를 기다린 후에 다음 명령을 쑬수있습니다.
// 또한 CGRAM 또는 DDRAM에 데이터를 쓰고 나면 40us를 기다린 후에 다음 명령을 쓸 수 있습니다.
void LCD_delay(BYTE ms)
{
    delay_ms(ms);
}

//연결된 포트 A와 G의 포트를 기본적으로 출력을 세팅해주는 함수입니다
void PortInit(void)
{
    DDRA = 0xFF; //PORTA를 출력으로 설정합니다.  LCD의 데이터 전송핀을 A에 연결합니다.
    DDRG = 0x0F; // PORTG의 하위 4비트를 출력으로 설정합니다
}

void LCD_Shift(char p) //LCD의 화면을 이동해주는 함수입니다 여기서 P는 오른쪽 왼쪽의 여부입니다.
{
    if (p == RIGHT) //명령어가 오른쪽으로 이동하라고 하면은
    {
        LCD_Comm(0x1C); // 0b0001 1100  즉 화면 DB3 DB2는 S/C=1은 화면을 이동한다는 뜻이고 R/L은 우로 시프트한다는 뜻입니다.
        LCD_delay(1);   //지연은 40us 정도 걸립니다.
    }
    else if (p == LEFT) //명령어가 왼쪽으로 이동하라고 하면은
    {
        LCD_Comm(0x18); // ob 0001 1000 S/C=1은 화면을 이동하고 R/L이0인 경우는 좌로 시프트한다는 뜻입니다.
        LCD_delay(1);
    }
}

void LCD_Data(BYTE ch) //데이터 레지스터에 데이터를 쓰는 함수입니다.
{
    LCD_CTRL |= (1 << LCD_RS);
    LCD_CTRL &= ~(1 << LCD_RW);
    LCD_CTRL |= (1 << LCD_EN);
    //여기서는 RS=1 RW=0으로 하여 dr을 선택하여 데이터 값을 쓰기 모드를 설정해줍니다.
    delay_us(50);
    LCD_WDATA = ch; //포트 A에 ch입력값을 넣어줍니다. 즉 데이터를 출력합니다.
    delay_us(50);
    LCD_CTRL &= ~(1 << LCD_EN); //PORTG에다가 LCD Disable 기능을 설정해줍니다.
}

void LCD_Comm(BYTE ch) // 명령 레지스터에 명령어 쓰기 함수입니다.
{
    LCD_CTRL &= ~(1 << LCD_RS);
    LCD_CTRL &= ~(1 << LCD_RW);
    LCD_CTRL |= (1 << LCD_EN);
    // 여기서는 RS=0 R/W=0으로 설정해줍니다 이 기능은 IR을 선택하여 제어 명령쓰기 입니다. 예시로는 디스플레이 클리어가 있습니다.
    delay_us(50);
    LCD_WINST = ch; //PORTA 에다가 ch값을 넣어줍니다. 즉 명령어를 적습니다.
    delay_us(50);
    LCD_CTRL &= ~(1 << LCD_EN); //Disable 모드로 바꿔줍니다.
}

void LCD_CHAR(BYTE c) //한 문자를 출력하는 함수입니다.
{
    LCD_Data(c); //DDRAM으로 데이터를 전달하는 명령어입니다.
    delay_ms(1);
}

void LCD_STR(BYTE *str) //str 포인터를 통해서 문자열을 받고 이 포인터가 가리키는 문자열을 문자열이 끝날 떄 까지 출력하는 함수입니다.
{
    while (*str != 0)
    {
        LCD_CHAR(*str);
        str++;
    }
}

void LCD_pos(unsigned char row, unsigned char col) //LCD 포지션 설정하는 함수입니다.
{
    LCD_Comm(0x80 | (row * 0x40 + col)); //row : 행 가로줄 col은 열 세로줄입니다.
}

void LCD_Clear(void) // 화면을 클리어 하는 함수입니다.
{
    LCD_Comm(0x01);
    LCD_delay(2);
}

void LCD_Init(void) //LCD의 초기화 상태를 사용하는 것입니다.
{
    LCD_Comm(0x38); // DDRAM, 데이터 8비트사용, LCD 2열로 사용 (6)
    LCD_delay(2);   // 2ms 지연
    LCD_Comm(0x38); // DDRAM, 데이터 8비트사용, LCD 2열로 사용 (6)
    LCD_delay(2);   // 2ms 지연
    LCD_Comm(0x38); // DDRAM, 데이터 8비트사용, LCD 2열로 사용 (6)
    LCD_delay(2);   // 2ms 지연
    //여기서 설정된 값(0x38)을 IR 레지스터에 연속하여 3회정도 쓰고 명령을 쓰는 과정에서 명령어가 처리 되는 시간을 지연함수를 사용하여 기다립니다.
    LCD_Comm(0x0e); // Display ON/OFF
    LCD_delay(2);   // 2ms 지연 여기서는 1.64ms 이상을 기다린다는 뜻입니다.
    LCD_Comm(0x06); // 주소+1 , 커서를 우측 이동 (3)  entry mode set이라는 뜻입니다.
    LCD_delay(2);   // 2ms 지연
    LCD_Clear();    // LCD 화면 클리어
}

void Cursor_Home(void) // Cursor를 (0,0)의 위치로 이동하는 함수입니다.
{
    LCD_Comm(0x02); // 0b 0000 0010 커서를 홈 위치로 돌아가게 한다는 뜻입니다.
    LCD_delay(2);   // 커서홈의 기능의 실행시간은 1.64ms입니다.
}

void Cursor_shift(BYTE p)
{
    if (p == RIGHT)
    {
        LCD_Comm(0x14); //ob 0001 0100 S/C는 0 즉 커서 이동을 선언하고 R/L에서는 RIGHT로 이동을 선언합니다
        LCD_delay(1);
    }
    else if (p == LEFT)
    {
        LCD_Comm(0x10); //ob 0001 0000 S/C=0 커서이동을 선언하고 R/L에서는 Left로 이동을 선언합니다.
        LCD_delay(1);
    }
}

// 화면 ON/OFF 제어 기능입니다.
void LCD_OnOFF(void)
{
    LCD_Comm(0x0e); //모든 기능을 on 합니다.
    LCD_delay(2);   //2ms를 지연시킵니다
}

//엔트리 모드 세트 기능을 하는 함수입니다.
void Init_Lcd(void)
{
    DDRA = 0xFF;    //DDRA를 출력으로 지정합니다.
    DDRG = 0x0F;    //PORTG의 하위비트 4비트를 출력으로 지정합니다
    LCD_Comm(0x38); //lcd 모드 를 2라인의 5x8로 지정을 합니다
    LCD_delay(2);   // 2ms 딜레이를 걸어줍니다.
    LCD_Comm(0x38); //lcd 모드 를 2라인의 5x8로 지정을 합니다
    LCD_delay(2);   // 2ms 딜레이를 걸어줍니다.
    LCD_Comm(0x38); //lcd 모드 를 2라인의 5x8로 지정을 합니다
    LCD_delay(2);   // 2ms 딜레이를 걸어줍니다.
    LCD_Comm(0x0e); //Display on /off 를 진행합니다
    LCD_delay(2);
    LCD_Comm(0x01); // LCD를 클리어합니다
    LCD_delay(30);
    LCD_Comm(0x06); //cursor entry mode를 세팅합니다
    LCD_delay(2);
}