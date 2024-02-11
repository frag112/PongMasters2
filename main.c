#include "inputs.h"
#include "display.h"
#include "players.h"
#include <libapi.h>
#include <libgs.h>
#include "font1.h"
#include "font2.h"

char selectedID = 1;
// change images 
Image ffont, sfont;
extern unsigned char font1[], font2[];

    void clearDisplay() {
	    currentBuffer = GsGetActiveBuff();

	    GsSetWorkBase((PACKET*)GPUOutputPacket[currentBuffer]);
	    GsClearOt(0, 0, &WorldOrderingTable[currentBuffer]);
    }



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

int main(void)
{                  
    init();
    InitPAD(controllers[0].pad, 34, controllers[1].pad, 34);
    StartPAD();

    theControllers[0].ypos = CENTERY - 32;
    theControllers[1].ypos = CENTERY - 32;
        ffont.sprite.x0 = 40;
        ffont.sprite.y0 = 10; 
    ffont = createImage(font1);
    //sfont = createImage(font2);
    SPRT *sprt;  

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
        

    }else{ // intro
        Intro();
    }
    if(theControllers[0].button1 == 0xF7){
        Game = 0;
    }
    FntOpen(MARGINX, MARGINY, 72, FONTSIZE, 2, 15); // p1 score
    SetDumpFnt(1);
    FntPrint("\n Player1\n");
    FntPrint(" %d ", Player1Score);
    FntFlush(1);

    FntOpen(CENTERX+174, MARGINY, 72, FONTSIZE, 2, 16); // p1 score
    SetDumpFnt(2);
    switch(p2connected){
        case 0:
            FntPrint("\n PrssStrt\n");
            break;
        case 1:
            FntPrint("\n Player2\n");
            break;
    }
    FntPrint(" %d ", Player2Score);
    FntFlush(2);
    FntOpen(240, 115, 72, FONTSIZE, 0, 4); 
    SetDumpFnt(3);
    FntPrint("Play");
    FntFlush(3);

    FntOpen(235, 172, 72, FONTSIZE, 0, 7); 
    SetDumpFnt(4);
    FntPrint("Reset");
    FntFlush(4);
    clearDisplay();
    display();
    }
    return 0;
    }   