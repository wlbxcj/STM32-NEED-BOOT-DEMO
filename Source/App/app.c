#include "config.h"

#include "led/led_app.c"
#include "tool/tool.c"
#include "debug/debug.c"
#include "Fatfs/diskio.c"
#include "Fatfs/ff.c"
#if (_USE_LFN && _CODE_PAGE == 936)
#include "Fatfs/option/cc936.c"
#endif
#include "global/global.c"
#include "lcd/lcd_app.c"
