//===========================================
//
// 爆弾のメイン処理[bomb.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "bomb.h"
#include "texture.h"
#include "useful.h"

#include "bomb_fuse.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\BombBody.x";		// モデルの名前
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CBomb*> CBomb::m_list = {};			// リスト

//==============================
// コンストラクタ
//==============================
CBomb::CBomb() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pFuse = nullptr;			// 導火線の情報

	// リストに追加する
	m_list.Regist(this);
}

//==============================
// デストラクタ
//==============================
CBomb::~CBomb()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CBomb::Init(void)
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
void CBomb::Uninit(void)
{
	if (m_pFuse != nullptr)
	{ // 導火線が NULL じゃない場合

		// 終了処理
		m_pFuse->Uninit();
		m_pFuse = nullptr;
	}

	// 終了処理
	CModel::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//========================================
//ブロックの更新処理
//========================================
void CBomb::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CBomb::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pFuse != nullptr)
	{ // 導火線が NULL じゃない場合

		// 導火線の描画処理
		m_pFuse->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CBomb::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(rot);					// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報

	// 全ての値を設定する
	m_pFuse = CBombFuse::Create(GetMatrixPoint());		// 導火線の情報
}

//=======================================
// 生成処理
//=======================================
CBomb* CBomb::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CBomb* pBomb = nullptr;			// 爆弾を生成

	if (pBomb == nullptr)
	{ // オブジェクトが NULL の場合

		// ブロックを生成する
		pBomb = new CBomb;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBomb != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBomb->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBomb->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 爆弾のポインタを返す
	return pBomb;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CBomb*> CBomb::GetList(void)
{
	// リストマネージャーを返す
	return m_list;
}