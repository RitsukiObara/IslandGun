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
#include "alter_light.h"
#include "boss.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Alter.x";			// モデルの名前
	const char* BREAKALTER_MODEL = "data\\MODEL\\BreakAlter.x";			// 壊れた祭壇のモデル
	const char* BREAKALTERPOLE_MODEL = "data\\MODEL\\BreakAlterPole.x";	// 壊れた祭壇の石柱のモデル
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
	switch (m_state)
	{
	case CAlter::STATE_NONE:

		if (m_apPole[0]->IsArrival() == true &&
			m_apPole[1]->IsArrival() == true &&
			m_apPole[2]->IsArrival() == true)
		{ // 石柱に全て金の骨が到着していた場合

			// チャージ状態にする
			m_state = STATE_CHARGE;

			// ボスを生成する
			CBoss::Create(NONE_D3DXVECTOR3, NONE_D3DXVECTOR3);

			CAlterLight::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 900.0f, GetPos().z));
		}

		break;

	case CAlter::STATE_CHARGE:



		break;

	case CAlter::STATE_BOSSAPPEAR:
		break;

	case CAlter::STATE_WAIT:
		break;

	case CAlter::STATE_BREAK:
		break;

	default:

		// 停止
		assert(false);

		break;
	}

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

//=======================================
// 状態の設定処理
//=======================================
void CAlter::SetState(const STATE state)
{
	// 状態を設定する
	m_state = state;
}

//=======================================
// 状態の取得処理
//=======================================
CAlter::STATE CAlter::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//=======================================
// 破壊処理
//=======================================
void CAlter::Break(void)
{
	// 祭壇のモデルを変える
	SetFileData(CManager::Get()->GetXFile()->Regist(BREAKALTER_MODEL));

	for (int nCntPole = 0; nCntPole < CAlter::NUM_POLE; nCntPole++)
	{
		if (m_apPole[nCntPole] != nullptr)
		{ // 石柱が NULL じゃない場合

			// 石柱のモデルを変える
			m_apPole[nCntPole]->SetFileData(CManager::Get()->GetXFile()->Regist(BREAKALTERPOLE_MODEL));
		}
	}

	// 破壊状態にする
	m_state = STATE_BREAK;
}