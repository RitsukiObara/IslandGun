//===================================
//
// タイトルロゴヘッダー[title_logo.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CTitleLogo)
//-----------------------------------
class CTitleLogo : public CObject2D
{
public:			// 誰でもアクセスできる

	CTitleLogo();			// コンストラクタ
	~CTitleLogo();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static CTitleLogo* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

};

#endif