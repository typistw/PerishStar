#ifndef __Audio_H__
#define __Audio_H__

class Audio
{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadGo();
	void playPop();
	void prepare();//��������
	void playCombo(int size);//��Ч����

private:
	static Audio* m_instance;
};

#endif //