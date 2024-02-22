//===========================================
//
// 的のメイン処理[tutorial_target.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "tutorial_target.h"
#include "renderer.h"
#include "useful.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Target.x";		// モデルの名前
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CTarget*> CTarget::m_list = {};			// リスト情報

//==============================
// コンストラクタ
//==============================
CTarget::CTarget() : CModel(CObject::TYPE_TARGET, CObject::PRIORITY_ENTITY)
{

}

//==============================
// デストラクタ
//==============================
CTarget::~CTarget()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CTarget::Init(void)
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
void CTarget::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CTarget::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CTarget::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CTarget::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデル情報
}

//=======================================
// ヒット処理
//=======================================
void CTarget::Hit(void)
{

}

//=======================================
// 生成処理
//=======================================
CTarget* CTarget::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CTarget* pTarget = nullptr;	// インスタンスを生成

	if (pTarget == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pTarget = new CTarget;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTarget != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTarget->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTarget->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 的のポインタを返す
	return pTarget;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CTarget*> CTarget::GetList(void)
{
	// リスト構造の情報を返す
	return m_list;
}