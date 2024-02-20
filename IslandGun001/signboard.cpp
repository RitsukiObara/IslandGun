//===========================================
//
// 看板のメイン処理[signboard.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "signboard.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Signboard.x";		// モデルの名前
}

//==============================
// コンストラクタ
//==============================
CSignboard::CSignboard() : CModel(TYPE_SIGNBOARD, PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_type = TYPE_JUMP;		// 種類
}

//==============================
// デストラクタ
//==============================
CSignboard::~CSignboard()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CSignboard::Init(void)
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
void CSignboard::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//========================================
//ブロックの更新処理
//========================================
void CSignboard::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CSignboard::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CSignboard::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(rot);					// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報

	// 全ての値を設定する
	m_type = type;		// 種類
}

//=======================================
// 生成処理
//=======================================
CSignboard* CSignboard::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ローカルオブジェクトを生成
	CSignboard* pSignboard = nullptr;		// インスタンスを生成

	if (pSignboard == nullptr)
	{ // オブジェクトが NULL の場合

		// ブロックを生成する
		pSignboard = new CSignboard;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSignboard != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pSignboard->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSignboard->SetData(pos, rot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 看板のポインタを返す
	return pSignboard;
}