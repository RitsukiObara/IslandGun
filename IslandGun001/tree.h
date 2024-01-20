//===================================
//
// 木ヘッダー[tree.h]
// Author 小原立暉
//
//===================================
#ifndef _TREE_H_
#define _TREE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(木)
//-----------------------------------
class CTree : public CModel
{
public:			// 誰でもアクセスできる

	CTree();					// コンストラクタ
	~CTree();					// デストラクタ

	// リスト構造関係
	void SetPrev(CTree* pPrev);	// 前のポインタの設定処理
	void SetNext(CTree* pNext);	// 後のポインタの設定処理
	CTree* GetPrev(void) const;	// 前のポインタの設定処理
	CTree* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理

	// 静的メンバ関数
	static CTree* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	
	// リスト構造関係
	CTree* m_pPrev;		// 前へのポインタ
	CTree* m_pNext;		// 次へのポインタ
};

#endif