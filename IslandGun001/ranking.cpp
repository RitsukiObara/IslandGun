//=======================================
//
// ランキングのメイン処理[Ranking.cpp]
// Author 小原立暉
//
//=======================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ranking.h"
#include "file.h"
#include "input.h"
#include "Fade.h"

#include "Objectmesh.h"
#include "game.h"
#include "objectElevation.h"
#include "skybox.h"
#include "ocean.h"
#include "ranking_rank.h"
#include "ranking_table.h"

//---------------------------------------
// 定数定義
//---------------------------------------
namespace
{
	const char* ELEVATION_TXT = "data/TXT/Elevation.txt";		// 起伏地面のテキスト
	const int SET_TITLE_TIMER = 300;		// タイトル画面に行く秒数
}

//==========================================
// コンストラクタ
//==========================================
CRanking::CRanking()
{
	// 全ての値をクリアする
	m_nTransCount = 0;			// 自動遷移カウント
}

//==========================================
// デストラクタ
//==========================================
CRanking::~CRanking()
{

}

//==========================================
// ランキングの初期化処理
//==========================================
HRESULT CRanking::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// カメラのリセット処理
	CManager::Get()->GetCamera()->Reset();

	// テキスト読み込み処理
	CElevation::TxtSet(ELEVATION_TXT);

	// マップの生成
	CManager::Get()->GetFile()->SetTree();
	CManager::Get()->GetFile()->SetRock();
	CManager::Get()->GetFile()->SetBlock();
	CManager::Get()->GetFile()->SetBangFlower();
	CManager::Get()->GetFile()->SetWall();

	// テキスト読み込み処理
	CMesh::TxtSet();

	// スカイボックスの生成処理
	CSkyBox::Create();

	// 海の生成
	COcean::Create();

	// 順位UIの生成
	CRankUI::Create();

	// ランキングの生成
	CRankingTable::Create();

	// 全ての値を初期化する
	m_nTransCount = 0;			// 自動遷移カウント

	// 成功を返す
	return S_OK;
}

//========================================
// スコアの終了処理
//========================================
void CRanking::Uninit(void)
{
	// 終了処理
	CScene::Uninit();
}

//======================================
//ランキングの更新処理
//======================================
void CRanking::Update(void)
{
	// 自動遷移カウントを加算する
	m_nTransCount++;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		m_nTransCount % SET_TITLE_TIMER == 0)
	{ // ENTERキーを押したまたは、カウントが一定数に達した場合

		// タイトルに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// 更新処理
		CManager::Get()->GetRenderer()->Update();
	}
}

//=====================================
//スコアの描画処理
//=====================================
void CRanking::Draw(void)
{

}