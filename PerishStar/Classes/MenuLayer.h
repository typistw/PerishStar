#ifndef __MenuLayer_H__
#define __MenuLayer_H__

#include "cocos2d.h"
USING_NS_CC;

class MenuLayer : public cocos2d::Scene
{
public:

	static Scene* createScene();
	virtual bool init();

	void startGame();

	CREATE_FUNC(MenuLayer);
};

#endif //__MenuLayer_H__