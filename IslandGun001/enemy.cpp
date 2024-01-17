//============================================================
//
// 敵処理 [enemy.cpp]
// Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "model.h"

#include "enemy_manager.h"
#include "motion.h"
#include "anim_reaction.h"

// マクロ定義
namespace
{
	const D3DXVECTOR3 COLLSIZE[CEnemy::TYPE_MAX] =		// 当たり判定のサイズ
	{
		D3DXVECTOR3(70.0f,140.0f,70.0f)
	};
}

//================================
// コンストラクタ
//================================
CEnemy::CEnemy() : CCharacter(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;			// モーション

	m_type = TYPE_TORDLE;			// 種類
	m_CollSize = NONE_D3DXVECTOR3;	// 当たり判定のサイズ

	// 全ての値をクリアする
	m_pPrev = nullptr;		// 前のアウトボールへのポインタ
	m_pNext = nullptr;		// 次のアウトボールへのポインタ

	if (CEnemyManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CEnemyManager::Get()->Regist(this);
	}
}

//================================
// デストラクタ
//================================
CEnemy::~CEnemy()
{

}

//============================
// 前のポインタの設定処理
//============================
void CEnemy::SetPrev(CEnemy* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CEnemy::SetNext(CEnemy* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CEnemy* CEnemy::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CEnemy* CEnemy::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//================================
// 初期化処理
//================================
HRESULT CEnemy::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(17);

	// データの設定処理
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		m_pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		m_pMotion->Load("data\\TXT\\PlayerMotion.txt");
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	// モーションの設定処理
	m_pMotion->Set(0);

	// 全ての値を初期化する
	m_type = TYPE_TORDLE;			// 種類
	m_CollSize = NONE_D3DXVECTOR3;	// 当たり判定のサイズ

	// 値を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CEnemy::Uninit(void)
{
	// モーションの終了処理
	delete m_pMotion;
	m_pMotion = nullptr;

	// 終了処理
	CCharacter::Uninit();

	if (CEnemyManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CEnemyManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//================================
// 更新処理
//================================
void CEnemy::Update(void)
{
	// モーションの更新処理
	m_pMotion->Update();
}

//================================
// 描画処理
//================================
void CEnemy::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//================================
// 情報の設定処理
//================================
void CEnemy::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 全ての値を初期化する
	SetPos(pos);				// 位置
	SetPosOld(GetPos());		// 前回の位置
	SetRot(rot);				// 向き
	SetScale(NONE_SCALE);		// 拡大率

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// データの設定処理
	}

	// 全ての値を設定する
	m_type = type;					// 種類
	m_CollSize = COLLSIZE[m_type];	// 当たり判定のサイズ
}

//===========================================
// ヒット処理
//===========================================
void CEnemy::Hit(const D3DXVECTOR3& pos)
{
	// アニメーションリアクションを生成
	CAnimReaction::Create(pos, D3DXVECTOR3(180.0f, 180.0f, 0.0f), NONE_D3DXCOLOR, CAnimReaction::TYPE::TYPE_GUNEXPLOSION, 4, 1);

	// 終了処理
	Uninit();
}

//===========================================
// 生成処理
//===========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 敵のインスタンスを生成
	CEnemy* pEnemy = nullptr;

	if (pEnemy == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pEnemy = new CEnemy;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pEnemy;
	}

	if (pEnemy != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEnemy->SetData(pos, rot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// 敵のポインタを返す
	return pEnemy;
}

//===========================================
// 当たり判定のサイズの取得処理
//===========================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// 当たり判定のサイズを取得する
	return m_CollSize;
}