//============================================
//
// 気絶演出ヘッダー[stun.h]
// Author：小原立暉
//
//============================================
#ifndef _STUN_H_					// このマクロ定義がされていなかったら
#define _STUN_H_					// 2重インクルード防止のマクロを定義する
//********************************************
// インクルードファイル
//********************************************
#include "object.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_STUN		(4)		// 気絶演出の最大数

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CBillboard;			// ビルボード

//--------------------------------------------
// クラス定義(気絶演出)
//--------------------------------------------
class CStun : public CObject
{
public:				// 誰でもアクセスできる

	CStun();				// コンストラクタ
	~CStun();				// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3 pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetPos(const D3DXVECTOR3& pos);				// 位置の設定処理

	// 静的メンバ変数
	static CStun* Create(const D3DXVECTOR3 pos);		// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	D3DXVECTOR3 m_pos;				// 位置
	float m_fRot;					// 回転用の向き
	CBillboard* m_apStun[MAX_STUN];	// 気絶演出の情報
};

#endif