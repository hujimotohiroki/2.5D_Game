#pragma once
class GameScene;
class BlackBoard :public KdGameObject {
public:
	BlackBoard() { Init(); };
	~BlackBoard() {};
	void DrawSprite() override;
	void Setalpha(float m_alpha) { alpha = m_alpha; }
	void SetOwner(GameScene* owner) { m_owner = owner; }
private:
	GameScene* m_owner = nullptr;
	float alpha = 0.0f;
};