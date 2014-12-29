#ifndef __FloatWord_H__
#define __FloatWord_H__

#include "cocos2d.h"
USING_NS_CC;

class FloatWord:public cocos2d::Node
{
public:
	//创建字符串、字体大小、起始位置
	static FloatWord* create(const std::string& word,const int fontSize, Point begin);

	bool init(const std::string &word,const int fontSize,Point begin);

	void floatIn(const float delay,std::function<void()> callback);

	void floatOut(const float delay,std::function<void()> callback);

	void floatInOut(const float speed,const float delayTime,std::function<void()> callback);


private:
	//字体大小
	int m_fontSize;

	//初始位置
	Point m_begin;

	Label* m_label;
};

#endif //__FloatWord_H__
