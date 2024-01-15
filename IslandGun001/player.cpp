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

#include "collision.h"
#include "camera.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "motion.h"
#include "bullet.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
namespace
{
	const float GRAVITY = 1.0f;						// 重力
	const float LAND_GRAVITY = -50.0f;				// 着地時の重力
	const float JUMP = 23.0f;						// ジャンプ力
	const float SPEED = 10.0f;						// 速度
	const float INIT_POSV_CAMERA_Y = 250.0f;		// カメラの視点のY座標
	const float ROT_CORRECT = 0.2f;					// 向きの補正倍率
	const float CAMERA_ROT_CORRECT = 0.000004f;		// カメラの向きの補正倍率
	const float CAMERA_HEIGHT = 0.0005f;			// カメラの高さの倍率
	const float CAMERA_MAX_HEIGHT = 500.0f;			// カメラの高さの最大値
	const float CAMERA_MIN_HEIGHT = 0.0f;			// カメラの高さの最小値
	const float CAMERA_ELEVATION_HEIGHT = 30.0f;	// カメラの起伏地面の高さ
}

//=========================================
// コンストラクタ
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;					// モーションの情報
	m_pAction = nullptr;					// プレイヤーの行動の情報
	m_rotDest = NONE_D3DXVECTOR3;			// 目標の向き
	m_move = NONE_D3DXVECTOR3;				// 移動量
	m_state = STATE_NONE;					// 状態
	m_nStateCount = 0;						// 状態カウント
	m_nDodge = 0;							// 回避カウント
	m_fSpeed = SPEED;						// 速度
	m_fAlpha = 1.0f;						// 体の透明度
	m_fCameraHeight = INIT_POSV_CAMERA_Y;	// カメラの高さ
	m_bMove = false;						// 移動状況
	m_bJump = false;						// ジャンプ状況
	m_bDodge = false;						// 回避状況
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
	SetNumModel(16);

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
	m_pMotion->Set(MOTIONTYPE_APPEAR);

	if (m_pAction == nullptr)
	{ // 行動の情報が NULL の場合

		// プレイヤーアクションの生成処理
		m_pAction = CPlayerAction::Create();
	}

	// 全ての値を初期化する
	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_NONE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_nDodge = 0;					// 回避カウント
	m_fSpeed = SPEED;				// 速度
	m_fAlpha = 1.0f;				// 体の透明度
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況
	m_bDodge = false;				// 回避状況

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CPlayer::Uninit(void)
{
	// モーションのメモリを開放する
	delete m_pMotion;
	m_pMotion = nullptr;

	// 行動のメモリを開放する
	m_pAction->Uninit();
	m_pAction = nullptr;

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

	// カメラの操作処理
	CameraControl();

	// 操作処理
	Control();

	// 攻撃処理
	Attack();

	// 移動処理
	Move();

	// 行動の更新処理
	m_pAction->Update(this);

	// モーションの更新処理
	m_pMotion->Update();

	// 起伏地面との当たり判定処理
	ElevationCollision();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// 全ての値を設定する
	m_rotDest = NONE_D3DXVECTOR3;	// 目標の向き
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_NONE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_nDodge = 0;					// 回避カウント
	m_fSpeed = SPEED;				// 速度
	m_fAlpha = 1.0f;				// 体の透明度
	m_bMove = false;				// 移動状況
	m_bJump = false;				// ジャンプ状況
	m_bDodge = false;				// 回避状況
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
// カメラの高さの設定処理
//=======================================
void CPlayer::SetCameraHeight(const float fHeight)
{
	// カメラの高さを設定する
	m_fCameraHeight = fHeight;
}

//=======================================
// カメラの高さの取得処理
//=======================================
float CPlayer::GetCameraHeight(void) const
{
	// カメラの高さを返す
	return m_fCameraHeight;
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
	// 向きの移動処理
	RotMove();

	// ジャンプ処理
	Jump();
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
	float fStickRot = 0.0f;		// スティックの向き
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();	// カメラの向き

	// スティックの向きを取る
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));

	if (fStickRotY != 0 ||
		fStickRotX != 0)
	{ // 右スティックをどっちかに倒した場合

		// スティックの向きを設定する
		fStickRot = atan2f(fStickRotX, fStickRotY);

		// 向きの正規化
		useful::RotNormalize(&fStickRot);

		// 向きにカメラの向きを加算する
		fStickRot += CameraRot.y;

		if (m_pAction->GetAction() != CPlayerAction::ACTION_SHOT)
		{ // 射撃状態以外の場合

			// 向きの正規化
			useful::RotNormalize(&fStickRot);

			// 向きを設定する
			m_rotDest.y = fStickRot;
		}

		// 移動量を設定する
		m_move.x = sinf(fStickRot) * m_fSpeed;
		m_move.z = cosf(fStickRot) * m_fSpeed;
	}
	else
	{ // 上記以外

		// 移動量を設定する
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}
}

//=======================================
// ジャンプ処理
//=======================================
void CPlayer::Jump(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true &&
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

	// カメラの高さを加算する
	m_fCameraHeight -= (fStickRotY * CAMERA_HEIGHT);

	if (m_fCameraHeight >= CAMERA_MAX_HEIGHT)
	{ // カメラの高さが一定数を超えた場合

		// カメラの高さを補正する
		m_fCameraHeight = CAMERA_MAX_HEIGHT;
	}

	if (m_fCameraHeight <= CAMERA_MIN_HEIGHT)
	{ // カメラの高さが一定数を超えた場合

		// カメラの高さを補正する
		m_fCameraHeight = CAMERA_MIN_HEIGHT;
	}

	// 起伏地面とカメラの当たり判定
	ElevationCamera();

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
// 攻撃処理
//=======================================
void CPlayer::Attack(void)
{
	if (CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY_RB, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY_LB, 0) == true)
	{ // LB・RBキーを押した場合

		// 射撃状態にする
		m_pAction->SetAction(CPlayerAction::ACTION_SHOT);
	}
	else
	{ // 上記以外

		// 通常状態にする
		m_pAction->SetAction(CPlayerAction::ACTION_NONE);
	}

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_RB, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetRepeat(CInputGamePad::JOYKEY_RB, 0, 10) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_LB, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetRepeat(CInputGamePad::JOYKEY_LB, 0, 10) == true)
	{ // LB・RBキーを押した場合

		// 弾バンバン
		CBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 80.0f, GetPos().z), GetRot().y + 0.01f, CBullet::TYPE::TYPE_HANDGUN);
		CBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 80.0f, GetPos().z), GetRot().y - 0.01f, CBullet::TYPE::TYPE_HANDGUN);
	}
}