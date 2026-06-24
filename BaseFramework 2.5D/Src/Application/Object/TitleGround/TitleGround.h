#pragma once

class TitleGround : public KdGameObject {
public:
	TitleGround() {};
	~TitleGround() override {};

	void Init()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdModelData> m_model;
};