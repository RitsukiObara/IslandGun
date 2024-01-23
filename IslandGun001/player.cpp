//============================================
//
// プレイヤーのメイン処理[player.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "useful.h"

#include "player.h"
#include "player_action.h"
#include "handgun.h"
#include "dagger.h"
#include "aim.h"
#include "bulletUI.h"
#include "gold_bone_UI.h"

#include "collision.h"
#include "camera.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "motion.h"
#include "bullet.h"
#include "block.h"
#include "block_manager.h"
#include "orbit.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
namespace
{
	const float GRAVITY = 1.0f;						// 重力
	const float LAND_GRAVITY = -50.0f;				// 着地時の重力
	const float JUMP = 24.0f;						// ジャンプ力
	const float SPEED = 14.0f;						// 速度
	const float INIT_POSV_CAMERA_Y = 250.0f;		// カメラの視点のY座標
	const float ROT_CORRECT = 0.2f;					// 向きの補正倍率
	const float CAMERA_ROT_CORRECT = 0.000003f;		// カメラの向きの補正倍率
	const float CAMERA_HEIGHT = 0.0005f;			// カメラの高さの倍率
	const float CAMERA_MAX_HEIGHT = 500.0f;			// カメラの高さの最大値
	const float CAMERA_MIN_HEIGHT = 0.0f;			// カメラの高さの最小値
	const float CAMERA_ELEVATION_HEIGHT = 30.0f;	// カメラの起伏地面の高さ
	const D3DXVECTOR3 COLLISION_SIZE = D3DXVECTOR3(40.0f, 130.0f, 40.0f);		// 当たり判定時のサイズ
	const D3DXVECTOR3 GUN_POS[NUM_HANDGUN] =		// 拳銃の位置
	{
		D3DXVECTOR3(-10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(+10.0f, 0.0f, 0.0f)
	};
	const D3DXVECTOR3 GUN_ROT[NUM_HANDGUN] =		// 拳銃の向き
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, -D3DX_PI * 0.5f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, D3DX_PI * 0.5f)
	};
	const float SHOT_SHIFT_ROT[NUM_HANDGUN] =		// 射撃時のずらす向き
	{
		(-D3DX_PI * 0.06f),
		(D3DX_PI * 0.06f),
	};
	const float SHOT_SHIFT_LENGTH = 95.0f;			// 射撃時のずらす幅
	const float SHOT_ADD_HEIGHT = 160.0f;			// 射撃時の高さの追加量
	const int DODGE_INTERVAL = 90;					// 回避インターバル
	const int SHOT_INTERVAL = 5;					// 撃つインターバル
	const float CAMERA_MOUSE_MAGNI = 5000.0f;		// マウスでのカメラ操作の倍率
	const float AIM_SHIFT = 1000.0f;				// エイムを表示する幅
	const int NUM_SHOTGUN_BULLET = 6;				// 散弾で飛ばす弾の数
	const int SHOTGUN_RAND_ROT = 60;				// 散弾のランダムで飛ばす向き
	const float SHOTGUN_GRAVITY = 15.0f;			// 散弾状態の時の重力
	const float SHOTGUN_RECOIL = 7.0f;				// 散弾状態の反動
}

//=========================================
// コンストラクタ
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;					// モーションの情報
	m_pAction = nullptr;					// プレイヤーの行動の情報
	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		m_apHandGun[nCntGun] = nullptr;		// 拳銃の情報
	}
	m_pAim = nullptr;						// エイムの情報
	m_pDagger = nullptr;					// ダガーの情報
	m_pBulletUI = nullptr;					// 弾丸UIの情報
	m_pGoldBoneUI = nullptr;				// 金の骨のUIの情報

	m_rotDest = NONE_D3DXVECTOR3;			// 目標の向き
	m_move = NONE_D3DXVECTOR3;				// 移動量
	m_state = STATE_NONE;					// 状態
	m_nStateCount = 0;						// 状態カウント
	m_nShotCount = 0;						// 射撃カウント
	m_fSpeed = SPEED;						// 速度
	m_fAlpha = 1.0f;						// 体の透明度
	m_fStickRot = 0.0f;						// スティックの向き
	m_bMove = false;						// 移動状況
	m_bJump = false;						// ジャンプ状況
}

