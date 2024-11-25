uartlib
=======

```
data register = UART[x]DR | UDR[x]
Receive Status Register =  UART[x]RSR | UCSR[x]B (RXCn
Error Clear Register =  UART[x]ECR | UCSR[x]A (: Frame error (FEn), data overrun (DORn) and parity error (UPEn))
Flag Register = UART[x]FR
interrupt =  | RXCIEn


UARTIBRD UARTFBRD | UBRR0L
```
### Reference
-  [UART Device - RT-Thread document center](https://www.rt-thread.io/document/site/programming-manual/device/uart/uart/)

### AVR
- [Arduino uart AVR-GCC](https://gist.github.com/Bouni/b96ce85f16d9863392ab)

### ARM
- [PrimeCell UART (PL011) Technical Reference Manual r1p5](https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers?lang=en)
- [QEMU AArch64 Virt Bare Bones - OSDev Wiki](https://wiki.osdev.org/QEMU_AArch64_Virt_Bare_Bones#boot.s)
- [嵌入式应用之UART串口_串口lcr寄存器-CSDN博客](https://blog.csdn.net/m0_62055248/article/details/122474532)
- [LPC2138微控制器之UART - 者旨於陽 - 博客园](https://www.cnblogs.com/justin-y-lin/p/12340711.html)
- [ARM UART Library - | Mbed](https://os.mbed.com/teams/Embedded-System/wiki/ARM-UART-Library)
- [baremetal-arm/src/06_uart/src/uart_pl011.c at master · umanovskis/baremetal-arm](https://github.com/umanovskis/baremetal-arm/blob/master/src/06_uart/src/uart_pl011.c)
- https://github.com/qemu/qemu/blob/0fbc798e4f51d6d2bc05f4965b0eae74ba204471/hw/arm/virt.c#L927
- [ARM UART Library - | Mbed](https://os.mbed.com/teams/Embedded-System/wiki/ARM-UART-Library)
- [Arm7 Lpc2148 Uart0 | Arm7](https://www.electronicwings.com/arm7/lpc2148-uart0)
- [UART in LPC2148 ARM7 Microcontroller](https://binaryupdates.com/uart-in-lpc2148-arm7/)
```c
#ifndef PCLK
#error "Error:Not defined Peripheral CLK;Define PCLK"
#endif

void _set_baud1(unsigned int baud);
void _set_baud0(unsigned int baud);
void UART0_Init (unsigned int baud);
void UART1_Init (unsigned int baud);
void UART0_Write (unsigned char ch);
int UART0_Read (void);
unsigned char UART0_Ready(void);
void UART1_Write (unsigned char ch);
int UART1_Read (void);
unsigned char UART1_Ready(void);
void UART0_Text (unsigned char* source);
void UART1_Text (unsigned char* source); 
unsigned char* UART0_Read_Size (unsigned char *destination,unsigned short size );
unsigned char* UART0_Read_CMD (unsigned char *destination,unsigned short CMD );
unsigned char* UART1_Read_Size (unsigned char *destination,unsigned short size );
unsigned char* UART1_Read_CMD (unsigned char *destination,unsigned short CMD );

void _set_baud0(unsigned int baud)
{
 unsigned char mul_val=1,div_add_val=0,u0_dlm=0,u0_dll;
 //unsigned char Cmul_val=1,Cdiv_add_val=0,Cu0_dlm=0,Cu0_dll;
 unsigned int Cbaud=100,Tbaud;   			//for accuracy tollerence
 while(u0_dlm<255){
 mul_val=1;div_add_val=0;
 while(mul_val<16){
 div_add_val=0;
 while(div_add_val<16){
u0_dll = ((PCLK*1000000) / (16 * baud))*(mul_val/(mul_val+div_add_val))-(256*u0_dlm);
Tbaud =(PCLK*1000000) /( (16 * (256*u0_dlm+u0_dll))*(1+div_add_val/mul_val));
Tbaud=abs(Tbaud-baud);
if(Tbaud<Cbaud){
Cbaud=Tbaud;
U0DLL=u0_dll;
U0DLM=u0_dlm;
U0FDR =0x00;
U0FDR |=div_add_val;
U0FDR |=mul_val<<4;
}
div_add_val++;
}
mul_val++;
}
u0_dlm++;
}
}
void _set_baud1(unsigned int baud)
{
 unsigned char mul_val=1,div_add_val=0,u0_dlm=0,u0_dll;
 
 unsigned int Cbaud=100,Tbaud;   			//for accuracy tollerence
 while(u0_dlm<255){
 while(mul_val<16){
 while(div_add_val<16){
u0_dll = ((PCLK*1000000) / (16 * baud))*(mul_val/(mul_val+div_add_val))-(256*u0_dlm);
Tbaud =(PCLK*1000000) /( (16 * (256*u0_dlm+u0_dll))*(1+div_add_val/mul_val));
Tbaud=abs(Tbaud-baud);
if(Tbaud<Cbaud){
Cbaud=Tbaud;
U1DLL=u0_dll;
U1DLM=u0_dlm;
U1FDR =0x00;
U1FDR |=div_add_val;
U1FDR |=mul_val<<4;
}
div_add_val++;
}
mul_val++;
}
u0_dlm++;
}
}
     
 void UART0_Init (unsigned int baud) {
 unsigned char a,b,c; 
 PINSEL0 &=~(0x0F);
 PINSEL0 |=0x00000005; // Enable RxD0 and TxD0  
 U0LCR    = 0x00000083;   //8 bits, no Parity, 1 Stop bit 
//U0DLL    = 0x000000C3; //9600 Baud Rate @ 30MHz VPB Clock  
 _set_baud0(baud);
 U0LCR    = 0x00000003; 
/*  PINSEL0 = 0x00000005; // Enable RxD0 and TxD0
 U0LCR = 0x00000083; //8 bits, no Parity, 1 Stop bit
U0DLL = 0x000000C3; //9600 Baud Rate @ 30MHz VPB Clock
U0LCR = 0x00000003;	*/

 }
  void UART1_Init (unsigned int baud) {  
 
 PINSEL0 &=~(0x0F<<16);
 PINSEL0 |=0x05<<16; // Enable RxD1 and TxD1           

 U1LCR    = 0x00000083;   //8 bits, no Parity, 1 Stop bit 
//U1DLL    = 0x000000C3; //9600 Baud Rate @ 30MHz VPB Clock  
  _set_baud1(baud);
  U1LCR    = 0x00000003;
 }   
void UART0_Write (unsigned char ch)  {       
               
 while (!(U0LSR & 0x20));
 U0THR = ch; }
      
int UART0_Read (void) {            
  // while (!(U0LSR & 0x01));
   return (U0RBR);
 }
unsigned char UART0_Ready(void)
{
return((U0LSR & 0x01)); 

} 
void UART1_Write (unsigned char ch)  {       
               
 while (!(U1LSR & 0x20));
 U1THR = ch; }
      
int UART1_Read (void) {            
  // while (!(U1LSR & 0x01));
   return (U1RBR);
 }
unsigned char UART1_Ready(void)
{
return((U1LSR & 0x01)); 

}
void UART0_Text (unsigned char* source)  {       
               
 
 while(*source!=0) {
 while (!(U0LSR & 0x20));
 U0THR = *source; 
 source++;
  }
 }
 void UART1_Text (unsigned char* source)  {       
               
 
 while(*source!=0) {
 while (!(U1LSR & 0x20));
 U1THR = *source; 
 source++;	  
  }
 }
unsigned char* UART0_Read_Size (unsigned char *destination,unsigned short size ) {
unsigned char *ret=destination;
unsigned char siz=0;
	while(size>siz) {	            
   while (!(U0LSR & 0x01));
   *destination=U0RBR;
   destination++;
   siz++;
   }
   *destination=0;
   return ret;
 }
unsigned char* UART0_Read_CMD (unsigned char *destination,unsigned short CMD ) {
unsigned char *ret=destination;
	while (!(U0LSR & 0x01));
   *destination=U0RBR;
	while(*destination!=CMD) {	            
   	while (!(U0LSR & 0x01));
	destination++;
   *destination=U0RBR;
   
   }
    destination++;
   *destination=0;
   return ret;
 }
 
unsigned char* UART1_Read_Size (unsigned char *destination,unsigned short size ) {
unsigned char *ret=destination;
	while(size>0) {	            
   while (!(U1LSR & 0x01));
   *destination=U1RBR;
   destination++;
   }
   *destination=0;
   return ret;
 }
unsigned char* UART1_Read_CMD (unsigned char *destination,unsigned short CMD ) {
unsigned char *ret=destination;
	while (!(U1LSR & 0x01));
   *destination=U1RBR;
	while(*destination!=CMD) {	            
   	while (!(U1LSR & 0x01));
	destination++;
   *destination=U1RBR;
   
   }
   destination++;
   *destination=0;
   return ret;
 }
```
```c
/*
 * Project Name:
    Four Bit LCD Library for ARM

 * Copyright:
    (c) G ANAND, Hitech Solutions, 2015.

 * Description:
    LCD Open source Header file provides a library for communication with LCDs  through the 4-bit interface

 */

#define CCLK	60	//System Frequency should mentioned for LCD
#define lcd_port IOPIN1	  //LCD Port
#define lcd_port_direction	IODIR1	 //LCD Direction Port
#include <lpc214x.h>
#include <stdio.h> 
#include "lcd.h"	  //LCD Header Files


char *name1 = "Hitech Solutions";
char *name2 = "JAA EmbeddedPark";

void delay(unsigned int n) ;

void Enable_PLL()
{
PLL0CFG &=~(0x7F);	//For clear 0t06
PLL0CFG |=0x04;		//External OSC 12MHZ so 60/12 =5-1=4
PLL0CFG |=0x01<<5;	//Multipler and divider setup
PLL0CON=0x01;	//Enable PLL
PLL0FEED=0xAA;	//Feed sequence
PLL0FEED=0x55;
while(!(PLL0STAT & 0x0400)); //is locked?
PLL0CON=0x03;	//Connect PLL after PLL is locked
PLL0FEED=0xAA;	//Feed sequence
PLL0FEED=0x55;

}


int main()
{  

Enable_PLL();



 LCD_Config(&lcd_port_direction,&lcd_port,16,18,17,22, 21, 20, 19);	//4bit LCD configuration

 LCD_Cmd(LCD_CLEAR);       // Clear display
 LCD_Cmd(LCD_CURSOR_OFF);  // Turn cursor off

 LCD_Out(1, 1, name1);      // Print text to LCD, 1nd row, 1st column
 LCD_Out(2, 1, name2);      // Print text to LCD, 2nd row, 1st column

 	

 return(0);
}

```
```json
[
    {
        " Offset ": " 0x000 ",
        " Name ": " UARTDR ",
        " Type ": " RW ",
        " Reset ": " 0x--- ",
        " Width ": " 12/8 ",
        " Description ": "Data Register, UARTDR"
    },
    {
        " Offset ": " 0x004 ",
        " Name ": " UARTRSR/ UARTECR ",
        " Type ": " RW ",
        " Reset ": " 0x0 ",
        " Width ": " 4/0 ",
        " Description ": " Receive Status Register&thinsp;/&thinsp;Error Clear Register, UARTRSR/UARTECR"
    },
    {
        " Offset ": " 0x008-0x014 ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": "Reserved"
    },
    {
        " Offset ": " 0x018 ",
        " Name ": " UARTFR ",
        " Type ": " RO ",
        " Reset ": " 0b-10010--- ",
        " Width ": " 9 ",
        " Description ": "Flag Register, UARTFR"
    },
    {
        " Offset ": " 0x01C ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": " Reserved "
    },
    {
        " Offset ": " 0x020 ",
        " Name ": " UARTILPR ",
        " Type ": " RW ",
        " Reset ": " 0x00 ",
        " Width ": " 8 ",
        " Description ": "IrDA Low-Power Counter Register, UARTILPR"
    },
    {
        " Offset ": " 0x024 ",
        " Name ": " UARTIBRD ",
        " Type ": " RW ",
        " Reset ": " 0x0000 ",
        " Width ": " 16 ",
        " Description ": "Integer Baud Rate Register, UARTIBRD"
    },
    {
        " Offset ": " 0x028 ",
        " Name ": " UARTFBRD ",
        " Type ": " RW ",
        " Reset ": " 0x00 ",
        " Width ": " 6 ",
        " Description ": "Fractional Baud Rate Register, UARTFBRD"
    },
    {
        " Offset ": " 0x02C ",
        " Name ": " UARTLCR_H ",
        " Type ": " RW ",
        " Reset ": " 0x00 ",
        " Width ": " 8 ",
        " Description ": "Line Control Register, UARTLCR_H"
    },
    {
        " Offset ": " 0x030 ",
        " Name ": " UARTCR ",
        " Type ": " RW ",
        " Reset ": " 0x0300 ",
        " Width ": " 16 ",
        " Description ": "Control Register, UARTCR"
    },
    {
        " Offset ": " 0x034 ",
        " Name ": " UARTIFLS ",
        " Type ": " RW ",
        " Reset ": " 0x12 ",
        " Width ": " 6 ",
        " Description ": "Interrupt FIFO Level Select Register, UARTIFLS"
    },
    {
        " Offset ": " 0x038 ",
        " Name ": " UARTIMSC ",
        " Type ": " RW ",
        " Reset ": " 0x000 ",
        " Width ": " 11 ",
        " Description ": "Interrupt Mask Set/Clear Register, UARTIMSC"
    },
    {
        " Offset ": " 0x03C ",
        " Name ": " UARTRIS ",
        " Type ": " RO ",
        " Reset ": " 0x00- ",
        " Width ": " 11 ",
        " Description ": "Raw Interrupt Status Register, UARTRIS"
    },
    {
        " Offset ": " 0x040 ",
        " Name ": " UARTMIS ",
        " Type ": " RO ",
        " Reset ": " 0x00- ",
        " Width ": " 11 ",
        " Description ": "Masked Interrupt Status Register, UARTMIS"
    },
    {
        " Offset ": " 0x044 ",
        " Name ": " UARTICR ",
        " Type ": " WO ",
        " Reset ": " - ",
        " Width ": " 11 ",
        " Description ": "Interrupt Clear Register, UARTICR"
    },
    {
        " Offset ": " 0x048 ",
        " Name ": " UARTDMACR ",
        " Type ": " RW ",
        " Reset ": " 0x00 ",
        " Width ": " 3 ",
        " Description ": "DMA Control Register, UARTDMACR"
    },
    {
        " Offset ": " 0x04C-0x07C ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": " Reserved "
    },
    {
        " Offset ": " 0x080-0x08C ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": " Reserved for test purposes "
    },
    {
        " Offset ": " 0x090-0xFCC ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": " Reserved "
    },
    {
        " Offset ": " 0xFD0-0xFDC ",
        " Name ": " - ",
        " Type ": " - ",
        " Reset ": " - ",
        " Width ": " - ",
        " Description ": " Reserved for future ID expansion "
    }
]
```
