#include "sys_data.h"
#include<iostream>
#pragma once
using namespace std;
const int N=40;//地图横坐标范围1-N
const int M=40;//地图纵坐标范围1-M
const int MAX_PLAYER=40;//最多玩家数量，ID从1-MAX_PLAYER
const int MAX_FOOD=50;//刷新食物数量
const int FOOD_ROUND=5;//刷新食物回合数
const int EMPTY=0;//格子为空
const int FOOD=-1;//食物
const int LEVEL_POINT=3;//升级能获得的点数

class fish{
private:
	int myID;
    void setID(int x) {myID=x;}//设置ID，只可被调用一次

public:
    bool move(int x,int y){return sys::move(x,y,myID);}//移动到某个位置
    bool attack(int x,int y){return sys::attack(x,y,myID);}//攻击某个位置
    int getPoint(){return sys::Point[myID];}//返回当前玩家剩余点数
    int getLevel(){return sys::Level[myID];}//返回当前玩家等级
    int getExp(){return sys::Level[myID];}//返回当前玩家经验
    int getX(){return sys::Location[myID][0];}//返回当前玩家横坐标
    int getY(){return sys::Location[myID][1];}//返回当前玩家纵坐标
    int getHP(){return sys::HP[myID];}//返回当前玩家生命值
    int getMaxHP(){return sys::MaxHP[myID];}//返回当前玩家生命上限
    int getAtt(){return sys::Strength[myID];}//返回当前玩家攻击力
    int getSp(){return sys::Speed[myID];}//返回当前玩家速度
    int getID(){return myID;}//获取玩家ID
    int askWhat(int x,int y)
	{
		if (x<=0 || y<=0 || x>=N || y>=M) return 0;
		int ans;
		ans=sys::System_Map[x][y];
		return ans;
	}//返回地图某个位置内容（玩家ID或FOOD或EMPTY）
    int askHP(int x)
	{
		if (x<=0 || x>=sys::Sum_Player) return 0;
		return sys::HP[x];
	}//询问某个玩家ID当前血量
	void inputID(int x) {setID(x);}
    bool increaseHealth(){return sys::increaseHealth(myID);}//增加health属性1
    bool increaseStrength(){return sys::increaseStrength(myID);}//增加Strength属性1
    bool increaseSpeed(){return sys::increaseSpeed(myID);}//增加Speed属性1

    virtual void init()=0;//初始化函数，每一局重新开始将调用
    virtual void play()=0;//行动函数，每回合行动将调用
    virtual void revive(int&,int&)=0;//复活时调用，参数传回选择复活位置（若不合法则随机）
};
