//============================================
//
// 岩マネージャーヘッダー[rock_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _ROCK_MANAGER_H_		// このマクロ定義がされていなかったら
#define _ROCK_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CRock;		// 岩

//--------------------------------------------
// クラス(木マネージャークラス)
//--------------------------------------------
class CRockManager
{
public:				// 誰でもアクセスできる

	CRockManager();			// コンストラクタ
	~CRockManager();			// デストラクタ

	// メンバ関数
	void Regist(CRock* pThis);		// 登録処理
	void Uninit(void);						// 終了処理

	CRock* GetTop(void);				// 先頭の取得処理
	void Pull(CRock* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CRockManager* Create(void);		// 生成処理
	static CRockManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CRock* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CRockManager* m_pManager;		// マネージャーの変数
};

#endif