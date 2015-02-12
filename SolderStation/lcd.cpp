#include "config.h"
#include "lcd.h"
#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define CS 10
#define DC 9
#define RESET 8
#define BL  2
#define DEGREE_SYM "\xF8"

#define FONT_WIDTH 6
#define FONT_HEIGHT 8

Adafruit_PCD8544 display = Adafruit_PCD8544(DC, CS, RESET);

/*
 * Print a temperature
 */
static void __lcd_print_temperature(int temperature) {
  if(temperature<10) {
    display.print(' ');
  }
  if(temperature<100) {
    display.print(' ');
  }
  display.print(temperature);
  display.print(DEGREE_SYM"C");
}


static void center_for_text(uint16_t y, const char *text, byte size) {
  int len = strlen(text);
  display.setCursor((display.width() - (FONT_WIDTH * size * len))/2, y);
}

static void right_for_text(uint16_t y, const char *text, byte size) {
  int len = strlen(text);
  display.setCursor((display.width() - (FONT_WIDTH * size * len)), y);
}

/*
 * Init LCD stuff
 */
void lcd_init() {
  display.begin();
  display.setContrast(30);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
  // Switch of the Backlight
  digitalWrite(BL, LOW); 
  pinMode(BL, OUTPUT);
}

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable) {
  digitalWrite(BL, enable); 
}

/*
 * Set contrast
 */
void lcd_set_contrast(byte contrast) {
  display.setContrast((byte)(((float)contrast) * 128.0f / 100.0f));
}

/*
 * Clear lcd
 */
void lcd_clear() {
  display.fillScreen(WHITE);
}

/*
 * Print heat signal
 */
void lcd_print_heat(boolean show) {
  display.setTextSize(2);
  display.setCursor(20, 34);
  display.setTextColor(BLACK, WHITE);
  display.print(show? MY_STR("****") : MY_STR("    "));
}

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature) {
  display.setTextSize(2);
  display.setCursor(15, 18);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature) {
  display.setTextSize(1);
  display.setCursor(54, 0);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print title
 */
void lcd_print_title(const char *title) {
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    center_for_text(0, title, 1);
    display.print(title);
    display.drawLine(0, FONT_HEIGHT, display.width(), FONT_HEIGHT, BLACK);
}

/*
 * Print item
 */
void lcd_print_item(byte line, const char *item, const char *value, item_state state) {
    display.setTextSize(1);
    byte y = ((FONT_HEIGHT + 2) * line);
    byte c;
    byte bg;
    if(state == ITEM_SELECTED) {
      c = WHITE;
      bg = BLACK;
    } else {
      c = BLACK;
      bg = WHITE;
    }
    display.fillRect(0, (FONT_HEIGHT + 1) + y, display.width(), FONT_HEIGHT + 2, bg);
    display.setTextColor(c, bg);
    display.setCursor(0, (FONT_HEIGHT + 2) + y);
    display.print(item);
    if(value != NULL) {
      if(state == ITEM_EDITION || state == ITEM_SELECTED) {
         c = WHITE;
         bg = BLACK;
      } else {
         c = BLACK;
        bg = WHITE;
      }
      display.setTextColor(c, bg);
      right_for_text((FONT_HEIGHT + 2) + y, value, 1);
      display.print(value);
    }
}

/*
 * Display on the lcd
 */
void lcd_display() {
    display.display();
}

