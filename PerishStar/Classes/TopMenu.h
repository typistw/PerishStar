#ifndef __TopMenu_H__
#define __TopMenu_H__

#include "cocos2d.h"
USING_NS_CC;

class TopMenu : public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(TopMenu);

	void refresh();

private:
	Label* m_highesScore;
	Label* m_level;
	Label* m_targetScore;
	Label* m_curScore;
};


#endif //__TopMenu_H__