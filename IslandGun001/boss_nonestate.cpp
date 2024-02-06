//================================================================================================================
//
// ボスの通常状態処理 [boss_nonestate.cpp]
// Author：小原立暉
//
//================================================================================================================
//****************************************************************************************************************
//	インクルードファイル
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_nonestate.h"
#include "motion.h"

#include "game.h"
#include "player.h"

#include "boss_flystate.h"

//----------------------------------------------------------------------------------------------------------------
// 無名名前空間
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const int STATECHANGE_COUNT = 90;		// 状態が変化するカウント数
}

//==========================
// コンストラクタ
//==========================
CBossNoneState::CBossNoneState()
{
	// 全ての値をクリアする
	m_nCount = 0;			// 経過カウント
}

//==========================
// デストラクタ
//==========================
CBossNoneState::~CBossNoneState()
{

}

//==========================
// 状態処理
//==========================
void CBossNoneState::Process(CBoss* pBoss)
{
	// 経過カウントを加算する
	m_nCount++;

	// 起伏地面の当たり判定
	pBoss->ElevationCollision();

	if (m_nCount >= STATECHANGE_COUNT)
	{ // 一定時間経過した場合

		// 飛行状態にする
		pBoss->ChangeState(new CBossFlyState);

		// この先の処理を行わない
		return;
	}
}

//==========================
// 情報の設定処理
//==========================
void CBossNoneState::SetData(CBoss* pBoss)
{
	// 全ての値を設定する
	m_nCount = 0;			// 経過カウント

	// 待機モーションを設定する
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_NEUTRAL);
}