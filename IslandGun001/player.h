//============================================
//
// プレイヤーヘッダー[player.h]
// Author：小原立暉
//
//============================================
#ifndef _PLAYER_H_					// このマクロ定義がされていなかったら
#define _PLAYER_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "character.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション
class CPlayerAction;		// プレイヤーの行動

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// 誰でもアクセスできる

	// 列挙型定義(モーションの種類)
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// 待機
		MOTIONTYPE_MOVE,			// 移動
		MOTIONTYPE_JETDASH,			// ジェットダッシュ
		MOTIONTYPE_JUMP,			// ジャンプ
		MOTIONTYPE_LANDING,			// 着地
		MOTIONTYPE_DAMAGE,			// ダメージ
		MOTIONTYPE_FLY,				// 浮遊
		MOTIONTYPE_QUAKE,			// 地震
		MOTIONTYPE_SCRATCH001,		// ひっかき001
		MOTIONTYPE_SCRATCH002,		// ひっかき002
		MOTIONTYPE_APPEAR,			// 登場
		MOTIONTYPE_MAX				// この列挙型の総数
	};

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,				// 通常状態
		STATE_DAMAGE,				// ダメージ状態
		STATE_INVINSIBLE,			// 無敵状態
		STATE_MAX
	};

	CPlayer();				// コンストラクタ
	~CPlayer();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// セット・ゲット関係
	CMotion* GetMotion(void) const;				// モーションの情報の取得処理
	CPlayerAction* GetAction(void) const;		// 行動の情報の取得処理

	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理
	void SetCameraHeight(const float fHeight);	// カメラの高さの設定処理
	float GetCameraHeight(void) const;			// カメラの高さの取得処理

	// 静的メンバ関数
	static CPlayer* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void ElevationCollision(void);	// 起伏地面の当たり判定処理
	void Control(void);				// 操作処理
	void Move(void);				// 移動処理
	void RotMove(void);				// 向きの設定処理
	void Jump(void);				// ジャンプ処理
	void CameraControl(void);		// カメラの操作処理

	// メンバ変数
	CMotion* m_pMotion;				// モーションの情報
	CPlayerAction* m_pAction;		// プレイヤーの行動の情報

	D3DXVECTOR3 m_rotDest;			// 目標の向き
	D3DXVECTOR3 m_move;				// 移動量
	STATE m_state;					// 状態
	int m_nStateCount;				// 状態カウント
	int m_nDodge;					// 回避カウント
	float m_fSpeed;					// 速度
	float m_fAlpha;					// 体の透明度
	float m_fCameraHeight;			// カメラの高さ
	bool m_bMove;					// 移動状況
	bool m_bJump;					// ジャンプ状況
	bool m_bDodge;					// 回避状況

};

#endif