//=========================================
// デストラクタ
//=========================================
CPlayer::~CPlayer()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(17);

	// データの設定処理
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		m_pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		m_pMotion->Load("data\\TXT\\PlayerMotion.txt");
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	// モーションの設定処理
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	if (m_pAction == nullptr)
	{ // 行動の情報が NULL の場合

		// プレイヤーアクションの生成処理
		m_pAction = CPlayerAction::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pBulletUI == nullptr)
	{ // 残弾UIが NULL の場合

		// 弾丸UIの生成
		m_pBulletUI = CBulletUI::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pGoldBoneUI == nullptr)
	{ // 金の骨UIが NULL の場合

		// 金の骨のUIの生成
		m_pGoldBoneUI = CGoldBoneUI::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	// 全ての値を初期化する
	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		m_apHandGun[nCntGun] = nullptr;	// 拳銃の情報
	}
	m_pAim = nullptr;				// エイムの情報
	m_pDagger = nullptr;			// ダガーの情報

	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_NONE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_nShotCount = 0;				// 射撃カウント
	m_fSpeed = SPEED;				// 速度
	m_fAlpha = 1.0f;				// 体の透明度
	m_fStickRot = 0.0f;				// スティックの向き
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況
	m_bRightShot = true;			// 右で撃つかどうか

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションのメモリを開放する
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pAction != nullptr)
	{ // 行動が NULL じゃない場合

		// 行動のメモリを開放する
		m_pAction->Uninit();
		m_pAction = nullptr;
	}

	if (m_pAim != nullptr)
	{ // エイムが NULL じゃない場合

		// エイムのメモリを開放する
		m_pAim->Uninit();
		m_pAim = nullptr;
	}

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (m_apHandGun[nCntGun] != nullptr)
		{ // 拳銃の情報が NULL じゃない場合

			// 拳銃の終了処理
			m_apHandGun[nCntGun]->Uninit();
			m_apHandGun[nCntGun] = nullptr;
		}
	}

	if (m_pDagger != nullptr)
	{ // ダガーの情報が NULL じゃない場合

		// ダガーの終了処理
		m_pDagger->Uninit();
		m_pDagger = nullptr;
	}

	if (m_pBulletUI != nullptr)
	{ // 残弾UIの情報が NULL じゃない場合

		// 残弾UIを NULL にする
		m_pBulletUI = nullptr;
	}

	if (m_pGoldBoneUI != nullptr)
	{ // 金の骨の情報が NULL じゃない場合

		// 金の骨UIを NULL にする
		m_pGoldBoneUI = nullptr;
	}

	// 終了処理
	CCharacter::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CPlayer::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// 操作処理
	Control();

	// 移動処理
	Move();

	// モーションの更新処理
	m_pMotion->Update();

	// 行動の更新処理
	m_pAction->Update(this);

	// 小判との当たり判定
	collision::CoinCollision(GetPos(), COLLISION_SIZE);

	// 木との当たり判定
	TreeCollision();

	// 起伏地面との当たり判定処理
	ElevationCollision();

	// ブロックとの当たり判定処理
	BlockCollision();

	// 金の骨との当たり判定
	collision::GoldBoneCollision(*this, COLLISION_SIZE);

	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f", GetPos().x, GetPos().y, GetPos().z);
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (m_apHandGun[nCntGun] != nullptr)
		{ // 拳銃の情報が NULL じゃない場合

			// 拳銃の描画処理
			m_apHandGun[nCntGun]->Draw();
		}
	}

	if (m_pDagger != nullptr)
	{ // 拳銃の情報が NULL じゃない場合

		// 拳銃の描画処理
		m_pDagger->Draw();
	}

	if (m_pAim != nullptr)
	{ // エイムの情報が NULL じゃない場合

		// エイムの描画処理
		m_pAim->Draw();
	}
}

//===========================================
// モーションの情報の設定処理
//===========================================
CMotion* CPlayer::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// 行動の情報の取得処理
//===========================================
CPlayerAction* CPlayer::GetAction(void) const
{
	// 行動の情報を返す
	return m_pAction;
}

//===========================================
// 拳銃の情報の取得処理
//===========================================
CHandgun* CPlayer::GetHandGun(const int nCount) const
{
	// 拳銃の情報を返す
	return m_apHandGun[nCount];
}

