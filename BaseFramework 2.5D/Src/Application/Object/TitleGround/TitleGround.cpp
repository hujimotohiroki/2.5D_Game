#include "TitleGround.h"

void TitleGround::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Block/normal.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("GroundCollision", m_model, KdCollider::TypeGround);
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(Math::Vector3(0, 0, 0));
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(5);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	m_mWorld = scaleMat * transMat* rotateMat;
}

void TitleGround::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
