//===================================
//
// 弾ヘッダー[bullet.h]
// Author 小原立暉
//
//===================================
#ifndef _BULLET_H_
#define _BULLET_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(CBullet)
//-----------------------------------
class CBullet : public CBillboard
{
public:

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_HANDGUN = 0,	// 二丁拳銃
		TYPE_SHOTGUN,		// 散弾
		TYPE_MAX			// この列挙型の総数
	};

	CBullet();				// コンストラクタ
	~CBullet();				// デストラクタ

	// リスト構造関係
	void SetPrev(CBullet* pPrev);	// 前のポインタの設定処理
	void SetNext(CBullet* pNext);	// 後のポインタの設定処理
	CBullet* GetPrev(void) const;	// 前のポインタの設定処理
	CBullet* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const float fRot, const TYPE type);				// 情報の設定処理

	// 静的メンバ関数
	static CBullet* Create(const D3DXVECTOR3& pos, const float fRot, const TYPE type);		// 生成処理

private:

	// メンバ変数
	D3DXVECTOR3 m_move;		// 移動量
	TYPE m_type;			// 種類
	int m_nLife;			// 寿命
	float m_fRot;			// 飛んでいく向き

	// リスト構造関係
	CBullet* m_pPrev;		// 前へのポインタ
	CBullet* m_pNext;		// 次へのポインタ
};

#endif