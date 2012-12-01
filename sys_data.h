#include<string.h>
#include<fstream>
#pragma once

namespace sys{
	extern int System_Map[51][51],Dead_Queue[51],Next_Dead_Queue[51];
	extern int Dead_Player,Sum_Player,Map_Len,Next_Dead_Player;
	extern int Location[51][2];
	extern int HP[51],MaxHP[51],Speed[51],Strength[51];
	extern int Level[51],Exp[51],Point[51],Score[51];
	extern bool haveMoved[51],haveAttack[51],haveDead[51];
	extern FILE *Log;
	extern char *action[7];
	extern bool increaseHealth(int x);
	extern bool increaseStrength(int x);
	extern bool increaseSpeed(int x);
	extern int move(int x,int y,int ID);
	extern int attack(int x,int y,int ID);
	extern void init(int x);
	extern void increaseLevel(int x);
	extern void Clear_Dead(int x);
	extern int calc_max(int x,int y);
	extern int calc_min(int x,int y);
};

