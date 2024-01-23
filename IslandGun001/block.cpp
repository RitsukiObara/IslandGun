//===========================================
//
// ブロックのメイン処理[block.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "block.h"
#include "texture.h"
#include "useful.h"

#include "block_manager.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Rock.x";		// モデルの名前
}

//==============================
// コンストラクタ
//==============================
CBlock::CBlock() : CModel(TYPE_BLOCK, PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CBlockManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CBlockManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CBlock::~CBlock()
{

}

//============================
// 前のポインタの設定処理
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CBlock* CBlock::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CBlock* CBlock::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CBlock::Init(void)
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
void CBlock::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CBlockManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CBlock::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CBlock::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CBlock* pBlock = nullptr;		// インスタンスを生成

	if (pBlock == nullptr)
	{ // オブジェクトが NULL の場合

		// ブロックを生成する
		pBlock = new CBlock;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBlock != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBlock->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBlock->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ブロックのポインタを返す
	return pBlock;
}