#pragma once

class GameScene;
class Back :public KdGameObject {
public:
	Back() { Init(); };
	~Back() {};
	void Init() override;
	void DrawUnLit() override;
	void Update() override;

	void SetOwner(GameScene* owner) { m_gowner = owner; }
private:
	GameScene* m_gowner = nullptr;
	std::shared_ptr<KdModelData> m_model;
};