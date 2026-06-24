#include "Clock.h"
#include "../../Scene/GameScene/GameScene.h"
void Clock::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Clock.png");
	m_pos = {0,0,0};
	m_pos.y += 1.0f;
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Clock::DrawUnLit()
{
	m_pos = m_owner->GetPlayerPos();
	m_pos.y += 2.0f;
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
