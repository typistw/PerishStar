#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "FloatWord.h"
#include "TopMenu.h"
#include "StarMatrix.h"

#include "cocos2d.h"
USING_NS_CC;

class StarMatrix;

class GameLayer:public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameLayer);

	//飘出关卡信息
	void floatLevelWord();

	//飘出目标分数
	void floatTargetScoreWord();

	//移除关卡信息和目标分数
	void removeFloatWord();

	//创造星星矩阵(所有的星星)
	void showStarMatrix();

	virtual void update(float dt);//update

	//接受触摸事件
	virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);

	//刷新顶部信息
	void refreshMenu();

	//显示连击信息
	void showLinkNum(int size);

	//影藏连击信息
	void hideLinkNum();

	//显示剩余星星数量
	void floatLeftStarMsg(int leftNum);

	//跳到另一关
	void gotoNextLevel();

	//游戏结束
	void gotoGameOver();

private:
	//关卡信息 （飘字）
	FloatWord* m_levelMsg;

	//目标分数 （飘字）
	FloatWord* m_targetScore;

	//顶部信息
	TopMenu* m_menu;

	StarMatrix* matrix;

	Label* linkMum;
};

#endif //__GameLayer_H__