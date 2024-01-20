//===================================
//
// 金の骨ヘッダー[gold_bone.h]
// Author 小原立暉
//
//===================================
#ifndef _GOLD_BONE_H_
#define _GOLD_BONE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(金の骨)
//-----------------------------------
class CGoldBone : public CModel
{
public:			// 誰でもアクセスできる

	CGoldBone();					// コンストラクタ
	~CGoldBone();					// デストラクタ

	// リスト構造関係
	void SetPrev(CGoldBone* pPrev);	// 前のポインタの設定処理
	void SetNext(CGoldBone* pNext);	// 後のポインタの設定処理
	CGoldBone* GetPrev(void) const;	// 前のポインタの設定処理
	CGoldBone* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move);				// 情報の設定処理
	void Hit(void);					// ヒット処理

	// 静的メンバ関数
	static CGoldBone* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Get(void);			// 取得状態処理

	// メンバ変数
	D3DXVECTOR3 m_move;		// 移動量
	
	// リスト構造関係
	CGoldBone* m_pPrev;		// 前へのポインタ
	CGoldBone* m_pNext;		// 次へのポインタ
};

#endif