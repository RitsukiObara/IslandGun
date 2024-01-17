//=======================================
//
// エイムのメイン処理[aim.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "aim.h"
#include "texture.h"
#include "useful.h"

// 無名名前空間
namespace
{
	const float RADIUS = 40.0f;		// 半径
	const float SHIFT = 100.0f;		// ずらす幅
}

//=========================
// コンストラクタ
//=========================
CAim::CAim() : CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
}

//=========================
// デストラクタ
//=========================
CAim::~CAim()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CAim::Init(void)
{
	if (FAILED(CBillboard::Init()))
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
void CAim::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CAim::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CAim::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff(true);
}

//=========================
// 情報の設定処理
//=========================
void CAim::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetRot(0.0f);			// 向き
	SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	// サイズ
	SetAngle();				// 方向の設定処理
	SetLength();			// 長さの設定処理
	SetEnableLookY(true);	// Y軸状況

	// エイムの設置処理
	SetAim(pos, rot);

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 生成処理
//=========================
CAim* CAim::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CAim* pAim = nullptr;	// エイムのインスタンスを生成

	if (pAim == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pAim = new CAim;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAim != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAim->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAim->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エイムのポインタを返す
	return pAim;
}

//=========================
// エイムの設置処理
//=========================
void CAim::SetAim(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// エイムの位置を宣言する
	D3DXVECTOR3 posAim;

	// 位置を設定する
	posAim.x = pos.x + sinf(rot.y) * SHIFT;
	posAim.y = pos.y + cosf(rot.x) * SHIFT;
	posAim.z = pos.z + cosf(rot.y) * SHIFT;

	// 位置を適用する
	SetPos(posAim);

	// 頂点情報の初期化
	SetVertex();
}