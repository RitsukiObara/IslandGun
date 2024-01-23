//============================================================
//
// タードル処理 [tordle.cpp]
// Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "tordle.h"
#include "motion.h"
#include "manager.h"

#include "game.h"
#include "player.h"
#include "useful.h"

//------------------------------------------------------------
// 無名名前空間
//------------------------------------------------------------
namespace
{
	const float SPEED = 3.0f;			// 移動量
}

//================================
// コンストラクタ
//================================
CTordle::CTordle() : CEnemy()
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_rotDest = NONE_D3DXVECTOR3;		// 目標の向き
}

//================================
// デストラクタ
//================================
CTordle::~CTordle()
{

}

//================================
// 初期化処理
//================================
HRESULT CTordle::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CTordle::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//================================
// 更新処理
//================================
void CTordle::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 追跡処理
	Chase();

	// 向きの移動処理
	RotMove();

	// 移動処理
	Move();

	// 更新処理
	CEnemy::Update();
}

//================================
// 描画処理
//================================
void CTordle::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//================================
// 情報の設定処理
//================================
void CTordle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CEnemy::SetData(pos, rot, type);

	// モーションのリセット処理
	GetMotion()->ResetMotion(MOTIONTYPE_MOVE);

	// 全ての値を設定する
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_rotDest = NONE_D3DXVECTOR3;		// 目標の向き
}

//===========================================
// ヒット処理
//===========================================
void CTordle::Hit(const D3DXVECTOR3& pos)
{
	// ヒット処理
	CEnemy::Hit(pos);
}

//===========================================
// 追跡処理
//===========================================
void CTordle::Chase(void)
{
	D3DXVECTOR3 pos;						// 敵の位置
	D3DXVECTOR3 posPlayer;					// プレイヤーの位置
	float fRot = 0.0f;						// 向き

	if (CGame::GetPlayer() != nullptr)
	{ // プレイヤーが存在した場合

		pos = GetPos();									// 位置を取得する
		posPlayer = CGame::GetPlayer()->GetPos();		// プレイヤーの位置を取得する

		// 向きを算出する
		fRot = atan2f((posPlayer.x - pos.x), (posPlayer.z - pos.z));

		// 移動量を設定する
		m_move.x = sinf(fRot) * SPEED;
		m_move.z = cosf(fRot) * SPEED;

		// 目標の向きを設定する
		m_rotDest.y = fRot;
	}
}

//===========================================
// 移動処理
//===========================================
void CTordle::Move(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動する
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 位置を適用する
	SetPos(pos);
}

//===========================================
// 向きの移動処理
//===========================================
void CTordle::RotMove(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.y, &rot.y, 0.1f);

	// 向きを適用する
	SetRot(rot);
}