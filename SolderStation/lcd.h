#ifndef _LCD_H
#define _LCD_H

// For boolean type
#include <Arduino.h>

/*
 * Init LCD stuff
 */
void lcd_init();

/*
 * Clear lcd
 */
void lcd_clear();

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable);

/*
 * Set contrast
 */
void lcd_set_contrast(byte contrast);

/*
 * Print heat signal
 */
void lcd_print_heat(boolean show);

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature);

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature);

/*
 * Print title
 */
void lcd_print_title(const char *title);

typedef enum {
  ITEM_NONE,
  ITEM_SELECTED,
  ITEM_EDITION,
} item_state;
/*
 * Print item
 */
void lcd_print_item(byte line, const char *item, const char *value, item_state state);

/*
 * Display on the lcd
 */
void lcd_display();

#endif //_LCD_H

