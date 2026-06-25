#pragma once

class Lava : public KdGameObject {
public:
	Lava() {};
	~Lava() override {};

	void Init()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdModelData> m_model;
};