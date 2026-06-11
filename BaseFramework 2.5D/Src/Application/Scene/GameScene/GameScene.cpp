#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Bike/Bike.h"
#include"../../Object/Ground/Ground.h"
void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
	Math::Vector3 camPos = { 0,1,-10 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	m_camera->SetCameraMatrix(transMat);
	timer++;
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	std::shared_ptr<Bike> bike = std::make_shared<Bike>();
	bike->Init();
	m_objList.push_back(bike);
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	ground->SetPos({0, 0, 0});
	m_objList.push_back(ground);
	timer = -180;
}
