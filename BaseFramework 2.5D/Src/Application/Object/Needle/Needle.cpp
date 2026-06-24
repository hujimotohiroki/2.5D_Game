#include "Needle.h"
#include "../../Scene/GameScene/GameScene.h"
void Needle::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Needle.png");
	m_pos = {0,0,0};
	m_pos.y += 1.0f;
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Needle::DrawUnLit()
{
	m_pos = m_owner->GetPlayerPos();
	m_pos.y += 2.0f;
	m_pos.z -= 0.1f;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-(float)(m_owner->GetTimer())/10.0f));
	m_mWorld = rotateMat * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
