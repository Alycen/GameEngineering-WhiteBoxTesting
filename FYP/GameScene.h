#ifndef _GAMESCENE_
#define _GAMESCENE_

class GameScene
{
private:
	static bool instanceFlag;
	static GameScene* instance;
	GameScene() { }
public:
	static GameScene* GetInstance();
	~GameScene()
	{
		delete instance;
		instanceFlag = false;
	}
	void Init();
};

#endif