//==================================================================
//
// ボスの爆破状態処理 [boss_explosionstate.cpp]
// Author：小原立暉
//
//==================================================================
//******************************************************************
//	インクルードファイル
//******************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_explosionstate.h"
#include "manager.h"
#include "motion.h"

#include "game.h"
#include "boss_ripple.h"

//------------------------------------------------------------------
// 定数定義
//------------------------------------------------------------------
namespace
{
	const int FINISH_COUNT = 100;		// 終了カウント
}

//==========================
// コンストラクタ
//==========================
CBossExplosionState::CBossExplosionState()
{
	// 全ての値をクリアする
	m_nCount = 0;		// カウント
}

//==========================
// デストラクタ
//==========================
CBossExplosionState::~CBossExplosionState()
{

}

//==========================
// 状態の設定処理
//==========================
void CBossExplosionState::Process(CBoss* pBoss)
{
	// カウントを加算する
	m_nCount++;

	if (m_nCount >= FINISH_COUNT)
	{ // 一定時間経過の場合

		// ボスの爆破波紋を生成
		CBossRipple::Create(pBoss->GetPos());

		// 終了状態にする
		CGame::SetState(CGame::STATE_FINISH);
	}
}

//==========================
// 情報の設定処理
//==========================
void CBossExplosionState::SetData(CBoss* pBoss)
{
	// 全ての値を設定する
	m_nCount = 0;		// カウント
}