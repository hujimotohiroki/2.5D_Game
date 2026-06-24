#include "BlackBoard.h"
#include "../../Scene/GameScene/GameScene.h"
void BlackBoard::DrawSprite()
{
	if (m_owner != nullptr) {
		if (m_owner->GetTimer() < 0) {
			alpha -= 0.016f;
			if (alpha < 0)m_isExpired=true;
		}
	}
	alpha += 0.01f;
	DirectX::SimpleMath::Color color = {0.0f,0.0f,0.0f,alpha};//4つめの数値を変化させる
	KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);
}
