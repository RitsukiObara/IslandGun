//============================================
//
// チュートリアルプレイヤーのメイン処理[player_tutorial.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "player_tutorial.h"
#include "tutorial.h"
#include "collision.h"
#include "renderer.h"

#include "player_controller.h"
#include "motion.h"
#include "player_action.h"
#include "handgun.h"
#include "aim.h"
#include "lifeUI.h"
#include "airplane.h"

// 定数定義
namespace
{
	const D3DXVECTOR3 COLLISION_SIZE = D3DXVECTOR3(40.0f, 190.0f, 40.0f);		// 当たり判定時のサイズ
}

//=========================================
// コンストラクタ
//=========================================
CTutorialPlayer::CTutorialPlayer() : CPlayer()
{

}

//=========================================
// デストラクタ
//=========================================
CTutorialPlayer::~CTutorialPlayer()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CTutorialPlayer::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CTutorialPlayer::Uninit(void)
{
	// 終了処理
	CPlayer::Uninit();

	// プレイヤーのNULL化処理
	CTutorial::DeletePlayer();
}

//===========================================
// 更新処理
//===========================================
void CTutorialPlayer::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	if (collision::SignboardCollision(GetPos(), COLLISION_SIZE.x) == true)
	{ // 看板に近づいた場合

		// この先の処理を行わない
		return;
	}

	// 操作処理
	GetController()->Control(this);

	// 移動処理
	Move();

	if (GetMotion() != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションの更新処理
		GetMotion()->Update();
	}

	if (GetAction() != nullptr)
	{ // 行動が NULL じゃない場合

		// 行動の更新処理
		GetAction()->Update(this);
	}

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (GetHandGun(nCntGun) != nullptr)
		{ // 拳銃が NULL じゃない場合

			// 更新処理
			GetHandGun(nCntGun)->Update();
		}
	}

	// 緊急のリロード処理
	EmergentReload();

	if (GetAim() != nullptr)
	{ // エイムが NULL じゃない場合

		// エイムの更新処理
		GetAim()->Update();
	}

	if (GetLifeUI() != nullptr)
	{ // 寿命が NULL じゃない場合

		// 寿命を設定する
		GetLifeUI()->SetLife(GetLife());
	}

	// ヤシの実との当たり判定
	collision::PalmFruitHit(this, COLLISION_SIZE.x, COLLISION_SIZE.y);

	// 小判との当たり判定
	collision::CoinCollision(this, COLLISION_SIZE);

	// 金の骨との当たり判定
	collision::GoldBoneCollision(*this, COLLISION_SIZE);

	// 木との当たり判定
	TreeCollision();

	// 起伏地面との当たり判定処理
	ElevationCollision();

	// ブロックとの当たり判定処理
	BlockCollision();

	// 岩との当たり判定
	RockCollision();

	// 壁との当たり判定
	WallCollision();

	// 祭壇との当たり判定
	AlterCollision();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CTutorialPlayer::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}

//=======================================
// 情報の設定処理
//=======================================
void CTutorialPlayer::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	CPlayer::SetData(pos);

	// 飛行機を消去する
	GetAirplane()->Uninit();
	RemoveAirplane();

	// 位置を再設定する
	SetPos(pos);
}

//===========================================
// 生成処理
//===========================================
CTutorialPlayer* CTutorialPlayer::Create(const D3DXVECTOR3& pos)
{
	// プレイヤーのインスタンスを生成
	CTutorialPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pPlayer = new CTutorialPlayer;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pPlayer;
	}

	if (pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPlayer->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}