#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include <ctime>

float StarMatrix::ONE_ClEAR_TIME=0.05f;

StarMatrix* StarMatrix::create(GameLayer* layer)
{
	StarMatrix* ret=new StarMatrix();
	if(ret && ret->init(layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer)
{
	if(!Node::init())
	{
		return false;
	}
	m_Layer=layer;
	needClear=false;
	clearSumTime=0;
	memset(stars,0,sizeof(Star*) * ROW_NUM * COL_NUM);

	initMatrix();

	return true;
}

void StarMatrix::initMatrix()
{
	srand(time(0));
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			int color=abs(rand()%Star::COLOR_MAX_NUM);
			if(color<0)
				CCLOG("color i=&d,j=&d");
			Star* star=Star::create(color);
			stars[i][j]=star;
			star->setPosition(getPositionByIndex(i,j)+Point(0,100));
			star->setDesPosition(getPositionByIndex(i,j));
			star->setIndex_xy(i,j);
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i,int j) 
{
	float x=j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y=(StarMatrix::COL_NUM-i) * Star::START_HEIGHT - Star::START_HEIGHT/2;
	return Point(x,y);
}