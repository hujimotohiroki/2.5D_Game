#pragma once

#include"../BaseScene/BaseScene.h"

class Bike;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	int GetTimer() { return timer; }
	void DeletePaper() { papernum--; }
private:
	std::shared_ptr<Bike> bike;
	int timer;
	int papernum;
	const int papermax = 5;
	void Event() override;
	void Init()  override;
};
