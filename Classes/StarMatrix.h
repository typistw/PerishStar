#ifndef __StarMatrix_H__
#define __StarMatrix_H__

#include "cocos2d.h"
#include "Star.h"
#include "GameLayer.h"
#include <deque>
USING_NS_CC;
using namespace std;
class GameLayer; //ǰ������(�������໥����)

class StarMatrix: public Node
{
public:
	static StarMatrix* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);
	void updateStar(float dt);
	void onTouch(const Point& p);
	void setNeedClear(bool b);
	void initMatrix();

	const static int ROW_NUM=10;
	const static int COL_NUM=10;

private:
	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);

	//�õ�һ�����ӵ�����
	void genSelectedList(Star* s);
	//ɾ��һ�����ӵ�����
	void deleteSelectedList();

	void adjustMatrix();
	void refreshScore();
	bool isEnded();
	void clearMatrixOneByOne();
	int getLeftStarNum();

private:
	Star* stars[ROW_NUM][COL_NUM];
	deque<Star*> selectedList;
	GameLayer* m_Layer;
	bool needClear;
	static float ONE_ClEAR_TIME;
	float clearSumTime;

};

#endif //__StarMatrix_H__