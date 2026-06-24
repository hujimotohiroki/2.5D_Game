#include "Crystal.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../Scene/TitleScene/TitleScene.h"
void Crystal::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Crystal/Crystal.gltf");
	m_pos = { 3,3,2 };
	m_dir = Math::Vector3::Zero;
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotx = -20;
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationX(rotx);
	m_mWorld = rotateMat*transMat;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollision", { 0,0.5,0 }, 1, KdCollider::TypeEvent);
	//m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	timer = 0;
}

void Crystal::Update()
{
	if (m_gowner != nullptr) {
		if (m_gowner->GetTimer() > 18000 || m_gowner->GetGoalFlg())
		{
			return;
		}
		timer++;
	}
	if (m_isExpired) {
		return;
	}

	
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation({m_pos.x,m_pos.y+0.2f,m_pos.z});
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rotx));
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(0.1);
	m_mWorld = scaleMat*rotateMat*transMat;
	
}

void Crystal::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Crystal::OnHit()
{
	if(m_gowner!=nullptr){
		if(m_gowner->GetPaperFlg()){
			m_gowner->DeleteCrystal();
			m_isExpired = true;
		}
	}
	else if (m_towner != nullptr) {
		m_isExpired = true;
	}
}
