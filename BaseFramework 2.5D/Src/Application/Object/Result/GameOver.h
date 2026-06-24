#pragma once
class GameScene;
class GameOver :public KdGameObject {
public:
	GameOver() { Init(); };
	~GameOver() {};
	void Init() override;
	void DrawUnLit() override;
	void SetOwner(GameScene* owner) { m_owner = owner; }
private:
	GameScene* m_owner=nullptr;
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
};