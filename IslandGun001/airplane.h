//===================================
//
// 飛行機ヘッダー[airplane.h]
// Author 小原立暉
//
//===================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CPropeller;			// プロペラ

//-----------------------------------
// クラス定義(飛行機)
//-----------------------------------
class CAirplane : public CModel
{
public:			// 誰でもアクセスできる

	CAirplane();			// コンストラクタ
	~CAirplane();			// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(D3DXVECTOR3 pos);				// 情報の設定処理

	// 静的メンバ関数
	static CAirplane* Create(D3DXVECTOR3 pos);	// 生成処理

	static CListManager<CAirplane*> GetList(void);			// リストの取得処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CPropeller* m_pPropeller;		// プロペラの情報

	// 静的メンバ変数
	static CListManager<CAirplane*> m_list;		// リスト
};

#endif