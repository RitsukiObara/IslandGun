//================================================================================================================
//
// ボスの雄たけび状態処理 [boss_howlingstate.cpp]
// Author：小原立暉
//
//================================================================================================================
//****************************************************************************************************************
//	インクルードファイル
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_howlingstate.h"
#include "motion.h"

#include "manager.h"
#include "camera.h"

#include "boss_nonestate.h"

//----------------------------------------------------------------------------------------------------------------
// 無名名前空間
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const int HOWLING_COUNT = 50;				// 雄たけびまでのカウント
	const int HOWLING_CAMERA_COUNT = 63;		// 雄たけびカメラまでのカウント
	const int NONESTATE_COUNT = 240;			// 通常状態までのカウント
}

//==========================
// コンストラクタ
//==========================
CBossHowlingState::CBossHowlingState()
{
	// 全ての値をクリアする
	m_nCount = 0;		// 経過カウント
}

//==========================
// デストラクタ
//==========================
CBossHowlingState::~CBossHowlingState()
{

}

//==========================
// 状態処理
//==========================
void CBossHowlingState::Process(CBoss* pBoss)
{
	// 経過カウントを加算する
	m_nCount++;

	if (m_nCount >= HOWLING_COUNT)
	{ // 一定時間経過した場合

		if (pBoss->GetMotion()->GetType() != CBoss::MOTIONTYPE_HOWLING)
		{ // 雄たけびモーションじゃない場合

			// 雄たけびモーションを設定する
			pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_HOWLING);
		}
	}

	if (m_nCount >= HOWLING_CAMERA_COUNT)
	{ // 一定時間経過した場合

		if (CManager::Get()->GetCamera()->GetType() != CCamera::TYPE_BOSSHOWLING)
		{ // 雄たけび状態以外の場合

			// 雄たけびカメラにする
			CManager::Get()->GetCamera()->SetType(CCamera::TYPE_BOSSHOWLING);
		}
	}

	if (m_nCount >= NONESTATE_COUNT)
	{ // 一定時間経過した場合

		// 通常状態にする
		pBoss->ChangeState(new CBossNoneState);

		// この先の処理を行わない
		return;
	}
}

//==========================
// 情報の設定処理
//==========================
void CBossHowlingState::SetData(CBoss* pBoss)
{
	// 全ての値を設定する
	m_nCount = 0;		// 経過カウント

	// ホバリングモーションを設定する
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_LANDING);

	// 振動カメラにする
	CManager::Get()->GetCamera()->SetType(CCamera::TYPE_VIBRATE);
}