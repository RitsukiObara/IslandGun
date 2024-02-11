//===================================
//
// ボスのかまいたち状態ヘッダー[boss_windstate.h]
// Author 小原立暉
//
//===================================
#ifndef _BOSS_WIND_STATE_H_
#define _BOSS_WIND_STATE_H_
//***********************************
// インクルードファイル
//***********************************
#include "boss_state.h"

// クラス定義(ボスのかまいたち状態クラス)
class CBossWindState : public CBossState
{
public:

	// 行動状況
	enum ACTION
	{
		ACTION_MOVE = 0,	// 移動行動
		ACTION_POSITION,	// 位置につく行動
		ACTION_WIND,		// かまいたち行動
		ACTION_MAX			// この列挙型の総数
	};

	CBossWindState();		// コンストラクタ
	~CBossWindState();		// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

	// メンバ関数
	void Chase(CBoss* pBoss);		// 追跡処理
	void Move(CBoss* pBoss);		// 移動処理
	void Position(CBoss* pBoss);	// 定位置到着処理
	void Wind(CBoss* pBoss);		// 風処理

	// メンバ変数
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;	// 目的の向き
	ACTION m_action;		// 行動状況
	int m_nCount;			// 経過カウント
};

#endif