#pragma once

#include"../BaseScene/BaseScene.h"

class Bike;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	int GetTimer() { return timer; }
	bool GetPaperFlg() { return paperflg; }
	bool GetGoalFlg() { return goalflg; }
	void SetGoalFlg(bool isgoal) { goalflg = isgoal; }
	void DeletePaper() { paperflg=true; }
	void DeleteCrystal() { score++; }
	void DeadBike() { bikeflg = false; }
	Math::Vector3 GetPlayerPos();
	Math::Vector3 GetCamPos() { return camPos; }
private:
	Math::Vector3 camPos;
	std::shared_ptr<Bike> bike;
	int timer;
	int resulttimer;
	int score;
	bool resultflg;
	bool bikeflg;
	bool paperflg;
	int papernum;
	float roty = 0;
	const int papermax = 20;
	bool goalflg = false;
	void Event() override;
	void Init()  override;
};
