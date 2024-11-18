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
### ARM
- [PrimeCell UART (PL011) Technical Reference Manual r1p5](https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers?lang=en)
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
