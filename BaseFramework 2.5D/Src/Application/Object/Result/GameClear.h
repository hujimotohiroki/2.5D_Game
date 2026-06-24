#pragma once
class GameScene;
class GameClear :public KdGameObject {
public:
	GameClear() { Init(); };
	~GameClear() {};
	void Init() override;
	void DrawUnLit() override;
	void SetOwner(GameScene* owner) { m_owner = owner; }
	void SetCrystal(int crystal) { rank = crystal; }
private:
	GameScene* m_owner=nullptr;
	int rank;
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
};