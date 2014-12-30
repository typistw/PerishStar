#include "GameData.h"
#include "cocos2d.h"
USING_NS_CC;

GameData* GameData::m_instance=0;

GameData::GameData()
{
	this->init();
}

GameData* GameData::getInstance()
{
	if(m_instance==0)
	{
		m_instance=new GameData();
	}
	return m_instance;
}

void GameData::init()
{
	setCurlevel(0);
	setCurScore(0);
	setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));
}

void GameData::setCurlevel(int level)
{
	if(level<0)
	{
		return ;
	}
	cur_level=level;
	next_level=level+1;
	next_score=getScoreByLevel(next_level);
}

int GameData::getScoreByLevel(int level)
{
	int score=0;
	if(level==1)
	{
		score=1000;
	}
	else if(level==2)
	{
		score=3000;
	}
	else if( (level>=3) && (level<=10) )
	{
		score=3000+3000*(level-2);
	}
	else
	{
		score=27000+4000*(level-10);
	}
	return score;
}

int GameData::getReward(int size)
{
	static const int reward[10][2]=
	{
		{0,2000},
		{1,1980},
		{2,1920},
		{3,1820},
		{4,1680},
		{5,1500},
		{6,1280},
		{7,1020},
		{8,720},
		{9,380}
	};

	if(size>9 || size<0)
	{
		return 0;
	}

	return reward[size][1];
}

void GameData::saveHighesScore()
{
	UserDefault::getInstance()->setIntegerForKey("highestScore",getHistoryScore());
}