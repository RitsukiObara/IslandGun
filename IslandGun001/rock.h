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

//-----------------------------------
// クラス定義(岩)
//-----------------------------------
class CRock : public CModel
{
public:			// 誰でもアクセスできる

	CRock(CObject::TYPE type = TYPE_ROCK, PRIORITY priority = PRIORITY_BLOCK);				// オーバーロードコンストラクタ
	~CRock();		// デストラクタ

	// リスト構造関係
	void SetPrev(CRock* pPrev);		// 前のポインタの設定処理
	void SetNext(CRock* pNext);		// 後のポインタの設定処理
	CRock* GetPrev(void) const;		// 前のポインタの設定処理
	CRock* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// 情報の設定処理
	void Break(void);				// 破壊処理

	// 静的メンバ関数
	static CRock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// 生成処理

private:		// 自分だけアクセスできる
	
	// メンバ変数
	int m_nBreakLevel;	// 破壊レベル

	// リスト構造関係
	CRock* m_pPrev;		// 前へのポインタ
	CRock* m_pNext;		// 次へのポインタ
};

#endif