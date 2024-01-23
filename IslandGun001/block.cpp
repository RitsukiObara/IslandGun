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

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Rock.x";		// モデルの名前
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CBlock*> CBlock::m_list = {};			// リスト

//==============================
// コンストラクタ
//==============================
CBlock::CBlock() : CModel(TYPE_BLOCK, PRIORITY_BLOCK)
{
	// リストに追加する
	m_list.Regist(this);
}

//==============================
// デストラクタ
//==============================
CBlock::~CBlock()
{

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

	// 引き抜き処理
	m_list.Pull(this);
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

//=======================================
// リストの取得処理
//=======================================
CListManager<CBlock*> CBlock::GetList(void)
{
	// リストマネージャーを返す
	return m_list;
}