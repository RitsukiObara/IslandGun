//============================================
//
// 炎注意のメイン処理[fire_warning.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "fire_warning.h"
#include "renderer.h"
#include "manager.h"
#include "useful.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const int NUM_ANGLE = 8;		// 角度の数
	const float RADIUS = 200.0f;	// 半径
	const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);		// 色の初期値
	const float INIT_COL_ANGLE = D3DX_PI;	// 色の向きの初期値
	const float ADD_COL_ANGLE = 0.005f;		// 色の向きの加算数
}

//=========================================
// コンストラクタ
//=========================================
CFireWarning::CFireWarning() : CObject3DFan(TYPE_FIREWARNING, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_col = INIT_COL;				// 色
	m_fColAngle = INIT_COL_ANGLE;	// 色の向き
	m_fAddColAngle = 0.0f;			// 色の向きの加算数
}

//=========================================
// デストラクタ
//=========================================
CFireWarning::~CFireWarning()
{

}

//===========================================
// オブジェクト3Dの初期化処理
//===========================================
HRESULT CFireWarning::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//===========================================
// オブジェクト3Dの終了処理
//===========================================
void CFireWarning::Uninit(void)
{
	// 終了処理
	CObject3DFan::Uninit();
}

//===========================================
// オブジェクト3Dの更新処理
//===========================================
void CFireWarning::Update(void)
{
	// 色を設定する
	m_fAddColAngle += ADD_COL_ANGLE;
	m_fColAngle += m_fAddColAngle;
	useful::RotNormalize(&m_fColAngle);
	m_col.g = sinf(m_fColAngle) * INIT_COL.g;
	
	// 頂点の設定処理
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(m_col);
}

//===========================================
// オブジェクト3Dの描画処理
//===========================================
void CFireWarning::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Zテストの有効/無効設定

	// 描画処理
	CObject3DFan::Draw();

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Zテストの有効/無効設定
}

//===========================================
// 情報の設定処理
//===========================================
void CFireWarning::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetNumAngle(NUM_ANGLE);			// 角度の総数
	SetRadius(RADIUS);				// 半径

	// 全ての値を設定する
	m_col = INIT_COL;				// 色
	m_fColAngle = INIT_COL_ANGLE;	// 色の向き
	m_fAddColAngle = 0.0f;			// 色の向きの加算数
}

//===========================================
// 生成処理
//===========================================
CFireWarning* CFireWarning::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CFireWarning* pWarning = nullptr;	// 炎注意のインスタンスを生成

	if (pWarning == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pWarning = new CFireWarning;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pWarning != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 情報の設定処理
		pWarning->SetData(pos);

		// 初期化処理
		if (FAILED(pWarning->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 炎注意のポインタを返す
	return pWarning;
}