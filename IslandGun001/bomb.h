//===================================
//
// 爆弾ヘッダー[bomb.h]
// Author 小原立暉
//
//===================================
#ifndef _BOMB_H_
#define _BOMB_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CBombFuse;		// 導火線

//-----------------------------------
// クラス定義(爆弾)
//-----------------------------------
class CBomb : public CModel
{
public:			// 誰でもアクセスできる

	CBomb();			// コンストラクタ
	~CBomb();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理

	// 静的メンバ関数
	static CBomb* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 生成処理

	static CListManager<CBomb*> GetList(void);			// リストの取得処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CBombFuse* m_pFuse;			// 導火線の情報

	// 静的メンバ変数
	static CListManager<CBomb*> m_list;		// リスト
};

#endif