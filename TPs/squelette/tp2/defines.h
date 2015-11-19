#ifndef DEFINES_H
#define DEFINES

#define SINGLE_REG 0x1

#define MEM_BASE       0x10000000
#define MEM_PDATA_SIZE 10*1024 // 10 Kio
#define MEM_VBUF_BASE  MEM_BASE+MEM_PDATA_SIZE
#define MEM_VBUF_SIZE  320*240 // 1o par pixel
#define MEM_SIZE       0x15400

#define LCDC_ADDR_BASE  0x0
#define LCDC_ADDR_RANGE 0x8
#define LCD_FREQ 1.0 / 25

#define FG_RED     "\033[31m"
#define FG_GREEN   "\033[32m"
#define FG_YELLOW  "\033[33m"
#define FG_DEFAULT "\033[39m"

#endif
