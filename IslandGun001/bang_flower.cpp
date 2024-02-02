//===========================================
//
// 爆弾花のメイン処理[bang_flower.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "bang_flower.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\BombFlower.x";		// モデルの名前
}

//==============================
// コンストラクタ
//==============================
CBangFlower::CBangFlower() : CModel(TYPE_BANGFLOWER, PRIORITY_ENTITY)
{

}

//==============================
// デストラクタ
//==============================
CBangFlower::~CBangFlower()
{

}

//==============================
//爆弾花の初期化処理
//==============================
HRESULT CBangFlower::Init(void)
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
//爆弾花の終了処理
//========================================
void CBangFlower::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//========================================
//爆弾花の更新処理
//========================================
void CBangFlower::Update(void)
{

}

//=====================================
//爆弾花の描画処理
//=====================================
void CBangFlower::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CBangFlower::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(scale);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CBangFlower* CBangFlower::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale)
{
	// ローカルオブジェクトを生成
	CBangFlower* pBangFlower = nullptr;		// インスタンスを生成

	if (pBangFlower == nullptr)
	{ // オブジェクトが NULL の場合

		// 爆弾花を生成する
		pBangFlower = new CBangFlower;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBangFlower != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBangFlower->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBangFlower->SetData(pos, scale);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 爆弾花のポインタを返す
	return pBangFlower;
}