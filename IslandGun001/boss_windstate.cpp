//================================================================================================================
//
// ボスのかまいたち状態処理 [boss_windstate.cpp]
// Author：小原立暉
//
//================================================================================================================
//****************************************************************************************************************
//	インクルードファイル
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_windstate.h"
#include "motion.h"

#include "game.h"
#include "player.h"

//----------------------------------------------------------------------------------------------------------------
// 無名名前空間
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const float CHASE_CORRECT = 0.2f;			// 追跡の補正数
	const float MOVE_ROT = D3DX_PI * 0.5f;		// 移動状態の向き
	const float MOVE_DEST_Y = 200.0f;			// 目的の移動量
	const float MOVE_POS_CORRECT = 0.05f;		// 移動状況の位置の補正量
	const float MOVE_ROT_CORRECT = 0.1f;		// 移動状況の向きの補正量
	const float MOVE_CHANGE_POS_Y = 10000.0f;	// 位置に着く状態になる高さ
	const D3DXVECTOR3 POSITION_POS = D3DXVECTOR3(0.0f, 500.0f, 8000.0f);		// 定位置
	const int POSITION_COUNT = 40;				// 定位置に移動するまでのカウント
}

//==========================
// コンストラクタ
//==========================
CBossWindState::CBossWindState()
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_action = ACTION_MOVE;			// 行動状況
	m_nCount = 0;					// 経過カウント
}

//==========================
// デストラクタ
//==========================
CBossWindState::~CBossWindState()
{

}

//==========================
// 状態処理
//==========================
void CBossWindState::Process(CBoss* pBoss)
{
	switch (m_action)
	{
	case CBossWindState::ACTION_MOVE:

		// 移動処理
		Move(pBoss);

		break;

	case CBossWindState::ACTION_POSITION:

		// 定位置到着処理
		Position(pBoss);

		break;

	case CBossWindState::ACTION_WIND:

		// 追跡処理
		Chase(pBoss);

		// かまいたち処理
		Wind(pBoss);

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//==========================
// 情報の設定処理
//==========================
void CBossWindState::SetData(CBoss* pBoss)
{
	// 飛行モーションにする
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_FLY);

	// 目的の向きを設定する
	m_rotDest.x = MOVE_ROT;
}

//==========================
// 追跡処理
//==========================
void CBossWindState::Chase(CBoss* pBoss)
{
	// プレイヤーの情報を取得する
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer != nullptr)
	{ // プレイヤーが NULL じゃない場合

		// 位置と向きを宣言
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
		D3DXVECTOR3 posBoss = pBoss->GetPos();
		D3DXVECTOR3 rotBoss = pBoss->GetRot();
		float fRotDest = atan2f(posPlayer.x - posBoss.x, posPlayer.z - posBoss.z);

		// 向きの補正処理
		useful::RotCorrect(fRotDest, &rotBoss.y, CHASE_CORRECT);

		// 向きを適用する
		pBoss->SetRot(rotBoss);
	}
}

//==========================
// 移動処理
//==========================
void CBossWindState::Move(CBoss* pBoss)
{
	// 位置と向きを取得
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// 移動量をどんどん早くしていく
	useful::Correct(MOVE_DEST_Y, &m_move.y, MOVE_POS_CORRECT);

	// 移動する
	pos.y += m_move.y;

	if (pos.y >= MOVE_CHANGE_POS_Y)
	{ // 一定の高さまで上がった場合

		// ベクトルを算出する
		D3DXVECTOR3 vec = POSITION_POS - pos;

		// 位置を補正する
		pos.y = MOVE_CHANGE_POS_Y;

		// 位置に着く状態にする
		m_action = ACTION_POSITION;

		// 移動量を設定する
		m_move.x = vec.x / POSITION_COUNT;
		m_move.y = vec.y / POSITION_COUNT;
		m_move.z = vec.z / POSITION_COUNT;

		// ベクトルの正規化(向きの設定の為)
		D3DXVec3Normalize(&vec, &vec);

		// 目的の向きを設定する
		m_rotDest.x = vec.y * D3DX_PI;
		m_rotDest.y = atan2f(vec.x, vec.z);
		m_rotDest.z = 0.0f;
	}

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);

	// 位置と向きを適用する
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// 定位置到着処理
//==========================
void CBossWindState::Position(CBoss* pBoss)
{
	// 経過カウントを加算する
	m_nCount++;

	// 位置と向きを取得
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// 移動する
	pos += m_move;

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.y, &rot.y, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.z, &rot.z, MOVE_ROT_CORRECT);

	if (m_nCount >= POSITION_COUNT)
	{ // 経過カウントが一定数になった場合

		// 経過カウントをリセットする
		m_nCount = 0;

		// かまいたち行動にする
		m_action = ACTION_WIND;

		// 位置を定位置にする
		pos = POSITION_POS;

		// 目的の向きを設定する
		m_rotDest = NONE_D3DXVECTOR3;
	}

	// 位置と向きを適用する
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// 風処理
//==========================
void CBossWindState::Wind(CBoss* pBoss)
{
	// 経過カウントを加算する
	m_nCount++;

	// 向きを取得
	D3DXVECTOR3 rot = pBoss->GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.z, &rot.z, MOVE_ROT_CORRECT);

	// 向きを適用する
	pBoss->SetRot(rot);
}