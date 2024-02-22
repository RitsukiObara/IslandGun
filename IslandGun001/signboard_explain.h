//===================================
//
// 看板の説明ヘッダー[signboard_explain.h]
// Author 小原立暉
//
//===================================
#ifndef _SIGNBOARD_EXPLAIN_H_
#define _SIGNBOARD_EXPLAIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"
#include "signboard.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CObject2D;			// オブジェクト2D

//-----------------------------------
// クラス定義(CSignboardExpl)
//-----------------------------------
class CSignboardExpl : public CObject
{
public:			// 誰でもアクセスできる

	// 構造体定義(画面)
	struct SScreen
	{
		float fAlpha;			// 透明度
		CObject2D* pScreen;		// ロゴマークの情報
	};

	CSignboardExpl();			// コンストラクタ
	~CSignboardExpl();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const CSignboard::TYPE type);						// 情報の設定処理

	// 静的メンバ関数
	static CSignboardExpl* Create(const CSignboard::TYPE type);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	SScreen m_screen;		// 画面の情報
	CObject2D* m_pExplain;	// 説明のポリゴン
};

#endif