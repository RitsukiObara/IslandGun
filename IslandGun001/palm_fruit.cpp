//===========================================
//
// ヤシの実のメイン処理[palm_fruit.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "palm_fruit.h"
#include "renderer.h"
#include "useful.h"

#include "palm_fruit_manager.h"
#include "elevation_manager.h"
#include "objectElevation.h"

namespace
{
	const float GRAVITY = 0.5f;			// 重力
	const float BOUND_GRAVITY = 10.0f;	// バウンドしたときのY軸の移動量
	const float BOUND_MOVE = 4.4f;		// バウンドしたときの移動量
	const float BOUND_MOVE_ROT = 0.6f;	// バウンドしたときの移動量の向き
}

//==============================
// コンストラクタ
//==============================
CPalmFruit::CPalmFruit() : CModel(CObject::TYPE_PALMFRUIT, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;	// 移動量
	m_state = STATE_NONE;		// 状態

	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CPalmFruitManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CPalmFruitManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CPalmFruit::~CPalmFruit()
{

}

//============================
// 前のポインタの設定処理
//============================
void CPalmFruit::SetPrev(CPalmFruit* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CPalmFruit::SetNext(CPalmFruit* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CPalmFruit* CPalmFruit::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CPalmFruit* CPalmFruit::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CPalmFruit::Init(void)
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
void CPalmFruit::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CPalmFruitManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CPalmFruitManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CPalmFruit::Update(void)
{
	switch (m_state)
	{
	case CPalmFruit::STATE_NONE:

		// 起伏地面の当たり判定
		ElevationCollision();

		break;

	case CPalmFruit::STATE_FALL:

		// 重力処理
		Gravity();

		if (ElevationCollision() == true)
		{ // 起伏の地面に付いた場合

			// バウンド状態にする
			m_state = STATE_BOUND;

			// 移動量を設定する
			m_move.x = sinf(GetRot().y + BOUND_MOVE_ROT) * BOUND_MOVE;
			m_move.y = BOUND_GRAVITY;
			m_move.z = cosf(GetRot().y + BOUND_MOVE_ROT) * BOUND_MOVE;
		}

		break;

	case CPalmFruit::STATE_BOUND:

		// 移動処理
		Move();

		// 重力処理
		Gravity();

		if (ElevationCollision() == true)
		{ // 起伏の地面に付いた場合

			// 停止状態にする
			m_state = STATE_STOP;

			// 重力を0.0fにする
			m_move.y = 0.0f;
		}

		break;

	case CPalmFruit::STATE_STOP:



		break;

	case CPalmFruit::STATE_GET:

		// モデルをヤシの実(アイテム型)にする
		SetFileData(CXFile::TYPE_PALMITEM);

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=====================================
//ブロックの描画処理
//=====================================
void CPalmFruit::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPalmFruit::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(rot);							// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_PALMFRUIT);	// モデルの情報

	// 全ての値を設定する
	m_move = NONE_D3DXVECTOR3;	// 移動量
	m_state = STATE_NONE;		// 状態
}

//=======================================
// 生成処理
//=======================================
CPalmFruit* CPalmFruit::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CPalmFruit* pFruit = nullptr;	// インスタンスを生成

	if (pFruit == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFruit = new CPalmFruit;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFruit != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFruit->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFruit->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ヤシの実のポインタを返す
	return pFruit;
}

//=======================================
// 移動量の設定処理
//=======================================
void CPalmFruit::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CPalmFruit::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 状態の設定処理
//=======================================
void CPalmFruit::SetState(const STATE state)
{
	// 状態を設定する
	m_state = state;
}

//=======================================
// 状態の取得処理
//=======================================
CPalmFruit::STATE CPalmFruit::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//=======================================
// ヒット処理
//=======================================
void CPalmFruit::Hit(void)
{

}

//=======================================
// 移動処理
//=======================================
void CPalmFruit::Move(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動させる
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 重力処理
//=======================================
void CPalmFruit::Gravity(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 重力処理
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 起伏地面の当たり判定処理
//=======================================
bool CPalmFruit::ElevationCollision(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	float fHeight = 0.0f;			// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			// 重力を設定する
			m_move.y = 0.0f;

			// 位置を更新する
			SetPos(pos);

			// true を返す
			return true;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// false を返す
	return false;
}