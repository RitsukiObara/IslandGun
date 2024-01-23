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

#include "motion.h"
#include "anim_reaction.h"

#include "tordle.h"
#include "collision.h"
#include "block.h"

//------------------------------------------------------------
// 無名名前空間
//------------------------------------------------------------
namespace
{
	const D3DXVECTOR3 COLLSIZE[CEnemy::TYPE_MAX] =		// 当たり判定のサイズ
	{
		D3DXVECTOR3(70.0f,140.0f,70.0f)
	};
	const char* MODEL[6] =
	{
		"data/MODEL/TordleBody.x",
		"data/MODEL/TordleHead.x",
		"data/MODEL/TordleRFLeg.x",
		"data/MODEL/TordleLFLeg.x",
		"data/MODEL/TordleRBLeg.x",
		"data/MODEL/TordleLBLeg.x",
	};
}

// 静的メンバ変数
CListManager<CEnemy*> CEnemy::m_list = {};				// リスト

//================================
// コンストラクタ
//================================
CEnemy::CEnemy() : CCharacter(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;			// モーション

	m_type = TYPE_TORDLE;			// 種類
	m_CollSize = NONE_D3DXVECTOR3;	// 当たり判定のサイズ

	// リストに追加する
	m_list.Regist(this);
}

//================================
// デストラクタ
//================================
CEnemy::~CEnemy()
{

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
	SetNumModel(6);

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
		m_pMotion->Load(CMotion::STYLE_TORDLE);
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

	// 引き抜き処理
	m_list.Pull(this);
}

//================================
// 更新処理
//================================
void CEnemy::Update(void)
{
	// モーションの更新処理
	m_pMotion->Update();

	// 木との当たり判定
	TreeCollision();

	// 岩との当たり判定
	RockCollision();

	// ブロックとの当たり判定
	BlockCollision();
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
		GetHierarchy(nCntData)->SetFileData(CMotion::GetSaveData(CMotion::STYLE_TORDLE, nCntData));	// データの設定処理
	}

	// モーションのリセット処理
	m_pMotion->ResetMotion(MOTIONTYPE_NEUTRAL);

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

		switch (type)
		{
		case CEnemy::TYPE_TORDLE:		// タードル

			// タードルを生成する
			pEnemy = new CTordle;

			break;

		default:

			// 停止
			assert(false);

			break;
		}
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
// モーションの取得処理
//===========================================
CMotion* CEnemy::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// 当たり判定のサイズの取得処理
//===========================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// 当たり判定のサイズを取得する
	return m_CollSize;
}

//===========================================
// リストの取得処理
//===========================================
CListManager<CEnemy*> CEnemy::GetList(void)
{
	// リストの情報を返す
	return m_list;
}

//===========================================
// 木との当たり判定
//===========================================
void CEnemy::TreeCollision(void)
{
	// 位置と半径を取得する
	D3DXVECTOR3 pos = GetPos();
	float fRadius = m_CollSize.x;

	// 木との当たり判定
	collision::TreeCollision(&pos, fRadius);

	// 位置を適用する
	SetPos(pos);
}

//===========================================
// 岩との当たり判定
//===========================================
void CEnemy::RockCollision(void)
{

}

//===========================================
// ブロックとの当たり判定
//===========================================
void CEnemy::BlockCollision(void)
{
	// ローカル変数宣言
	collision::SCollision coll = { false,false,false,false,false,false };				// 当たり判定の変数
	D3DXVECTOR3 pos = GetPos();							// 位置を取得する
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-m_CollSize.x, 0.0f, -m_CollSize.z);		// 最小値を取得する
	D3DXVECTOR3 vtxMax = m_CollSize;					// 最大値を取得する
	CListManager<CBlock*> list = CBlock::GetList();
	CBlock* pBlock = nullptr;		// 先頭の値
	CBlock* pBlockEnd = nullptr;	// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pBlock = list.GetTop();

		// 末尾の値を取得する
		pBlockEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// 六面体の当たり判定
			coll = collision::HexahedronClush
			(
				&pos,
				pBlock->GetPos(),
				GetPosOld(),
				pBlock->GetPosOld(),
				vtxMin,
				pBlock->GetFileData().vtxMin,
				vtxMax,
				pBlock->GetFileData().vtxMax
			);

			if (pBlock == pBlockEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pBlock = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}

	// 位置を適用する
	SetPos(pos);
}