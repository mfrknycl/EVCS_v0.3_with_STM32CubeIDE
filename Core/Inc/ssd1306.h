#ifndef __SSD1306_H__
#define __SSD1306_H__


/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stm32f0xx_hal.h"
#include "ssd1306_fonts.h"

extern I2C_HandleTypeDef hi2c1;
/* Variables ------------------------------------------------------------------*/





/* Private define ------------------------------------------------------------*/
#define SSD1306_I2C_PORT		  hi2c1
#define SSD1306_I2C_ADDR     (0x3C << 1)
#define SSD1306_HEIGHT        32
#define SSD1306_WIDTH         128


// some LEDs don't display anything in first two columns
// #define SSD1306_WIDTH           130


/* Typedef ------------------------------------------------------------------*/
// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1306_t;


/* Function Decleration ------------------------------------------------------------------*/
// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_WriteInteger(int num, FontDef Font, SSD1306_COLOR color);
void ssd1306_WriteFloat(float num, FontDef Font, SSD1306_COLOR color);

void ssd1306_SetCursor(uint8_t x, uint8_t y);
void testdrawbitmap(void) ;

// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size);



#endif // __SSD1306_H__
