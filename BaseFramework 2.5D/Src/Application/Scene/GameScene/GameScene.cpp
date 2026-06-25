#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Bike/Bike.h"
#include"../../Object/Back/Back.h"
#include"../../Object/BlackBoard/BlackBoard.h"
#include"../../Object/Paper/Paper.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Goal/Goal.h"
#include"../../Object/Clock/Clock.h"
#include"../../Object/Crystal/Crystal.h"
#include"../../Object/Rank/Rank.h"
#include"../../Object/Needle/Needle.h"
#include"../../Object/Lava/Lava.h"
#include"../../Object/Result/TimeOver.h"
#include"../../Object/Result/GameOver.h"
#include"../../Object/Result/GameClear.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
	if (GetAsyncKeyState('R') & 0x8000) {
		KdAudioManager::Instance().StopAllSound();
		m_objList.clear();
		Init();
	}
	
	if ((timer > 3600||bikeflg == false) && resultflg == false) {
		KdAudioManager::Instance().StopAllSound();
		resultflg = true;
		resulttimer = 0;
		std::shared_ptr<BlackBoard> blackboard = std::make_shared<BlackBoard>();
		blackboard->Init();
		m_objList.push_back(blackboard);
	}
	if (goalflg==true && resultflg == false) {
		KdAudioManager::Instance().StopAllSound();
		resultflg = true;
		resulttimer = 0;
		std::shared_ptr<BlackBoard> blackboard = std::make_shared<BlackBoard>();
		blackboard->Init();
		m_objList.push_back(blackboard);
	}
	if (resultflg == true) {
		if (resulttimer > 120) {
			if (timer > 3600) {
				m_objList.clear();
				std::shared_ptr<TimeOver> timeover = std::make_shared<TimeOver>();
				timeover->Init();
				timeover->SetOwner(this);
				m_objList.push_back(timeover);
			}
			if (bikeflg == false) {
				m_objList.clear();
				std::shared_ptr<Back> back = std::make_shared<Back>();
				back->Init();
				m_objList.push_back(back);
				std::shared_ptr<GameOver> gameover = std::make_shared<GameOver>();
				gameover->SetOwner(this);
				gameover->Init();
				m_objList.push_back(gameover);
			}
			if (goalflg == true) {
				m_objList.clear();
				std::shared_ptr<GameClear> gameclear = std::make_shared<GameClear>();
				gameclear->SetCrystal(score);
				gameclear->Init();
				gameclear->SetOwner(this);
				m_objList.push_back(gameclear);
				std::shared_ptr<Rank> rank = std::make_shared<Rank>();
				rank->Init();
				rank->SetCrystal(score);
				rank->SetOwner(this);
				m_objList.push_back(rank);

			}
		}
	}
	Math::Vector3 bikePos = bike->GetPos();
	camPos = bikePos+Math::Vector3{ 0,5,-6 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	Math::Matrix rotateX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));

	/*if (GetAsyncKeyState('A') & 0x8000)
	{
		roty += 1.0f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		roty -= 1.0f;
	}*/
	Math::Matrix rotateY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(roty));
	m_camera->SetCameraMatrix(rotateX*transMat*rotateY);
	if (resultflg == false)timer++;
	if (resultflg == true)resulttimer++;
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	bike = std::make_shared<Bike>();
	bike->Init();
	bike->SetPos({ -18, -19, -18 });
	bike->SetOwner(this);
	m_objList.push_back(bike);
	bikeflg = true;
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	ground->SetPos({0, 0, 0});
	m_objList.push_back(ground);
	std::shared_ptr<Back> back = std::make_shared<Back>();
	back->Init();
	m_objList.push_back(back);

	std::shared_ptr<Paper> paper;
	paper = std::make_shared<Paper>();
	paper->Init();
	paper->SetPos({ 0,-15,0 });
	paper->SetOwner(this);
	m_objList.push_back(paper);
	paperflg = false;

	std::shared_ptr<Goal> goal = std::make_shared<Goal>();
	goal->Init();
	goal->SetOwner(this);
	m_objList.push_back(goal);
	std::shared_ptr<Clock> clock = std::make_shared<Clock>();
	clock->SetOwner(this);
	clock->Init();
	m_objList.push_back(clock);
	std::shared_ptr<Needle> needle = std::make_shared<Needle>();
	needle->SetOwner(this);
	needle->Init();
	m_objList.push_back(needle);
	std::shared_ptr<BlackBoard> blackboard = std::make_shared<BlackBoard>();
	blackboard->Init();
	blackboard->SetOwner(this);
	blackboard->Setalpha(1.0f);
	m_objList.push_back(blackboard);
	resultflg = false;
	timer = -180;
	
	std::shared_ptr<Crystal> crystal = std::make_shared<Crystal>();
	crystal->Init();
	crystal->SetOwner(this);
	crystal->SetPos({ -19,-19.5,-18 });
	m_objList.push_back(crystal);
	crystal = std::make_shared<Crystal>();
	crystal->Init();
	crystal->SetOwner(this);
	crystal->SetPos({ -18,-21.2,18 });
	m_objList.push_back(crystal);
	crystal = std::make_shared<Crystal>();
	crystal->Init();
	crystal->SetOwner(this);
	crystal->SetPos({ 18,-3.7,-18 });
	m_objList.push_back(crystal);

	std::shared_ptr<Lava> lava = std::make_shared<Lava>();
	lava->Init();

	m_objList.push_back(lava);
	score = 0;
}

Math::Vector3 GameScene::GetPlayerPos()
{
	if (bikeflg) {
		return bike->GetPos();
	}
	return Math::Vector3::Zero ;
}