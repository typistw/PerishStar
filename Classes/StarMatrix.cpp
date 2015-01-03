#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include "ComboEffect.h"
#include "Audio.h"
#include <ctime>

float StarMatrix::ONE_ClEAR_TIME=0.05f;

StarMatrix* StarMatrix::create(GameLayer* layer)
{
	StarMatrix* ret=new StarMatrix();
	if(ret && ret->init(layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer)
{
	if(!Node::init())
	{
		return false;
	}
	m_Layer=layer;
	needClear=false;
	clearSumTime=0;
	memset(stars,0,sizeof(Star*) * ROW_NUM * COL_NUM);

	initMatrix();

	return true;
}

//��������λ��
void StarMatrix::updateStar(float dt)
{
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			if(stars[i][j]!=nullptr)
			{
				stars[i][j]->updatePosition();
			}
		}
	}

	if(needClear)
	{
		clearSumTime += dt;
		if(clearSumTime>ONE_ClEAR_TIME)
		{
			clearMatrixOneByOne();
			clearSumTime=0;
		}
	}
}

void StarMatrix::onTouch(const Point& p)
{
	Star* s=getStarByTouch(p);
	if(s)
	{
		genSelectedList(s);
		CCLOG("SIZE=%d",selectedList.size());
		deleteSelectedList();
	}
}

void StarMatrix::setNeedClear(bool b)
{
	needClear=b;
}

//�������Ǿ���
void StarMatrix::initMatrix()
{
	srand(time(0));
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			int color=abs(rand()%Star::COLOR_MAX_NUM);
			if(color<0)
				CCLOG("color i=%d,j=%d",i,j);
			Star* star=Star::create(color);
			stars[i][j]=star;
			star->setPosition(getPositionByIndex(i,j)+Point(0,100));
			star->setDesPosition(getPositionByIndex(i,j));
			star->setIndex_xy(i,j);
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i,int j) 
{
	float x=j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y=(StarMatrix::COL_NUM-i) * Star::START_HEIGHT - Star::START_HEIGHT/2;
	return Point(x,y);
}

Star* StarMatrix::getStarByTouch(const Point& p)
{
	int k=p.y/Star::START_HEIGHT; //�� k תһ��int 
	int i=ROW_NUM - 1 - k;
	int j=p.x/Star::STAR_WIDTH;
	if(i>=0 && i<ROW_NUM && j>=0 && j<COL_NUM && stars[i][j]!=nullptr)
	{
		CCLOG("i=%d,j=%d",i,j);
		return stars[i][j];
	}
	else
	{
		return nullptr;
	}
}

void StarMatrix::genSelectedList(Star* s)
{
	//ÿ�ε����Ҫ�Ѵ�ɾ���б����
	selectedList.clear();
	//��������
	deque<Star*> travelList;
	//�ѵ�������ǷŽ���������
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for(it=travelList.begin(); it!=travelList.end();)
	{
		Star* star=*it;
		Star* linkStar=nullptr;
		int index_i=star->getIndexX();
		int index_j=star->getIndexY();

		CCLOG("index_i=%d,indeex_j=%d",index_i,index_j);

		//��
		if(index_i-1>=0 && (linkStar=stars[index_i-1][index_j]) ) //�ж��Ƿ�����Խ��
		{
			//�ж��Ƿ�������ѡ����в�����������е�������ɫһ��
			if(!linkStar->isSelected() && linkStar->getColor()==star->getColor())
				travelList.push_back(stars[index_i-1][index_j]); //��û������ɫһ���ͼ����������
		}

		//��
		if(index_i+1<ROW_NUM && (linkStar=stars[index_i+1][index_j]) )
		{
			if(!linkStar->isSelected() && linkStar->getColor()==star->getColor())
				travelList.push_back(stars[index_i+1][index_j]);
		}

		//��
		if(index_j-1>=0 && (linkStar=stars[index_i][index_j-1]) )
		{
			if(!linkStar->isSelected() && linkStar->getColor()==star->getColor())
				travelList.push_back(stars[index_i][index_j-1]);
		}

		//��
		if(index_j+1<COL_NUM && (linkStar=stars[index_i][index_j+1]) )
		{
			if(!linkStar->isSelected() && linkStar->getColor()==star->getColor())
				travelList.push_back(stars[index_i][index_j+1]);
		}

		if(!star->isSelected())//����ǰ������
		{
			star->setSelected(true);//�����ѱ����뵽ѡ�����(��ɾ������)
			selectedList.push_back(star);//���뵽ѡ�����(��ɾ������)
		}

		travelList.pop_front();//��ͷ����
		it=travelList.begin();//�õ��µĶ�ͷ
	}
}


