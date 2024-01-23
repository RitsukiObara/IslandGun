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

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\GoldBone.x";		// モデルの名前
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CGoldBone*> CGoldBone::m_list = {};		// リスト

//==============================
// コンストラクタ
//==============================
CGoldBone::CGoldBone() : CModel(CObject::TYPE_GOLDBONE, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;	// 移動量

	// リストに追加する
	m_list.Regist(this);
}

//==============================
// デストラクタ
//==============================
CGoldBone::~CGoldBone()
{

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

	// 引き抜き処理
	m_list.Pull(this);
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
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));		// モデルの情報

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
// リストの取得処理
//=======================================
CListManager<CGoldBone*> CGoldBone::GetList(void)
{
	// リストマネージャーを返す
	return m_list;
}

//=======================================
// ヒット処理
//=======================================
void CGoldBone::Hit(void)
{
	// 終了処理
	Uninit();
}

//=======================================
// 取得状態処理
//=======================================
void CGoldBone::Get(void)
{

}