//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "game.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "coin.h"
#include "coin_manager.h"
#include "enemy.h"
//#include "enemy_manager.h"
#include "tree.h"
#include "tree_manager.h"
#include "gold_bone.h"
#include "gold_bone_manager.h"
#include "player.h"
#include "player_action.h"
#include "gold_bone_UI.h"
#include "useful.h"

//===============================
// �}�N����`
//===============================
namespace
{
	const float COLLISION_ADD_DIFF_LENGTH = 0.01f;			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)
	const float TREE_RADIUS[CTree::TYPE_MAX] =				// �؂̓����蔻�莞�̔��a
	{
		50.5f,		// �؂̔��a
	};
	const float DAGGER_RADIUS = 100.0f;						// �_�K�[�̔��a
}

//===============================
// �N���n�ʂ͈̔͊O�̓����蔻��
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �擪�̋N���n�ʂ��擾����
	bool bCollision = false;									// �����蔻���

	while (pElev != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
			pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
			pElev->GetPos().y > pPos->y)
		{ // �N���n�ʂ�艺�ɂ���ꍇ

			if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
				pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
			{ // ���̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
			else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
				pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
			{ // �E�̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pElev = pElev->GetNext();
	}

	// �����蔻��󋵂�Ԃ�
	return bCollision;
}

//===============================
// �����Ƃ̓����蔻��
//===============================
void collision::CoinCollision(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMaxCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMinCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMax = size;		// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-size.x, 0.0f, -size.z);	// �ŏ��l
	CCoin* pCoin = CCoinManager::Get()->GetTop();			// �擪�̏������擾����
	CCoin* pCoinNext = nullptr;		// ���̂̏���

	while (pCoin != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// ���̏������擾����
		pCoinNext = pCoin->GetNext();

		// �R�C���̕ϐ����擾����
		posCoin = pCoin->GetPos();
		vtxMaxCoin = pCoin->GetFileData().vtxMax;
		vtxMinCoin = pCoin->GetFileData().vtxMin;

		if (useful::RectangleCollisionXY(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true &&
			useful::RectangleCollisionXZ(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true &&
			useful::RectangleCollisionYZ(pos, posCoin, vtxMax, vtxMaxCoin, vtxMin, vtxMinCoin) == true)
		{ // �����Əd�Ȃ����ꍇ

			// �擾����
			pCoin->Hit();
		}

		// ���̃I�u�W�F�N�g��������
		pCoin = pCoinNext;
	}
}

//===============================
// �G�Əe�̓����蔻��
//===============================
bool collision::EnemyHitToGun(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 bulletMax = D3DXVECTOR3(size.x, size.y, size.x);	// �e�̍ő�l
	D3DXVECTOR3 bulletMin = D3DXVECTOR3(-size.x, -size.y, -size.x);	// �e�̍ŏ��l
	D3DXVECTOR3 enemyMax;		// �G�̍ő�l
	D3DXVECTOR3 enemyMin;		// �G�̍ŏ��l
	CEnemy* pEnemy = nullptr;		// �擪�̓G
	CEnemy* pEnemyEnd = nullptr;	// �����̒l
	int nIdx = 0;

	// while������
	if (CEnemy::GetList().IsEmpty() == false)
	{ // �󔒂���Ȃ��ꍇ

		// �擪�̒l���擾����
		pEnemy = CEnemy::GetList().GetTop();

		// �����̒l���擾����
		pEnemyEnd = CEnemy::GetList().GetEnd();	

		while (true)
		{ // �������[�v

			// �G�֌W�̕ϐ���ݒ�
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
			{ // �G�Əd�Ȃ����ꍇ

				// �q�b�g����
				pEnemy->Hit(pos);

				// true ��Ԃ�
				return true;
			}

			if (pEnemy == pEnemyEnd)
			{ // �����ɒB�����ꍇ

				// while���𔲂��o��
				break;
			}

			// ���̃I�u�W�F�N�g��������
			pEnemy = CEnemy::GetList().GetData(nIdx + 1);

			// �C���f�b�N�X�����Z����
			nIdx++;
		}
	}

	// false ��Ԃ�
	return false;
}

//===============================
// ���̍��Ƃ̓����蔻��
//===============================
void collision::GoldBoneCollision(const CPlayer& pPlayer, const D3DXVECTOR3& size)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = pPlayer.GetPos();
	D3DXVECTOR3 posCoin = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMaxBone = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMinBone = NONE_D3DXVECTOR3;
	D3DXVECTOR3 vtxMax = size;		// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-size.x, 0.0f, -size.z);	// �ŏ��l
	CGoldBone* pBone = CGoldBoneManager::Get()->GetTop();			// �擪�̋��̍����擾����
	CGoldBone* pBoneNext = nullptr;		// ���̋��̍�

	while (pBone != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// ���̋��̍����擾����
		pBoneNext = pBone->GetNext();

		// �R�C���̕ϐ����擾����
		posCoin = pBone->GetPos();
		vtxMaxBone = pBone->GetFileData().vtxMax;
		vtxMinBone = pBone->GetFileData().vtxMin;

		if (useful::RectangleCollisionXY(pos, posCoin, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true &&
			useful::RectangleCollisionXZ(pos, posCoin, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true &&
			useful::RectangleCollisionYZ(pos, posCoin, vtxMax, vtxMaxBone, vtxMin, vtxMinBone) == true)
		{ // ���̍��Əd�Ȃ����ꍇ

			// �擾����
			pBone->Hit();

			if (pPlayer.GetGoldBoneUI() != nullptr)
			{ // ���̍�UI�� NULL ����Ȃ��ꍇ

				// ���̍��擾����
				pPlayer.GetGoldBoneUI()->GetGoldBone();
			}
		}

		// ���̃I�u�W�F�N�g��������
		pBone = pBoneNext;
	}
}

//===============================
// �؂̓����蔻��
//===============================
bool collision::TreeCollision(D3DXVECTOR3* pos, const float fRadius)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posTree = NONE_D3DXVECTOR3;			// �؂̈ʒu
	float fObjectRadius;							// ���a
	CTree* pTree = CTreeManager::Get()->GetTop();	// �擪�̖؂��擾����
	bool bCollision = false;						// �����蔻���

	while (pTree != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		posTree = pTree->GetPos();		// �؂̈ʒu
		fObjectRadius = fRadius + TREE_RADIUS[pTree->GetType()];	// ���a

		if (useful::CylinderCollision(pos, posTree, fObjectRadius) == true)
		{ // �~���̓����蔻��ɓ������ꍇ

			// �����蔻��󋵂� true �ɂ���
			bCollision = true;
		}

		// ���̃I�u�W�F�N�g��������
		pTree = pTree->GetNext();
	}

	// �����蔻��� ��Ԃ�
	return bCollision;
}

//===============================
// �؂ւ̍U�����菈��
//===============================
void collision::TreeAttack(const CPlayer& pPlayer, const float fHeight)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posTree = NONE_D3DXVECTOR3;			// �؂̈ʒu
	D3DXVECTOR3 posPlayer = pPlayer.GetPos();		// �v���C���[�̈ʒu
	CTree* pTree = CTreeManager::Get()->GetTop();	// �擪�̖؂��擾����

	while (pTree != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// �؂̈ʒu��ݒ肷��
		posTree = pTree->GetPos();

		if (useful::CircleCollisionXZ(posPlayer, posTree, DAGGER_RADIUS, TREE_RADIUS[pTree->GetType()]) &&
			posPlayer.y <= posTree.y + pTree->GetFileData().vtxMax.y &&
			posPlayer.y + fHeight >= posTree.y)
		{ // �_�K�[���؂ɐڐG�����ꍇ

			// �q�b�g����
			pTree->Hit();
		}

		// ���̃I�u�W�F�N�g��������
		pTree = pTree->GetNext();
	}
}

/*
* @brief �Z�ʑ̂̓����蔻��
* @param pos [out] �Ώۂ̈ʒu
* @param posBlock [in] �u���b�N�̈ʒu
* @param posOld [in] �Ώۂ̑O��̈ʒu
* @param posOldBlock [in] �u���b�N�̑O��̈ʒu
* @param min [in] �ŏ��l
* @param minBlock [in] �u���b�N�̍ŏ��l
* @param max [in] �ő�l
* @param maxBlock [in] �u���b�N�̍ő�l
* @return bool �Ԃ��������ǂ���
*/
bool collision::HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

/*
* @brief �Z�ʑ̂̃q�b�g����
* @param pos [out] �Ώۂ̈ʒu
* @param posBlock [in] �u���b�N�̈ʒu
* @param posOld [in] �Ώۂ̑O��̈ʒu
* @param posOldBlock [in] �u���b�N�̑O��̈ʒu
* @param min [in] �ŏ��l
* @param minBlock [in] �u���b�N�̍ŏ��l
* @param max [in] �ő�l
* @param maxBlock [in] �u���b�N�̍ő�l
* @return bool �Ԃ��������ǂ���
*/
bool collision::HexahedronHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
		if (posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos.x + min.x)
		{ // �E�ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos.x + max.x)
		{ // ���ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos.z + min.z)
		{ // ���ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos.z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos.y + min.y)
		{ // ��ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos.y + max.y)
		{ // ���ɂԂ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

/*
* @brief �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t��)
* @param pos [out] �Ώۂ̈ʒu
* @param posBlock [in] �u���b�N�̈ʒu
* @param posOld [in] �Ώۂ̑O��̈ʒu
* @param posOldBlock [in] �u���b�N�̑O��̈ʒu
* @param min [in] �ŏ��l
* @param minBlock [in] �u���b�N�̍ŏ��l
* @param max [in] �ő�l
* @param maxBlock [in] �u���b�N�̍ő�l
* @return SCollision �Z�ʑ̂̓����蔻��
*/
collision::SCollision collision::HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// �E�̓����蔻��� true �ɂ���
			collision.bRight = true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bFar = true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// ��O�̓����蔻��� true �ɂ���
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// ��̓����蔻��� true �ɂ���
			collision.bTop = true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bBottom = true;
		}
	}

	// �����蔻��̕ϐ���Ԃ�
	return collision;
}