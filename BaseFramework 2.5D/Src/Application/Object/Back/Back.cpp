#include "Back.h"

void Back::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Back/Back.gltf");
	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3(0, 20, 0));
	Math::Matrix scaleMat = Math::Matrix::CreateScale(100);
	m_mWorld = scaleMat*transMat;
}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
