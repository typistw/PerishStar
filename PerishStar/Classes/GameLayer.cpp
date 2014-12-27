#include "GameLayer.h"

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize=Director::getInstance()->getVisibleSize();
	
	//±³¾°Í¼
	Sprite* background=Sprite::createWithSpriteFrameName("bg_mainscene.jpg");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(background,-1);


	return true;
}









