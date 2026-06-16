#pragma once

class GameScene;

class Paper : public KdGameObject {
public:
	Paper() {};
	~Paper() override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void OnHit();
	void SetOwner(GameScene* owner) { m_owner = owner; }
	void SetPos(const Math::Vector3& pos) override{ m_pos = pos; }
private:
	GameScene* m_owner;
	float m_gravity = 0.003f;
	std::shared_ptr<KdModelData> m_model;
	int timer;
	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
};