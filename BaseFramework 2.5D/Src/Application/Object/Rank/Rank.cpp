#include "Rank.h"
#include "../../Scene/GameScene/GameScene.h"
void Rank::Init()
{
	m_model = std::make_shared<KdModelData>();
	modelflg = false;
}

void Rank::DrawUnLit()
{
	if(modelflg==false){
		switch (rank) {
		case 0:
			m_model->Load("Asset/Rank/C.gltf");
			break;
		case 1:
			m_model->Load("Asset/Rank/B.gltf");
			break;
		case 2:
			m_model->Load("Asset/Rank/A.gltf");
			break;
		case 3:
			m_model->Load("Asset/Rank/S.gltf");
			break;
		default:
			m_model->Load("Asset/Rank/S.gltf");
			break;
		}
		modelflg = true;
	}
	m_pos = m_owner->GetCamPos();
	m_pos -= Math::Vector3{ 0,7,-8 };
	m_pos += Math::Vector3{ 0.3,4.05,-5.25 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix rotateMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	Math::Matrix rotateMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotateMatY * rotateMatX * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
