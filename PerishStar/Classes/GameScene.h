#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene:public cocos2d::Scene
{
public:

	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif //__GameScene_H__