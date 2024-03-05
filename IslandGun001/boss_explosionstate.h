//===================================
//
// ボスの爆破状態ヘッダー[boss_explosionstate.h]
// Author 小原立暉
//
//===================================
#ifndef _BOSS_EXPLOSION_STATE_H_
#define _BOSS_EXPLOSION_STATE_H_

//***********************************
// インクルードファイル
//***********************************
#include "boss_state.h"

// クラス定義(ボスの爆破状態クラス)
class CBossExplosionState : public CBossState
{
public:

	CBossExplosionState();		// コンストラクタ
	~CBossExplosionState();		// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

	// メンバ変数
	int m_nCount;		// カウント
};

#endif