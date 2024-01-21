//============================================
//
// ヤシの実マネージャーヘッダー[palm_fruit_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _PALM_FRUIT_MANAGER_H_		// このマクロ定義がされていなかったら
#define _PALM_FRUIT_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CPalmFruit;		// ヤシの実

//--------------------------------------------
// クラス(ヤシの実マネージャークラス)
//--------------------------------------------
class CPalmFruitManager
{
public:				// 誰でもアクセスできる

	CPalmFruitManager();			// コンストラクタ
	~CPalmFruitManager();			// デストラクタ

	// メンバ関数
	void Regist(CPalmFruit* pThis);		// 登録処理
	void Uninit(void);						// 終了処理

	CPalmFruit* GetTop(void);				// 先頭の取得処理
	void Pull(CPalmFruit* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CPalmFruitManager* Create(void);		// 生成処理
	static CPalmFruitManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CPalmFruit* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CPalmFruitManager* m_pManager;		// マネージャーの変数
};

#endif