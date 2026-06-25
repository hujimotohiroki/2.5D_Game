#include "SunBack.h"

void SunBack::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Back/SunBack.gltf");
	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3(-47, 20, -47));
	Math::Matrix scaleMat = Math::Matrix::CreateScale(200);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(3));
	m_mWorld = scaleMat*rotateMat*transMat;
}

void SunBack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}