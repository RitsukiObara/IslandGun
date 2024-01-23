//===================================
//
// 岩ヘッダー[rock.h]
// Author 小原立暉
//
//===================================
#ifndef _ROCK_H_
#define _ROCK_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// クラス定義(岩)
//-----------------------------------
class CRock : public CModel
{
public:			// 誰でもアクセスできる

	CRock();			// コンストラクタ
	~CRock();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// 情報の設定処理
	void Break(void);				// 破壊処理

	// 静的メンバ関数
	static CRock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// 生成処理

	static CListManager<CRock*> GetList(void);			// リストの取得処理

private:		// 自分だけアクセスできる
	
	// メンバ変数
	int m_nBreakLevel;	// 破壊レベル

	// 静的メンバ変数
	static CListManager<CRock*> m_list;		// リスト
};

#endif