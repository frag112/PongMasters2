#pragma once
#include <libgpu.h>
#define PHeight 64
#define PWidth 17

extern short BallX, BallY, dX, dY;
extern int diffTimer;
extern short P1Y, P2Y;
extern int Player1Score, Player2Score;
extern char Game, p2connected, WidthModificator;
extern TILE * PLAYER1;
extern TILE * PLAYER2;
extern TILE * Ball;

void DrawPlayer(TILE * player, short playerNum);

void DrawButtonIdle(char y);

void DrawButtonSelected (char y);

void DrawBorder();

void MoveBall();

void ResetBall();

void CheckWalls();

void ResetScore();

void P2AI();

void ChangeDifficulty();

void  ResetDifficulty();

void PlayerBoundaryCheck (short controllerID);