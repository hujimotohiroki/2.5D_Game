#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	int GetTimer() { return timer; }
private:
	int timer;
	void Event() override;
	void Init()  override;
};
