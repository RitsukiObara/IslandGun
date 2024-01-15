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

//=========================
// コンストラクタ
//=========================
CPlayerAction::CPlayerAction()
{

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