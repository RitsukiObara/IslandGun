//===========================================
//
// 飛行機のメイン処理[airplane.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "airplane.h"
#include "useful.h"

#include "propeller.h"

//-------------------------------------------
// 定数定義
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Airplane.x";		// モデルのパス名
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CAirplane*> CAirplane::m_list = {};		// リスト

//==============================
// コンストラクタ
//==============================
CAirplane::CAirplane() : CModel(CObject::TYPE_AIRPLANE, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pPropeller = nullptr;		// プロペラの情報

	// リストに追加する
	m_list.Regist(this);
}

//==============================
// デストラクタ
//==============================
CAirplane::~CAirplane()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CAirplane::Init(void)
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
// 破片の終了処理
//========================================
void CAirplane::Uninit(void)
{
	if (m_pPropeller != nullptr)
	{ // プロペラが NULL じゃない場合

		// 終了処理
		m_pPropeller->Uninit();
		m_pPropeller = nullptr;
	}

	// 終了処理
	CModel::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//=====================================
// 破片の更新処理
//=====================================
void CAirplane::Update(void)
{
	if (m_pPropeller != nullptr)
	{ // プロペラが NULL じゃない場合

		// 更新処理
		m_pPropeller->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CAirplane::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pPropeller != nullptr)
	{ // プロペラの情報が NULL じゃない場合

		// プロペラの描画処理
		m_pPropeller->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CAirplane::SetData(D3DXVECTOR3 pos)
{
	// 情報の設定処理
	SetPos(pos);						// 位置
	SetPosOld(pos);						// 前回の位置
	SetRot(NONE_D3DXVECTOR3);			// 向き
	SetScale(NONE_SCALE);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデル情報

	// 全ての値を設定する
	m_pPropeller = CPropeller::Create(GetMatrixPoint());		// プロペラの情報
}

//=======================================
// 生成処理
//=======================================
CAirplane* CAirplane::Create(D3DXVECTOR3 pos)
{
	// ローカルオブジェクトを生成
	CAirplane* pAirplane = nullptr;	// インスタンスを生成

	if (pAirplane == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pAirplane = new CAirplane;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAirplane != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAirplane->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAirplane->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 飛行機のポインタを返す
	return pAirplane;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CAirplane*> CAirplane::GetList(void)
{
	// リストマネージャーの情報を返す
	return m_list;
}