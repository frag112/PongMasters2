#include "inputs.h"
#include "display.h"
#include "players.h"
#include <libapi.h>


int main(void)
{                  
    TILE * START, * SELECT;

    // players
    TILE * PLAYER1;
    TILE * PLAYER2;
    TILE * Ball;

    init();
    InitPAD(controllers[0].pad, 34, controllers[1].pad, 34);
    StartPAD();

    theControllers[0].ypos = CENTERY - 32;
    theControllers[1].ypos = CENTERY - 32;

    while (1)
    {
        read_controller( &theControllers[0], &controllers[0].pad[0], 0 );  // Read controllers
        read_controller( &theControllers[1], &controllers[1].pad[0], 1 );
        ClearOTagR(ot[db], OTLEN);

        if (theControllers[0].ypos < 2 ){
            theControllers[0].ypos = 2;
        } else if(theControllers[0].ypos > 174){
            theControllers[0].ypos = 174;
        }

        if (theControllers[1].ypos < 2 ){
            theControllers[1].ypos = 2;
        } else if(theControllers[1].ypos > 174){
            theControllers[1].ypos = 174;
        }

        DrawPlayer(PLAYER1, 1);
        DrawPlayer(PLAYER2, 2);
        DrawPlayer(Ball, 3);

        START = (TILE *)nextpri;
        setTile(START);
        setRGB0(START, 0, 153, 0);        
        setXY0(START, 0 , 0);
        setWH(START, 40, 40);
        addPrim(ot[db], START);
        nextpri += sizeof(TILE);
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
        // D-pad
        switch(theControllers[0].button1){
           /* case 0xDF:                      // Right 
                PADL->x0 = CENTERX - 64;
                break;
            case 0x7F:                      // Left  
                PADL->x0 = CENTERX - 96;
                break; */
            case 0xEF:       // Up    
                  
                break;
            case 0xBF: // Down

                break;

            // Start & Select
            case 0xF7:
               // START->w = 32; START->h = 32;START->x0 -= 4;START->y0 -= 4; // START
                break;
            case 0xFE:                                                      // SELECT
                //START->r0 = 0;
                break;
        }
        /*switch(theControllers[1].button1){
            case 0xEF:                      // Up   

                break;
            case 0xBF: // Down  
                  
                break;
            // Start & Select
            case 0xF7:
                START->w = 32; START->h = 32;START->x0 -= 4;START->y0 -= 4; // START
                break;
            case 0xFE:                                                      // SELECT
                // START->r0 = 0;
                break;
        }*/
        // Buttons
        switch(theControllers[0].button2){
            case 0xDF:                      // ⭘
                //PADR->x0 = CENTERX + 66;
                break;
            case 0xBF:                      // ╳
                //PADR->y0 = CENTERY + 16;
                break;
        }
        FntPrint("Working %d pads!\n\n", theControllers[0].ypos);
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
        FntFlush(-1);
        display();
        }
    return 0;
    }