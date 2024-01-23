//=======================================
//
// 草処理[grass.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "grass.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// 無名名前空間
//---------------------------------------
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Grass001.png";		// テクスチャ
}

//---------------------------------------
// 静的メンバ変数宣言
//---------------------------------------
CListManager<CGrass*> CGrass::m_list = {};		// リスト

//=========================
// コンストラクタ
//=========================
CGrass::CGrass() : CObject3D(CObject::TYPE_CONFETTI, CObject::PRIORITY_BLOCK)
{
	// リストに追加する
	m_list.Regist(this);
}

//=========================
// デストラクタ
//=========================
CGrass::~CGrass()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CGrass::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CGrass::Uninit(void)
{
	// 終了
	CObject3D::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//=========================
// 更新処理
//=========================
void CGrass::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CGrass::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// カリングの設定をOFFにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画処理
	CObject3D::DrawLightOff();

	// カリングの設定をONにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// 情報の設定処理
//=========================
void CGrass::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// スクロールの設定処理
	SetPos(pos);					// 位置設定
	SetPosOld(pos);					// 位置設定
	SetRot(rot);					// 向き設定
	SetSize(size);					// サイズ設定

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// 生成処理
//=========================
CGrass* CGrass::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// ローカルオブジェクトを生成
	CGrass* pGrass = nullptr;	// 草のインスタンスを生成

	if (pGrass == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pGrass = new CGrass;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pGrass != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pGrass->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pGrass->SetData(pos, rot, size);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 草のポインタを返す
	return pGrass;
}

//=========================
// リストの取得処理
//=========================
CListManager<CGrass*> CGrass::GetList(void)
{
	// リストマネージャーを返す
	return m_list;
}