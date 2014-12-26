#include "MenuLayer.h"

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

	//初始化背景
	Sprite* background=Sprite::create("bg_menuscene.jpg");
	background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(background,-1);

	//菜单初始化
	MenuItemImage* startBtn=MenuItemImage::create(
		"menu_start.png",
		"menu_start.png",
		CC_CALLBACK_0(MenuLayer::startGame,this));
	startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	Menu* menu=Menu::create(startBtn,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame()
{

}

