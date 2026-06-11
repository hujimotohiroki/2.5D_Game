#include"Bike.h"
#include"../../Scene/SceneManager.h"

void Bike::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Bike.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(2,1);
	m_pos = { 0,0,0 };
	m_Frontpos = { 0.4,0,0 };
	m_Rearpos = { -0.4,0,0 };
	m_rot = { 0,0,0 };
	m_dir = { 0,0,0 };
	m_Frontdir = { 0,0,0 };
	m_Reardir = { 0,0,0 };
	m_Frontgravity = 0;
	m_Reargravity = 0;
	speed = 0;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Bike::Update()
{
	AnimCnt += speed;
	m_polygon->SetUVRect(((int)(abs(AnimCnt)*10)) % 2);

	m_Frontpos.x=m_pos.x+ cosf(DirectX::XMConvertToRadians(m_rot.y))*0.5f;
	m_Frontpos.z=m_pos.z-sinf(DirectX::XMConvertToRadians(m_rot.y))*0.5f;
	m_Rearpos.x=m_pos.x- cosf(DirectX::XMConvertToRadians(m_rot.y))*0.5f;
	m_Rearpos.z=m_pos.z+ sinf(DirectX::XMConvertToRadians(m_rot.y))*0.5f;

	m_Frontgravity -= gravityacc;	// 重力による落下速度の変更
	m_Reargravity -= gravityacc;	// 重力による落下速度の変更

	// ========================================
	// 当たり判定　・・・　レイ判定　ここから
	// ========================================

	KdCollider::RayInfo FrontrayInfo,RearrayInfo;
	// レイの発射位置（座標）を設定
	FrontrayInfo.m_pos = m_Frontpos;
	RearrayInfo.m_pos = m_Rearpos;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.1f;

	FrontrayInfo.m_pos.y += enableStepHigh;
	RearrayInfo.m_pos.y += enableStepHigh;
	// 0.1f までの段差は登れる

	// レイの方向を設定
	FrontrayInfo.m_dir = { 0.0f, -1.0f, 0.0f };
	RearrayInfo.m_dir = { 0.0f, -1.0f, 0.0f };

	// レイの長さを設定
	FrontrayInfo.m_range = enableStepHigh - m_Frontgravity;
	RearrayInfo.m_range = enableStepHigh - m_Reargravity;

	// 当たり判定をしたいタイプを設定
	FrontrayInfo.m_type = KdCollider::TypeGround;
	RearrayInfo.m_type = KdCollider::TypeGround;

	// デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine
	(
		RearrayInfo.m_pos,	// 線の開始位置
		RearrayInfo.m_dir,	// 線の方向
		RearrayInfo.m_range	// 線の長さ
	);


	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> FrontretRayList,RearretRayList;

	// 作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(FrontrayInfo, &FrontretRayList);
		obj->Intersects(RearrayInfo, &RearretRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	bool hit=false;
	float maxOverLap=0;
	Math::Vector3 FrontgroundPos = {}, ReargroundPos = {};	// レイが遮断された(Hitした)座標

	for (auto& ret : FrontretRayList)
	{
		// レイが当たったオブジェクトの中から
		// 「m_overlapDistance = 貫通した長さ」が一番長いものを探す
		// 「m_overlapDistance が一番長い = 一番近くで当たった」と判定できる
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			FrontgroundPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit)
	{
		m_Frontpos = FrontgroundPos;	// レイの着弾地点に着地
		m_Frontgravity = 0;
		m_Frontdir.y = tanf(DirectX::XMConvertToRadians(m_rot.z));
		//前が地面についていないと向きを変えられない
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_rot.y -= 1.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_rot.y += 1.0f;
		}
	}

	hit = false;
	maxOverLap = 0;

	for (auto& ret : RearretRayList)
	{
		// レイが当たったオブジェクトの中から
		// 「m_overlapDistance = 貫通した長さ」が一番長いものを探す
		// 「m_overlapDistance が一番長い = 一番近くで当たった」と判定できる
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			ReargroundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		m_Rearpos = ReargroundPos;	// レイの着弾地点に着地
		m_Reargravity = 0;
		m_Reardir.y = tanf(DirectX::XMConvertToRadians(m_rot.z));
		//後ろが地面についていないと慣性移動しかできない
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
	
	float x, y;
	x = 1.0f; //中央からタイヤまでの距離の二倍
	y = m_Frontpos.y - m_Rearpos.y;
	m_rot.z = DirectX::XMConvertToDegrees(atan2(y,x));//あからさまに二度手間だがdirをディグリーに統一するためにディグリーに変える
	
	//座標更新
	m_Frontdir.x = cosf(DirectX::XMConvertToRadians(m_rot.y));
	m_Frontdir.z = -sinf(DirectX::XMConvertToRadians(m_rot.y));
	m_Reardir.x = cosf(DirectX::XMConvertToRadians(m_rot.y));
	m_Reardir.z = -sinf(DirectX::XMConvertToRadians(m_rot.y));

	m_Frontpos.x += m_Frontdir.x * speed;
	m_Frontpos.y += m_Frontdir.y*speed+m_Frontgravity;
	m_Frontpos.z += m_Frontdir.z * speed;
	m_Rearpos.x += m_Reardir.x * speed;
	m_Rearpos.y += m_Reardir.y*speed+m_Reargravity;
	m_Rearpos.z += m_Reardir.z * speed;

	

	m_pos = (m_Frontpos + m_Rearpos) / 2;
	
	//移動行列
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos);
	//回転行列
	Math::Matrix rotatematY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	Math::Matrix rotatematZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	//ワールド行列の合成
	m_mWorld = rotatematZ * rotatematY * transmat;
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
