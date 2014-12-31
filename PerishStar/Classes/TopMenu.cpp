#include "TopMenu.h"
#include "GameData.h"
#include "Chinese.h"

bool TopMenu::init()
{
	if(!Node::init())
	{
		return false;
	}

	Size visibleSize=Director::getInstance()->getVisibleSize();

	m_highesScore=Label::create(
		ChineseWord("highestScore")+String::createWithFormat("%d",GameData::getInstance()->getHistoryScore())->_string,"Verdana_Bold",30);
	m_highesScore->setPosition(Point(visibleSize.width/2,visibleSize.height-50));
	this->addChild(m_highesScore);

	m_level=Label::create(
		ChineseWord("guanqia")+String::createWithFormat("%d",GameData::getInstance()->getNextLevel())->_string,"Verdana_Bold",30);
	m_level->setPosition(Point(200,visibleSize.height-100));
	this->addChild(m_level);

	m_targetScore=Label::create(
		ChineseWord("mubiao")+String::createWithFormat("%d",GameData::getInstance()->getNextScore())->_string+ChineseWord("fen"),"Verdana-Bold",30);
	m_targetScore->setPosition(Point(400,visibleSize.height-100));
	this->addChild(m_targetScore);

	m_curScore=Label::create(String::createWithFormat("%d",GameData::getInstance()->getCurScore())->_string,"Verdana-Bold",50);
	m_curScore->setPosition(Point(visibleSize.width/2,visibleSize.height-150));
	this->addChild(m_curScore);

	return true;
}

void TopMenu::refresh()
{
	char buf[64];
	sprintf(buf,"%d",GameData::getInstance()->getCurScore());
	m_curScore->setString(buf);

	string history=ChineseWord("highestScore")+String::createWithFormat("%d",GameData::getInstance()->getHistoryScore())->_string;
	m_highesScore->setString(history);

	string level=ChineseWord("guanqia")+String::createWithFormat("%d",GameData::getInstance()->getNextLevel())->_string;
	m_level->setString(level);

	string target=ChineseWord("mubiao")+String::createWithFormat("%d",GameData::getInstance()->getNextScore())->_string+ChineseWord("fen");
	m_targetScore->setString(target);
}