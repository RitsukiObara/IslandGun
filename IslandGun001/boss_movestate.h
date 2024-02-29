//===================================
//
// ボスの移動状態ヘッダー[boss_movestate.h]
// Author 小原立暉
//
//===================================
#ifndef _BOSS_MOVE_STATE_H_
#define _BOSS_MOVE_STATE_H_

//***********************************
// インクルードファイル
//***********************************
#include "boss_state.h"

// クラス定義(ボスの移動状態クラス)
class CBossMoveState : public CBossState
{
public:

	CBossMoveState();	// コンストラクタ
	~CBossMoveState();	// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

	// メンバ関数
};

#endif