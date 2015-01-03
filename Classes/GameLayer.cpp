#include "GameLayer.h"
#include "Chinese.h"
#include "GameData.h"
#include "MenuScene.h"
#include "Audio.h"

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	matrix=nullptr;

	this->scheduleUpdate();

	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	Size visibleSize=Director::getInstance()->getVisibleSize();
	
	//背景图
	Sprite* background=Sprite::createWithSpriteFrameName("bg_mainscene.jpg");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(background,-1);

	m_menu=TopMenu::create();
	this->addChild(m_menu);

	//连击得分显示
	linkMum=Label::create("","Arial",40);
	linkMum->setPosition(Point(visibleSize.width/2,visibleSize.height-250));
	linkMum->setVisible(false);
	this->addChild(linkMum,1);

	this->floatLevelWord();

	return true;
}

void GameLayer::floatLevelWord()
{
	Size visible=Director::getInstance()->getVisibleSize();
	m_levelMsg=FloatWord::create(
		ChineseWord("guanqia")+String::createWithFormat(":%d",GameData::getInstance()->getNextLevel())->_string,
		50,Point(visible.width,visible.height/3*2));
	this->addChild(m_levelMsg);
	m_levelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::floatTargetScoreWord,this));
	Audio::getInstance()->playReadGo();
}

void GameLayer::floatTargetScoreWord()
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	m_targetScore=FloatWord::create(
		ChineseWord("mubiao")+String::createWithFormat(":%d",GameData::getInstance()->getNextScore())->_string+ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/3));
	this->addChild(m_targetScore);
	m_targetScore->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removeFloatWord,this));
}

void GameLayer::removeFloatWord()
{
	m_levelMsg->floatOut(0.5f,nullptr);
	m_targetScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

void GameLayer::showStarMatrix()
{
	matrix=StarMatrix::create(this);
	this->addChild(matrix);
}

void GameLayer::update(float dt)
{
	if(matrix)
	{
		matrix->updateStar(dt);
	}
}

bool GameLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Point p=pTouch->getLocationInView();
	p=Director::getInstance()->convertToGL(p);
	CCLOG("x=%f, y=%f",p.x,p.y);
	if(matrix)
	{
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshMenu()
{
	m_menu->refresh();
}

void GameLayer::showLinkNum(int size)
{
	string s=String::createWithFormat("%d",size)->_string+ChineseWord("lianji")+
		String::createWithFormat("%d",size*size*5)->_string+ChineseWord("fen");
	linkMum->setString(s);
	linkMum->setVisible(true);
}

void GameLayer::hideLinkNum()
{
	linkMum->setVisible(false);
}

void GameLayer::floatLeftStarMsg(int leftNum)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	
	FloatWord* leftStarMsg1=FloatWord::create(ChineseWord("shengyu")+
		String::createWithFormat("%d",leftNum)->_string+ChineseWord("ge"),
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
	
	int rewardScore=GameData::getInstance()->getReward(leftNum);
	FloatWord* leftStarMsg2=FloatWord::create(ChineseWord("jiangli")+
		String::createWithFormat("%d",rewardScore)->_string+ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/2-50));
	this->addChild(leftStarMsg2);

	leftStarMsg1->floatInOut(0.5f,1.0f,[=]()
	{
		hideLinkNum();
		matrix->setNeedClear(true);
		GameData* data=GameData::getInstance();
		data->setCurScore(data->getCurScore() + rewardScore);
		if(data->getCurScore() > data->getHistoryScore() )
		{
			data->setHistoryScore(data->getCurScore());
		}
		refreshMenu();
	});

	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
}

void GameLayer::gotoNextLevel()
{
	refreshMenu();
	floatLevelWord();
}

void GameLayer::gotoGameOver()
{
	GameData::getInstance()->saveHighesScore();

	Size visibleSize=Director::getInstance()->getVisibleSize();

	FloatWord* gameOver=FloatWord::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOver);

	gameOver->floatIn(1.0f,[]{Director::getInstance()->replaceScene(MenuScene::create());});
}