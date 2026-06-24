#pragma once

#include"../BaseScene/BaseScene.h"
class Bike;
class TitleScene : public BaseScene
{
public :

	TitleScene()  { Init(); }
	~TitleScene() {}
	bool GetPaperFlg() { return paperflg; }
	bool GetGoalFlg() { return goalflg; }
	void SetGoalFlg(bool isgoal) { goalflg=isgoal; }
	void DeadBike() { bikeflg = false; }
	void DeletePaper() { paperflg = true; }
private :
	int timer;
	std::shared_ptr<Bike> bike;
	bool goalflg = false;
	bool sceneflg = false;
	bool bikeflg = false;
	bool paperflg;
	void Event() override;
	void Init()  override;
};
