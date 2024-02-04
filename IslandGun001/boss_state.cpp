//================================================================================================================
//
// ボスの状態処理 [boss_state.cpp]
// Author：小原立暉
//
//================================================================================================================
//****************************************************************************************************************
//	インクルードファイル
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_state.h"
#include "motion.h"

#include "game.h"
#include "player.h"
#include "ripple.h"

//----------------------------------------------------------------------------------------------------------------
// 無名名前空間
//----------------------------------------------------------------------------------------------------------------
namespace
{
	// 登場状態関係
	const float APPEAR_LENGTH = 8000.0f;		// 距離
	const float APPEAR_HEIGHT = 2000.0f;		// 初期高度
	const float APPEAR_SLOPE = -0.9f;			// 傾き
	const float APPEAR_ADD_ROT = 0.05f;			// 向きの追加量
	const float APPEAR_SUB_LENGTH = 20.0f;		// 距離の減算量
	const float APPEAR_SUB_HEIGHT = 5.0f;		// 高度の減算量
	const float APPEAR_SUB_SLOPE = 0.00225f;	// 傾きの減算量
	const int APPEAR_RIPPLE_FREQ = 6;			// 波紋の出る頻度
	const float APPEAR_RIPPLE_HEIGHT = 600.0f;	// 波紋の高度
	const D3DXVECTOR3 RIPPLE_SCALE = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	// 波紋の拡大率

	// 向き直り状態関係
	const float TURN_ROT_CORRECT = 0.08f;		// 向きの補正倍率
	const int TURN_COUNT = 140;					// 向き直り状態のカウント数
}

//----------------------------------------------------------------------------------------------------------------
// 基本クラス
//----------------------------------------------------------------------------------------------------------------
//==========================
// コンストラクタ
//==========================
CBossState::CBossState()
{

}

//==========================
// デストラクタ
//==========================
CBossState::~CBossState()
{

}

//==========================
// 終了処理
//==========================
void CBossState::Uninit()
{
	// 自身を削除する
	delete this;
}

//----------------------------------------------------------------------------------------------------------------
// 飛行状態
//----------------------------------------------------------------------------------------------------------------
//==========================
// コンストラクタ
//==========================
CBossAppearState::CBossAppearState()
{
	// 全ての値をクリアする
	m_fLangeRot = 0.0f;			// 離れる向き
	m_fLength = APPEAR_LENGTH;	// 距離
	m_fHeight = APPEAR_HEIGHT;	// 高度
}

//==========================
// デストラクタ
//==========================
CBossAppearState::~CBossAppearState()
{

}

//==========================
// 状態の設定処理
//==========================
void CBossAppearState::Process(CBoss* pBoss)
{
	// カウントを加算する
	m_nCount++;

	// 距離関係処理
	Length();

	if (m_fLength <= 0.0f)
	{ // 長さが 0.0f 以下になった場合

		// 位置を適用する
		pBoss->SetPos(NONE_D3DXVECTOR3);

		// 向き直り状態にする
		pBoss->ChangeState(new CBossTurnState());

		// この先の処理を行わない
		return;
	}

	// 位置向き設定処理
	PosRot(pBoss);

	// 波紋の設置処理
	Ripple(pBoss);
}

