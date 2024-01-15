//============================================
//
// 弾マネージャーヘッダー[bullet_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _BULLET_MANAGER_H_		// このマクロ定義がされていなかったら
#define _BULLET_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CBullet;		// 弾

//--------------------------------------------
// クラス(起伏マネージャークラス)
//--------------------------------------------
class CBulletManager
{
public:				// 誰でもアクセスできる

	CBulletManager();			// コンストラクタ
	~CBulletManager();			// デストラクタ

	// メンバ関数
	void Regist(CBullet* pThis);		// 登録処理
	void Uninit(void);						// 終了処理
	
	CBullet* GetTop(void);				// 先頭の取得処理
	void Pull(CBullet* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CBulletManager* Create(void);		// 生成処理
	static CBulletManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CBullet* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CBulletManager* m_pManager;		// マネージャーの変数
};

#endif