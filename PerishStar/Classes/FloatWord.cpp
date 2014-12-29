#include "FloatWord.h"

FloatWord* FloatWord::create(const std::string& word,const int fontSize,Point begin)
{
	FloatWord* ret=new FloatWord();
	if(ret && ret->init(word,fontSize,begin))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

//初始化 FloatWord 内置的 Label
bool FloatWord::init(const std::string& word,const int fontSize,Point begin)
{
	if(!Node::init())
	{
		return false;
	}

	m_begin=begin;
	Size visibleSize=Director::getInstance()->getVisibleSize();

	m_label=Label::create(word,"Verdana-Bold",fontSize);
	m_label->setPosition(begin);
	this->addChild(m_label);

	return true;
}

//飘入
void FloatWord::floatIn(const float delay,std::function<void()> callback)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	MoveTo* move=MoveTo::create(delay,Point(visibleSize.width/2,m_begin.y));
	CallFunc* call=CallFunc::create(callback);
	Sequence* action=Sequence::create(move,call,NULL);
	m_label->runAction(action);
}

//飘出
void FloatWord::floatOut(const float delay,std::function<void()> callback)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	MoveTo* move=MoveTo::create(delay,Point(0,m_begin.y));
	CallFunc* call=CallFunc::create(callback);
	/*调用一个有 Lambda 表达式构造的匿名函数，用于销毁 FloatWord 对象*/
	CallFunc* removeC=CallFunc::create([this]()
	{
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action=Sequence::create(move,call,removeC,NULL);
	m_label->runAction(action);
}

//飘入飘出(速度，停留时间)
void FloatWord::floatInOut(const float speed, const float delayTime,std::function<void()> callback)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	MoveTo* moveIn=MoveTo::create(speed,Point(visibleSize.width/2,m_begin.y));
	MoveTo* moveOut=MoveTo::create(speed,Point(0,m_begin.y));
	CallFunc* removeC=CallFunc::create([this]()
	{
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action=Sequence::create(moveIn,DelayTime::create(delayTime),moveOut,removeC,CallFunc::create(callback),NULL);
	m_label->runAction(action);
}