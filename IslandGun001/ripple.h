//===================================
//
// 波紋ヘッダー[ripple.h]
// Author：小原立暉
//
//===================================
#ifndef _RIPPLE_H_			// このマクロ定義がされていなかったら
#define _RIPPLE_H_			// 2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(着地の波紋)
//-----------------------------------
class CRipple : public CModel
{
public:		// 誰でもアクセスできる

	CRipple(const CObject::TYPE type = TYPE_RIPPLE, const CObject::PRIORITY priority = PRIORITY_PLAYER);	// オーバーロードコンストラクタ
	virtual ~CRipple();		// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void) override;	// 初期化処理
	virtual void Uninit(void) override;		// 終了処理
	virtual void Update(void) override;		// 更新処理
	virtual void Draw(void) override;		// 描画処理

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);			// 情報の設定処理

	// セット・ゲット関係
	void SetAlpha(const float fAlpha);		// 透明度の設定処理
	float GetAlpha(void) const;				// 透明度の取得処理

	// 静的メンバ関数
	static CRipple* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// 生成処理

private:	// 自分だけアクセスできる

	// メンバ変数
	float m_fAlpha;								// 透明度
};

#endif