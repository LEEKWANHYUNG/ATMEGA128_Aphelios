#include <iom128v.h>
#include "lcd.h"
#include "my128.h"

#pragma interrupt_handler timer0_comp_isr : iv_TIM0_COMP //Ÿ�̸� �����÷ο찡 �񱳸� �߶� ������ �ϴ� ���ͷ�Ʈ �Դϴ�.
#pragma interrupt_handler ext_int0_isr : iv_EXT_INT0     //ext_int0_isr��� ���ͷ�Ʈ �Լ��� ���ͷ�Ʈ ���Ͷ�� ������ ���ݴϴ�. �켱 ����2
#pragma interrupt_handler ext_int1_isr : iv_EXT_INT1     //ext_int1_isr��� ���ͷ�Ʈ �Լ��� ���ͷ�Ʈ ���Ͷ�� ������ ���ݴϴ�. �켱 ����3
#pragma interrupt_handler ext_int2_isr : iv_EXT_INT2     //ext_int2_isr��� ���ͷ�Ʈ �Լ��� ���ͷ�Ʈ ���Ͷ�� ������ ���ݴϴ�. �켱 ����4

int cnt = 0;

void Interrupt_init(void); //���ͷ�Ʈ�� �ʱ�ȭ ���ִ� �Լ��Դϴ�.
void Init_timer0(void);    // Ÿ�̸�/ī����2�� ����ϱ� ������ �ʱ�ȭ�Լ��� �������ݴϴ�.
void ext_int0_isr(void);
void ext_int1_isr(void);
void ext_int2_isr(void);
void timer0_comp_isr(void);

BYTE SPEED_SECOND = 0X30;
BYTE SECOND = 0X30;
BYTE MINUTE = 0X30;

BYTE TIME[] = "TIME ";
BYTE TMP[] = ":";
BYTE DOT[] = ".";

void main(void)
{
    Init_timer0();
    Interrupt_init(); // ó���� ���ͷ�Ʈ�� �ʱ�ȭ ���ݴϴ�.
    PortInit();       //LCD�� ���� ��Ʈ�� �����մϴ�.
    LCD_Init();       //LCD�� ������ �ʱ�ȭ���ݴϴ�.
    LCD_pos(0, 0); // LCD�� ��ġ�� 0��0�� ��ġ��ŵ�ϴ�.
    LCD_STR(TIME); // str�� ���ڸ� ǥ�����ݴϴ�
    while (1)
    {
    }
}

void Interrupt_init(void) //���ͷ�Ʈ�� �ʱ�ȭ ���ִ� �Լ��Դϴ�.
{
    EICRA = 0x2A; //0b 0010 1010 : INT0,INT1,INT2 ��Ʈ ������ �մϴ� �ܺ� INT0,INT1,INT2 �㰡 �մϴ�.
    EIMSK = 0x09; // INT0,INT1,INT2�� ���ͷ�Ʈ�� �㰡�մϴ�.
    SREG |= 0x80; //��ü ���ͷ�Ʈ �㰡�� �Դϴ�.
}

void Init_timer0(void)
{
    TCCR0 |= (1 << WGM01) | (1 << COM00) | (1 << CS02) | (1 << CS01); //Ÿ�̸�0�� CTC��� ���� ����ġ���� ��� ���ֺ� 256���� �����մϴ�.
    OCR0 = 156;
}

void timer0_comp_isr(void)
{
    cnt++;
    if (cnt ==63 ) //0.01�� ����
    {
        SPEED_SECOND++;
        cnt = 0;
    }
    if (SPEED_SECOND == 0x3A) //���࿡ 1���ڸ����� 0x3A = 0b 0011 1010 �� 10�� �ƽ�Ű�ڵ尡 �Ǹ���
    {
        SPEED_SECOND = 0x30; //1�� �ڸ������ٰ� 0�� �־��ݴϴ�.
        SECOND++;            // �״����� 1�� �ڸ����� 0���� �ʱ�ȭ�ǰ� 10�� �ڸ����� �ϳ� �ö󰩴ϴ�.
    }
    if (SECOND == 0x3A) // ���� ���� ������ 10���ڸ����ڰ� 10�� ���� ����Դϴ�.
    {
        SECOND = 0x30; //10���ڸ������ٰ� 0�� �־��ݴϴ�.
        MINUTE++;      // �״����� 100���ڸ����� �ϳ� ���������ݴϴ�.
    }
    if (MINUTE == 0x3A)
    {
        BYTE SPEED_SECOND = 0X30;
        BYTE SECOND = 0X30;
        BYTE MINUTE = 0X30;
    }

    PortInit();             //LCD�� ���� ��Ʈ�� �����մϴ�.
    LCD_Init();             //LCD�� ������ �ʱ�ȭ���ݴϴ�.
    LCD_pos(0, 0);          // LCD�� ��ġ�� 0��0�� ��ġ��ŵ�ϴ�.
    LCD_STR(TIME);          // str�� ���ڸ� ǥ�����ݴϴ�
    LCD_pos(0, 6);          //0�� 0������ ����Ѵ�
    LCD_Data(MINUTE);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(TMP);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SECOND);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(DOT);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SPEED_SECOND); //�������� LCD�� ������ݴϴ�.
}

void ext_int0_isr(void) // START 1/100�� ������ �ð��� ����� �ϸ鼭 �����ϸ� ����� LCD�� ���������� ������Ʈ�Ѵ�
{
    PortInit();             //LCD�� ���� ��Ʈ�� �����մϴ�.
    LCD_Init();             //LCD�� ������ �ʱ�ȭ���ݴϴ�.
    LCD_pos(0, 0);          // LCD�� ��ġ�� 0��0�� ��ġ��ŵ�ϴ�.
    LCD_STR(TIME);          // str�� ���ڸ� ǥ�����ݴϴ�
    LCD_pos(0, 6);          //0�� 0������ ����Ѵ�
    LCD_Data(MINUTE);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(TMP);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SECOND);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(DOT);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SPEED_SECOND); //�������� LCD�� ������ݴϴ�.
}

void ext_int1_isr(void)
{
    cnt = 0;
    PortInit();             //LCD�� ���� ��Ʈ�� �����մϴ�.
    LCD_Init();             //LCD�� ������ �ʱ�ȭ���ݴϴ�.
    LCD_pos(0, 0);          // LCD�� ��ġ�� 0��0�� ��ġ��ŵ�ϴ�.
    LCD_STR(TIME);          // str�� ���ڸ� ǥ�����ݴϴ�
    LCD_pos(0, 6);          //0�� 0������ ����Ѵ�
    LCD_Data(MINUTE);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(TMP);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SECOND);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(DOT);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SPEED_SECOND); //�������� LCD�� ������ݴϴ�.
}

void ext_int2_isr(void)
{
    LCD_Init();    //LCD�� �ʱ�ȭ �����ݴϴ�.
    LCD_pos(0, 0); //0�� 0������ ����Ѵ�
    LCD_STR(TIME); //�������� LCD�� ������ݴϴ�.
    BYTE SPEED_SECOND = 0X30;
    BYTE SECOND = 0X30;
    BYTE MINUTE = 0X30;
    LCD_Data(MINUTE);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(TMP);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SECOND);       //�������� LCD�� ������ݴϴ�.
    LCD_STR(DOT);           //�������� LCD�� ������ݴϴ�.
    LCD_Data(SPEED_SECOND); //�������� LCD�� ������ݴϴ�.
}
