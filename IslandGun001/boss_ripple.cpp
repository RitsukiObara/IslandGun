//========================================================================
//
//	ボスの死亡波紋処理 [boss_ripple.cpp]
//	Author：小原立暉
//
//========================================================================
//************************************************************************
//	インクルードファイル
//************************************************************************
#include "manager.h"
#include "boss_ripple.h"
#include "texture.h"
#include "useful.h"

//------------------------------------------------------------------------
// 定数定義
//------------------------------------------------------------------------
namespace
{
	const D3DXVECTOR3 ROT = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);		// 向き
	const float WIDTH = 300.0f;					// 横の幅
	const float CIRCUM = 50.0f;					// 円周の幅
	const CMesh::SGrid GRID = { 1,8 };			// 分割数
	const char* TEXTURE = "data\\TEXTURE\\BossRipple.png";		// テクスチャ
	const float INIT_ADD_CIRCUM = 60.0f;		// 円周の追加量
	const float INIT_ADD_WIDTH = 60.0f;			// 幅の追加量
	const float CIRCUM_CORRECT = 0.3f;			// 円周の追加量
}

//================================
// オーバーロードコンストラクタ
//================================
CBossRipple::CBossRipple() : CMeshDonut(PRIORITY_EFFECT)
{
	// 全ての値をクリアする
	m_fAddCircum = INIT_ADD_CIRCUM;		// 円周の追加量
	CObject::SetType(TYPE_BOSSRIPPLE);
}

//================================
// デストラクタ
//================================
CBossRipple::~CBossRipple()
{

}

//================================
// 初期化処理
//================================
HRESULT CBossRipple::Init(void)
{
	if (FAILED(CMeshDonut::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 頂点情報の設定処理
	SetVertex();

	// インデックスの設定処理
	SetIndex(GetVtx().nWidth, GetVtx().nHeight);

	// 成功を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CBossRipple::Uninit(void)
{
	// 終了処理
	CMesh::Uninit();
}

//================================
// 更新処理
//================================
void CBossRipple::Update(void)
{
	// 広げ処理
	Spread();

	// 頂点座標の設定処理
	SetVertex();
}

//================================
// 描画処理
//================================
void CBossRipple::Draw(void)
{
	// 描画処理
	CMesh::Draw();
}

//================================
// 情報の設定処理
//================================
void CBossRipple::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	CMeshDonut::SetData
	(
		pos,
		ROT,
		WIDTH,
		CIRCUM,
		GRID
	);

	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));	// テクスチャの割り当て処理
	SetCulling(true);		// カリング
	SetLighting(true);		// ライティング

	// 全ての値を設定する
	m_fAddCircum = INIT_ADD_CIRCUM;		// 円周の追加量
}

//================================
// 生成処理
//================================
CBossRipple* CBossRipple::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CBossRipple* pRipple = nullptr;		// 波紋のインスタンスを生成

	if (pRipple == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pRipple = new CBossRipple;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRipple != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 情報の設定処理
		pRipple->SetData(pos);

		// 初期化処理
		if (FAILED(pRipple->Init()))
		{ // 初期化処理に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 波紋のポインタを返す
	return pRipple;
}

//================================
// 広げ処理
//================================
void CBossRipple::Spread(void)
{
	// 円周と幅を取得
	float fCircum = GetCircum();
	float fWidth = GetWidth();

	// 円を広げる
	fCircum += m_fAddCircum;
	fWidth += m_fAddCircum;

	// 円周と幅を適用
	SetCircum(fCircum);
	SetWidth(fWidth);

	// 追加量を0に近づける
	useful::FrameCorrect(0.0f, &m_fAddCircum, CIRCUM_CORRECT);
}