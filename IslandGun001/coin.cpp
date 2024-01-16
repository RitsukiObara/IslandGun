//===========================================
//
// 小判のメイン処理[coin.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "coin.h"
#include "useful.h"

#include "coin_manager.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const float INIT_CYCLESPEED = 0.08f;		// 初期の回転速度
	const float GET_CYCLESPEED = 0.2f;			// 取得時の回転速度
	const float GET_HEIGHTDEST = 150.0f;		// 取得時の目的の高さ
	const float GET_POS_CORRECT = 10.0f;		// 取得時の位置の補正数
	const int DEATH_COUNT = 70;					// 死亡までのカウント
}

//==============================
// コンストラクタ
//==============================
CCoin::CCoin() : CModel(CObject::TYPE_COIN, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_state = STATE_NONE;		// 状態
	m_nDeathCount = 0;			// 死亡カウント
	m_fCycleSpeed = 0.0f;		// 回転速度
	m_fHeightDest = 0.0f;		// 目標の高さ

	// 全ての値をクリアする
	m_pPrev = nullptr;			// 前のポインタ
	m_pNext = nullptr;			// 次のポインタ

	if (CCoinManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CCoinManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CCoin::~CCoin()
{

}

//============================
// 前のポインタの設定処理
//============================
void CCoin::SetPrev(CCoin* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CCoin::SetNext(CCoin* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CCoin* CCoin::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CCoin* CCoin::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CCoin::Init(void)
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
void CCoin::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CCoinManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CCoinManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CCoin::Update(void)
{
	switch (m_state)
	{
	case CCoin::STATE_NONE:		// 通常状態

		// 特になし

		break;

	case CCoin::STATE_GET:		// 取得状態

		// 取得処理
		Get();

		break;

	case STATE_DEATH:			// 死亡状態

		// 死亡カウントを加算する
		m_nDeathCount++;

		if (m_nDeathCount >= DEATH_COUNT)
		{ //死亡カウントが一定数以上になった場合

			// 終了処理
			Uninit();

			// この先の処理を行わない
			return;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 回転処理
	Cycle();
}

//=====================================
//ブロックの描画処理
//=====================================
void CCoin::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CCoin::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);						// 位置
	SetPosOld(pos);						// 前回の位置
	SetRot(NONE_D3DXVECTOR3);			// 向き
	SetScale(NONE_SCALE);				// 拡大率
	SetFileData(CXFile::TYPE_COIN);		// モデルの情報

	// 全ての値を初期化する
	m_state = STATE_NONE;						// 状態
	m_nDeathCount = 0;							// 死亡カウント
	m_fCycleSpeed = INIT_CYCLESPEED;			// 回転速度
	m_fHeightDest = pos.y + GET_HEIGHTDEST;		// 目標の高さ
}

//=======================================
// 生成処理
//=======================================
CCoin* CCoin::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCoin* pCoin = nullptr;	// インスタンスを生成

	if (pCoin == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pCoin = new CCoin;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCoin != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCoin->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCoin->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ネジのポインタを返す
	return pCoin;
}

//=======================================
// ヒット処理
//=======================================
void CCoin::Hit(void)
{
	// 取得状態にする
	m_state = STATE_GET;

	// 回転速度を早くする
	m_fCycleSpeed = GET_CYCLESPEED;
}

//=======================================
// 取得状態処理
//=======================================
void CCoin::Get(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	if (useful::FrameCorrect(m_fHeightDest, &pos.y, 10.0f) == true)
	{ // 目的の値に達した場合

		// 死亡状態にする
		m_state = STATE_DEATH;
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 回転処理
//=======================================
void CCoin::Cycle(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きを加算する
	rot.y += m_fCycleSpeed;

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	// 向きを適用する
	SetRot(rot);
}