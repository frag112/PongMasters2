#include <stdlib.h>
#include "display.h"
#include "inputs.h"
#include "players.h"

short BallX = CENTERX -8, BallY = CENTERY - 8, dX = 1, dY = 1;
short P1Y, P2Y;
int Player1Score=0, Player2Score=0;

char Game=0;

TILE * PLAYER1;
TILE * PLAYER2;
TILE * Ball;

void DrawPlayer(TILE * player, short playerNum){
        player = (TILE *)nextpri;
        setTile(player);
        setRGB0(player, 0, 255, 0);  
                switch(playerNum){
                    case 1:
                        setXY0(player,26, theControllers[0].ypos);
                        setWH(player, PWidth, PHeight);
                        P1Y = player->y0;
                        break;
                    case 2:
                        setXY0(player,SCREENXRES-26-PWidth, theControllers[1].ypos);
                        setWH(player, PWidth, PHeight);
                        P2Y = player->y0;
                        break;
                    case 3:
                        setXY0(player, BallX, BallY);
                        setWH(player, 16, 16);
                        break;
                }


        addPrim(ot[db], player);
        nextpri += sizeof(TILE);
}

void DrawBorder(){
         TILE * box1 = (TILE *)nextpri;
        setTile(box1);
        setRGB0(box1, 0, 153, 0);        
        setXY0(box1, CENTERX - 4, 12);
        setWH(box1, 8, 24);
        addPrim(ot[db], box1);
        nextpri += sizeof(TILE);

        TILE * box2 = (TILE *)nextpri;
        setTile(box2);
        setRGB0(box2, 0, 153, 0);        
        setXY0(box2, CENTERX - 4, 60);
        setWH(box2, 8, 24);
        addPrim(ot[db], box2);
        nextpri += sizeof(TILE);

        TILE * box3 = (TILE *)nextpri;
        setTile(box3);
        setRGB0(box3, 0, 153, 0);        
        setXY0(box3, CENTERX - 4, 108);
        setWH(box3, 8, 24);
        addPrim(ot[db], box3);
        nextpri += sizeof(TILE);

        TILE * box4 = (TILE *)nextpri;
        setTile(box4);
        setRGB0(box4, 0, 153, 0);        
        setXY0(box4, CENTERX - 4, 156);
        setWH(box4, 8, 24);
        addPrim(ot[db], box4);
        nextpri += sizeof(TILE);

        TILE * box5 = (TILE *)nextpri;
        setTile(box5);
        setRGB0(box5, 0, 153, 0);        
        setXY0(box5, CENTERX - 4, 204);
        setWH(box5, 8, 24);
        addPrim(ot[db], box5);
        nextpri += sizeof(TILE);
}

void MoveBall(){
	BallX = BallX + dX;
	BallY = BallY + dY;
}
void ResetBall(){
    BallX = CENTERX -8;
	BallY = CENTERY -8;
    // randomize direction
   char randomNum = rand() % 2;
   switch (randomNum){
    case 0:
        dX = -1;
        break;
    case 1:
        dX = 1;
        break;
   }
   randomNum = rand() % 2;
   switch (randomNum){
    case 0:
        dY = -1;
        break;
    case 1:
        dY = 1;
        break;
   }
}

void CheckWalls(){
    if (BallY <= 2 || (BallY+16) >= SCREENYRES-2){ //check floor and ceiling
        dY = dY * (-1);
    }
    if (BallX <= (-18)){ 
        Player2Score++;
        ResetBall();
    }
    if (BallX >=(SCREENXRES+2)){ 
        Player1Score++;
        ResetBall();
    }

    if (BallX == (26+PWidth)){ //contact p1
        if((BallY+16)>=P1Y && BallY <=(P1Y+PHeight))
        dX = dX * (-1);
    }
    if ((BallX+16) == (SCREENXRES-26-PWidth)){ //contact p2
        if((BallY+16)>=P2Y && BallY <=(P2Y+PHeight))
        dX = dX * (-1);
    }

}

void ResetScore(){
    Player1Score = 0;
    Player2Score = 0;
}

