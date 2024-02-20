//===========================================
//
// 石柱のメイン処理[alter_pole.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "alter_pole.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\AlterPole.x";		// モデルの名前
}

//==============================
// コンストラクタ
//==============================
CAlterPole::CAlterPole() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_bEmpty = true;			// 空白状況
}

//==============================
// デストラクタ
//==============================
CAlterPole::~CAlterPole()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CAlterPole::Init(void)
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
//ブロックの終了処理
//========================================
void CAlterPole::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//========================================
//ブロックの更新処理
//========================================
void CAlterPole::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CAlterPole::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CAlterPole::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報

	// 全ての値を設定する
	m_bEmpty = true;				// 空白状況
}

//=======================================
// 生成処理
//=======================================
CAlterPole* CAlterPole::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CAlterPole* pPole = nullptr;		// インスタンスを生成

	if (pPole == nullptr)
	{ // オブジェクトが NULL の場合

		// ブロックを生成する
		pPole = new CAlterPole;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPole != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPole->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPole->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 石柱のポインタを返す
	return pPole;
}

//=======================================
// 空白状況の設定処理
//=======================================
void CAlterPole::SetEnableEmpty(const bool bEmpty)
{
	// 空白状況を設定する
	m_bEmpty = bEmpty;
}

//=======================================
// 空白状況の取得処理
//=======================================
bool CAlterPole::IsEmpty(void) const
{
	// 空白状況を返す
	return m_bEmpty;
}