//===========================================
//
// 拳銃のメイン処理[handgun.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "handgun.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CHandgun::CHandgun() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMtxParent = nullptr;		// 親のマトリックス
}

//==============================
// デストラクタ
//==============================
CHandgun::~CHandgun()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CHandgun::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CHandgun::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CHandgun::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CHandgun::Draw(void)
{
	// 描画処理
	CModel::DrawMatrix(*m_pMtxParent);
}

//=====================================
// 情報の設定処理
//=====================================
void CHandgun::SetData(const D3DXVECTOR3& pos, D3DXMATRIX* mtx)
{
	// 情報の設定処理
	SetPos(pos);						// 位置
	SetPosOld(pos);						// 前回の位置
	SetRot(NONE_D3DXVECTOR3);			// 向き
	SetScale(NONE_SCALE);				// 拡大率
	SetFileData(CXFile::TYPE_HANDGUN);	// モデル情報

	// 全ての値をクリアする
	m_pMtxParent = mtx;		// 親のマトリックス
}

//=======================================
// 生成処理
//=======================================
CHandgun* CHandgun::Create(const D3DXVECTOR3& pos, D3DXMATRIX* mtx)
{
	// ローカルオブジェクトを生成
	CHandgun* pGun = nullptr;	// インスタンスを生成

	if (pGun == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pGun = new CHandgun;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pGun != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pGun->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pGun->SetData(pos, mtx);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 拳銃のポインタを返す
	return pGun;
}