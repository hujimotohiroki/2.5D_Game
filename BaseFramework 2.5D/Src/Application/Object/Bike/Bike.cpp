#include"Bike.h"
#include"../../Scene/SceneManager.h"
#include"../../Scene/GameScene/GameScene.h"
#include"../../Scene/TitleScene/TitleScene.h"
void Bike::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Bike.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(2, 1);
	m_pos = { -18, -19, -18 };
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
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
	paper = 0;
	engineflg=false;
}

void Bike::Update()
{
	if (m_OutroFlg)
	{
		PostUpdate();
		return;
	}
	AnimCnt += speed;
	m_polygon->SetUVRect(((int)(abs(AnimCnt) * 10)) % 2);
	if(m_gowner!=nullptr){
		if (m_gowner->GetTimer() < 0||m_gowner->GetTimer() > 18000||m_gowner->GetGoalFlg())
		{
			return;
		}
	}
	if(m_towner!=nullptr){
		if (m_towner->GetGoalFlg())
		{
			return;
		}
	}
	
	m_Frontpos.x = m_pos.x + cosf(DirectX::XMConvertToRadians(m_rot.y)) * 0.4f;
	m_Frontpos.y = m_pos.y + tanf(DirectX::XMConvertToRadians(m_rot.z)) * 0.4f;
	m_Frontpos.z = m_pos.z - sinf(DirectX::XMConvertToRadians(m_rot.y)) * 0.4f;
	m_Rearpos.x = m_pos.x - cosf(DirectX::XMConvertToRadians(m_rot.y)) * 0.4f;
	m_Rearpos.y = m_pos.y - tanf(DirectX::XMConvertToRadians(m_rot.z)) * 0.4f;
	m_Rearpos.z = m_pos.z + sinf(DirectX::XMConvertToRadians(m_rot.y)) * 0.4f;

	m_Frontgravity -= gravityacc;	// 重力による落下速度の変更
	m_Reargravity -= gravityacc;	// 重力による落下速度の変更

	//===================
	//球（スフィア）判定
	//===================
	//球判定用の変数を用意
	KdCollider::SphereInfo Frontsphere, Rearsphere;

	//球の中心座標を設定
	Frontsphere.m_sphere.Center = m_Frontpos;
	Rearsphere.m_sphere.Center = m_Rearpos;
	static const float enableStepHigh = 0.1f;
	Frontsphere.m_sphere.Center.y += enableStepHigh;
	Rearsphere.m_sphere.Center.y += enableStepHigh;

	//球の半径を設定
	Rearsphere.m_sphere.Radius = 0.1;
	Frontsphere.m_sphere.Radius = 0.1;

	//当たり判定をしたいタイプを設定
	Rearsphere.m_type = KdCollider::TypeGround;
	Frontsphere.m_type = KdCollider::TypeGround;

	//デバッグ
	//m_pDebugWire->AddDebugSphere(Rearsphere.m_sphere.Center, Frontsphere.m_sphere.Radius);

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> FrontretSphereList, RearretSphereList;
	for (auto& obj : SceneManager::Instance().GetObjList()) {
		obj->Intersects(Frontsphere, &FrontretSphereList);
		obj->Intersects(Rearsphere, &RearretSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを探す
	float maxOverlap = 0;
	bool hit = false;
	Math::Vector3 hitDir;//当たった方向
	for (auto& ret : FrontretSphereList) {
		if (maxOverlap < ret.m_overlapDistance) {
			maxOverlap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true) {
		//方向ベクトルを長さ1にする
		hitDir.Normalize();
		m_Frontpos += hitDir * maxOverlap;
		m_Frontgravity = 0;
		m_Frontdir.y = sinf(DirectX::XMConvertToRadians(m_rot.z));//坂を上っているときのy速度
		//前が地面についていないと向きを変えられない
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_rot.y -= 1.5f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_rot.y += 1.5f;
		}
		speed *= 0.995;
	}
	else {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_rot.y -= 0.5f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_rot.y += 0.5f;
		}
	}

	maxOverlap = 0;
	hit = false;
	for (auto& ret : RearretSphereList) {
		if (maxOverlap < ret.m_overlapDistance) {
			maxOverlap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true) {
		//方向ベクトルを長さ1にする
		hitDir.Normalize();
		m_Rearpos += hitDir * maxOverlap;
		m_Reargravity = 0;
		m_Reardir.y = sinf(DirectX::XMConvertToRadians(m_rot.z));//坂を上っているときのy速度
		//後ろが地面についていないと慣性移動しかできない
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			speed += 0.001f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			speed -= 0.0006f;
		}
		speed *= 0.995;
		if (abs(speed) < 0.0005)speed = 0;
	}
	//当たり判定（アイテムとの）
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos() + Math::Vector3{ -sinf(DirectX::XMConvertToRadians(m_rot.z)) * BikeRadius,cosf(DirectX::XMConvertToRadians(m_rot.z)) * BikeRadius,0 };
	sphere.m_sphere.Radius = BikeRadius;
	sphere.m_type = KdCollider::TypeEvent;

	//デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	//当たったオブジェクト情報を格納するリストは不要

	for (auto& obj : SceneManager::Instance().GetObjList())
	{

		if (obj->Intersects(sphere, nullptr) == true) {
			obj->OnHit();
			paper++;
			//紙を回収した
		}
	}

	float x, y;
	Math::Vector3 dist;
	dist.x = m_Frontpos.x - m_Rearpos.x;
	dist.z = m_Frontpos.z - m_Rearpos.z;
	x = dist.Length();
	y = m_Frontpos.y - m_Rearpos.y;
	m_rot.z = DirectX::XMConvertToDegrees(atan2(y, x));//あからさまに二度手間だがdirをディグリーに統一するためにディグリーに変える

	//座標更新
	m_Frontdir.x = cosf(DirectX::XMConvertToRadians(m_rot.y));
	m_Frontdir.z = -sinf(DirectX::XMConvertToRadians(m_rot.y));
	m_Reardir.x = cosf(DirectX::XMConvertToRadians(m_rot.y));
	m_Reardir.z = -sinf(DirectX::XMConvertToRadians(m_rot.y));

	m_Frontpos.x += m_Frontdir.x * speed;
	m_Frontpos.y += m_Frontdir.y * speed + m_Frontgravity;
	m_Frontpos.z += m_Frontdir.z * speed;
	m_Rearpos.x += m_Reardir.x * speed;
	m_Rearpos.y += m_Reardir.y * speed + m_Reargravity;
	m_Rearpos.z += m_Reardir.z * speed;

	m_pos = (m_Frontpos + m_Rearpos) / 2;
	//Math::Vector3 dist = m_Frontpos - m_Rearpos;
	//移動行列
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos);
	//回転行列
	Math::Matrix rotatematY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));
	Math::Matrix rotatematZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rot.z));
	//ワールド行列の合成
	m_mWorld = rotatematZ * rotatematY * transmat;
	if (m_pos.y < -28){
		m_OutroFlg = true;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if(engineflg==false)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/Engine.wav", true);
		}
		engineflg = true;
	}
	else
	{
		if (engineflg == true) {
			KdAudioManager::Instance().StopAllSound();
		}
		engineflg = false;
	}
	
}

void Bike::PostUpdate()
{
	if (m_OutroFlg) {
		m_Dissolve += 0.01f;
		if (m_Dissolve > 1)
		{
			if (m_gowner != nullptr)m_gowner->DeadBike();
			else if (m_towner != nullptr)m_towner->DeadBike();
			m_isExpired = true;
		}
	}
}

void Bike::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Bike::DrawLit()
{
	float range = 0.3;
	Math::Vector3 color = { 1,0.3,0.3 };
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_Dissolve, &range, &color);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}