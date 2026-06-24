#pragma once

class GameScene;
class TitleScene;

class Title : public KdGameObject {
public:
	Title() {};
	~Title() override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void SetOwner(GameScene* owner) { m_gowner = owner; }
	void SetOwner(TitleScene* owner) { m_towner = owner; }
	void SetPos(const Math::Vector3& pos) override { m_pos = pos; }
private:
	GameScene* m_gowner = nullptr;
	TitleScene* m_towner = nullptr;
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
};