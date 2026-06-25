#include "BreakBack.h"

void BreakBack::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Back/Back2.gltf");
	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3(-47, 20, -47));
	Math::Matrix scaleMat = Math::Matrix::CreateScale(100);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(3));
	m_mWorld = scaleMat*rotateMat*transMat;
}

void BreakBack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}