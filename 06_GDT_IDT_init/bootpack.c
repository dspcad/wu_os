#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

void io_hlt(void);
void io_cli(void);
void io_sti(void);
void io_out8(int port, int data);
int  io_load_eflags(void);
void io_store_eflags(int eflags);


//CYLS    EQU   0x0ff0  
//LEDS    EQU   0x0ff1
//VMODE   EQU   0x0ff2 
//SCRNX   EQU   0x0ff4      
//SCRNY   EQU   0x0ff6      
//VRAM    EQU   0x0ff8      
struct BOOTINFO{
    char  cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};


void init_palette(void);
void init_screen(struct BOOTINFO *binfo);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(char *vram, int xsize, unsigned char color, int x0, int y0, int x1, int y1);
void putfont8(char *vram, int xsize, int x, int y, char color, char *font, char c);



static unsigned char table_rgb[16*3]={
                                      0x00, 0x00, 0x00,        //0:  black
                                      0xff, 0x00, 0x00,        //1:  bright red
                                      0x00, 0xff, 0x00,        //2:  bright green
                                      0xff, 0xff, 0x00,        //3:  bright yellow
                                      0x00, 0x00, 0xff,        //4:  bright blue
                                      0xff, 0x00, 0xff,        //5:  bright purple
                                      0x00, 0xff, 0xff,        //6:  light bright blue
                                      0xff, 0xff, 0xff,        //7:  white
                                      0xc6, 0xc6, 0xc6,        //8:  bright grey
                                      0x84, 0x00, 0x00,        //9:  dark red
                                      0x00, 0x84, 0x00,        //10: dark green
                                      0x84, 0x84, 0x00,        //11: dark yellow
                                      0x00, 0x00, 0x84,        //12: dark green
                                      0x84, 0x00, 0x84,        //13: dark purple
                                      0x00, 0x84, 0x84,        //14: light dark green
                                      0x84, 0x84, 0x84         //15: dark grey
};

/*
       A

0 0 0 0 0 0 0 0       0x00
0 0 0 1 1 0 0 0       0x18
0 0 0 1 1 0 0 0       0x18
0 0 0 1 1 0 0 0       0x18
0 0 0 1 1 0 0 0       0x18
0 0 1 0 0 1 0 0       0x24
0 0 1 0 0 1 0 0       0x24
0 0 1 0 0 1 0 0       0x24
0 0 1 0 0 1 0 0       0x24
0 1 1 1 1 1 1 0       0x7e
0 1 0 0 0 0 1 0       0x42
0 1 0 0 0 0 1 0       0x42
0 1 0 0 0 0 1 0       0x42
1 1 1 0 0 1 1 1       0xe7
0 0 0 0 0 0 0 0       0x00
0 0 0 0 0 0 0 0       0x00

               16x8
               a row is represented by a byte
*/



static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
	};



int main(void) {
    struct BOOTINFO *binfo = (struct BOOTINFO *)0x0ff0;
    extern char hhwu[4096];
    init_palette();
    init_screen(binfo);
   
    //putfont8(binfo->vram, binfo->scrnx, 100, 100, COL8_FFFFFF, font_A);

    putfont8(binfo->vram, binfo->scrnx,   8, 8, COL8_FFFFFF, hhwu, 'h'); //a character is represetned by 16 bytes
    putfont8(binfo->vram, binfo->scrnx,  16, 8, COL8_FFFFFF, hhwu, 'h'); 
    putfont8(binfo->vram, binfo->scrnx,  24, 8, COL8_FFFFFF, hhwu, 'w'); 
    putfont8(binfo->vram, binfo->scrnx,  32, 8, COL8_FFFFFF, hhwu, 'u'); 
    putfont8(binfo->vram, binfo->scrnx,  48, 8, COL8_FFFFFF, hhwu, 'l'); 
    putfont8(binfo->vram, binfo->scrnx,  56, 8, COL8_FFFFFF, hhwu, 'o');
    putfont8(binfo->vram, binfo->scrnx,  64, 8, COL8_FFFFFF, hhwu, 'v');
    putfont8(binfo->vram, binfo->scrnx,  72, 8, COL8_FFFFFF, hhwu, 'e');
    putfont8(binfo->vram, binfo->scrnx,  80, 8, COL8_FFFFFF, hhwu, 's');
    putfont8(binfo->vram, binfo->scrnx,  96, 8, COL8_FFFFFF, hhwu, 'A');
    putfont8(binfo->vram, binfo->scrnx, 104, 8, COL8_FFFFFF, hhwu, 'n');
    putfont8(binfo->vram, binfo->scrnx, 112, 8, COL8_FFFFFF, hhwu, 'n');
    putfont8(binfo->vram, binfo->scrnx, 120, 8, COL8_FFFFFF, hhwu, 'a');

    //int d1 = 'A'*16;
    //putfont8(binfo->vram, binfo->scrnx, 40, 48, COL8_FFFFFF, hhwu + d1);
 
    for(;;){
        io_hlt();
    }
}


