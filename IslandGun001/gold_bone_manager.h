//============================================
//
// 金の骨マネージャーヘッダー[gold_bone_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _GOLD_BONE_MANAGER_H_		// このマクロ定義がされていなかったら
#define _GOLD_BONE_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CGoldBone;		// 金の骨

//--------------------------------------------
// クラス(金の骨マネージャークラス)
//--------------------------------------------
class CGoldBoneManager
{
public:				// 誰でもアクセスできる

	CGoldBoneManager();			// コンストラクタ
	~CGoldBoneManager();			// デストラクタ

	// メンバ関数
	void Regist(CGoldBone* pThis);		// 登録処理
	void Uninit(void);						// 終了処理

	CGoldBone* GetTop(void);				// 先頭の取得処理
	void Pull(CGoldBone* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CGoldBoneManager* Create(void);		// 生成処理
	static CGoldBoneManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CGoldBone* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CGoldBoneManager* m_pManager;		// マネージャーの変数
};

#endif