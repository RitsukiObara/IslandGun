//============================================
//
// 木マネージャーヘッダー[tree_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _TREE_MANAGER_H_		// このマクロ定義がされていなかったら
#define _TREE_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CTree;		// 木

//--------------------------------------------
// クラス(木マネージャークラス)
//--------------------------------------------
class CTreeManager
{
public:				// 誰でもアクセスできる

	CTreeManager();			// コンストラクタ
	~CTreeManager();			// デストラクタ

	// メンバ関数
	void Regist(CTree* pThis);		// 登録処理
	void Uninit(void);						// 終了処理

	CTree* GetTop(void);				// 先頭の取得処理
	void Pull(CTree* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CTreeManager* Create(void);		// 生成処理
	static CTreeManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CTree* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CTreeManager* m_pManager;		// マネージャーの変数
};

#endif