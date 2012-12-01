#include "sys_data.h"
#include<iostream>
#pragma once
using namespace std;
const int N=40;//��ͼ�����귶Χ1-N
const int M=40;//��ͼ�����귶Χ1-M
const int MAX_PLAYER=40;//������������ID��1-MAX_PLAYER
const int MAX_FOOD=50;//ˢ��ʳ������
const int FOOD_ROUND=5;//ˢ��ʳ��غ���
const int EMPTY=0;//����Ϊ��
const int FOOD=-1;//ʳ��
const int LEVEL_POINT=3;//�����ܻ�õĵ���

class fish{
private:
	int myID;
    void setID(int x) {myID=x;}//����ID��ֻ�ɱ�����һ��

public:
    bool move(int x,int y){return sys::move(x,y,myID);}//�ƶ���ĳ��λ��
    bool attack(int x,int y){return sys::attack(x,y,myID);}//����ĳ��λ��
    int getPoint(){return sys::Point[myID];}//���ص�ǰ���ʣ�����
    int getLevel(){return sys::Level[myID];}//���ص�ǰ��ҵȼ�
    int getExp(){return sys::Level[myID];}//���ص�ǰ��Ҿ���
    int getX(){return sys::Location[myID][0];}//���ص�ǰ��Һ�����
    int getY(){return sys::Location[myID][1];}//���ص�ǰ���������
    int getHP(){return sys::HP[myID];}//���ص�ǰ�������ֵ
    int getMaxHP(){return sys::MaxHP[myID];}//���ص�ǰ�����������
    int getAtt(){return sys::Strength[myID];}//���ص�ǰ��ҹ�����
    int getSp(){return sys::Speed[myID];}//���ص�ǰ����ٶ�
    int getID(){return myID;}//��ȡ���ID
    int askWhat(int x,int y)
	{
		if (x<=0 || y<=0 || x>=N || y>=M) return 0;
		int ans;
		ans=sys::System_Map[x][y];
		return ans;
	}//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��
    int askHP(int x)
	{
		if (x<=0 || x>=sys::Sum_Player) return 0;
		return sys::HP[x];
	}//ѯ��ĳ�����ID��ǰѪ��
	void inputID(int x) {setID(x);}
    bool increaseHealth(){return sys::increaseHealth(myID);}//����health����1
    bool increaseStrength(){return sys::increaseStrength(myID);}//����Strength����1
    bool increaseSpeed(){return sys::increaseSpeed(myID);}//����Speed����1

    virtual void init()=0;//��ʼ��������ÿһ�����¿�ʼ������
    virtual void play()=0;//�ж�������ÿ�غ��ж�������
    virtual void revive(int&,int&)=0;//����ʱ���ã���������ѡ�񸴻�λ�ã������Ϸ��������
};
