#include"Bike.h"
#include"../Scene/SceneManager.h"

void Bike::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Bike.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = { 0,0,0 };
	m_rot = { 0,0,0 };
	speed = 0;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Bike::Update()
{
	
	
	m_gravity += 0.003f;	// 重力加速度

	//座標更新
	m_pos.y -= m_gravity;	// 重力による落下
	

	// ========================================
	// 当たり判定　・・・　レイ判定　ここから
	// ========================================

	KdCollider::RayInfo rayInfo;
	// レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.1f;
	rayInfo.m_pos.y += enableStepHigh;			// 0.1f までの段差は登れる

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
		m_gravity = 0.0f;
		//地面についていないと慣性移動しかできない
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_rot.y -= 1.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_rot.y += 1.0f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			speed += 0.001f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			speed -= 0.001f;
		}
	}
	// ========================================
	// 当たり判定　・・・　レイ判定　ここまで
	// ========================================
	
	//座標更新
	m_pos.x += cosf(DirectX::XMConvertToRadians(m_rot.y)) * speed;
	m_pos.z -= sinf(DirectX::XMConvertToRadians(m_rot.y)) * speed;
	
	//移動行列
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos);
	//回転行列
	Math::Matrix rotatemat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	//ワールド行列の合成
	m_mWorld = rotatemat * transmat;
}

void Bike::PostUpdate()
{

}

void Bike::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Bike::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
