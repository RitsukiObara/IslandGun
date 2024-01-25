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
// マクロ定義
//--------------------------------------------
#define NUM_HANDGUN		(2)		// 拳銃の数

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション
class CPlayerAction;		// プレイヤーの行動
class CHandgun;				// 拳銃
class CDagger;				// ダガー
class CAim;					// エイム
class CBulletUI;			// 弾丸UI
class CGoldBoneUI;			// 金の骨UI

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
		MOTIONTYPE_DODGE,			// 回避
		MOTIONTYPE_DAGGER,			// ダガー
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
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// セット・ゲット関係
	CMotion* GetMotion(void) const;					// モーションの情報の取得処理
	CPlayerAction* GetAction(void) const;			// 行動の情報の取得処理
	CHandgun* GetHandGun(const int nCount) const;	// 拳銃の情報の取得処理
	CDagger* GetDagger(void) const;					// ダガーの情報の取得処理
	CBulletUI* GetBulletUI(void) const;				// 残弾UIの情報の取得処理
	CGoldBoneUI* GetGoldBoneUI(void) const;			// 金の骨UIの情報の取得処理

	void SetRotDest(const D3DXVECTOR3& rot);	// 目的の向きの設定処理
	D3DXVECTOR3 GetRotDest(void) const;			// 目的の向きの取得処理
	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理

	// 静的メンバ関数
	static CPlayer* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);				// 移動処理
	void ElevationCollision(void);	// 起伏地面の当たり判定処理
	void ElevationCamera(void);		// 起伏地面とカメラの当たり判定
	void TreeCollision(void);		// 木との当たり判定
	void BlockCollision(void);		// ブロックとの当たり判定

	// 操作感系
	void CameraControl(void);		// カメラの操作処理
	void CameraMouse(void);			// マウスでのカメラの操作処理
	void Control(void);				// 操作処理
	void RotMove(void);				// 向きの設定処理
	void KeyboardMove(void);		// キーボードでの設定処理
	void Jump(void);				// ジャンプ処理
	void Shot(void);				// 射撃処理
	void HandGun(int* nNumBullet);	// 拳銃処理
	void ShotGun(int* nNumBullet);	// 散弾処理
	void Avoid(void);				// 回避処理
	void Dagger(void);				// ダガー処理

	// メンバ変数
	CMotion* m_pMotion;					// モーションの情報
	CPlayerAction* m_pAction;			// プレイヤーの行動の情報
	CHandgun* m_apHandGun[NUM_HANDGUN];	// 拳銃の情報
	CDagger* m_pDagger;					// ダガーの情報
	CAim* m_pAim;						// エイムの情報
	CBulletUI* m_pBulletUI;				// 弾丸の情報
	CGoldBoneUI* m_pGoldBoneUI;			// 金の骨UIの情報

	D3DXVECTOR3 m_rotDest;		// 目標の向き
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態
	int m_nStateCount;			// 状態カウント
	int m_nShotCount;			// 射撃カウント
	float m_fSpeed;				// 速度
	float m_fAlpha;				// 体の透明度
	float m_fStickRot;			// スティックの向き
	bool m_bMove;				// 移動状況
	bool m_bJump;				// ジャンプ状況
	bool m_bRightShot;			// 右で撃つかどうか

};

#endif