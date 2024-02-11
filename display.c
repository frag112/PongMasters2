#include "display.h"


DISPENV disp[2];                 // Double buffered DISPENV and DRAWENV
DRAWENV draw[2];
GsOT WorldOrderingTable[2];
PACKET GPUOutputPacket[2][PACKETMAX];
short currentBuffer;
u_long ot[2][OTLEN];             // double ordering table of length 8 * 32 = 256 bits / 32 bytes
char primbuff[2][32768];   // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes
char *nextpri = primbuff[0];     // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]
short db = 0;     // index of which buffer is used, values 0, 1 
      


void init(void)
{
    ResetGraph(0);
    SetDefDispEnv(&disp[0], 0, 0, SCREENXRES, SCREENYRES);
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[1], 0, 0, SCREENXRES, SCREENYRES);
    if (VMODE)
    {
        SetVideoMode(MODE_PAL);
        disp[0].screen.y += 8;
        disp[1].screen.y += 8;
        }
    SetDispMask(1);                 // Display on screen    
    setRGB0(&draw[0], 0, 92, 0);// bg color
    setRGB0(&draw[1], 0, 92, 0);
    draw[0].isbg = 1;
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);

	nextpri = primbuff[0]; 

    PutDrawEnv(&draw[db]);
    FntLoad(960, 0);
    
    FntOpen(MARGINX, MARGINY, 120, FONTSIZE, 0, 15); // p1 score
}
void display(void)
{


    DrawSync(0);
    VSync(0);
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;
    nextpri = primbuff[db];
}

Image createImage(unsigned char imageData[8216]) {

	// Initialize image
	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);

	// Load the image into the frame buffer
	image.rect.x = image.tim_data.px;            	// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;            	// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;            	// data width
	image.rect.h = image.tim_data.ph;            	// data height
	LoadImage(&image.rect, image.tim_data.pixel);
    DrawSync(0);
	// Initialize sprite

	image.sprite.x0 = 0;                         	// draw at x coord
	image.sprite.y0 = 0;                          	// draw at y coord
	image.sprite.w = 64;         	// width of sprite
	image.sprite.h = 64;             // height of sprite


	image.sprite.u0=0;                               // position within timfile for sprite
	image.sprite.v0=0;								// position within timfile for sprite





	return image;

}

