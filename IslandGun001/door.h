//===================================
//
// ドアヘッダー[door.h]
// Author 小原立暉
//
//===================================
#ifndef _DOOR_H_
#define _DOOR_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(ドア)
//-----------------------------------
class CDoor : public CModel
{
public:			// 誰でもアクセスできる

	CDoor();		// コンストラクタ
	~CDoor();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CDoor* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CModel* m_pDoor;	// ドア本体の情報
};

#endif