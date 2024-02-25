//============================================
//
// チュートリアル画面のメイン処理[tutorial.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "fade.h"
#include "renderer.h"

#include "objectElevation.h"
#include "Objectmesh.h"
#include "motion.h"
#include "file.h"
#include "skybox.h"

#include "player_tutorial.h"
#include "balloon_spawner.h"
#include "signboard.h"
#include "door.h"

//--------------------------------------------
// 定数定義
//--------------------------------------------
namespace
{
	const int TRANS_COUNT = 120;			// 遷移までのカウント数
}

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CTutorialPlayer* CTutorial::m_pPlayer = nullptr;		// プレイヤーの情報
CSignboard* CTutorial::m_pLook = nullptr;				// 現在見てる看板
bool CTutorial::m_bExpl = false;						// 説明状況

//=========================================
// コンストラクタ
//=========================================
CTutorial::CTutorial()
{
	// 全ての情報をクリアする
	m_nEndCount = 0;			// 終了までのカウント
	m_pPlayer = nullptr;		// プレイヤーの情報
	m_pLook = nullptr;			// 現在見てる看板
	m_bExpl = false;			// 説明状況
}

//=========================================
// デストラクタ
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CTutorial::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// モーションの読み込み処理
	CMotion::Load(CMotion::STYLE_PLAYER);		// プレイヤー
	CMotion::Load(CMotion::STYLE_TORDLE);		// タードル
	CMotion::Load(CMotion::STYLE_IWAKARI);		// イワカリ
	CMotion::Load(CMotion::STYLE_BOSS);			// ボス

	// マップの生成
	CManager::Get()->GetFile()->SetEnemy();
	CManager::Get()->GetFile()->SetCoin();
	CManager::Get()->GetFile()->SetGoldBone();
	CManager::Get()->GetFile()->SetTree();
	CManager::Get()->GetFile()->SetRock();
	CManager::Get()->GetFile()->SetBlock();
	CManager::Get()->GetFile()->SetBangFlower();
	CManager::Get()->GetFile()->SetWall();

	// テキスト読み込み処理
	CMesh::TxtSet();

	// スカイボックスの生成処理
	CSkyBox::Create();

	// プレイヤーを生成
	m_pPlayer = CTutorialPlayer::Create(NONE_D3DXVECTOR3);

	CBalloonSpawner::Create(D3DXVECTOR3(300.0f, 600.0f, 0.0f));

	CSignboard::Create(D3DXVECTOR3(3000.0f, 50.0f, 3000.0f), NONE_D3DXVECTOR3, CSignboard::TYPE::TYPE_JUMP);

	CDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 400.0f));

	// 全ての値をクリアする
	m_nEndCount = 0;			// 終了までのカウント

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CTutorial::Uninit(void)
{
	// 全ての値をクリアする
	m_pPlayer = nullptr;		// プレイヤーのポインタ
	m_pLook = nullptr;			// 現在見てる看板
	m_bExpl = false;			// 説明状況

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CTutorial::Update(void)
{
	//// 終了カウントを加算する
	//m_nEndCount++;

	//if (m_nEndCount >= TRANS_COUNT)
	//{ // スキップ時または、終了時の場合

	//	// ゲームモードにする
	//	CManager::Get()->GetFade()->SetFade(MODE_GAME);
	//}

	if (m_bExpl == false)
	{ // 説明状況じゃない場合

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// 更新処理
			CManager::Get()->GetRenderer()->Update();
		}
	}
	else
	{ // 上記以外

		// 看板の説明のみ更新
		CObject::AnyUpdate(CObject::TYPE_SIGNEXPLAIN);
	}
}

//======================================
//描画処理
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// プレイヤーの取得処理
//======================================
CTutorialPlayer* CTutorial::GetPlayer(void)
{
	// プレイヤーの情報を返す
	return m_pPlayer;
}

//======================================
// 説明状況の設定処理
//======================================
void CTutorial::SetEnableExplain(const bool bExpl)
{
	// 説明状況を設定する
	m_bExpl = bExpl;
}

//======================================
// 説明状況の取得処理
//======================================
bool CTutorial::IsExplain(void)
{
	// 説明状況を返す
	return m_bExpl;
}

//======================================
// 看板の設定処理
//======================================
void CTutorial::SetLookSign(CSignboard* pSign)
{
	// 看板の情報を設定する
	m_pLook = pSign;
}

//======================================
// 看板の取得処理
//======================================
CSignboard* CTutorial::GetLookSign(void)
{
	// 看板の情報を返す
	return m_pLook;
}

//======================================
// プレイヤーのプレイヤーのNULL化処理
//======================================
void CTutorial::DeletePlayer(void)
{
	// プレイヤーを NULL にする
	m_pPlayer = nullptr;
}