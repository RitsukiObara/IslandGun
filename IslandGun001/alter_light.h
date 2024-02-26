//============================================
//
// 祭壇の光ヘッダー[alter_light.h]
// Author：小原立暉
//
//============================================
#ifndef _ALTER_LIGHT_H_			//このマクロ定義がされていなかったら
#define _ALTER_LIGHT_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// クラス(祭壇の光クラス)
//--------------------------------------------
class CAlterLight : public CBillboard
{
public:			// 誰でもアクセスできる

	CAlterLight();		// コンストラクタ
	~CAlterLight();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// 静的メンバ関数
	static CAlterLight* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	float m_fAddSize;		// サイズの追加量
};

#endif