//===========================================
//
// 当たり判定のメイン処理[collision.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "game.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "coin.h"
#include "enemy.h"
#include "tree.h"
#include "gold_bone.h"
#include "player.h"
#include "player_action.h"
#include "gold_bone_UI.h"
#include "useful.h"

//===============================
// マクロ定義
//===============================
namespace
{
	const float COLLISION_ADD_DIFF_LENGTH = 0.01f;			// 僅かな誤差を埋めるためのマクロ定義(突っかかり防止)
	const float TREE_RADIUS[CTree::TYPE_MAX] =				// 木の当たり判定時の半径
	{
		50.5f,		// 木の半径
	};
	const float DAGGER_RADIUS = 100.0f;						// ダガーの半径
}

//===============================
// 起伏地面の範囲外の当たり判定
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ローカル変数宣言
	bool bCollision = false;									// 当たり判定状況
	CListManager<CElevation*> list = CElevation::GetList();
	CElevation* pElev = nullptr;			// 先頭の小判
	CElevation* pElevEnd = nullptr;		// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pElev = list.GetTop();

		// 末尾の値を取得する
		pElevEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
				pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
				pElev->GetPos().y > pPos->y)
			{ // 起伏地面より下にいる場合

				if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
					pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
				{ // 左の当たり判定

					// 位置を設定する
					pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

					// 当たり判定状況を true にする
					bCollision = true;
				}
				else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
					pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
				{ // 右の当たり判定

					// 位置を設定する
					pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

					// 当たり判定状況を true にする
					bCollision = true;
				}
			}

			if (pElev == pElevEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pElev = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}

	// 当たり判定状況を返す
	return bCollision;
}

