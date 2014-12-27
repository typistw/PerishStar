#ifndef __GameLayer_H__
#define __GameLayer_H__
#include "cocos2d.h"
USING_NS_CC;

class GameLayer:public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameLayer);
};

#endif //__GameLayer_H__