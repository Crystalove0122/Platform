#include "st08.h"
#include <cstdio>
#include <cstdlib>

void st08::init(){
	int i;
	for (i=1;i<=4;i++) increaseHealth();
	for (i=1;i<=5;i++) increaseSpeed();
	while (getPoint()) increaseStrength();
	dir[0][0]=1;dir[0][1]=0;dir[1][0]=0;dir[1][1]=1;
	dir[2][0]=-1;dir[2][1]=0;dir[3][0]=0;dir[3][1]=-1;
}

void st08::try_again()
{
	int i,j,k;
	int max_value=0,delvalue,delx,dely;
	int min_len=100;
	int assess=5-(Rounds % 5);
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
		if (map[i][j] == FOOD)
		{
			if (abs(i-getX())+abs(j-getY())>assess*mySpeed) continue;
			delvalue=100-4*assess;
			for (k=1;k<=MAX_PLAYER;k++)
			{
				if (k == myID) continue;
				if (abs(last_location[k][0]-i)+abs(last_location[k][1]-j)<=Player_Speed[k])
					delvalue-=2;
			}
			if (delvalue>max_value)
			{
				max_value=delvalue;delx=i;dely=j;
			}
		}
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
			if (abs(i-delx)+abs(j-dely)<min_len && map[i][j] == 0)
			{
				min_len=abs(i-delx)+abs(j-dely);
				maxx=i;maxy=j;
			}
}

void st08::increasePoint()
{
	while(getPoint())
	{
		if (getLevel()<=3)
		{
			increaseSpeed();
			increaseStrength();
			increaseHealth();
		}
		else
		{
			if (mySpeed<=15)
			{
				increaseSpeed();
				if (myAttack*3>=getMaxHP()) increaseHealth();
				else increaseStrength();
				srand(time(NULL));
				increaseHealth();
			}
			else
			{
				if (getLevel() % 4 == 0 && mySpeed<=45)
				{
					for (int i=1;i<=2;i++) increaseSpeed();
					increaseHealth();
				}
				else
				{
					increaseHealth();
					increaseStrength();
					if (mySpeed<=50)
					{
						int i=rand() % 5;
						if (i==0) increaseHealth();
						else if (i==1) increaseStrength();
						else increaseSpeed();
					}
					else
					{
						if (myAttack*3>=getMaxHP()) increaseHealth();
						else increaseStrength();
					}
				}
			}
		}
	}
}

void st08::play()
{
	myID=getID();mySpeed=getSp();myAttack=getAtt();
	Rounds++,SeaBath=0;
	memset(appeal,0,sizeof(appeal));
	memset(value,0,sizeof(value));

	int i,j;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
		{
			map[i][j]=askWhat(i,j);
			if (map[i][j]<0) SeaBath++;
			if (map[i][j]>0)
			{
				int focus=map[i][j];
				appeal[focus]=1;
				if (last_location[focus][0] == 0) continue;
				int delSpeed;
				delSpeed=abs(i-last_location[focus][0])+abs(j-last_location[focus][j]);
				if (delSpeed>Player_Speed[focus]) Player_Speed[focus]=delSpeed;
			}
		}
	for (i=1;i<=MAX_PLAYER;i++)
		if (appeal[i] == 0)
		{
			last_location[i][0]=0;last_location[i][1]=0;
		}
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
			if (map[i][j]>0)
			{
				int focus=map[i][j];
				last_location[focus][0]=i;last_location[focus][1]=j;
			}
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
		{
			int length;
			length=abs(i-getX())+abs(j-getY());
			if (((map[i][j] == 0) || (i==getX() && j==getY())) && (length<=mySpeed))
			{
				int delx,dely;
				for (delx=1;delx<=N;delx++)
					for (dely=1;dely<=M;dely++)
					if (((map[delx][dely]!=0) && (map[delx][dely]!=myID)) && (abs(delx-i)+abs(dely-j)<=mySpeed))
					{
						if (map[delx][dely] == FOOD)
						{
							if (abs(delx-i)+abs(dely-j) == 1) value[i][j]+=200;
							else value[i][j]+=20;
						}
						else
						{
							if (abs(delx-i)+abs(dely-j) == 1)
							{
								if (askHP(map[delx][dely])<=myAttack) value[i][j]+=10*Rounds;
								else if (askHP(map[delx][dely])>myAttack && askHP(map[delx][dely])<=myAttack*2) value[i][j]+=5*Rounds;
								else if (askHP(map[delx][dely])>myAttack*4) value[i][j]-=4*Rounds;
							}
							else
							{
								if (abs(delx-i)+abs(dely-j)<=Player_Speed[map[delx][dely]]) value[i][j]-=150+Rounds;
								else if (askHP(map[delx][dely])<=myAttack) value[i][j]+=2*Rounds;
								else if (askHP(map[delx][dely])<=myAttack*2) value[i][j]+=Rounds;
							}
						}
					}
			}
		}
	max_value=-110000,maxx=getX(),maxy=getY();
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
			if (value[i][j]>max_value)
			{
				max_value=value[i][j];
				maxx=i;maxy=j;
			}
	if (SeaBath!=0 && maxx==getX() && maxy==getY())
		try_again();
	move(maxx,maxy);
	max_value=-110000;
	int k;
	for (k=0;k<=3;k++)
	{
		int delx=getX()+dir[k][0],dely=getY()+dir[k][1],delvalue=0;
		if (delx<=0 || dely<=0 || delx>N || dely>M) continue;
		if (map[delx][dely] == FOOD) delvalue=9;
		else if (map[delx][dely]>0)
		{
			if (askHP(map[delx][dely])<=myAttack) delvalue=askHP(map[delx][dely])*10;
			else if (askHP(map[delx][dely])<=myAttack*2 && Player_Speed[map[delx][dely]]<=mySpeed) delvalue=10;
			else delvalue=2;
		}
		if (delvalue>=max_value)
		{
			max_value=delvalue;
			maxx=delx;maxy=dely;
		}
	}
	attack(maxx,maxy);
	if (getPoint()) increasePoint();
	mySpeed=getSp();myAttack=getAtt();
	return;
}

void st08::revive(int& x,int& y)
{
	Rounds++;
	max_value=-110000;maxx=0;maxy=0;
	int i,j,k;
	for (i=1;i<=N;i++)
		for (j=1;j<=M;j++)
		if (map[i][j] == EMPTY)
		{
			int delvalue=0;
			for (k=1;k<=MAX_PLAYER;k++)
			if (last_location[k][0]!=0 && k != myID)
				if (abs(i-last_location[k][0])+abs(j-last_location[k][1]) <= Player_Speed[k])
					delvalue-=20;
			int deli,delj;
			for (deli=1;deli<=N;deli++)
				for (delj=1;delj<=M;delj++)
				if (map[deli][delj] == FOOD && abs(i-deli)+abs(j-delj)<=mySpeed)
					delvalue+=1;
			if (max_value<delvalue)
			{
				max_value=delvalue;
				maxx=i;maxy=j;
			}
		}
	x=maxx;y=maxy;
}