void init_palette(void){
    set_palette(0,15,table_rgb);
    return;
}

void init_screen(struct BOOTINFO *binfo){
    boxfill8(binfo->vram, binfo->scrnx, COL8_008484,               0,               0, binfo->scrnx- 1, binfo->scrny-29);
    boxfill8(binfo->vram, binfo->scrnx, COL8_C6C6C6,               0, binfo->scrny-28, binfo->scrnx- 1, binfo->scrny-28);
    boxfill8(binfo->vram, binfo->scrnx, COL8_FFFFFF,               0, binfo->scrny-27, binfo->scrnx- 1, binfo->scrny-27);
    boxfill8(binfo->vram, binfo->scrnx, COL8_C6C6C6,               0, binfo->scrny-26, binfo->scrnx- 1, binfo->scrny- 1);

    boxfill8(binfo->vram, binfo->scrnx, COL8_FFFFFF,               3, binfo->scrny-24,              59, binfo->scrny-24);
    boxfill8(binfo->vram, binfo->scrnx, COL8_FFFFFF,               2, binfo->scrny-24,               2, binfo->scrny- 4);
    boxfill8(binfo->vram, binfo->scrnx, COL8_848484,               3, binfo->scrny- 4,              59, binfo->scrny- 4);
    boxfill8(binfo->vram, binfo->scrnx, COL8_848484,              59, binfo->scrny-23,              59, binfo->scrny- 5);
    boxfill8(binfo->vram, binfo->scrnx, COL8_000000,               2, binfo->scrny- 3,              59, binfo->scrny- 3);
    boxfill8(binfo->vram, binfo->scrnx, COL8_000000,              60, binfo->scrny-24,              60, binfo->scrny- 3);

    boxfill8(binfo->vram, binfo->scrnx, COL8_848484, binfo->scrnx-47, binfo->scrny-24, binfo->scrnx- 4, binfo->scrny-24);
    boxfill8(binfo->vram, binfo->scrnx, COL8_848484, binfo->scrnx-47, binfo->scrny-23, binfo->scrnx-47, binfo->scrny- 4);
    boxfill8(binfo->vram, binfo->scrnx, COL8_FFFFFF, binfo->scrnx-47, binfo->scrny- 3, binfo->scrnx- 4, binfo->scrny- 3);
    boxfill8(binfo->vram, binfo->scrnx, COL8_FFFFFF, binfo->scrnx- 3, binfo->scrny-24, binfo->scrnx- 3, binfo->scrny- 3);
}

void set_palette(int start, int end, unsigned char *rgb){
    int eflags = io_load_eflags();

    io_cli();
    io_out8(0x03c8, start);
    for(int i=start;i<=end;++i){
        io_out8(0x03c9, rgb[0]/4);
        io_out8(0x03c9, rgb[1]/4);
        io_out8(0x03c9, rgb[2]/4);
        rgb+=3;
    }

    io_sti();
    io_store_eflags(eflags);
    return;
}

void boxfill8(char *        vram,
              int           xsize, 
              unsigned char color,
              int           x0,
              int           y0,
              int           x1,
              int           y1)
{

    for(int y=y0;y<=y1;++y){
        for(int x=x0;x<=x1;++x){
            vram[x+y*xsize]=color;
        }
    }

}

void putfont8(char *vram, int xsize, int x, int y, char color, char *font, char c)
{
    int idx = c*16; 
    char *p, d /* data */;
    for (int i = 0; i < 16; i++) {
        p = vram + (y + i) * xsize + x;
        d = font[idx+i];
        if ((d & 0x80) != 0) { p[0] = color; }// d AND 1000 0000
        if ((d & 0x40) != 0) { p[1] = color; }// d AND 0100 0000
        if ((d & 0x20) != 0) { p[2] = color; }// d AND 0010 0000
        if ((d & 0x10) != 0) { p[3] = color; }// d AND 0001 0000
        if ((d & 0x08) != 0) { p[4] = color; }// d AND 0000 1000
        if ((d & 0x04) != 0) { p[5] = color; }// d AND 0000 0100
        if ((d & 0x02) != 0) { p[6] = color; }// d AND 0000 0010
        if ((d & 0x01) != 0) { p[7] = color; }// d AND 0000 0001
    }

    return;
}
