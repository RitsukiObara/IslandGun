//===========================================
//
// ドアのメイン処理[door.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "door.h"
#include "useful.h"

#include "input.h"

//-------------------------------------------
// 定数定義
//-------------------------------------------
namespace
{
	const char* DOOR_MODEL = "data\\MODEL\\Door.x";						// ドアモデルの名前
	const char* FRAME_MODEL = "data\\MODEL\\DoorFrame.x";				// ドアフレームモデルの名前
	const D3DXVECTOR3 DOOR_OFFSET = D3DXVECTOR3(60.7f, 0.0f, 0.0f);		// ドアのオフセット
}

//==============================
// コンストラクタ
//==============================
CDoor::CDoor() : CModel(CObject::TYPE_DOOR, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pDoor = nullptr;			// ドアのモデル
}

//==============================
// デストラクタ
//==============================
CDoor::~CDoor()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CDoor::Init(void)
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
void CDoor::Uninit(void)
{
	if (m_pDoor != nullptr)
	{ // ドアが NULL じゃない場合

		// ドアの終了処理
		m_pDoor->Uninit();
		m_pDoor = nullptr;
	}

	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CDoor::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CDoor::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pDoor != nullptr)
	{ // ドアが NULL じゃない場合

		// ドアの描画処理
		m_pDoor->DrawMatrix(GetMatrix());
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CDoor::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(FRAME_MODEL));	// モデル情報

	if (m_pDoor == nullptr)
	{ // ドアが NULL じゃない場合

		// ドアの生成
		m_pDoor = CModel::Create(TYPE_NONE, PRIORITY_ENTITY);

		// 情報の設定処理
		m_pDoor->SetPos(DOOR_OFFSET);		// 位置
		m_pDoor->SetPosOld(DOOR_OFFSET);	// 前回の位置
		m_pDoor->SetRot(NONE_D3DXVECTOR3);	// 向き
		m_pDoor->SetScale(NONE_SCALE);		// 拡大率
		m_pDoor->SetFileData(CManager::Get()->GetXFile()->Regist(DOOR_MODEL));	// モデル情報
	}
}

//=======================================
// 生成処理
//=======================================
CDoor* CDoor::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CDoor* pDoor = nullptr;		// インスタンスを生成

	if (pDoor == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pDoor = new CDoor;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pDoor != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pDoor->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pDoor->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ドアのポインタを返す
	return pDoor;
}