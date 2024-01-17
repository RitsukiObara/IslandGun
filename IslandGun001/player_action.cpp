//===========================================
//
// プレイヤーの行動のメイン処理[player_action.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "player_action.h"
#include "renderer.h"

#include "player.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const float DODGE_SPEED = 80.0f;		// 回避状態の速度
	const int DODGE_COUNT = 3;				// 回避状態のカウント数
}

//=========================
// コンストラクタ
//=========================
CPlayerAction::CPlayerAction()
{
	// 全ての値をクリアする
	m_action = ACTION_NONE;		// 行動
	m_nActionCount = 0;			// 行動カウント
	m_fDodgeRot = 0.0f;			// 回避する向き
}

//=========================
// デストラクタ
//=========================
CPlayerAction::~CPlayerAction()
{

}

//=========================
// ライトの初期化処理
//=========================
HRESULT CPlayerAction::Init(void)
{
	// 全ての値を初期化する
	m_action = ACTION_NONE;		// 行動
	m_nActionCount = 0;			// 行動カウント
	m_fDodgeRot = 0.0f;			// 回避する向き

	// 成功を返す
	return S_OK;
}

//=========================
// ライトの終了処理
//=========================
void CPlayerAction::Uninit(void)
{
	// 自身を消去する
	delete this;
}

//=========================
// ライトの更新処理
//=========================
void CPlayerAction::Update(CPlayer* pPlayer)
{
	switch (m_action)
	{
	case CPlayerAction::ACTION_NONE:	// 通常状態

		// 通常状態処理
		NoneProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SHOT:	// 射撃状態

		// 射撃状態
		ShotProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_DAGGER:	// ダガー状態

		// ダガー状態処理
		DaggerPrecess(pPlayer);

		break;

	case CPlayerAction::ACTION_DODGE:	// 回避状態

		// 回避状態処理
		DodgeProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SHOTGUN:	// 散弾(J+銃)状態

		// 散弾状態処理
		ShotgunProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SWOOP:	// 急降下(J+ダガー)状態

		// 急降下状態処理
		SwoopProcess(pPlayer);

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=========================
// 生成処理
//=========================
CPlayerAction* CPlayerAction::Create(void)
{
	// ローカルオブジェクトを生成
	CPlayerAction* pAction = nullptr;		// 行動のインスタンスを生成

	if (pAction == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pAction = new CPlayerAction;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAction != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAction->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 行動のポインタを返す
	return pAction;
}

//=========================
// 行動の設定処理
//=========================
void CPlayerAction::SetAction(const ACTION action)
{
	// 行動を設定する
	m_action = action;

	// 行動カウントをリセットする
	m_nActionCount = 0;
}

//=========================
// 行動の取得処理
//=========================
CPlayerAction::ACTION CPlayerAction::GetAction(void) const
{
	// 行動を返す
	return m_action;
}

//=========================
// 回避する向きの設定処理
//=========================
void CPlayerAction::SetDodgeRot(const float fRot)
{
	// 回避する向きを設定する
	m_fDodgeRot = fRot;
}

//=========================
// 通常状態処理
//=========================
void CPlayerAction::NoneProcess(CPlayer* pPlayer)
{

}

//=========================
// 射撃状態処理
//=========================
void CPlayerAction::ShotProcess(CPlayer* pPlayer)
{
	// 向きを取得する
	D3DXVECTOR3 rotDest = pPlayer->GetRotDest();
	D3DXVECTOR3 rotCamera = CManager::Get()->GetCamera()->GetRot();

	// カメラの向きを同じ向きを揃える
	rotDest.y = rotCamera.y;

	// 向きを適用する
	pPlayer->SetRotDest(rotDest);

	// 腕を真っ直ぐ伸ばす
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERRIGHTARM - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERLEFTARM - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERRIGHTUPPER - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERLEFTUPPER - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================
// ダガー状態処理
//=========================
void CPlayerAction::DaggerPrecess(CPlayer* pPlayer)
{

}

//=========================
// 回避状態処理
//=========================
void CPlayerAction::DodgeProcess(CPlayer* pPlayer)
{
	// 位置を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();

	pos.x += sinf(m_fDodgeRot) * DODGE_SPEED;
	pos.z += cosf(m_fDodgeRot) * DODGE_SPEED;

	// 位置を適用する
	pPlayer->SetPos(pos);

	// 行動カウントを加算する
	m_nActionCount++;

	if (m_nActionCount >= DODGE_COUNT)
	{ // 行動カウントが一定数以上になった場合

		// 行動を設定する
		SetAction(ACTION_NONE);
	}
}

//=========================
// 散弾(J+銃)状態
//=========================
void CPlayerAction::ShotgunProcess(CPlayer* pPlayer)
{

}

//=========================
// 急降下状態処理
//=========================
void CPlayerAction::SwoopProcess(CPlayer* pPlayer)
{

}