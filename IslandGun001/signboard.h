//===================================
//
// 看板ヘッダー[signboard.h]
// Author 小原立暉
//
//===================================
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CPushTiming;		// ボタン表示
class CSignboardExpl;	// 看板の説明

//-----------------------------------
// クラス定義(看板)
//-----------------------------------
class CSignboard : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_JUMP = 0,		// ジャンプの説明
		TYPE_MAX			// この列挙型の総数
	};

	CSignboard();			// コンストラクタ
	~CSignboard();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);					// 情報の設定処理

	// 静的メンバ関数
	static CSignboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 生成処理

	static CListManager<CSignboard*> GetList(void);			// リストの取得処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CPushTiming* m_pButton;		// ボタンの情報
	CSignboardExpl* m_pExplain;	// 説明の情報
	TYPE m_type;				// 種類
	bool m_bDisp;				// 描画状況

	// 静的メンバ変数
	static CListManager<CSignboard*> m_list;		// リスト
};

#endif