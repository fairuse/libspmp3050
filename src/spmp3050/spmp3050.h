#include <stdint.h>

#define	IO_BASE					((volatile void*)0x10000000)

//--- UART ---//
#define UART_BASE				(IO_BASE + 0x1800)
#define	UART(n)					(UART_BASE + (n << 5))
#define UART_FIFO(n)			(*(volatile uint8_t*)(UART(n) + 0x02))
#define UART_STATUS(n)			(*(volatile uint8_t*)(UART(n) + 0x0A))
#define UART_ENABLE(n)			(*(volatile uint8_t*)(UART_BASE + 0x80)) |= (1 << n)
#define UART_DISABLE(n)			(*(volatile uint8_t*)(UART_BASE + 0x80)) &= ~(1 << n)

#define UART_TX_BUSY			0x02
#define UART_RX_VALID			0x04

//--- GPIO ---//
#define DEV_ENABLE				(*(volatile uint8_t*)(IO_BASE + 0x1100))
#define DEV_ENABLE_OUT			(*(volatile uint8_t*)(IO_BASE + 0x1108))	// For lack of a better term...

#define GPIO_BASE				(IO_BASE + 0xB000)
#define GPIO_A					(GPIO_BASE + 0x60)
#define GPIO_A_DIR				(*(volatile uint32_t*)(GPIO_A + 0x4))
#define GPIO_A_OUT				(*(volatile uint32_t*)(GPIO_A + 0x8))
#define GPIO_A_IN				(*(volatile uint32_t*)(GPIO_A + 0xC))

#define GPIO_B					(GPIO_BASE + 0xE0)
#define GPIO_B_DIR				(*(volatile uint32_t*)(GPIO_B + 0x4))
#define GPIO_B_OUT				(*(volatile uint32_t*)(GPIO_B + 0x8))
#define GPIO_B_IN				(*(volatile uint32_t*)(GPIO_B + 0xC))

#define GPIO_DISABLE			(*(volatile uint32_t*)(GPIO_BASE + 0x320))

//--- LCD ---//
#define LCD_HEIGHT				320
#define LCD_WIDTH				240
#define LCD_BPP					16

#define LCD_BASE				(IO_BASE + 0xA000)
#define LCD_DATA				(*(volatile uint16_t*)(LCD_BASE + 0x196))
#define LCD_DATA_EXT			(*(volatile uint8_t*)(LCD_BASE + 0xE4))		/* Useless, should be for an 18 bit bus, but we only have 16 */
#define LCD_CTRL				(*(volatile uint8_t*)(LCD_BASE + 0x195))
#define	LCD_nRS					0x04
#define LCD_CS					0x20
#define LCD_WR					0x40

#define LCD_DATA_DIR			(*(volatile uint8_t*)(LCD_BASE + 0x192))
#define LCD_OUT					0x20

#define LCD_RESET_REG			(*(volatile uint8_t*)(LCD_BASE + 0x1B1))
#define LCD_RESET				0x80

#define LCD_GFX_ENABLE			(*(volatile uint8_t*)(LCD_BASE + 0x0F))

#define LCD_FB_HEIGHT			(*(volatile uint16_t*)(LCD_BASE + 0x1A0))
#define LCD_FB_WIDTH			(*(volatile uint16_t*)(LCD_BASE + 0x1A2))
#define LCD_FB_UNK				(*(volatile uint16_t*)(LCD_BASE + 0x19E))

//--- Timers ---//
#define TIMER_PERIOD(n)			(*(volatile uint16_t*)(IO_BASE + 0x1318 + (n << 1)))
#define TIMER_ENABLE			(*(volatile uint8_t*)(IO_BASE + 0x1044))
#define TIMER_COUNTER(n)		(*(volatile uint32_t*)(IO_BASE + 0x1030 + (n << 2)))
#define TIMER_FLAGS(n)			(*(volatile uint8_t*)(IO_BASE + 0x1040 + n))

#define TIMER_REPEAT			0x10

//--- IRQ ---//
#define IRQ_FLAG_LO				(*(volatile uint32_t*)(IO_BASE + 0x10C0))
#define IRQ_FLAG_HI				(*(volatile uint32_t*)(IO_BASE + 0x10C4))

#define IRQ_MASK_LO				(*(volatile uint32_t*)(IO_BASE + 0x1310))
#define IRQ_MASK_HI				(*(volatile uint32_t*)(IO_BASE + 0x1314))

#define IRQ_ENABLE_LO			(*(volatile uint32_t*)(IO_BASE + 0x10D0))
#define IRQ_ENABLE_HI			(*(volatile uint32_t*)(IO_BASE + 0x10D4))

//--- Graphics ---//
#define GFX_BASE				(IO_BASE + 0x7000)
#define GFX_BLIT				(*(volatile uint8_t*)(GFX_BASE + 0x2F))
#define GFX_FB_START			(*(volatile uint32_t*)(GFX_BASE + 0x130))
#define GFX_FB_END				(*(volatile uint32_t*)(GFX_BASE + 0x134))
#define GFX_FB_HORIZ			(*(volatile uint16_t*)(GFX_BASE + 0x138))
#define GFX_FB_VERT				(*(volatile uint16_t*)(GFX_BASE + 0x13A))

//--- NAND ---//
#define NAND_BASE				(IO_BASE + 0x4000)
#define NAND_DATA				(*(volatile uint8_t*)(NAND_BASE + 0x20))

#define NAND_CTRL_LO			(*(volatile uint8_t*)(NAND_BASE + 0x22))
#define NAND_CTRL_RE			0x2

#define NAND_CTRL_HI			(*(volatile uint8_t*)(NAND_BASE + 0x23))
#define NAND_CTRL_CLE			0x8
#define NAND_CTRL_ALE			0x4

#define NAND_STATUS				(*(volatile uint8_t*)(NAND_BASE + 0x104))
#define NAND_STATUS_READ_BUSY	0x08

#define NAND_STATUS2			(*(volatile uint8_t*)(NAND_BASE + 0x24))
#define NAND_STATUS_CMD_BUSY	0x01