//===========================================
// ダガーの情報の取得処理
//===========================================
CDagger* CPlayer::GetDagger(void) const
{
	// ダガーの情報を返す
	return m_pDagger;
}

//===========================================
// 金の骨UIの情報の取得処理
//===========================================
CGoldBoneUI* CPlayer::GetGoldBoneUI(void) const
{
	// 金の骨UIの情報を返す
	return m_pGoldBoneUI;
}

//=======================================
// 情報の設定処理
//=======================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を初期化する
	SetPos(pos);					// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// データの設定処理
	}

	// モーションの設定処理
	m_pMotion->ResetMotion(MOTIONTYPE_NEUTRAL);

	for (int nCnt = 0; nCnt < NUM_HANDGUN; nCnt++)
	{
		// 拳銃の情報を生成する
		m_apHandGun[nCnt] = CHandgun::Create(GUN_POS[nCnt], GUN_ROT[nCnt], GetHierarchy((CXFile::TYPE_PLAYERRIGHTHAND - INIT_PLAYER) + nCnt)->GetMatrixP());
	}

	// ダガーを生成する
	m_pDagger = CDagger::Create(GetHierarchy(CXFile::TYPE_PLAYERRIGHTHAND - INIT_PLAYER)->GetMatrixP());

	D3DXVECTOR3 posCamera;

	// 位置を設定する
	posCamera.x = GetPos().x + sinf(CManager::Get()->GetCamera()->GetRot().y) * SHOT_SHIFT_LENGTH;
	posCamera.y = GetPos().y + cosf(CManager::Get()->GetCamera()->GetRot().x) * SHOT_SHIFT_LENGTH;
	posCamera.z = GetPos().z + cosf(CManager::Get()->GetCamera()->GetRot().y) * SHOT_SHIFT_LENGTH;

	// エイムを生成する
	m_pAim = CAim::Create(CManager::Get()->GetCamera()->GetPosR());
	
	// 全ての値を設定する
	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_NONE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_nShotCount = 0;				// 射撃カウント
	m_fSpeed = SPEED;				// 速度
	m_fAlpha = 1.0f;				// 体の透明度
	m_fStickRot = 0.0f;				// スティックの向き
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況
}

//===========================================
// 生成処理
//===========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	// プレイヤーのインスタンスを生成
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pPlayer = new CPlayer;
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

//=======================================
// 目的の向きの設定処理
//=======================================
void CPlayer::SetRotDest(const D3DXVECTOR3& rot)
{
	// 目的の向きを設定する
	m_rotDest = rot;
}

//=======================================
// 目的の向きの取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetRotDest(void) const
{
	// 目的の向きを返す
	return m_rotDest;
}

//=======================================
// 移動量の設定処理
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 起伏地面の当たり判定処理
//=======================================
void CPlayer::ElevationCollision(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	float fHeight = 0.0f;			// 高さ
	bool bJump = true;				// ジャンプ状況
	bool bRange = false;			// 範囲内状況

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos, bRange);

		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			// 重力を設定する
			m_move.y = LAND_GRAVITY;

			// ジャンプ状況を false にする
			bJump = false;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// ジャンプ状況を代入する
	m_bJump = bJump;

	// 位置を更新する
	SetPos(pos);
}

//=======================================
// 操作処理
//=======================================
void CPlayer::Control(void)
{
	if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // ゲームパッドが接続されている場合

		// カメラの操作処理
		CameraControl();
	}
	else
	{ // 上記以外

		// マウスでのカメラの操作処理
		CameraMouse();
	}

	if (m_pAction->GetAction() != CPlayerAction::ACTION_DODGE &&
		m_pAction->GetAction() != CPlayerAction::ACTION_DAGGER &&
		m_pAction->GetAction() != CPlayerAction::ACTION_SHOTGUN &&
		m_pAction->GetAction() != CPlayerAction::ACTION_SWOOP)
	{ // 一定状態以外の場合

		if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
		{ // ゲームパッドが刺さっていた場合

			// 向きの移動処理
			RotMove();
		}
		else
		{ // 上記以外

			// キーボードでの処理
			KeyboardMove();
		}

		// ジャンプ処理
		Jump();

		// 攻撃処理
		Shot();

		// ダガー処理
		Dagger();

		// 回避処理
		Avoid();
	}
}

