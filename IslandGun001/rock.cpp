//===========================================
//
// 岩のメイン処理[rock.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "rock.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const int MAX_BREAK_LEVEL = 3;				// 破壊レベルの最大値
	const char* MODEL[CRock::TYPE_MAX] =		// モデルの名前
	{
		"data\\MODEL\\Rock001.x",				// 柔らかい岩
		"data\\MODEL\\Rock002.x"				// 硬い岩
	};
	const char* TEXTURE[MAX_BREAK_LEVEL] =		// 破壊レベルごとのテクスチャ
	{
		"data\\TEXTURE\\Rock001.png",
		"data\\TEXTURE\\Rock002.png",
		"data\\TEXTURE\\Rock003.png",
	};
	const int TEXTURE_IDX = 0;					// 変えるテクスチャの番号
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CRock*> CRock::m_list = {};		// リスト

//==============================
// コンストラクタ
//==============================
CRock::CRock() : CModel(TYPE_ROCK, PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_type = TYPE_SOFT;			// 種類
	m_nBreakLevel = 0;			// 破壊レベル

	// リストに追加する
	m_list.Regist(this);
}

//==============================
// デストラクタ
//==============================
CRock::~CRock()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CRock::Init(void)
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
void CRock::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//========================================
//ブロックの更新処理
//========================================
void CRock::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CRock::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(rot);					// 向き
	SetScale(scale);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL[type]));	// モデルの情報

	// 全ての値を設定する
	m_type = type;				// 種類
	m_nBreakLevel = 0;			// 破壊レベル

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[m_nBreakLevel]), TEXTURE_IDX);
}

//=====================================
// 破壊処理
//=====================================
void CRock::Break(void)
{
	// 破壊レベルを加算する
	m_nBreakLevel++;

	if (m_nBreakLevel >= MAX_BREAK_LEVEL)
	{ // 破壊レベルが最大数以上の場合

		// 破片ばら撒く
	}
	else
	{ // 上記以外

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[m_nBreakLevel]), TEXTURE_IDX);
	}
}

//=======================================
// 生成処理
//=======================================
CRock* CRock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
{
	// ローカルオブジェクトを生成
	CRock* pRock = nullptr;		// インスタンスを生成

	if (pRock == nullptr)
	{ // オブジェクトが NULL の場合

		// 岩を生成する
		pRock = new CRock;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRock != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pRock->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pRock->SetData(pos, rot, scale, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 岩のポインタを返す
	return pRock;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CRock*> CRock::GetList(void)
{
	// リストマネージャーを返す
	return m_list;
}