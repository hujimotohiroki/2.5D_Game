#pragma once
class GameScene;
class TitleScene;
class Bike :public KdGameObject {
public:
	Bike() {};
	~Bike() override {};
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;


	void SetOwner(GameScene* owner) { m_gowner = owner; }
	void SetOwner(TitleScene* owner) { m_towner = owner; }
	void SetPos(const Math::Vector3& pos) override { m_pos = pos; }
	int GetPaper() { return paper; }
private:
	GameScene* m_gowner=nullptr;
	TitleScene* m_towner=nullptr;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	//座標
	//バイク自体の座標
	Math::Vector3 m_pos;
	
	//方向(ベクトルの向き)
	Math::Vector3 m_dir;
	
	
	//回転
	Math::Vector3 m_rot;
	//前のタイヤ
	Math::Vector3 m_Frontpos;
	Math::Vector3 m_Frontdir;
	//後ろのタイヤ
	Math::Vector3 m_Rearpos;
	Math::Vector3 m_Reardir;
	//移動量
	float speed;
	//重力
	float m_Frontgravity;//前のタイヤ
	float m_Reargravity;//後ろのタイヤ
	const float gravityacc = 0.002f;
	float AnimCnt = 0.0f;
	float BikeRadius = 0.35f;//画像の半径
	int paper;
	bool engineflg;

	float m_Dissolve = 0.0f;
	bool m_OutroFlg = false;
};