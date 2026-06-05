#pragma once
class Bike :public KdGameObject {
public:
	Bike() {};
	~Bike() override {};
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	//座標
	Math::Vector3 m_pos;
	//方向(ベクトルの向き)
	Math::Vector3 m_rot;
	//移動量
	float speed;
	//重力
	float m_gravity = 0.0f;
};