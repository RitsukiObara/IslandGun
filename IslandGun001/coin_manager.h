//============================================
//
// 小判マネージャーヘッダー[coin_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _COIN_MANAGER_H_		// このマクロ定義がされていなかったら
#define _COIN_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CCoin;		// 起伏

//--------------------------------------------
// クラス(起伏マネージャークラス)
//--------------------------------------------
class CCoinManager
{
public:				// 誰でもアクセスできる

	CCoinManager();			// コンストラクタ
	~CCoinManager();			// デストラクタ

	// メンバ関数
	void Regist(CCoin* pThis);		// 登録処理
	void Uninit(void);						// 終了処理

	CCoin* GetTop(void);				// 先頭の取得処理
	void Pull(CCoin* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CCoinManager* Create(void);		// 生成処理
	static CCoinManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CCoin* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CCoinManager* m_pManager;		// マネージャーの変数
};

#endif