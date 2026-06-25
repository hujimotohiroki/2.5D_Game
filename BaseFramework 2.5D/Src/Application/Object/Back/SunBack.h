#pragma once

class SunBack :public KdGameObject {
public:
	SunBack() { Init(); };
	~SunBack() {};
	void Init() override;
	void DrawUnLit() override;
private:
	std::shared_ptr<KdModelData> m_model;
};