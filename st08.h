#include "fish.h"
#include <cstring>
#include <time.h>
#pragma once

class st08:virtual public fish{
	private:
	int map[41][41],Player_Speed[41],last_location[41][2],value[41][41];
	bool appeal[41];
	int SeaBath;
	int dir[4][2];
	int Rounds,relivex,relivey,myID,mySpeed,myAttack;
	int max_value,maxx,maxy;
	void try_again();
	void increasePoint();
	
	public:
    void init();
    void play();
    void revive(int&,int&);

};

//可自行增加所需函数所需函数及变量，但需保证上面每个函数的完整与可调用

//不要使用全局变量！！
