//===========================================
//
// 木のメイン処理[tree.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "tree.h"
#include "renderer.h"
#include "useful.h"

#include "tree_manager.h"

#include "palm_tree.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const CXFile::TYPE FILE_TYPE[CTree::TYPE_MAX] =		// Xファイルの種類
	{
		CXFile::TYPE_PALMTREE,			// ヤシの木
	};
}

//==============================
// コンストラクタ
//==============================
CTree::CTree(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// 全ての値をクリアする
	m_type = TYPE_PALM;		// 種類

	// 全ての値をクリアする
	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CTreeManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CTreeManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CTree::~CTree()
{

}

//============================
// 前のポインタの設定処理
//============================
void CTree::SetPrev(CTree* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CTree::SetNext(CTree* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CTree* CTree::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CTree* CTree::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CTree::Init(void)
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
void CTree::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CTreeManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CTreeManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CTree::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CTree::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CTree::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(rot);					// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(FILE_TYPE[type]);	// モデルの情報

	// 全ての値を設定する
	m_type = type;		// 種類
}

//=====================================
// ヒット処理
//=====================================
void CTree::Hit(void)
{

}

//=======================================
// 生成処理
//=======================================
CTree* CTree::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ローカルオブジェクトを生成
	CTree* pTree = nullptr;	// インスタンスを生成

	if (pTree == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case CTree::TYPE_PALM:		// ヤシの木

			// ヤシの木を生成する
			pTree = new CPalmTree;

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTree != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTree->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTree->SetData(pos, rot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 木のポインタを返す
	return pTree;
}

//=======================================
// 種類の取得処理
//=======================================
CTree::TYPE CTree::GetType(void) const
{
	// 種類を返す
	return m_type;
}