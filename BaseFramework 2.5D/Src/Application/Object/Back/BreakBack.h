#pragma once

class BreakBack :public KdGameObject {
public:
	BreakBack() { Init(); };
	~BreakBack() {};
	void Init() override;
	void DrawUnLit() override;
private:
	std::shared_ptr<KdModelData> m_model;
};