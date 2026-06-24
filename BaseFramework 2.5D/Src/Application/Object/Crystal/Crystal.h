#pragma once

class GameScene;
class TitleScene;

class Crystal : public KdGameObject {
public:
	Crystal() {};
	~Crystal() override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void OnHit();
	void SetOwner(GameScene* owner) { m_gowner = owner; }
	void SetOwner(TitleScene* owner) { m_towner = owner; }
	void SetPos(const Math::Vector3& pos) override{ m_pos = pos; }
private:
	GameScene* m_gowner=nullptr;
	TitleScene* m_towner=nullptr;
	float m_gravity = 0.003f;
	std::shared_ptr<KdModelData> m_model;
	int timer;
	float rotx;
	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
};