//============================================
//
// コンティニューUI処理[continueUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "continueUI.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "useful.h"

#include "object2D.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "game_score.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const char* TEXTURE[CContinueUI::TYPE_MAX] =			// テクスチャ
	{
		nullptr,
		"data\\TEXTURE\\ContGround.png",
		"data\\TEXTURE\\ContQuery.png",
		"data\\TEXTURE\\ContYes.png",
		"data\\TEXTURE\\ContNo.png",
	};
	const D3DXVECTOR3 POS[CContinueUI::TYPE_MAX] =			// 位置
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f),
		D3DXVECTOR3(390.0f,450.0f,0.0f),
		D3DXVECTOR3(890.0f,450.0f,0.0f),
	};
	const D3DXVECTOR3 POLY_SIZE[CContinueUI::TYPE_MAX] =	// サイズ
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(550.0f,330.0f,0.0f),
		D3DXVECTOR3(500.0f,80.0f,0.0f),
		D3DXVECTOR3(160.0f,80.0f,0.0f),
		D3DXVECTOR3(160.0f,80.0f,0.0f),
	};
	const D3DXCOLOR SCREEN_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);		// 背景の色
	const int CONTINUE_LIFE = 100;			// コンティニューしたときの体力
}

//========================
// コンストラクタ
//========================
CContinueUI::CContinueUI() : CObject(TYPE_CONTINUEUI, DIM_2D, PRIORITY_UI)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;		// ポリゴンの情報
	}
	m_select = SELECT_YES;		// 選択肢
}

//========================
// デストラクタ
//========================
CContinueUI::~CContinueUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CContinueUI::Init(void)
{
	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CContinueUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // ポリゴンの情報が NULL じゃない場合

			// ポリゴンの終了処理
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// 数字の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CContinueUI::Update(void)
{
	if (Decide() == true)
	{ // 決定した場合

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}
}

//========================
// 描画処理
//========================
void CContinueUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // ポリゴンが NULL じゃない場合

			// 描画処理
			m_apObject[nCnt]->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CContinueUI::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // ポリゴンが NULL じゃない場合

			// ポリゴンを生成
			m_apObject[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// 設定処理
			m_apObject[nCnt]->SetPos(POS[nCnt]);			// 位置
			m_apObject[nCnt]->SetPosOld(POS[nCnt]);			// 前回の位置
			m_apObject[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apObject[nCnt]->SetSize(POLY_SIZE[nCnt]);		// サイズ
			m_apObject[nCnt]->SetAngle();					// 方向
			m_apObject[nCnt]->SetLength();					// 長さ

			// テクスチャの割り当て処理
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[nCnt]));

			// 頂点座標の設定処理
			m_apObject[nCnt]->SetVertex();

			if (nCnt == TYPE::TYPE_SCREEN)
			{ // 背景の場合

				// 色を設定する
				m_apObject[nCnt]->SetVtxColor(SCREEN_COL);
			}
		}
	}
	m_select = SELECT_YES;		// 選択肢
}

//========================
// 生成処理
//========================
CContinueUI* CContinueUI::Create(void)
{
	// ローカルオブジェクトを生成
	CContinueUI* pUI = nullptr;			// UIのインスタンスを生成

	if (pUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pUI = new CContinueUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pUI->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// UIのポインタを返す
	return pUI;
}

//========================
// 決定処理
//========================
bool CContinueUI::Decide(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // 決定キーを押した場合

		switch (m_select)
		{
		case CContinueUI::SELECT_YES:

			// コンティニュー処理
			Continue();

			break;


		case CContinueUI::SELECT_NO:


			break;

		default:

			// 停止処理
			assert(false);

			break;
		}

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//========================
// コンティニュー処理
//========================
void CContinueUI::Continue(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();		// プレイヤーの情報
	CGameScore* pScore = CGame::GetGameScore();	// ゲームスコアの情報

	if (pPlayer != nullptr)
	{ // プレイヤーが NULL じゃない場合

		// 体力を設定する
		pPlayer->SetLife(CONTINUE_LIFE);

		// プレイヤーを無敵状態に設定
		CPlayer::SState state = pPlayer->GetState();
		state.state = CPlayer::STATE_INVINSIBLE;
		pPlayer->SetState(state);

		// プレイモードにする
		CGame::SetState(CGame::STATE_PLAY);

		// 通常カメラにする
		CManager::Get()->GetCamera()->SetType(CCamera::TYPE_NONE);

		// スコアを減らす
		pScore->SetScore(pScore->GetScore() - 200);
	}
}