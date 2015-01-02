#ifndef __Audio_H__
#define __Audio_H__

class Audio
{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadGo();
	void playPop();
	void prepare();//º”‘ÿ“Ù¿÷
	void playCombo(int size);//Ãÿ–ß“Ù¿÷

private:
	static Audio* m_instance;
};

#endif //