//===========================================
//
// 風船のメイン処理[balloon.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "balloon.h"
#include "renderer.h"
#include "useful.h"

#include "model.h"
#include "balloon_rope.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Balloon.x";		// 風船モデルの名前
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CBalloon*> CBalloon::m_list = {};			// リスト情報

//==============================
// コンストラクタ
//==============================
CBalloon::CBalloon() : CObject(CObject::TYPE_TARGET, DIM_3D, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pos = NONE_D3DXVECTOR3;	// 位置
	m_pBalloon = nullptr;		// 風船のモデル
	m_pRope = nullptr;			// 紐のモデル
}

//==============================
// デストラクタ
//==============================
CBalloon::~CBalloon()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CBalloon::Init(void)
{
	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CBalloon::Uninit(void)
{
	if (m_pBalloon != nullptr)
	{ // 風船が NULL じゃない場合

		// 風船の終了処理
		m_pBalloon->Uninit();
		m_pBalloon = nullptr;
	}

	if (m_pRope != nullptr)
	{ // 紐が NULL じゃない場合

		// 紐の終了処理
		m_pRope->Uninit();
		m_pRope = nullptr;
	}

	// 本体の終了処理
	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CBalloon::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CBalloon::Draw(void)
{
	if (m_pBalloon != nullptr)
	{ // 風船が NULL じゃない場合

		// 風船の描画処理
		m_pBalloon->Draw();
	}

	if (m_pRope != nullptr)
	{ // 紐が NULL じゃない場合

		// 紐の描画処理
		m_pRope->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CBalloon::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を設定する
	m_pos = pos;	// 位置

	if (m_pBalloon == nullptr)
	{ // 風船が NULL の場合

		// 風船を生成
		m_pBalloon = CModel::Create(TYPE_NONE, PRIORITY_ENTITY);

		// 情報の設定処理
		m_pBalloon->SetPos(pos);
		m_pBalloon->SetPosOld(pos);
		m_pBalloon->SetRot(NONE_D3DXVECTOR3);
		m_pBalloon->SetScale(NONE_SCALE);
		m_pBalloon->SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
	}

	if (m_pRope == nullptr)
	{ // 紐が NULL の場合

		// 風船を生成
		m_pRope = CBalloonRope::Create(m_pBalloon->GetMatrixPoint());
	}
}

//=======================================
// ヒット処理
//=======================================
void CBalloon::Hit(void)
{

}

//=======================================
// 生成処理
//=======================================
CBalloon* CBalloon::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CBalloon* pTarget = nullptr;	// インスタンスを生成

	if (pTarget == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pTarget = new CBalloon;
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
CListManager<CBalloon*> CBalloon::GetList(void)
{
	// リスト構造の情報を返す
	return m_list;
}