//==========================
// 情報の設定処理
//==========================
void CBossAppearState::SetData(CBoss* pBoss)
{
	// 全ての値を設定する
	m_fLangeRot = 0.0f;			// 離れる向き
	m_fLength = APPEAR_LENGTH;	// 距離
	m_fHeight = APPEAR_HEIGHT;	// 高度

	// 位置と向きを取得する
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// 位置を設定する
	pos.x = sinf(m_fLangeRot) * m_fLength;
	pos.y = m_fHeight;
	pos.z = cosf(m_fLangeRot) * m_fLength;

	// 向きを設定する
	rot.y = m_fLangeRot + (D3DX_PI * 0.5f);
	rot.z = APPEAR_SLOPE;

	// 位置と向きを適用する
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// 距離関係処理
//==========================
void CBossAppearState::Length(void)
{
	// 向きを加算する
	m_fLangeRot += APPEAR_ADD_ROT;

	// 向きの正規化
	useful::RotNormalize(&m_fLangeRot);

	// 距離を減算する
	m_fLength -= APPEAR_SUB_LENGTH;

	// 高度を減算する
	m_fHeight -= APPEAR_SUB_HEIGHT;
}

//==========================
// 位置向き設定処理
//==========================
void CBossAppearState::PosRot(CBoss* pBoss)
{
	// 位置と向きを取得する
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// 位置を設定する
	pos.x = sinf(m_fLangeRot) * m_fLength;
	pos.y = m_fHeight;
	pos.z = cosf(m_fLangeRot) * m_fLength;

	// 向きを設定する
	rot.y = m_fLangeRot + (D3DX_PI * 0.5f);
	rot.z += APPEAR_SUB_SLOPE;

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	// 位置と向きを適用する
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// 波紋の設置処理
//==========================
void CBossAppearState::Ripple(CBoss* pBoss)
{
	if (m_nCount % APPEAR_RIPPLE_FREQ == 0)
	{ // 一定カウントごとに

		// 位置と向きを取得する
		D3DXVECTOR3 pos = pBoss->GetPos();
		D3DXVECTOR3 rot = pBoss->GetRot();

		// 波紋の生成処理
		CRipple::Create
		(
			D3DXVECTOR3(pos.x, pos.y + APPEAR_RIPPLE_HEIGHT, pos.z),
			D3DXVECTOR3(D3DX_PI * 0.5f, rot.y, D3DX_PI),
			RIPPLE_SCALE
		);
	}
}

//----------------------------------------------------------------------------------------------------------------
// 向き直り状態
//----------------------------------------------------------------------------------------------------------------
//==========================
// コンストラクタ
//==========================
CBossTurnState::CBossTurnState()
{
	// 全ての値をクリアする
	m_nCount = 0;		// 経過カウント
}

//==========================
// デストラクタ
//==========================
CBossTurnState::~CBossTurnState()
{

}

//==========================
// 状態処理
//==========================
void CBossTurnState::Process(CBoss* pBoss)
{
	// プレイヤーの情報を取得する
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer != nullptr)
	{ // プレイヤーが NULL じゃない場合

		// カウントを加算する
		m_nCount++;

		// 向きを取得する
		D3DXVECTOR3 rot = pBoss->GetRot();
		D3DXVECTOR3 pos = pBoss->GetPos();
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
		float fRotDest = atan2f(posPlayer.x - pos.x, posPlayer.z - pos.z);

		// 向きの補正処理
		useful::RotCorrect(fRotDest, &rot.y, TURN_ROT_CORRECT);

		// 向きの正規化
		useful::RotNormalize(&rot.y);

		// 向きを適用する
		pBoss->SetRot(rot);

		if (m_nCount >= TURN_COUNT)
		{ // 一定数経過した場合

			// 向きを補正する
			rot.y = fRotDest;

			// 向きを適用する
			pBoss->SetRot(rot);

			// 遠吠え状態にする
			pBoss->ChangeState(new CBossHowlingState());

			// この先の処理を行わない
			return;
		}
	}
}

//==========================
// 情報の設定処理
//==========================
void CBossTurnState::SetData(CBoss* pBoss)
{
	// 全ての値を設定する
	m_nCount = 0;		// 経過カウント

	// ホバリングモーションを設定する
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_HOVERING);
}

//----------------------------------------------------------------------------------------------------------------
// 遠吠え状態
//----------------------------------------------------------------------------------------------------------------
//==========================
// コンストラクタ
//==========================
CBossHowlingState::CBossHowlingState()
{

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

}

//==========================
// 情報の設定処理
//==========================
void CBossHowlingState::SetData(CBoss* pBoss)
{

}