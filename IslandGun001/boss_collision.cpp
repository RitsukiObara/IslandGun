//=========================================================
//
// ボスの当たり判定処理 [boss_collision.cpp]
// Author：小原立暉
//
//=========================================================
//*********************************************************
//	インクルードファイル
//*********************************************************
#include "boss_collision.h"

//===============================
// コンストラクタ
//===============================
CBossCollision::CBossCollision()
{
	// 全ての値をクリアする
	memset(m_coll, 0, sizeof(m_coll));	// 当たり判定の情報
	m_nNumColl = 0;						// 当たり判定の総数
}

//===============================
// デストラクタ
//===============================
CBossCollision::~CBossCollision()
{

}

//===============================
// 更新処理
//===============================
void CBossCollision::Update(void)
{

}

//===============================
// 生成処理
//===============================
CBossCollision* CBossCollision::Create(void)
{
	// ボスのインスタンス
	CBossCollision* pColl = nullptr;

	if (pColl == nullptr)
	{ // オブジェクトが NULL の場合

		// ボスを生成する
		pColl = new CBossCollision;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pColl;
	}

	// ボスのポインタを返す
	return pColl;
}

//===============================
// 当たり判定の情報の設定処理
//===============================
void CBossCollision::SetColl(const SCollision& coll, const int nIdx)
{
	// 当たり判定の情報を設定する
	m_coll[nIdx] = coll;
}

//===============================
// 当たり判定の情報の取得処理
//===============================
CBossCollision::SCollision CBossCollision::GetColl(const int nIdx) const
{
	// 当たり判定の情報を返す
	return m_coll[nIdx];
}

//===============================
// オフセット座標の設定処理
//===============================
void CBossCollision::SetCollOffset(const D3DXVECTOR3& offset, const int nIdx)
{
	// オフセット座標を設定する
	m_coll[nIdx].offset = offset;
}

//===============================
// オフセット座標の取得処理
//===============================
D3DXVECTOR3 CBossCollision::GetCollOffset(const int nIdx) const
{
	// オフセット座標を返す
	return m_coll[nIdx].offset;
}

//===============================
// 半径の設定処理
//===============================
void CBossCollision::SetRadius(const float fRadius, const int nIdx)
{
	// 半径を設定する
	m_coll[nIdx].fRadius = fRadius;
}

//===============================
// 半径の取得処理
//===============================
float CBossCollision::GetRadius(const int nIdx) const
{
	// 半径を返す
	return m_coll[nIdx].fRadius;
}

//===============================
// 当たり判定の総数の設定処理
//===============================
void CBossCollision::SetNumColl(const int nNum)
{
	// 総数を設定する
	m_nNumColl = nNum;
}

//===============================
// 当たり判定の総数の取得処理
//===============================
int CBossCollision::GetNumColl(void) const
{
	// 総数を返す
	return m_nNumColl;
}