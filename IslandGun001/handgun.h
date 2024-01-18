//===================================
//
// 拳銃ヘッダー[handgun.h]
// Author 小原立暉
//
//===================================
#ifndef _HANDGUN_H_
#define _HANDGUN_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(拳銃)
//-----------------------------------
class CHandgun : public CModel
{
public:			// 誰でもアクセスできる

	CHandgun();			// コンストラクタ
	~CHandgun();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot, D3DXMATRIX* mtx);				// 情報の設定処理

	// セット・ゲット関係
	void SetEnableDisp(const bool bDisp);		// 描画状況の設定処理
	bool IsDisp(void) const;					// 描画状況の取得処理

	// 静的メンバ関数
	static CHandgun* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot, D3DXMATRIX* mtx);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	D3DXMATRIX* m_pMtxParent;		// 親のマトリックス
	bool m_bDisp;					// 描画状況
};

#endif