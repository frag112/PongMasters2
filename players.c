#include "display.h"
#include "inputs.h"
#include "players.h"

void DrawPlayer(TILE * player, short playerNum){
        player = (TILE *)nextpri;
        setTile(player);
        setRGB0(player, 0, 255, 0);  // chage color later
                switch(playerNum){
                    case 1:
                        setXY0(player,CENTERX - 230, theControllers[0].ypos);
                        setWH(player, 17, 64);
                        break;
                    case 2:
                        setXY0(player,CENTERX + 230 - 17, theControllers[1].ypos);
                        setWH(player, 17, 64);
                        break;
                    case 3:
                        setXY0(player, CENTERX -8 , CENTERY - 8);
                        setWH(player, 16, 16);
                        break;
                }


        addPrim(ot[db], player);
        nextpri += sizeof(TILE);
}