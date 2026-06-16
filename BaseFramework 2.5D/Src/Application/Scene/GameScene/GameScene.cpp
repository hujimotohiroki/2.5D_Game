#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Bike/Bike.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Paper/Paper.h"
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
	if (GetAsyncKeyState('R') & 0x8000) {
		m_objList.clear();
		Init();
	}
	Math::Vector3 bikePos = bike->GetPos();
	Math::Vector3 camPos = bikePos+Math::Vector3{ 0,2,-6 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(20));
	m_camera->SetCameraMatrix(rotateMat*transMat);
	std::shared_ptr<Paper> paper;
	while (papernum < papermax) {
		paper = std::make_shared<Paper>();
		paper->Init();
		paper->SetPos({ KdRandom::GetFloat(-5, 5),0,KdRandom::GetFloat(-5, 5) });
		paper->SetOwner(this);
		m_objList.push_back(paper);
		papernum++;
	}
	timer++;
	
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	bike = std::make_shared<Bike>();
	bike->Init();
	bike->SetOwner(this);
	m_objList.push_back(bike);
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	ground->SetPos({0, 0, 0});
	m_objList.push_back(ground);
	std::shared_ptr<Back> back = std::make_shared<Back>();
	back->Init();
	m_objList.push_back(back);
	std::shared_ptr<Paper> paper;
	for(papernum=0;papernum<papermax;papernum++){
		paper = std::make_shared<Paper>();
		paper->Init();
		paper->SetPos({ KdRandom::GetFloat(-5, 5),0,KdRandom::GetFloat(-5, 5) });
		paper->SetOwner(this);
		m_objList.push_back(paper);
	}
	timer = -180;
}
