//===================================
//
// 爆弾花ヘッダー[bang_flower.h]
// Author 小原立暉
//
//===================================
#ifndef _BANG_FLOWER_H_
#define _BANG_FLOWER_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// クラス定義(爆弾花)
//-----------------------------------
class CBangFlower : public CModel
{
public:			// 誰でもアクセスできる

	CBangFlower();			// コンストラクタ
	~CBangFlower();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale);				// 情報の設定処理

	// 静的メンバ関数
	static CBangFlower* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale);	// 生成処理

	static CListManager<CBangFlower*> GetList(void);			// リストの取得処理

private:		// 自分だけアクセスできる

	// 静的メンバ変数
	static CListManager<CBangFlower*> m_list;		// リスト
};

#endif