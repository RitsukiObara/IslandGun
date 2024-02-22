//===================================
//
// 的ヘッダー[tutorial_target.h]
// Author 小原立暉
//
//===================================
#ifndef _TUTORIAL_TARGET_H_
#define _TUTORIAL_TARGET_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// クラス定義(ターゲット)
//-----------------------------------
class CTarget : public CModel
{
public:			// 誰でもアクセスできる

	CTarget();			// コンストラクタ
	~CTarget();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理
	void Hit(void);					// ヒット処理

	// 静的メンバ関数
	static CTarget* Create(const D3DXVECTOR3& pos);		// 生成処理

	static CListManager<CTarget*> GetList(void);		// リストの取得処理

private:		// 自分だけアクセスできる

	// 静的メンバ変数
	static CListManager<CTarget*> m_list;		// リスト情報
};

#endif