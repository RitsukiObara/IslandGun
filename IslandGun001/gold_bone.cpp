//===========================================
//
// 金の骨のメイン処理[gold_bone.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "gold_bone.h"
#include "renderer.h"
#include "useful.h"

#include "gold_bone_manager.h"

//==============================
// コンストラクタ
//==============================
CGoldBone::CGoldBone() : CModel(CObject::TYPE_GOLDBONE, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;	// 移動量

	// 全ての値をクリアする
	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CGoldBoneManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CGoldBoneManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CGoldBone::~CGoldBone()
{

}

//============================
// 前のポインタの設定処理
//============================
void CGoldBone::SetPrev(CGoldBone* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CGoldBone::SetNext(CGoldBone* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CGoldBone* CGoldBone::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CGoldBone* CGoldBone::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CGoldBone::Init(void)
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
void CGoldBone::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CGoldBoneManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CGoldBoneManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CGoldBone::Update(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動させる
	pos += m_move;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
//ブロックの描画処理
//=====================================
void CGoldBone::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CGoldBone::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_GOLDBONE);		// モデルの情報

	// 全ての値を設定する
	m_move = move;	// 移動量
}

//=======================================
// 生成処理
//=======================================
CGoldBone* CGoldBone::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ローカルオブジェクトを生成
	CGoldBone* pBone = nullptr;	// インスタンスを生成

	if (pBone == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pBone = new CGoldBone;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBone != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBone->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBone->SetData(pos, move);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 金の骨のポインタを返す
	return pBone;
}

//=======================================
// ヒット処理
//=======================================
void CGoldBone::Hit(void)
{

}

//=======================================
// 取得状態処理
//=======================================
void CGoldBone::Get(void)
{

}