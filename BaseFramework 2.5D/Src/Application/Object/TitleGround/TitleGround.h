#pragma once

class TitleScene;
class TitleGround : public KdGameObject {
public:
	TitleGround() {};
	~TitleGround() override {};

	void Init()override;
	void DrawLit()override;
	void Update()override;

	void SetOwner(TitleScene* owner) { m_towner = owner; }
private:
	TitleScene* m_towner = nullptr;
	std::shared_ptr<KdModelData> m_model;
};