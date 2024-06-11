/* view.h -- #defines for view options
 *
 * D Provine, 17 October 2017
 * 
 * Copyright (C) Darren Provine, 2009-2023, All Rights Reserved
 */

/* VIEW OPTIONS
 *
 * AMPM (default is 24-hour) --+
 * reserved -----------------+ |
 * date -------------------+ | |
 * LED mode--------------+ | | |
 *                       | | | |
 * test -----------+     | | | |
 *                 |     | | | |
 *                 |     | | | |
 *                 V     V V V V
 *           0 0 0 0     0 0 0 0
 */
#define  AMPM_MODE  0x01
#define  DATE_MODE  0x04
#define  LED_MODE   0x08
#define  TEST_MODE  0x10

// set packed bits for what you want
void set_view_properties( int );
int get_view_properties( void );

void show(struct tm *);

