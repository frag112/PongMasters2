#include "inputs.h"
#include "display.h"
#include "players.h"
#include <libapi.h>
#include <libgs.h>
#include <limits.h>
#include "font1.h"
#include "font2.h"

char selectedID = 1;
// add fonts, music
unsigned long __ramsize = 0x00200000;
unsigned long __stacksize = 0x00004000;

GsSPRITE images[2];
extern unsigned char font1[], font2[];

long int font1_addr;
// To keep a copy of the TIM coordinates for later
int tim_mode;
RECT tim_prect,tim_crect;


void Intro(){
    // title screen
    // add name and button text
    // start 15, reset -40
    switch (selectedID) {
        case 1:
            DrawButtonSelected(15);
            DrawButtonIdle(-40);
            break;
        case 2:
            DrawButtonIdle(15);
            DrawButtonSelected(-40);
            break;
    }

    switch(theControllers[0].button1){
        case 0xEF:       // Up    
            selectedID = 1;
            break;
        case 0xBF: // Down
            selectedID = 2;
            break;
        }
    switch(theControllers[0].button2){
        case 0xDF:                      // ⭘
                break;
        case 0xBF:                      // ╳
                //PADR->y0 = CENTERY + 16;
            (selectedID == 1) ?  Game = 1 :  ResetScore();
            break;
        }
    if(theControllers[0].button1 == 0xF7){
            Game = 1;       
    }
}

void LoadTexture(u_long *tim, TIM_IMAGE *tparam) {

    // Read TIM information 
    OpenTIM(tim);
    ReadTIM(tparam);

    // Upload pixel data to framebuffer
    LoadImage(tparam->prect, (u_long*)tparam->paddr);
    DrawSync(0);

    // Upload CLUT to framebuffer if present
    if( tparam->mode & 0x8 ) {

        LoadImage(tparam->crect, (u_long*)tparam->caddr);
        DrawSync(0);

    }

}

void LoadStuff(void) {

    // This can be defined locally, if you don't need the TIM coordinates
    TIM_IMAGE my_image;

    // Load the TIM
    LoadTexture((u_long*)tim_my_image, &my_image);
    
    // Copy the TIM coordinates
    tim_prect   = *my_image.prect;
    tim_crect   = *my_image.crect;
    tim_mode    = my_image.mode;
    
}

int main(void)
{                  
    init();
    InitPAD(controllers[0].pad, 34, controllers[1].pad, 34);
    StartPAD();

    theControllers[0].ypos = CENTERY - 32;
    theControllers[1].ypos = CENTERY - 32;


    getTPage(2, 1, 520, 4);
    u_long ass = 1;
    OpenTIM(0);
    ReadTIM(font1);

    while (1)
    {
        read_controller( &theControllers[0], &controllers[0].pad[0], 0 );  // Read controllers
        read_controller( &theControllers[1], &controllers[1].pad[0], 1 );
        ClearOTagR(ot[db], OTLEN);
    
    if(Game==1){
        PlayerBoundaryCheck (0);
        PlayerBoundaryCheck (1);

        DrawPlayer(PLAYER1, 1);
        if (p2connected == 0) P2AI();
        DrawPlayer(PLAYER2, 2);
        DrawPlayer(Ball, 3);
        DrawBorder();
        MoveBall();

        CheckWalls();
        ChangeDifficulty();
        FntOpen(MARGINX, MARGINY, 72, FONTSIZE, 2, 15); // p1 score
        SetDumpFnt(1);
        FntPrint("\n Player1\n");
        FntPrint(" %d ", Player1Score);
        FntFlush(1);

        FntOpen(CENTERX+174, MARGINY, 72, FONTSIZE, 2, 16); // p1 score
        SetDumpFnt(2);
        switch(p2connected){
            case 0:
                FntPrint("\n Start\n");
                break;
            case 1:
                FntPrint("\n Player2\n");
                break;
        }
        FntPrint(" %d ", Player2Score);
        FntFlush(2);
    }else{ // intro
        Intro();
    }
    if(theControllers[0].button1 == 0xF7){
        Game = 0;
    }

        // /\, X, O, [] 
       /* PADR = (TILE *)nextpri;
        setTile(PADR);
        setRGB0(PADR, 0, 255, 0);        
        setXY0(PADR, CENTERX + 50, CENTERY);
        setWH(PADR, 24, 24);
        addPrim(ot[db], PADR);
        nextpri += sizeof(TILE);*/
        // START + SELECT
        /*START = (TILE *)nextpri;
        setTile(START);
        setRGB0(START, 240, 240, 240);        
        setXY0(START, CENTERX - 16, CENTERY - 36);
        setWH(START, 24, 24);
        addPrim(ot[db], START);
        nextpri += sizeof(TILE);*/
     /*
        switch(theControllers[1].button1){
            // Start & Select
            case 0xF7:
                //START->w = 32; START->h = 32;START->x0 -= 4;START->y0 -= 4; // START
                p2connected = 1;
                ResetScore();
                theControllers[1].ypos = P2Y;
                break;
            case 0xFE:                                                      // SELECT
                // START->r0 = 0;
                break;
        }

        

        
        /*
        FntOpen(MARGINX+40, SCREENYRES - MARGINY - FONTSIZE, SCREENXRES - MARGINX * 2, FONTSIZE, 0, 280 );
        SetDumpFnt(3);
        FntPrint( "Pad 1 : %02x\nButtons:%02x %02x, Stick:%02x %02x %02x %02x\n",
                    theControllers[0].type,             // Controller type : 00 == none,  41 == standard, 73 == analog/dualshock, 12 == mouse, 23 == steering wheel, 63 == gun, 53 == analog joystick
                    theControllers[0].button1,          // 
                    theControllers[0].button2,
                    theControllers[0].analog0,
                    theControllers[0].analog1,
                    theControllers[0].analog2,
                    theControllers[0].analog3 );
       /* FntPrint( "Pad 2 : %02x\nButtons:%02x %02x, Stick:%02x %02x %02x %02x\n",
                    theControllers[1].type,             // 
                    theControllers[1].button1,          // 
                    theControllers[1].button2,
                    theControllers[1].analog0,          // R3 horizontal
                    theControllers[1].analog1,          // R3 vertical
                    theControllers[1].analog2,          // L3 horizontal
                    theControllers[1].analog3 );        // L3 vertical */
        //FntFlush(3); 
        display();
        }
    return 0;
    }