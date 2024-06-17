void io_hlt(void);
void io_cli(void);
void io_sti(void);
void io_out8(int port, int data);
int  io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

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


int main(void) {
    char *p = (char *)0xa0000;
    init_palette();
 
    for(int i=0;i<=0xffff;++i){
        /*
        Have to convert i&0x0f to char first.
        Otherwise, the display would be flickering and stay in the booting screen.
        I guess that i&0x0f in 32 bits mode might be the cause but no idea why.
        Hopefully, I could find it in the future. Now I have to move on ^_^.
        */
        char sel = i&0x0f;
        p[i] = sel;
    }


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
