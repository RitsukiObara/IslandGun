//=======================================
//
// 弾のメイン処理[bullet.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "bullet_manager.h"
#include "locus3D.h"

//=======================================
// 無名名前空間
//=======================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Bullet.png";		// 弾のテクスチャ
	const D3DXVECTOR3 RADIUS[CBullet::TYPE_MAX] =
	{
		D3DXVECTOR3(20.0f,20.0f,0.0f),		// 二丁拳銃
		D3DXVECTOR3(3.0f,3.0f,0.0f),		// 散弾銃
	};
	const float SPEED = 45.0f;		// 速度
	const int LIFE = 90;			// 寿命
}

//=========================
// コンストラクタ
//=========================
CBullet::CBullet() : CBillboard(CObject::TYPE_BULLET, CObject::PRIORITY_SHADOW)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;	// 移動量
	m_type = TYPE_HANDGUN;		// 種類
	m_nLife = LIFE;				// 寿命
	m_fRot = 0.0f;				// 飛んでいく向き

	// 全ての値をクリアする
	m_pPrev = nullptr;		// 前のアウトボールへのポインタ
	m_pNext = nullptr;		// 次のアウトボールへのポインタ

	if (CBulletManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CBulletManager::Get()->Regist(this);
	}
}

//=========================
// デストラクタ
//=========================
CBullet::~CBullet()
{

}

//============================
// 前のポインタの設定処理
//============================
void CBullet::SetPrev(CBullet* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CBullet::SetNext(CBullet* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CBullet* CBullet::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CBullet* CBullet::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//=========================
// 初期化処理
//=========================
HRESULT CBullet::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;	// 移動量
	m_type = TYPE_HANDGUN;		// 種類
	m_nLife = LIFE;				// 寿命
	m_fRot = 0.0f;				// 飛んでいく向き

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CBullet::Uninit(void)
{
	// 終了
	CBillboard::Uninit();

	if (CBulletManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CBulletManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=========================
// 更新処理
//=========================
void CBullet::Update(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動量を設定する
	pos += m_move;

	// 位置を適用する
	SetPos(pos);

	// 寿命を減算する
	m_nLife--;

	if (m_nLife % 2 == 0)
	{ // 一定時間ごとに

		// 残像の生成
		CLocus3D::Create(GetPos(), GetSize(), 0.5f, 20, GetTexIdx(), true, true);
	}

	if (m_nLife <= 0)
	{ // 寿命が0になった場合

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CBullet::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff(true);
}

//=========================
// 情報の設定処理
//=========================
void CBullet::SetData(const D3DXVECTOR3& pos, const float fRot, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetRot(0.0f);			// 向き
	SetSize(RADIUS[type]);	// サイズ
	SetAngle();				// 方向
	SetLength();			// 長さ
	SetEnableLookY(true);	// Y軸状況

	// 全ての値を設定する
	m_type = type;			// 種類
	m_nLife = LIFE;			// 寿命
	m_fRot = fRot;			// 飛んでいく向き

	// 移動量を設定する
	m_move.x = sinf(m_fRot) * SPEED;	// X軸
	m_move.y = 0.0f;					// Y軸
	m_move.z = cosf(m_fRot) * SPEED;	// Z軸

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// 生成処理
//=========================
CBullet* CBullet::Create(const D3DXVECTOR3& pos, const float fRot, const TYPE type)
{
	// ローカルオブジェクトを生成
	CBullet* pBullet = nullptr;	// 弾のインスタンスを生成

	if (pBullet == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pBullet = new CBullet;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBullet != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBullet->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBullet->SetData(pos, fRot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 弾のポインタを返す
	return pBullet;
}