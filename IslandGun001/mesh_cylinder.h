//=====================================================
//
// メッシュシリンダーヘッダー [mesh_cylinder.h]
// Author：小原立暉
//
//=====================================================
#ifndef _MESH_CYLINDER_H_			// このマクロ定義がされていない場合
#define _MESH_CYLINDER_H_			// 二重インクルード防止のマクロを定義する

//*****************************************************
// インクルードファイル
//*****************************************************
#include "Objectmesh.h"

//-----------------------------------------------------
// クラス定義(メッシュシリンダー)
//-----------------------------------------------------
class CMeshCylinder : public CMesh
{
public:		// 誰でもアクセスできる

	CMeshCylinder(CObject::PRIORITY priority = PRIORITY_BG);		// オーバーロードコンストラクタ
	virtual ~CMeshCylinder();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircum, const float fHeight, const SGrid& Divi);			// 情報の設定処理
	void SetVertex(void);	// 頂点の設定処理

	// 静的メンバ関数
	static CMeshCylinder* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircum, const float fHeight, const SGrid& Divi, const PRIORITY priority);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	float m_fCircumSize;		// 幅のサイズ
	float m_fHeightSize;		// 縦のサイズ
	float m_fHeightSizeDivi;	// 縦1面ずつのサイズ
};


#endif