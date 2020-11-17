Project:      .\Aphelios_ATMEGA128
Build Number: 0
Date:         Tue Nov 17 23:08:00 2020
Compiler:     ICCAVR
Version:      8.18.00
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 2% full. 1519 out of 131072 bytes used (does not include absolute areas).
  RAM 15 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   00D4   000F =     15. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __idata_start
       00E3  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00E4   05E0 =   1504. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0072  __text_start
       0072  __start
       0094  _exit
       0095  _LCD_delay
       009D  _PortInit
       00A3  _LCD_Shift
       00B4  _LCD_Data
       00D5  _LCD_Comm
       00F6  _LCD_CHAR
       0100  _LCD_STR
       0110  _LCD_pos
       0120  _LCD_Clear
       0124  _LCD_Init
       0139  _Cursor_Home
       013D  _Cursor_shift
       014E  _LCD_OnOFF
       0152  _Init_Lcd
       016F  _main
       017F  _Interrupt_init
       0186  _Init_timer0
       018C  _timer0_comp_isr
       0214  _ext_int0_isr
       0265  _ext_int1_isr
       02BC  _ext_int2_isr
       030C  _delay_ms
       0323  _delay_us
       033A  <LIBRARY>
       033A  empy16s
       034A  push_xgsetF000
       034F  pop_xgsetF000
       0354  push_xgsetF00C
       035B  pop_xgsetF00C
       0362  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  _cnt
       0100  __data_start
       0102  _SPEED_SECOND
       0103  _SECOND
       0104  _MINUTE
       0105  _TIME
       010B  _TMP
       010D  _DOT
       010F  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0040 =     64. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.objs\lcd.o	[ lcd.c ]
.objs\main.o	[ main.c ]
.objs\my128.o	[ my128.c ]
<library>	[ emul16s.s, gpushy.s, gpushz.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x1000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
