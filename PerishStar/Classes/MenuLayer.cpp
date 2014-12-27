#include "MenuLayer.h"
#include "GameScene.h"

Scene* MenuLayer::createScene()
{
	auto scene=Scene::create();
	auto layer=MenuLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MenuLayer::init()
{
	if(!Scene::init())
	{
		return false;
	}

	Size visibleSize=Director::getInstance()->getVisibleSize();

	//读取游戏的图片资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("m_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("m_menu.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("m_word.plist");

	//初始化背景
	Sprite* background=Sprite::createWithSpriteFrameName("bg_menuscene.jpg");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(background,-1);

	//菜单初始化
	Sprite* startSprite=Sprite::createWithSpriteFrameName("menu_start.png");
	MenuItemSprite* startBtn=MenuItemSprite::create(
		startSprite,
		startSprite,
		CC_CALLBACK_0(MenuLayer::startGame,this));
	startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	Menu* menu=Menu::create(startBtn,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame()
{
	CCLOG("START");
	Director::getInstance()->replaceScene(GameScene::create());
}

