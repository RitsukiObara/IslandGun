//===================================
//
// 小判ヘッダー[coin.h]
// Author 小原立暉
//
//===================================
#ifndef _COIN_H_
#define _COIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(小判)
//-----------------------------------
class CCoin : public CModel
{
public:			// 誰でもアクセスできる

	CCoin();					// コンストラクタ
	~CCoin();					// デストラクタ

	// リスト構造関係
	void SetPrev(CCoin* pPrev);	// 前のポインタの設定処理
	void SetNext(CCoin* pNext);	// 後のポインタの設定処理
	CCoin* GetPrev(void) const;	// 前のポインタの設定処理
	CCoin* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);			// 情報の設定処理

	// 静的メンバ関数
	static CCoin* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// リスト構造関係
	CCoin* m_pPrev;	// 前へのポインタ
	CCoin* m_pNext;	// 次へのポインタ
};

#endif