//============================================
//
// チュートリアル画面ヘッダー[tutorial.h]
// Author：小原立暉
//
//============================================
#ifndef _TUTORIAL_H_			//このマクロ定義がされていなかったら
#define _TUTORIAL_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "scene.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CTutorialPlayer;			// チュートリアルプレイヤー

//--------------------------------------------
// クラス(チュートリアルクラス)
//--------------------------------------------
class CTutorial : public CScene
{
public:				// 誰でもアクセスできる

	CTutorial();		// コンストラクタ
	~CTutorial();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;		// 初期化処理
	void Uninit(void) override;			// 終了処理
	void Update(void) override;			// 更新処理
	void Draw(void) override;			// 描画処理

	// 静的メンバ関数
	static CTutorialPlayer* GetPlayer(void);		// プレイヤーの取得処理
	static void SetEnableExplain(const bool bExpl);	// 説明状況の設定処理
	static bool IsExplain(void);					// 説明状況の取得処理

	static void DeletePlayer(void);				// プレイヤーのNULL化処理

private:			// 自分だけアクセスできる

	// メンバ変数
	int m_nEndCount;					// 終了までのカウント

	// 静的メンバ変数
	static CTutorialPlayer* m_pPlayer;	// プレイヤーの情報
	static bool m_bExpl;				// 説明状況
};

#endif