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

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(char *vram, int xsize, unsigned char color, int x0, int y0, int x1, int y1);



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


int main(void) {
    struct BOOTINFO *binfo = (struct BOOTINFO *)0x0ff0;
    init_palette();
 
    
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



    for(;;){
        io_hlt();
    }
}


void init_palette(void){
    set_palette(0,15,table_rgb);
    return;
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
