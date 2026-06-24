#pragma once
class GameScene;
class TimeOver :public KdGameObject {
public:
	TimeOver() { Init(); };
	~TimeOver() {};
	void Init() override;
	void DrawUnLit() override;
	void SetOwner(GameScene* owner) { m_owner=owner; }
private:
	GameScene* m_owner=nullptr;
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
};