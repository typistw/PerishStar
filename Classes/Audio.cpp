#include "Audio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Audio* Audio::m_instance=nullptr;

Audio* Audio::getInstance()
{
	if(m_instance==nullptr)
	{
		m_instance=new Audio();
	}
	return m_instance;
}

void Audio::playBGM()
{
	//后面为true 表示重复(否则一边,默认值 false)
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.wav",true);
}

void Audio::playReadGo()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/readgo.wav");
}

void Audio::playCombo(int size)
{
	if(size<5)
		return ;
	if(size>=10)
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.wav",false);
	}
	else if(size>=7)
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.wav",false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.wav",false);
	}
}

void Audio::playPop()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/pop.wav");
}

void Audio::prepare()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.wav");
}