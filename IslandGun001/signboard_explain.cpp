//============================================
//
// 看板の説明処理[signboard_explain.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "signboard_explain.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// 定数定義
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 SCREEN_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// 背景の位置
	const D3DXVECTOR3 SCREEN_SIZE = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// 背景のサイズ
	const D3DXVECTOR3 EXPLAIN_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -200.0f, 0.0f);					// 説明の位置
	const D3DXVECTOR3 EXPLAIN_SIZE = D3DXVECTOR3(200.0f, 200.0f, 0.0f);									// 説明のサイズ
	const char* EXPLAIN_TEXTURE[CSignboard::TYPE_MAX] = 	// 説明のテクスチャ
	{
		""
	};
	const D3DXCOLOR SCREEN_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// 背景の色
	const float SCREEN_ADD_ALPHA = 0.01f;			// 背景の透明度の加算数
	const float SCREEN_MAX_ALPHA = 0.5f;			// 背景の透明度の最大数
}

//============================
// コンストラクタ
//============================
CSignboardExpl::CSignboardExpl() : CObject(CObject::TYPE_SIGNEXPLAIN, DIM_2D, PRIORITY_UI)
{
	// 全ての値をクリアする
	m_screen.pScreen = nullptr;		// 画面の情報
	m_screen.fAlpha = 0.0f;			// 透明度
	m_pExplain = nullptr;			// 説明のポリゴン
}

//============================
// デストラクタ
//============================
CSignboardExpl::~CSignboardExpl()
{

}

//============================
// 初期化処理
//============================
HRESULT CSignboardExpl::Init(void)
{
	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CSignboardExpl::Uninit(void)
{
	if (m_screen.pScreen != nullptr)
	{ // 背景が NULL じゃない場合

		// 背景の終了処理
		m_screen.pScreen->Uninit();
		m_screen.pScreen = nullptr;
	}

	if (m_pExplain != nullptr)
	{ // 説明が NULL じゃない場合

		// 説明の終了処理
		m_pExplain->Uninit();
		m_pExplain = nullptr;
	}

	// 破棄処理
	Release();
}

//============================
// 更新処理
//============================
void CSignboardExpl::Update(void)
{
	// 均等な補正処理
	useful::FrameCorrect(SCREEN_MAX_ALPHA, &m_screen.fAlpha, SCREEN_ADD_ALPHA);

	D3DXVECTOR3 pos = m_pExplain->GetPos();

	useful::FrameCorrect(SCREEN_HEIGHT * 0.5f, &pos.y, 10.0f);

	m_pExplain->SetPos(pos);

	// 頂点カラーの設定処理
	m_screen.pScreen->SetVtxColor(D3DXCOLOR(SCREEN_COL.r, SCREEN_COL.g, SCREEN_COL.b, m_screen.fAlpha));
}

//============================
// 描画処理
//============================
void CSignboardExpl::Draw(void)
{
	if (m_screen.pScreen != nullptr)
	{ // 背景が NULL じゃない場合

		// 背景の描画処理
		m_screen.pScreen->Draw();
	}

	if (m_pExplain != nullptr)
	{ // 説明が NULL じゃない場合

		// 説明の描画処理
		m_pExplain->Draw();
	}
}

//============================
// 情報の設定処理
//============================
void CSignboardExpl::SetData(const CSignboard::TYPE type)
{
	if (m_screen.pScreen == nullptr)
	{ // 背景が NULL の場合

		// 背景を生成
		m_screen.pScreen = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

		// 情報の設定処理
		m_screen.pScreen->SetPos(SCREEN_POS);		// 位置
		m_screen.pScreen->SetPosOld(SCREEN_POS);	// 前回の位置
		m_screen.pScreen->SetRot(NONE_D3DXVECTOR3);	// 向き
		m_screen.pScreen->SetSize(SCREEN_SIZE);		// サイズ
		m_screen.pScreen->SetAngle();				// 方向
		m_screen.pScreen->SetLength();				// 長さ

		// 頂点座標の設定処理
		m_screen.pScreen->SetVertex();

		// 頂点カラーの設定処理
		m_screen.pScreen->SetVtxColor(D3DXCOLOR(SCREEN_COL.r, SCREEN_COL.g, SCREEN_COL.b, m_screen.fAlpha));
	}
	m_screen.fAlpha = 0.0f;

	if (m_pExplain != nullptr)
	{ // 説明が NULL の場合

		// 説明を生成
		m_pExplain = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

		// 情報の設定処理
		m_pExplain->SetPos(EXPLAIN_POS);		// 位置
		m_pExplain->SetPosOld(EXPLAIN_POS);		// 前回の位置
		m_pExplain->SetRot(NONE_D3DXVECTOR3);	// 向き
		m_pExplain->SetSize(EXPLAIN_SIZE);		// サイズ
		m_pExplain->SetAngle();					// 方向
		m_pExplain->SetLength();				// 長さ

		// テクスチャの設定処理
		m_pExplain->BindTexture(CManager::Get()->GetTexture()->Regist(EXPLAIN_TEXTURE[type]));

		// 頂点座標の設定処理
		m_pExplain->SetVertex();
	}
}

//============================
//生成処理
//============================
CSignboardExpl* CSignboardExpl::Create(const CSignboard::TYPE type)
{
	// ローカルオブジェクトを生成
	CSignboardExpl* pExplain = nullptr;			// 説明のインスタンスを生成

	if (pExplain == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pExplain = new CSignboardExpl;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pExplain != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pExplain->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pExplain->SetData(type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 説明のポインタを返す
	return pExplain;
}