void StarMatrix::deleteSelectedList()
{
	if(selectedList.size()<=1)
	{
		m_Layer->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return ;
	}

	for(auto it=selectedList.begin();it!=selectedList.end();it++)
	{
		Star* star=*it;
		//����Ч��
		showStartParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexX()][star->getIndexY()]=nullptr;
		star->removeFromParentAndCleanup(true);
		//��Ч
		Audio::getInstance()->playPop();
	}

	//comboЧ��
	showComboEffect(selectedList.size(),this);
	Audio::getInstance()->playCombo(selectedList.size());

	refreshScore();

	m_Layer->showLinkNum(selectedList.size());
	adjustMatrix();
	if(isEnded())
	{
		m_Layer->floatLeftStarMsg(getLeftStarNum());//֪ͨlayer����ʣ���������Ϣ
		CCLOG("ENDED");
	}
}

void StarMatrix::adjustMatrix()
{
	//��ֱ�������(��������)
	for(int i=ROW_NUM-1;i>=0;i--)
	{
		for(int j=COL_NUM-1;j>=0;j--)
		{
			if(stars[i][j]==nullptr)
			{
				int up=i;
				int dis=0;
				while(stars[up][j]==nullptr)
				{
					dis++;
					up--;
					if(up<0)
					{
						break;
					}
				}

				for(int begin_i=i-dis;begin_i>=0;begin_i--)
				{
					if(stars[begin_i][j] == nullptr)
						continue;
					Star* s=stars[begin_i+dis][j] = stars[begin_i][j];
					s->setIndex_xy(begin_i+dis,j);
					s->setDesPosition(getPositionByIndex(begin_i+dis,j));
					stars[begin_i][j]=nullptr;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//ˮƽ����(�����ж�û��ʱ��������£)
	for(int j=0;j<COL_NUM;j++)
	{
		if(stars[ROW_NUM-1][j]==nullptr)
		{
			int des=0;
			int right=j;
			while(stars[ROW_NUM-1][right]==nullptr)
			{
				des++;
				right++;
			}

			for(int begin_i=0;begin_i<ROW_NUM;begin_i++)
			{
				for(int begin_j=j+des;begin_j<COL_NUM;begin_j++)
				{
					if(stars[begin_i][begin_j]==nullptr)
						continue;
					Star* s=stars[begin_i][begin_j-des]=stars[begin_i][begin_j];
					s->setIndex_xy(begin_i,begin_j-des);
					s->setDesPosition(getPositionByIndex(begin_i,begin_j-des));
					stars[begin_i][begin_j]=nullptr;
				}
			}
		}
	}

}


void StarMatrix::refreshScore()
{
	GameData* data=GameData::getInstance();
	data->setCurScore(data->getCurScore()+selectedList.size()*selectedList.size()*5);
	if(data->getCurScore() > data->getHistoryScore() )
	{
		data->setHistoryScore(data->getCurScore());
	}

	m_Layer->refreshMenu();
}

bool StarMatrix::isEnded()
{
	bool bRet=true;
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			if(stars[i][j]==nullptr)
				continue;
			int curColor=stars[i][j]->getColor();

			//��
			if(i-1>=0 && stars[i-1][j]!=nullptr && stars[i-1][j]->getColor()==curColor)
				return false;
			//��
			if(i+1<ROW_NUM && stars[i+1][j]!=nullptr && stars[i+1][j]->getColor()==curColor)
				return false;
			//��
			if(j-1>=0 && stars[i][j-1]!=nullptr && stars[i][j-1]->getColor()==curColor)
				return false;
			//��
			if(j+1<COL_NUM && stars[i][j+1]!=nullptr && stars[i][j+1]->getColor()==curColor)
				return false;
		}
	}
	return bRet;
}

void StarMatrix::clearMatrixOneByOne()
{
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			if(stars[i][j]==nullptr)
				continue;
			showStartParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			CCLOG("show i=%d,j=%d,color=%d",i,j,stars[i][j]->getColor());
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j]=nullptr;
			return ;
		}
	}

	//ִ�е���һ��˵�� Matrix ȫΪ�գ�������Ҫ���
	needClear=false;
	//ת����һ�ػ��ߵ�����Ϸ��������
	if(GameData::getInstance()->getCurScore()>=GameData::getInstance()->getNextScore())
	{
		GameData::getInstance()->setCurlevel(GameData::getInstance()->getCurLevel()+ 1 );
		m_Layer->gotoNextLevel();
	}
	else
	{
		m_Layer->gotoGameOver();
		CCLog("GAME��OVER");
	}
}

int StarMatrix::getLeftStarNum()
{
	int ret=0;
	for(int i=0;i<ROW_NUM;i++)
	{
		for(int j=0;j<COL_NUM;j++)
		{
			if(stars[i][j]==nullptr)
				continue;
			ret++;
		}
	}

	return ret;
}