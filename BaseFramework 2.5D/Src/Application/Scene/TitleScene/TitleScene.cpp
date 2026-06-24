#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/Bike/Bike.h"
#include"../../Object/Back/Back.h"
#include"../../Object/BlackBoard/BlackBoard.h"
#include"../../Object/Paper/Paper.h"
#include"../../Object/TitleGround/TitleGround.h"
#include"../../Object/Title/Title.h"
#include"../../Object/Goal/Goal.h"
#include"../../Object/Crystal/Crystal.h"

void TitleScene::Event()
{
	if (goalflg==true&&sceneflg==false)
	{
		std::shared_ptr<BlackBoard> blackboard = std::make_shared<BlackBoard>();
		blackboard->Init();
		m_objList.push_back(blackboard);
		timer = 0;
		sceneflg = true;
	}
	if (sceneflg == true) timer++;
	if (timer > 120) {
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
	if (!bikeflg) {
		m_objList.clear();
		Init();
	}
	Math::Vector3 camPos = Math::Vector3{ 0,5,-6 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	Math::Matrix rotateX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	m_camera->SetCameraMatrix(rotateX * transMat);
}

void TitleScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	bike = std::make_shared<Bike>();
	bike->Init();
	bike->SetPos({ -2.4f, 0, -0.3f });
	bike->SetOwner(this);
	m_objList.push_back(bike);
	bikeflg = true;
	std::shared_ptr<TitleGround> ground = std::make_shared<TitleGround>();
	ground->Init();
	ground->SetPos({ 0, 0, 0 });
	m_objList.push_back(ground);
	std::shared_ptr<Back> back = std::make_shared<Back>();
	back->Init();
	m_objList.push_back(back);
	std::shared_ptr<Paper> paper;
	paper = std::make_shared<Paper>();
	paper->Init();
	paper->SetPos({ 3,0,3 });
	paper->SetOwner(this);
	m_objList.push_back(paper);
	paperflg = false;
	std::shared_ptr<Goal> goal = std::make_shared<Goal>();
	goal->Init();
	goal->SetOwner(this);
	goal->SetPos({ 3,0,-3 });
	m_objList.push_back(goal);
	std::shared_ptr<Title> title = std::make_shared<Title>();
	title->Init();
	m_objList.push_back(title);
	std::shared_ptr<Crystal> crystal = std::make_shared<Crystal>();
	crystal->Init();
	crystal->SetOwner(this);
	crystal->SetPos({ 3.5,-0.2,0 });
	m_objList.push_back(crystal);
	timer = 0;
}
