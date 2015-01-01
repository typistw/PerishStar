#ifndef __Star_H__
#define __Star_H__

#include "cocos2d.h"
USING_NS_CC;

class Star: public cocos2d::Sprite
{
public:
	enum color
	{
		GREEN,
		RED,
		YELLOW,
		PURPLE,
		BLUE
	};

	static Star* create(int color);
	bool isSelected();

	inline void setSelected(bool b)
	{
		selected=b;
	}

	int getColor();
	void setDesPosition(const Point& p);

	inline Point getDesPosition()
	{
		return desPosition;
	}

	void updatePosition();

	inline int getIndexX()
	{
		return index_x;
	}

	inline int getIndexY()
	{
		return index_y;
	}

	inline void setIndex_xy(int x,int y)
	{
		index_x=x;
		index_y=y;
	}

private:
	char* getImage(int color);

public:
	const static int MOVE_SPEED=4;
	static const int COLOR_MAX_NUM=5;
	static const int STAR_WIDTH=48;
	static const int START_HEIGHT=48;

private:
	int color;
	Point desPosition;
	bool selected;
	int index_x;
	int index_y;

};

#endif //__Star_H__