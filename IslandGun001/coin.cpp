//===========================================
//
// 小判のメイン処理[coin.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "coin.h"
#include "useful.h"

#include "coin_manager.h"

//==============================
// コンストラクタ
//==============================
CCoin::CCoin() : CModel(CObject::TYPE_COIN, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする

	// 全ての値をクリアする
	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CCoinManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CCoinManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CCoin::~CCoin()
{

}

//============================
// 前のポインタの設定処理
//============================
void CCoin::SetPrev(CCoin* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CCoin::SetNext(CCoin* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CCoin* CCoin::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CCoin* CCoin::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CCoin::Init(void)
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
void CCoin::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CCoinManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CCoinManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CCoin::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	// 向きを加算する
	rot.y += 0.01f;

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	// 向きを適用する
	SetRot(rot);
}

//=====================================
//ブロックの描画処理
//=====================================
void CCoin::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CCoin::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);						// 位置
	SetPosOld(pos);						// 前回の位置
	SetRot(NONE_D3DXVECTOR3);			// 向き
	SetScale(NONE_SCALE);				// 拡大率
	SetFileData(CXFile::TYPE_PLAYERHEAD);	// モデルの情報

	// 全ての値を初期化する
}

//=======================================
// 生成処理
//=======================================
CCoin* CCoin::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCoin* pCoin = nullptr;	// インスタンスを生成

	if (pCoin == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pCoin = new CCoin;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCoin != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCoin->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCoin->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ネジのポインタを返す
	return pCoin;
}