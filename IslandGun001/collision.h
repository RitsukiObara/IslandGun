//===================================
//
// 当たり判定ヘッダー[collision.h]
// Author 小原立暉
//
//===================================
#ifndef _COLLISION_H_			//このマクロ定義がされていなかったら
#define _COLLISION_H_			//2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "main.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CPlayer;			// プレイヤー
class CEnemy;			// 敵
class CBullet;			// 弾丸

//-----------------------------------
// 名前空間(当たり判定)
//-----------------------------------
namespace collision
{
	// 構造体定義(当たり判定)
	struct SCollision
	{
		bool bTop;		// 上の当たり判定
		bool bBottom;	// 下の当たり判定
		bool bRight;	// 右の当たり判定
		bool bLeft;		// 左の当たり判定
		bool bFar;		// 奥の当たり判定
		bool bNear;		// 手前の当たり判定
	};

	// 起伏地面の当たり判定
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// 起伏地面の範囲外の当たり判定

	// 小判との当たり判定
	void CoinCollision(CPlayer* pPlayer, const D3DXVECTOR3 size, const int nAreaIdx);				// 小判との当たり判定

	// 敵との当たり判定
	bool EnemyHitToGun(const CBullet& bullet);			// 敵と銃の当たり判定
	bool EnemyHitToDagger(const D3DXVECTOR3& pos, const float fHeight, const float fRadius);		// 敵とダガーの当たり判定
	bool EnemyHitToPlayer(CPlayer* pPlayer, const float fRadius, const float fHeight);				// 敵とプレイヤーとの当たり判定
	void EnemyHitToEnemy(CEnemy* pTarget);		// 敵同士の当たり判定

	// 金の骨との当たり判定
	void GoldBoneCollision(const CPlayer& pPlayer, const D3DXVECTOR3& size);		// 金の骨との当たり判定

	// 木との当たり判定
	bool TreeCollision(D3DXVECTOR3* pos, const float fRadius, const int nAreaIdx);			// 木の当たり判定
	void TreeAttack(const CPlayer& pPlayer, const float fRadius, const float fHeight);		// 木への攻撃判定処理

	// ヤシの実との当たり判定
	void PalmFruitHit(CPlayer* pPlayer, const float fRadius, const float fHeight);			// ヤシの実との当たり判定
	bool PalmFruitAttack(const D3DXVECTOR3& pos, const float fRadius, const int nAreaIdx);	// ヤシの実への攻撃判定

	// 岩との当たり判定
	bool RockCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const float fRadius, const float fHeight, const int nAreaIdx, float* fGravity = nullptr, bool* bJump = nullptr);		// 岩との当たり判定

	// 爆弾花との当たり判定
	bool BangFlowerHit(const D3DXVECTOR3& pos, const float fRadius, const float fHeight);			// 爆弾花のヒット判定
	bool BombHitToGun(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fRadius);		// 爆弾のヒット判定(銃弾)
	bool BombHitToDagger(const D3DXVECTOR3& pos, const float fRadius, const float fHeight);			// 爆弾のヒット判定(ダガー)
	bool BombHitToSlashRipple(const D3DXVECTOR3& pos, const float fRadius, const float fHeight);	// 爆弾のヒット判定(斬撃波紋)

	// 爆風との当たり判定
	void ExplosionHitToRock(const D3DXVECTOR3& pos, const float fRadius, const float fHeight, const int nAreaIdx);		// 爆風と岩との当たり判定
	void ExplosionHitToEnemy(const D3DXVECTOR3& pos, const float fRadius, const float fHeight);		// 爆風と敵との当たり判定
	bool ExplosionHitToPlayer(CPlayer* pPlayer, const float fRadius, const float fHeight);			// 爆風とプレイヤーとの当たり判定
	
	// 壁との当たり判定
	bool WallCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& vtxMax, const D3DXVECTOR3& vtxMin, const int nAreaIdx);		// 壁との当たり判定

	// ブロックとの当たり判定
	bool BlockHit(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& vtxMax, const D3DXVECTOR3& vtxMin, const int nAreaIdx);			// ブロックとのヒット判定

	// ボスとの当たり判定
	bool BossHit(const D3DXVECTOR3& pos, const float fRadius, const int nDamage);				// ボスの当たり判定
	bool BossAttack(const D3DXVECTOR3& pos, const float fRadius, float* fRotSmash = nullptr);	// ボスとのヒット判定

	// 祭壇との当たり判定
	bool AlterCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& vtxMax, const D3DXVECTOR3& vtxMin);		// 祭壇との当たり判定
	
	// 斬撃波紋との当たり判定
	bool RippleHit(const D3DXVECTOR3& pos, const float fRadius, const float fHeight, float* fRotSmash = nullptr);		// 斬撃の波紋の当たり判定
	
	// 風攻撃との当たり判定
	bool WindShotHit(const D3DXVECTOR3& pos, const float fRadius, const float fHeight, float* fSmashRot = nullptr);		// 風攻撃との当たり判定

	// 炎攻撃との当たり判定
	bool FireShotHit(const D3DXVECTOR3& pos, const float fRadius, const float fHeight, float* fSmashRot = nullptr);		// 炎攻撃との当たり判定

	// 看板の当たり判定
	bool SignboardCollision(const D3DXVECTOR3& pos, const float fRadius);		// 看板との当たり判定

	// 的の当たり判定
	bool TargetHit(const D3DXVECTOR3& pos, const float fRadius);				// 的との当たり判定

	// ドアとの当たり判定
	bool DoorHit(const D3DXVECTOR3& pos, const float fRadius);					// ドアとのヒット判定
	bool DoorCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size);		// ドアとの当たり判定

	// ステージの当たり判定
	void StageCollision(D3DXVECTOR3* pos, const float fWidth);					// ステージの当たり判定

	// 汎用的な当たり判定
	bool HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定
	bool HexahedronHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体のヒット判定
	bool HexahedronHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);																	// 六面体のヒット判定(Old無し)
	SCollision HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定(どの面に乗ったかの判定付き)
}

#endif