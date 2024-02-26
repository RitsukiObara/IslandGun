//============================================
//
// 祭壇の光のメイン処理[alter_light.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "alter_light.h"
#include "renderer.h"
#include "texture.h"

//--------------------------------------------
// 定数定義
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 INIT_SIZE = D3DXVECTOR3(60.0f, 60.0f, 0.0f);		// 初期サイズ
	const char* TEXTURE = "data\\TEXTURE\\AlterLight.png";				// テクスチャ
	const float ADD_SIZE = 1.5f;			// サイズの追加量
	const float DEATH_SIZE = 10000.0f;		// 消去するサイズ
}

//===========================================
// コンストラクタ
//===========================================
CAlterLight::CAlterLight() : CBillboard(CObject::TYPE_ALTERLIGHT, CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
	m_fAddSize = 0.0f;		// サイズの追加量
}

//===========================================
// デストラクタ
//===========================================
CAlterLight::~CAlterLight()
{

}

//===========================================
// 初期化処理
//===========================================
HRESULT CAlterLight::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// 終了処理
//===========================================
void CAlterLight::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CAlterLight::Update(void)
{
	// サイズの追加量を大きくしていく
	m_fAddSize += ADD_SIZE;

	// サイズを取得
	D3DXVECTOR3 size = GetSize();

	// サイズを拡大する
	size.x += m_fAddSize;
	size.y += m_fAddSize;

	if (size.x >= DEATH_SIZE ||
		size.y >= DEATH_SIZE)
	{ // サイズが一定数以上になった場合

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}

	// サイズを適用
	SetSize(size);

	// 頂点座標の設定処理
	SetVertex();

	// 更新処理
	CBillboard::Update();
}

//===========================================
// 描画処理
//===========================================
void CAlterLight::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff(false);
}

//===========================================
// 設定処理
//===========================================
void CAlterLight::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);				// 位置
	SetPosOld(pos);				// 前回の位置
	SetRot(0.0f);				// 向き
	SetSize(INIT_SIZE);			// サイズ設定
	SetAngle();					// 方向
	SetLength();				// 長さ
	SetEnableLookY(true);		// Y軸状況

	// 頂点情報の設定処理
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

	// 全ての値を設定する
	m_fAddSize = 0.0f;		// サイズの追加量
}

//===========================================
// 生成処理
//===========================================
CAlterLight* CAlterLight::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CAlterLight* pLight = nullptr;		// 光のインスタンスを生成

	if (pLight == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pLight = new CAlterLight;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (pLight != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pLight->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pLight->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// 光のポインタを返す
	return pLight;
}