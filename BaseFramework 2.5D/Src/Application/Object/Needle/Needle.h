#pragma once
class GameScene;
class Needle :public KdGameObject {
public:
	Needle() { Init(); };
	~Needle() {};
	void Init() override;
	void DrawUnLit() override;
	void SetOwner(GameScene* owner) { m_owner = owner; }
private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;
	GameScene* m_owner = nullptr;
	KdTexture clocktex;
	KdTexture needletex;
};