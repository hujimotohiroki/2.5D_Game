#include "Goal.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../Scene/TitleScene/TitleScene.h"
void Goal::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Goal/lock.gltf");
	m_pos = { 19,-5,18 };
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationY(0);
	m_mWorld = rotateMat*transMat;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Goal", { 0,0.5,0 }, 1, KdCollider::TypeEvent);
	LoadFlg = false;
}

void Goal::Update()
{
	if (m_gowner != nullptr) {
		if (m_gowner->GetPaperFlg()&&!LoadFlg) {
			m_model->Load("Asset/Goal/Unlock.gltf");
			LoadFlg = true;
		}
	}
	else if (m_towner != nullptr) {
		if (m_towner->GetPaperFlg() && !LoadFlg) {
			m_model->Load("Asset/Goal/Unlock.gltf");
			LoadFlg = true;
		}
	}
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = rotateMat * transMat;
}

void Goal::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Goal::OnHit()
{
	if(m_gowner!=nullptr){
		if(m_gowner->GetPaperFlg())
		{
			m_gowner->SetGoalFlg(true);
		}
	}
	else if (m_towner != nullptr) {
		if(m_towner->GetPaperFlg())
		{
			m_towner->SetGoalFlg(true);
		}
	}
}
