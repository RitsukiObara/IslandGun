//===================================
//
// プレイヤーの行動ヘッダー[player_action.h]
// Author 小原立暉
//
//===================================
#ifndef _PLAYER_ACTION_H_			// このマクロ定義がされていなかったら
#define _PLAYER_ACTION_H_			// 2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "main.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CPlayer;		// プレイヤー

//-----------------------------------
// クラス定義(プレイヤーの行動)
//-----------------------------------
class CPlayerAction
{
public:			// 誰でもアクセスできる

	// 列挙型定義(行動)
	enum ACTION
	{
		ACTION_NONE = 0,	// 通常状態
		ACTION_SHOT,		// 射撃状態
		ACTION_DAGGER,		// ダガー状態
		ACTION_DODGE,		// 回避状態
		ACTION_SHOTGUN,		// 散弾(J+銃)状態
		ACTION_SWOOP,		// 急降下(J+ダガー)状態
		ACTION_MAX			// この列挙型の総数
	};

	CPlayerAction();		// コンストラクタ
	~CPlayerAction();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(CPlayer* pPlayer);		// 更新処理

	// 静的メンバ関数
	static CPlayerAction* Create(void);		// 生成処理

private:		// 誰でもアクセスできる

	// メンバ変数
	ACTION m_action;		// 行動
};

#endif