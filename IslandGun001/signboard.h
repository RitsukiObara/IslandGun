//===================================
//
// 看板ヘッダー[signboard.h]
// Author 小原立暉
//
//===================================
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(看板)
//-----------------------------------
class CSignboard : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_JUMP = 0,		// ジャンプの説明
		TYPE_MAX			// この列挙型の総数
	};

	CSignboard();			// コンストラクタ
	~CSignboard();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);					// 情報の設定処理

	// 静的メンバ関数
	static CSignboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	TYPE m_type;		// 種類
};

#endif