//=======================================
// 移動処理
//=======================================
void CPlayer::Move(void)
{
	// 位置と向きを取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_rotDest.y, &rot.y, ROT_CORRECT);

	// 位置を移動させる
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 重力をかける
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);

	// 位置と向きを適用する
	SetPos(pos);
	SetRot(rot);
}

//=======================================
// 向きの設定処理
//=======================================
void CPlayer::RotMove(void)
{
	// ローカル変数を宣言する
	float fStickRotX = 0.0f;	// スティックのX座標
	float fStickRotY = 0.0f;	// スティックのY座標
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();	// カメラの向き

	// スティックの向きを取る
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));

	if (fStickRotY != 0 ||
		fStickRotX != 0)
	{ // 右スティックをどっちかに倒した場合

		// スティックの向きを設定する
		m_fStickRot = atan2f(fStickRotX, fStickRotY);

		// 向きの正規化
		useful::RotNormalize(&m_fStickRot);

		// 向きにカメラの向きを加算する
		m_fStickRot += CameraRot.y;

		if (m_pAction->GetAction() != CPlayerAction::ACTION_SHOT)
		{ // 射撃状態以外の場合

			// 向きの正規化
			useful::RotNormalize(&m_fStickRot);

			// 向きを設定する
			m_rotDest.y = m_fStickRot;
		}

		// 移動量を設定する
		m_move.x = sinf(m_fStickRot) * m_fSpeed;
		m_move.z = cosf(m_fStickRot) * m_fSpeed;

		if (m_pMotion->GetType() != MOTIONTYPE_MOVE)
		{ // 移動モーションじゃなかった場合

			// 移動モーションを設定する
			m_pMotion->Set(MOTIONTYPE_MOVE);
		}
	}
	else
	{ // 上記以外

		// 移動量を設定する
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		if (m_pMotion->GetType() != MOTIONTYPE_NEUTRAL)
		{ // 移動モーションじゃなかった場合

			// 移動モーションを設定する
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//=======================================
// キーボードでの設定処理
//=======================================
void CPlayer::KeyboardMove(void)
{
	// ローカル変数を宣言する
	float fMoveX = 0.0f;	// X軸の移動量
	float fMoveZ = 0.0f;	// Z軸の移動量
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();	// カメラの向き

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // Wキーを押した場合

		// Z軸の移動量を設定する
		fMoveZ = 1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // Sキーを押した場合

		// Z軸の移動量を設定する
		fMoveZ = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押した場合

		// X軸の移動量を設定する
		fMoveX = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押した場合

		// X軸の移動量を設定する
		fMoveX = 1.0f;
	}

	if (fMoveX != 0 ||
		fMoveZ != 0)
	{ // 右スティックをどっちかに倒した場合

		// スティックの向きを設定する
		m_fStickRot = atan2f(fMoveX, fMoveZ);

		// 向きの正規化
		useful::RotNormalize(&m_fStickRot);

		// 向きにカメラの向きを加算する
		m_fStickRot += CameraRot.y;

		if (m_pAction->GetAction() != CPlayerAction::ACTION_SHOT)
		{ // 射撃状態以外の場合

			// 向きの正規化
			useful::RotNormalize(&m_fStickRot);

			// 向きを設定する
			m_rotDest.y = m_fStickRot;
		}

		// 移動量を設定する
		m_move.x = sinf(m_fStickRot) * m_fSpeed;
		m_move.z = cosf(m_fStickRot) * m_fSpeed;

		if (m_pMotion->GetType() != MOTIONTYPE_MOVE)
		{ // 移動モーションじゃなかった場合

			// 移動モーションを設定する
			m_pMotion->Set(MOTIONTYPE_MOVE);
		}
	}
	else
	{ // 上記以外

		// 移動量を設定する
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		if (m_pMotion->GetType() != MOTIONTYPE_NEUTRAL)
		{ // 移動モーションじゃなかった場合

			// 移動モーションを設定する
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//=======================================
// ジャンプ処理
//=======================================
void CPlayer::Jump(void)
{
	if ((CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true) &&
		m_bJump == false)
	{ // Aボタンを押した場合

		// 移動量を設定する
		m_move.y = JUMP;

		// ジャンプしている
		m_bJump = true;
	}
}

//=======================================
// カメラの操作処理
//=======================================
void CPlayer::CameraControl(void)
{
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// カメラの向きを取得する
	float fStickRotX, fStickRotY;		// スティックの向き

	// 右スティックの傾け度を取得する
	fStickRotX = CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0);
	fStickRotY = CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0);

	// カメラの向きを加算する
	CameraRot.y += (fStickRotX * CAMERA_ROT_CORRECT);

	// 向きの正規化
	useful::RotNormalize(&CameraRot.y);

	// カメラの向きを加算する
	CameraRot.x -= (fStickRotY * CAMERA_ROT_CORRECT);

	if (CameraRot.x >= D3DX_PI - 0.01f)
	{ // 向きが一定を超えた場合

		CameraRot.x = D3DX_PI - 0.01f;
	}
	else if (CameraRot.x <= 0.0f + 0.01f)
	{ // 向きが一定を超えた場合

		CameraRot.x = 0.0f + 0.01f;
	}

	if (m_pAim != nullptr)
	{ // エイムが NULL じゃない場合

		D3DXVECTOR3 posAim;			// レティクルを表示する場所
		D3DXVECTOR3 posShot;		// 弾を出す位置

		// 位置を設定する
		posShot.x = GetPos().x;
		posShot.y = GetPos().y + SHOT_ADD_HEIGHT;
		posShot.z = GetPos().z;

		// 目的の視点を設定する
		posAim.x = posShot.x + sinf(CameraRot.y) * AIM_SHIFT;
		posAim.y = posShot.y + cosf(CameraRot.x) * AIM_SHIFT;
		posAim.z = posShot.z + cosf(CameraRot.y) * AIM_SHIFT;

		// エイムの設置処理
		m_pAim->SetAim(posAim);
	}

	//// 起伏地面とカメラの当たり判定
	//ElevationCamera();

	// 向きを適用する
	CManager::Get()->GetCamera()->SetRot(CameraRot);
}

//=======================================
// マウスでのカメラの操作処理
//=======================================
void CPlayer::CameraMouse(void)
{
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// カメラの向きを取得する
	float fMoveX = 0.0f;
	float fMoveZ = 0.0f;		// スティックの向き

	fMoveX = CManager::Get()->GetInputMouse()->GetMove().x * CAMERA_MOUSE_MAGNI;
	fMoveZ = -CManager::Get()->GetInputMouse()->GetMove().y * CAMERA_MOUSE_MAGNI;

	// カメラの向きを加算する
	CameraRot.y += (fMoveX * CAMERA_ROT_CORRECT);

	// 向きの正規化
	useful::RotNormalize(&CameraRot.y);

	// カメラの向きを加算する
	CameraRot.x -= (fMoveZ * CAMERA_ROT_CORRECT);

	if (CameraRot.x >= D3DX_PI - 0.01f)
	{ // 向きが一定を超えた場合

		CameraRot.x = D3DX_PI - 0.01f;
	}
	else if (CameraRot.x <= 0.0f + 0.01f)
	{ // 向きが一定を超えた場合

		CameraRot.x = 0.0f + 0.01f;
	}

	if (m_pAim != nullptr)
	{ // エイムが NULL じゃない場合

		D3DXVECTOR3 posAim;			// レティクルを表示する場所
		D3DXVECTOR3 posShot;		// 弾を出す位置

		// 位置を設定する
		posShot.x = GetPos().x;
		posShot.y = GetPos().y + SHOT_ADD_HEIGHT;
		posShot.z = GetPos().z;

		// 目的の視点を設定する
		posAim.x = posShot.x + sinf(CameraRot.y) * AIM_SHIFT;
		posAim.y = posShot.y + cosf(CameraRot.x) * AIM_SHIFT;
		posAim.z = posShot.z + cosf(CameraRot.y) * AIM_SHIFT;

		// エイムの設置処理
		m_pAim->SetAim(posAim);
	}

	//// 起伏地面とカメラの当たり判定
	//ElevationCamera();

	// 向きを適用する
	CManager::Get()->GetCamera()->SetRot(CameraRot);
}

//=======================================
// 起伏地面とカメラの当たり判定
//=======================================
void CPlayer::ElevationCamera(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 posV = CManager::Get()->GetCamera()->GetPosV();	// 位置を取得する
	float fHeight = 0.0f;			// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(posV) + CAMERA_ELEVATION_HEIGHT;

		if (posV.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			posV.y = fHeight;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	CManager::Get()->GetCamera()->SetPosV(posV);
}

//=======================================
// 木との当たり判定
//=======================================
void CPlayer::TreeCollision(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 木との当たり判定
	collision::TreeCollision(&pos, COLLISION_SIZE.x);

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// ブロックとの当たり判定
//=======================================
void CPlayer::BlockCollision(void)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();	// 先頭の木を取得する
	collision::SCollision coll = { false,false,false,false,false,false };				// 当たり判定の変数
	D3DXVECTOR3 pos = GetPos();							// 位置を取得する
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-COLLISION_SIZE.x, 0.0f, -COLLISION_SIZE.z);		// 最小値を取得する
	D3DXVECTOR3 vtxMax = COLLISION_SIZE;				// 最大値を取得する

	while (pBlock != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		// 六面体の当たり判定
		coll = collision::HexahedronClush
		(
			&pos,
			pBlock->GetPos(),
			GetPosOld(),
			pBlock->GetPosOld(),
			vtxMin,
			pBlock->GetFileData().vtxMin,
			vtxMax,
			pBlock->GetFileData().vtxMax
		);

		if (coll.bTop == true)
		{ // 上に乗った場合

			// 移動量を設定する
			m_move.y = 0.0f;

			// ジャンプしていない
			m_bJump = false;
		}

		// 次のオブジェクトを代入する
		pBlock = pBlock->GetNext();
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 射撃系処理
//=======================================
void CPlayer::Shot(void)
{
	// 残弾数を取得する
	int nNumBullet = m_pBulletUI->GetNumBullet();

	if ((m_pAction->GetAction() == CPlayerAction::ACTION_NONE ||
		m_pAction->GetAction() == CPlayerAction::ACTION_SHOT) &&
		(CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY_RB, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY_LB, 0) == true ||
		CManager::Get()->GetInputMouse()->GetPress(CInputMouse::MOUSE_L) == true) &&
		nNumBullet > 0)
	{ // 残弾があり、RB・LBキーを押した場合

		if (m_bJump == true)
		{ // ジャンプしていた場合

			// 散弾処理
			ShotGun(&nNumBullet);
		}
		else
		{ // 上記以外

			// 拳銃処理
			HandGun(&nNumBullet);
		}

		// 射撃カウントを加算する
		m_nShotCount++;
	}

	if (m_pAction->GetAction() != CPlayerAction::ACTION_SHOTGUN &&
		(CManager::Get()->GetInputGamePad()->GetRelease(CInputGamePad::JOYKEY_RB, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetRelease(CInputGamePad::JOYKEY_LB, 0) == true ||
		CManager::Get()->GetInputMouse()->GetRelease(CInputMouse::MOUSE_L) == true))
	{ // RB・LBボタンを離した場合

		// 射撃カウントを0にする
		m_nShotCount = 0;

		// 通常状態にする
		m_pAction->SetAction(CPlayerAction::ACTION_NONE);
	}
}

//=======================================
// 拳銃処理
//=======================================
void CPlayer::HandGun(int* nNumBullet)
{
	// 射撃状態にする
	m_pAction->SetAction(CPlayerAction::ACTION_SHOT);

	if (m_nShotCount % 10 == 0)
	{ // 一定カウントごとに

		D3DXVECTOR3 pos;		// 弾の出る位置を宣言
		D3DXVECTOR3 rot;		// 弾の出る向きを宣言

		// 向きを設定する
		rot = CManager::Get()->GetCamera()->GetRot();

		// 向きの正規化
		useful::RotNormalize(&rot.x);

		// 位置を設定する
		pos.x = GetPos().x + sinf(GetRot().y + SHOT_SHIFT_ROT[(int)(m_bRightShot)]) * SHOT_SHIFT_LENGTH;
		pos.y = GetPos().y + SHOT_ADD_HEIGHT;
		pos.z = GetPos().z + cosf(GetRot().y + SHOT_SHIFT_ROT[(int)(m_bRightShot)]) * SHOT_SHIFT_LENGTH;

		// 弾を撃つ
		CBullet::Create(pos, rot, CBullet::TYPE::TYPE_HANDGUN);

		// 右で撃つかどうかを変える
		m_bRightShot = !m_bRightShot;

		// 残弾数を減らす
		(*nNumBullet)--;

		// 残弾数を適用する
		m_pBulletUI->SetNumBullet(*nNumBullet);
	}
}

//=======================================
// 散弾処理
//=======================================
void CPlayer::ShotGun(int* nNumBullet)
{
	// 散弾状態にする
	m_pAction->SetAction(CPlayerAction::ACTION_SHOTGUN);

	// 移動量を設定する
	m_move.x = sinf(GetRot().y) * -SHOTGUN_RECOIL;
	m_move.y = SHOTGUN_GRAVITY;
	m_move.z = cosf(GetRot().y) * -SHOTGUN_RECOIL;

	D3DXVECTOR3 pos = GetPos();		// プレイヤーの位置を宣言
	D3DXVECTOR3 rot;				// プレイヤーの向きを宣言
	D3DXVECTOR3 rotBullet;			// 弾の出る向きを宣言

	// 向きを設定する
	rot = CManager::Get()->GetCamera()->GetRot();

	// 向きの正規化
	useful::RotNormalize(&rot.x);

	// 位置を設定する
	pos.x = GetPos().x;
	pos.y = GetPos().y + SHOT_ADD_HEIGHT;
	pos.z = GetPos().z;

	for (int nCnt = 0; nCnt < NUM_SHOTGUN_BULLET; nCnt++)
	{
		// 弾の出る向きを設定する
		rotBullet.x = rot.x + (float)((rand() % SHOTGUN_RAND_ROT - (SHOTGUN_RAND_ROT/ 2)) * 0.01f);
		rotBullet.y = rot.y + (float)((rand() % SHOTGUN_RAND_ROT - (SHOTGUN_RAND_ROT/ 2)) * 0.01f);
		rotBullet.z = rot.z + (float)((rand() % SHOTGUN_RAND_ROT - (SHOTGUN_RAND_ROT/ 2)) * 0.01f);

		// 弾を撃つ
		CBullet::Create(pos, rotBullet, CBullet::TYPE::TYPE_SHOTGUN);
	}

	// 残弾数を減らす
	(*nNumBullet)--;

	// 残弾数を適用する
	m_pBulletUI->SetNumBullet(*nNumBullet);
}

//=======================================
// 回避処理
//=======================================
void CPlayer::Avoid(void)
{
	if (m_bJump == false &&
		m_pAction->IsDodgeUse() == true &&
		(CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true ||
			CManager::Get()->GetInputMouse()->GetTrigger(CInputMouse::MOUSE_R) == true))
	{ // 地上でBキーを押した場合

		// 回避状態にする
		m_pAction->SetAction(CPlayerAction::ACTION_DODGE);

		// 回避する向きを設定する
		m_pAction->SetDodgeRot(m_fStickRot);

		if (m_pMotion->GetType() != MOTIONTYPE_DODGE)
		{ // 回避モーションじゃない場合

			// 回避モーションにする
			m_pMotion->Set(MOTIONTYPE_DODGE);
		}

		// 目標の向きを設定する
		m_rotDest.y = m_fStickRot;

		// 回避インターバルを設定する
		m_pAction->SetDodgeInterval(DODGE_INTERVAL);

		// 使用可能状況を0にする
		m_pAction->SetEnableDodgeUse(false);
	}
}

//=======================================
// ダガー処理
//=======================================
void CPlayer::Dagger(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_X, 0) == true ||
		CManager::Get()->GetInputMouse()->GetTrigger(CInputMouse::MOUSE_WHEEL) == true)
	{ // Xキーを押した場合

		if (m_bJump == true)
		{ // ジャンプ状況が true の場合

			// 急降下状態にする
			m_pAction->SetAction(CPlayerAction::ACTION_SWOOP);
		}
		else
		{ // 上記以外

			// ダガー状態にする
			m_pAction->SetAction(CPlayerAction::ACTION_DAGGER);
		}

		if (m_pMotion->GetType() != MOTIONTYPE_DAGGER)
		{ // ダガーモーション以外の場合

			// ダガーモーションを設定する
			m_pMotion->Set(MOTIONTYPE_DAGGER);
		}

		// ダガーを表示する
		m_pDagger->SetEnableDisp(true);

		// 拳銃を描画しない
		m_apHandGun[0]->SetEnableDisp(false);
		m_apHandGun[1]->SetEnableDisp(false);
	}
}