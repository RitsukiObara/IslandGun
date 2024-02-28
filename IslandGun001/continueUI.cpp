//============================================
//
// コンティニューUI処理[continueUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "continueUI.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "object2D.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const char* TEXTURE[CContinueUI::TYPE_MAX] =
	{
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
	};
	const D3DXVECTOR3 POS[CContinueUI::TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f),
		D3DXVECTOR3(390.0f,450.0f,0.0f),
		D3DXVECTOR3(890.0f,450.0f,0.0f),
	};
	const D3DXVECTOR3 POLY_SIZE[CContinueUI::TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(500.0f,300.0f,0.0f),
		D3DXVECTOR3(450.0f,100.0f,0.0f),
		D3DXVECTOR3(100.0f,50.0f,0.0f),
		D3DXVECTOR3(100.0f,50.0f,0.0f),
	};
}

//========================
// コンストラクタ
//========================
CContinueUI::CContinueUI() : CObject(TYPE_CONTINUEUI, DIM_2D, PRIORITY_UI)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;		// ポリゴンの情報
	}
}

//========================
// デストラクタ
//========================
CContinueUI::~CContinueUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CContinueUI::Init(void)
{
	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CContinueUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // ポリゴンの情報が NULL じゃない場合

			// ポリゴンの終了処理
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// 数字の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CContinueUI::Update(void)
{

}

//========================
// 描画処理
//========================
void CContinueUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // ポリゴンが NULL じゃない場合

			// 描画処理
			m_apObject[nCnt]->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CContinueUI::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // ポリゴンが NULL じゃない場合

			// ポリゴンを生成
			m_apObject[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// 設定処理
			m_apObject[nCnt]->SetPos(POS[nCnt]);			// 位置
			m_apObject[nCnt]->SetPosOld(POS[nCnt]);			// 前回の位置
			m_apObject[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apObject[nCnt]->SetSize(POLY_SIZE[nCnt]);		// サイズ
			m_apObject[nCnt]->SetAngle();					// 方向
			m_apObject[nCnt]->SetLength();					// 長さ

			// テクスチャの割り当て処理
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[nCnt]));

			// 頂点座標の設定処理
			m_apObject[nCnt]->SetVertex();

			switch (nCnt)
			{
			case TYPE::TYPE_SCREEN:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

				break;

			case TYPE::TYPE_GROUND:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				break;

			case TYPE::TYPE_QUERY:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

				break;

			case TYPE::TYPE_YES:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

				break;

			case TYPE::TYPE_NO:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				break;
			}
		}
	}
}

//========================
// 生成処理
//========================
CContinueUI* CContinueUI::Create(void)
{
	// ローカルオブジェクトを生成
	CContinueUI* pUI = nullptr;			// UIのインスタンスを生成

	if (pUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pUI = new CContinueUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pUI->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// UIのポインタを返す
	return pUI;
}