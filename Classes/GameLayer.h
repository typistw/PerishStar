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

	//Ʈ���ؿ���Ϣ
	void floatLevelWord();

	//Ʈ��Ŀ�����
	void floatTargetScoreWord();

	//�Ƴ��ؿ���Ϣ��Ŀ�����
	void removeFloatWord();

	//�������Ǿ���(���е�����)
	void showStarMatrix();

	virtual void update(float dt);//update

	//���ܴ����¼�
	virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);

	//ˢ�¶�����Ϣ
	void refreshMenu();

	//��ʾ������Ϣ
	void showLinkNum(int size);

	//Ӱ��������Ϣ
	void hideLinkNum();

	//��ʾʣ����������
	void floatLeftStarMsg(int leftNum);

	//������һ��
	void gotoNextLevel();

	//��Ϸ����
	void gotoGameOver();

private:
	//�ؿ���Ϣ ��Ʈ�֣�
	FloatWord* m_levelMsg;

	//Ŀ����� ��Ʈ�֣�
	FloatWord* m_targetScore;

	//������Ϣ
	TopMenu* m_menu;

	StarMatrix* matrix;

	Label* linkMum;
};

#endif //__GameLayer_H__