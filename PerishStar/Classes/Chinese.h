#ifndef __Chinese_H__
#define __Chinese_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

//txt_vec 保存文档（xml）内容的一个容器，以后读取操作就从txt_vec中获取
static ValueVector txt_vec=FileUtils::getInstance()->getValueVectorFromFile("ChineseWords.xml");

string ChineseWord(const char* wordId);

#endif //__Chinese_H__