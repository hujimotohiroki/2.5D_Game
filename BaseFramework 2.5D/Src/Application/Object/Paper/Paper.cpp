#include "Paper.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene/GameScene.h"
void Paper::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Paper/Paper.gltf");
	m_pos = { 3,3,2 };
	m_dir = Math::Vector3::Zero;
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollision", { 0,0.5,0 }, 1, KdCollider::TypeDamage);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	timer = 0;
}

void Paper::Update()
{
	timer++;
	if (timer > 1800)
	{
		m_owner->DeletePaper();
		m_isExpired = true;
	}
	if (m_isExpired) {
		return;
	}
	if (timer % 60 == 0) {
		m_dir.x = KdRandom::GetFloat(-0.01, 0.01);
		m_dir.z = KdRandom::GetFloat(-0.01, 0.01);
	}
	m_dir.y -= m_gravity;
	m_pos += m_dir;
	// ========================================
	// 当たり判定　・・・　レイ判定　ここから
	// ========================================

	KdCollider::RayInfo rayInfo;
	// レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;			// 0.2f までの段差は登れる

	// レイの方向を設定
	rayInfo.m_dir = { 0.0f, -1.0f, 0.0f };

	// レイの長さを設定
	rayInfo.m_range = enableStepHigh + m_gravity;

	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine
	(
		rayInfo.m_pos,	// 線の開始位置
		rayInfo.m_dir,	// 線の方向
		rayInfo.m_range	// 線の長さ
	);


	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	// 作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};	// レイが遮断された(Hitした)座標

	for (auto& ret : retRayList)
	{
		// レイが当たったオブジェクトの中から
		// 「m_overlapDistance = 貫通した長さ」が一番長いものを探す
		// 「m_overlapDistance が一番長い = 一番近くで当たった」と判定できる
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		m_pos = groundPos;	// レイの着弾地点に着地
		m_dir.y = 0.0f;
	}
	// ========================================
	// 当たり判定　・・・　レイ判定　ここまで
	// ========================================
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Paper::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Paper::OnHit()
{
	m_owner->DeletePaper();
	m_isExpired = true;
}
