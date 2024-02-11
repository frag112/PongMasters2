#pragma once

#include <libetc.h>
#include <libgpu.h>
#include <libgs.h>

#define VMODE 1                  // Video Mode : 0 : NTSC, 1: PAL
#define SCREENXRES 512//320
#define SCREENYRES 240
#define CENTERX SCREENXRES/2
#define CENTERY SCREENYRES/2
#define MARGINX 10               // margins for text display
#define MARGINY 10
#define FONTSIZE 30           // Text Field Height
#define OTLEN 8    // Ordering Table Length 

#define PACKETMAX 300


#define __ramsize   0x00200000
#define __stacksize 0x00004000
extern PACKET GPUOutputPacket[2][PACKETMAX];

extern DISPENV disp[2];                 // Double buffered DISPENV and DRAWENV
extern DRAWENV draw[2];

extern GsOT WorldOrderingTable[2]; // ordering table handlers

extern u_long ot[2][OTLEN];             // double ordering table of length 8 * 32 = 256 bits / 32 bytes
extern char primbuff[2][32768];   // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes
extern char *nextpri;     // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]
extern short db;     // index of which buffer is used, values 0, 1     

extern int tim_mode;           // TIM image parameters
extern RECT tim_prect,tim_crect;
extern int tim_uoffs,tim_voffs;
extern short currentBuffer;

typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	SPRT sprite;
} Image;

void init(void);
void display(void);

Image createImage(unsigned char imagedata[]);

