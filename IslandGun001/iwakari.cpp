//============================================================
//
// イワカリ処理 [iwakari.cpp]
// Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "iwakari.h"
#include "motion.h"
#include "manager.h"
#include "useful.h"

#include "iwakari_shell.h"

#include "game.h"
#include "player.h"

//------------------------------------------------------------
// 無名名前空間
//------------------------------------------------------------
namespace
{
	const float SPEED = 3.0f;			// 移動量
	const float MOVE_LENGTH = 900.0f;	// 追跡する距離
}

//================================
// コンストラクタ
//================================
CIwakari::CIwakari() : CEnemy()
{
	// 全ての値をクリアする
	m_pShell = nullptr;				// 殻の情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_state = STATE_NONE;			// 状態
}

//================================
// デストラクタ
//================================
CIwakari::~CIwakari()
{

}

//================================
// 初期化処理
//================================
HRESULT CIwakari::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// モデルの総数を設定
	SetNumModel(CMotion::GetNumModel(CMotion::STYLE_IWAKARI));

	// データの設定処理
	CCharacter::SetData();

	if (GetMotion() == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		CreateMotion();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (GetMotion() != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		GetMotion()->SetInfo(CMotion::STYLE_IWAKARI, GetHierarchy(), GetNumModel());
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	// 値を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CIwakari::Uninit(void)
{
	if (m_pShell != nullptr)
	{ // 殻の情報が NULL じゃない場合

		// 殻の終了処理
		m_pShell->Uninit();
		m_pShell = nullptr;
	}

	// 終了処理
	CEnemy::Uninit();
}

//================================
// 更新処理
//================================
void CIwakari::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 追跡処理
	Chase();

	switch (m_state)
	{
	case CIwakari::STATE_NONE:		// 通常状態



		break;

	case CIwakari::STATE_MOVE:		// 移動状態

		// 向きの移動処理
		RotMove();

		// 移動処理
		Move();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 更新処理
	CEnemy::Update();

	if (m_pShell != nullptr)
	{ // 殻が NULL じゃない場合

		// 殻の位置と向きを設定する
		m_pShell->SetPos(GetPos());
		m_pShell->SetRot(GetRot());
	}
}

//================================
// 描画処理
//================================
void CIwakari::Draw(void)
{
	// 描画処理
	CEnemy::Draw();

	if (m_pShell != nullptr)
	{ // 殻が NULL じゃない場合

		// 殻の描画処理
		m_pShell->Draw();
	}
}

//================================
// 情報の設定処理
//================================
void CIwakari::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CEnemy::SetData(pos, rot, type);

	// 全ての値を設定する
	m_pShell = CIwakariShell::Create(pos, rot);		// 殻の情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_state = STATE_NONE;			// 状態

	// モーションのリセット処理
	GetMotion()->ResetMotion(MOTIONTYPE_NEUTRAL);
}

//===========================================
// ヒット処理
//===========================================
void CIwakari::Hit(const D3DXVECTOR3& pos)
{
	// ヒット処理
	CEnemy::Hit(pos);

	if (m_pShell != nullptr)
	{ // 殻が NULL じゃない場合

		// 殻の種類を変える
		m_pShell->SetType(TYPE_SHELL);

		// 殻を NULL にする
		m_pShell = nullptr;
	}
}

//===========================================
// 追跡処理
//===========================================
void CIwakari::Chase(void)
{
	D3DXVECTOR3 pos;							// 敵の位置
	D3DXVECTOR3 posPlayer;						// プレイヤーの位置
	int motiontype = GetMotion()->GetType();	// モーションの種類
	float fRot = 0.0f;							// 向き
	float fLength = 0.0f;						// 長さ

	if (CGame::GetPlayer() != nullptr)
	{ // プレイヤーが存在した場合

		pos = GetPos();									// 位置を取得する
		posPlayer = CGame::GetPlayer()->GetPos();		// プレイヤーの位置を取得する

		// 長さを設定する
		fLength = sqrtf((posPlayer.x - pos.x) * (posPlayer.x - pos.x) + (posPlayer.z - pos.z) * (posPlayer.z - pos.z));

		if (fLength <= MOVE_LENGTH)
		{ // 長さが一定以下になった場合

			// 向きを算出する
			fRot = atan2f((posPlayer.x - pos.x), (posPlayer.z - pos.z));

			// 移動量を設定する
			m_move.x = sinf(fRot) * SPEED;
			m_move.z = cosf(fRot) * SPEED;

			// 目標の向きを設定する
			m_rotDest.y = fRot;

			// 移動状態にする
			m_state = STATE_MOVE;

			if (motiontype != MOTIONTYPE_MOVE)
			{ // 移動モーション以外の場合

				// 移動モーションにする
				GetMotion()->Set(MOTIONTYPE_MOVE);
			}
		}
		else
		{ // 上記以外

			// 通常状態にする
			m_state = STATE_NONE;

			if (motiontype != MOTIONTYPE_NEUTRAL)
			{ // 待機モーション以外の場合

				// 待機モーションにする
				GetMotion()->Set(MOTIONTYPE_NEUTRAL);
			}
		}
	}
	else
	{ // 上記以外

		// 通常状態にする
		m_state = STATE_NONE;

		if (motiontype != MOTIONTYPE_NEUTRAL)
		{ // 待機モーション以外の場合

			// 待機モーションにする
			GetMotion()->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//===========================================
// 移動処理
//===========================================
void CIwakari::Move(void)
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
void CIwakari::RotMove(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.y, &rot.y, 0.1f);

	// 向きを適用する
	SetRot(rot);
}