//===============================
// 小判との当たり判定
//===============================
void collision::CoinCollision(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ローカル変数宣言
	D3DXVECTOR3 posCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMaxCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMinCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMax = size;		// 最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-size.x, 0.0f, -size.z);	// 最小値
	CListManager<CCoin*> list = CCoin::GetList();
	CCoin* pCoin = nullptr;			// 先頭の小判
	CCoin* pCoinEnd = nullptr;		// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pCoin = list.GetTop();

		// 末尾の値を取得する
		pCoinEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// コインの変数を取得する
			posCoin = pCoin->GetPos();
			vtxMaxCoin = pCoin->GetFileData().vtxMax;
			vtxMinCoin = pCoin->GetFileData().vtxMin;

			if (useful::RectangleCollisionXY(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true &&
				useful::RectangleCollisionXZ(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true &&
				useful::RectangleCollisionYZ(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true)
			{ // 小判と重なった場合

				// 取得処理
				pCoin->Hit();
			}

			if (pCoin == pCoinEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pCoin = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}
}

//===============================
// 敵と銃の当たり判定
//===============================
bool collision::EnemyHitToGun(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// ローカル変数宣言
	D3DXVECTOR3 bulletMax = D3DXVECTOR3(size.x, size.y, size.x);	// 弾の最大値
	D3DXVECTOR3 bulletMin = D3DXVECTOR3(-size.x, -size.y, -size.x);	// 弾の最小値
	D3DXVECTOR3 enemyMax;		// 敵の最大値
	D3DXVECTOR3 enemyMin;		// 敵の最小値
	CListManager<CEnemy*> list = CEnemy::GetList();
	CEnemy* pEnemy = nullptr;		// 先頭の敵
	CEnemy* pEnemyEnd = nullptr;	// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pEnemy = list.GetTop();

		// 末尾の値を取得する
		pEnemyEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// 敵関係の変数を設定
			enemyMax = pEnemy->GetCollSize();
			enemyMin = D3DXVECTOR3
			(
				-pEnemy->GetCollSize().x,
				0.0f,
				-pEnemy->GetCollSize().z
			);

			if (HexahedronHit
			(
				pos,
				pEnemy->GetPos(),
				posOld,
				pEnemy->GetPosOld(),
				bulletMin,
				enemyMin,
				bulletMax,
				enemyMax) == true)
			{ // 敵と重なった場合

				// ヒット処理
				pEnemy->Hit(pos);

				// true を返す
				return true;
			}

			if (pEnemy == pEnemyEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pEnemy = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}

	// false を返す
	return false;
}

//===============================
// 金の骨との当たり判定
//===============================
void collision::GoldBoneCollision(const CPlayer& pPlayer, const D3DXVECTOR3& size)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = pPlayer.GetPos();
	D3DXVECTOR3 posBone = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMaxBone = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMinBone = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMax = size;		// 最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-size.x, 0.0f, -size.z);	// 最小値
	CListManager<CGoldBone*> list = CGoldBone::GetList();
	CGoldBone* pBone = nullptr;		// 先頭の値
	CGoldBone* pBoneEnd = nullptr;	// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pBone = list.GetTop();

		// 末尾の値を取得する
		pBoneEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// 金の骨の変数を取得する
			posBone = pBone->GetPos();
			vtxMaxBone = pBone->GetFileData().vtxMax;
			vtxMinBone = pBone->GetFileData().vtxMin;

			if (useful::RectangleCollisionXY(pos, posBone, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true &&
				useful::RectangleCollisionXZ(pos, posBone, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true &&
				useful::RectangleCollisionYZ(pos, posBone, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true)
			{ // 金の骨と重なった場合

				// 取得処理
				pBone->Hit();

				if (pPlayer.GetGoldBoneUI() != nullptr)
				{ // 金の骨UIが NULL じゃない場合

					// 金の骨取得処理
					pPlayer.GetGoldBoneUI()->GetGoldBone();
				}
			}

			if (pBone == pBoneEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pBone = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}
}

//===============================
// 木の当たり判定
//===============================
bool collision::TreeCollision(D3DXVECTOR3* pos, const float fRadius)
{
	// ローカル変数宣言
	D3DXVECTOR3 posTree = NONE_D3DXVECTOR3;			// 木の位置
	float fObjectRadius;							// 半径
	bool bCollision = false;						// 当たり判定状況
	CListManager<CTree*> list = CTree::GetList();
	CTree* pTree = nullptr;		// 先頭の値
	CTree* pTreeEnd = nullptr;	// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pTree = list.GetTop();

		// 末尾の値を取得する
		pTreeEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			posTree = pTree->GetPos();		// 木の位置
			fObjectRadius = fRadius + TREE_RADIUS[pTree->GetType()];	// 半径

			if (useful::CylinderCollision(pos, posTree, fObjectRadius) == true)
			{ // 円柱の当たり判定に入った場合

				// 当たり判定状況を true にする
				bCollision = true;
			}

			if (pTree == pTreeEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pTree = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}

	// 当たり判定状況 を返す
	return bCollision;
}

//===============================
// 木への攻撃判定処理
//===============================
void collision::TreeAttack(const CPlayer& pPlayer, const float fHeight)
{
	// ローカル変数宣言
	D3DXVECTOR3 posTree = NONE_D3DXVECTOR3;			// 木の位置
	D3DXVECTOR3 posPlayer = pPlayer.GetPos();		// プレイヤーの位置
	CListManager<CTree*> list = CTree::GetList();
	CTree* pTree = nullptr;		// 先頭の値
	CTree* pTreeEnd = nullptr;	// 末尾の値
	int nIdx = 0;

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pTree = list.GetTop();

		// 末尾の値を取得する
		pTreeEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// 木の位置を設定する
			posTree = pTree->GetPos();

			if (useful::CircleCollisionXZ(posPlayer, posTree, DAGGER_RADIUS, TREE_RADIUS[pTree->GetType()]) &&
				posPlayer.y <= posTree.y + pTree->GetFileData().vtxMax.y &&
				posPlayer.y + fHeight >= posTree.y)
			{ // ダガーが木に接触した場合

				// ヒット処理
				pTree->Hit();
			}

			if (pTree == pTreeEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pTree = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}
}

/*
* @brief 六面体の当たり判定
* @param pos [out] 対象の位置
* @param posBlock [in] ブロックの位置
* @param posOld [in] 対象の前回の位置
* @param posOldBlock [in] ブロックの前回の位置
* @param min [in] 最小値
* @param minBlock [in] ブロックの最小値
* @param max [in] 最大値
* @param maxBlock [in] ブロックの最大値
* @return bool ぶつかったかどうか
*/
bool collision::HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

/*
* @brief 六面体のヒット判定
* @param pos [out] 対象の位置
* @param posBlock [in] ブロックの位置
* @param posOld [in] 対象の前回の位置
* @param posOldBlock [in] ブロックの前回の位置
* @param min [in] 最小値
* @param minBlock [in] ブロックの最小値
* @param max [in] 最大値
* @param maxBlock [in] ブロックの最大値
* @return bool ぶつかったかどうか
*/
bool collision::HexahedronHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
		if (posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos.x + min.x)
		{ // 右にぶつかった場合

			// true を返す
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos.x + max.x)
		{ // 左にぶつかった場合

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos.z + min.z)
		{ // 奥にぶつかった場合

			// true を返す
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos.z + max.z)
		{ // 手前にぶつかった場合

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos.y + min.y)
		{ // 上にぶつかった場合

			// true を返す
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos.y + max.y)
		{ // 下にぶつかった場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

/*
* @brief 六面体の当たり判定(どの面に乗ったかの判定付き)
* @param pos [out] 対象の位置
* @param posBlock [in] ブロックの位置
* @param posOld [in] 対象の前回の位置
* @param posOldBlock [in] ブロックの前回の位置
* @param min [in] 最小値
* @param minBlock [in] ブロックの最小値
* @param max [in] 最大値
* @param maxBlock [in] ブロックの最大値
* @return SCollision 六面体の当たり判定
*/
collision::SCollision collision::HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// 当たり判定の変数を宣言
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// 右の当たり判定を true にする
			collision.bRight = true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// 左の当たり判定を true にする
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// 奥の当たり判定を true にする
			collision.bFar = true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// 手前の当たり判定を true にする
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// 上の当たり判定を true にする
			collision.bTop = true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// 下の当たり判定を true にする
			collision.bBottom = true;
		}
	}

	// 当たり判定の変数を返す
	return collision;
}