#include "Title.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../Scene/TitleScene/TitleScene.h"
void Title::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Title/Title.gltf");
	m_pos = { 0,1,6 };
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Title::Update()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(Math::Vector3 {-1,2.8,0});
	m_mWorld =transMat;
}

void Title::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}