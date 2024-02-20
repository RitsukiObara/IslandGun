//===========================================
//
// 祭壇のメイン処理[alter.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "alter.h"
#include "texture.h"
#include "useful.h"

#include "game.h"
#include "alter_pole.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Alter.x";			// モデルの名前
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	const D3DXVECTOR3 POLE_POS[CAlter::NUM_POLE] =		// 石柱の位置
	{
		D3DXVECTOR3(0.0f,0.0f,-450.0f),
		D3DXVECTOR3(450.0f,0.0f,0.0f),
		D3DXVECTOR3(-450.0f,0.0f,0.0f),
	};
}

//==============================
// コンストラクタ
//==============================
CAlter::CAlter() : CModel(TYPE_ALTER, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		m_apPole[nCnt] = nullptr;		// 石柱の情報
	}
}

//==============================
// デストラクタ
//==============================
CAlter::~CAlter()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CAlter::Init(void)
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
void CAlter::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // 石柱の情報が NULL じゃない場合

			// 終了処理
			m_apPole[nCnt]->Uninit();
			m_apPole[nCnt] = nullptr;
		}
	}

	// 終了処理
	CModel::Uninit();

	// 祭壇のNULL化処理
	CGame::DeleteAlter();
}

//========================================
//ブロックの更新処理
//========================================
void CAlter::Update(void)
{
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // 石柱の情報が NULL じゃない場合

			// 更新処理
			m_apPole[nCnt]->Update();
		}
	}
}

//=====================================
//ブロックの描画処理
//=====================================
void CAlter::Draw(void)
{
	// 描画処理
	CModel::Draw();

	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // 石柱の情報が NULL じゃない場合

			// 描画処理
			m_apPole[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CAlter::SetData(void)
{
	// 情報の設定処理
	SetPos(POS);					// 位置
	SetPosOld(POS);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報

	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] == nullptr)
		{ // 石柱が NULL だった場合

			// 石柱を生成
			m_apPole[nCnt] = CAlterPole::Create(POLE_POS[nCnt]);
		}
	}
}

//=======================================
// 生成処理
//=======================================
CAlter* CAlter::Create(void)
{
	// ローカルオブジェクトを生成
	CAlter* pAlter = nullptr;		// インスタンスを生成

	if (pAlter == nullptr)
	{ // オブジェクトが NULL の場合

		// ブロックを生成する
		pAlter = new CAlter;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAlter != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAlter->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAlter->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 祭壇のポインタを返す
	return pAlter;
}

//=======================================
// 石柱の取得処理
//=======================================
CAlterPole* CAlter::GetPole(const int nIdx) const
{
	if (nIdx >= NUM_POLE)
	{ // インデックスが最大数以上の場合

		// 停止
		assert(false);
	}

	// 石柱の情報を返す
	return m_apPole[nIdx];
}