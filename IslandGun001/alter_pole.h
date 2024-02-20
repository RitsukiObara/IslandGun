//===================================
//
// 石柱ヘッダー[alter_pole.h]
// Author 小原立暉
//
//===================================
#ifndef _ALTER_POLE_H_
#define _ALTER_POLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(石柱)
//-----------------------------------
class CAlterPole : public CModel
{
public:			// 誰でもアクセスできる

	CAlterPole();			// コンストラクタ
	~CAlterPole();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetEnableEmpty(const bool bEmpty);		// 空白状況の設定処理
	bool IsEmpty(void) const;					// 空白状況の取得処理

	// 静的メンバ関数
	static CAlterPole* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	bool m_bEmpty;		// 空白状況
};

#endif