//============================================
//
// リザルトヘッダー[result.h]
// Author：小原立暉
//
//============================================
#ifndef _RESULT_H_			//このマクロ定義がされていなかったら
#define _RESULT_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "scene.h"

//--------------------------------------------
// クラス(ロゴ画面クラス)
//--------------------------------------------
class CResult : public CScene
{
public:				// 誰でもアクセスできる

	CResult();		// コンストラクタ
	~CResult();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

private:					// 自分だけアクセスできる
};

#endif