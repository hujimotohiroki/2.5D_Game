#pragma once
class GameScene;
class Rank :public KdGameObject {
public:
	Rank() { Init(); };
	~Rank() {};
	void Init() override;
	void DrawUnLit() override;
	void SetOwner(GameScene* owner) { m_owner = owner; }
	void SetCrystal(int crystal) { rank = crystal; }
private:
	GameScene* m_owner=nullptr;
	bool modelflg = false;
	int rank=0;
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
};