#include "GameClear.h"
#include "../../Scene/GameScene/GameScene.h"
void GameClear::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Result/GameClear.gltf");
}

void GameClear::DrawUnLit()
{
	m_pos = m_owner->GetCamPos();
	m_pos -= Math::Vector3{ 0,6.9,-8 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix rotateMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	Math::Matrix rotateMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotateMatY * rotateMatX * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
