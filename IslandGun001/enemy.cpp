//============================================================
//
// �G���� [enemy.cpp]
// Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "model.h"

#include "motion.h"
#include "block.h"
#include "collision.h"
#include "anim_reaction.h"

#include "tordle.h"
#include "iwakari.h"

//------------------------------------------------------------
// �������O���
//------------------------------------------------------------
namespace
{
	const D3DXVECTOR3 COLLSIZE[CEnemy::TYPE_MAX] =		// �����蔻��̃T�C�Y
	{
		D3DXVECTOR3(85.0f,85.0f,85.0f),
		D3DXVECTOR3(80.0f,0.0f,80.0f),
	};
	const int LIFE[CEnemy::TYPE_MAX] =					// �̗�
	{
		30,
		5,
	};
	const D3DXVECTOR3 DEATH_EXPLOSION = D3DXVECTOR3(200.0f, 200.0f, 0.0f);		// ���S���̔���
}

// �ÓI�����o�ϐ�
CListManager<CEnemy*> CEnemy::m_list = {};				// ���X�g

//================================
// �R���X�g���N�^
//================================
CEnemy::CEnemy() : CCharacter(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V����

	m_type = TYPE_TORDLE;			// ���
	m_collSize = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y
	m_nLife = 0;					// �̗�

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//================================
// �f�X�g���N�^
//================================
CEnemy::~CEnemy()
{

}

//================================
// �I������
//================================
void CEnemy::Uninit(void)
{
	// ���[�V�����̏I������
	delete m_pMotion;
	m_pMotion = nullptr;

	// �I������
	CCharacter::Uninit();

	// ������������
	m_list.Pull(this);
}

//================================
// �X�V����
//================================
void CEnemy::Update(void)
{
	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �؂Ƃ̓����蔻��
	TreeCollision();

	// ��Ƃ̓����蔻��
	RockCollision();

	// �u���b�N�Ƃ̓����蔻��
	BlockCollision();
}

//================================
// �`�揈��
//================================
void CEnemy::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//================================
// ���̐ݒ菈��
//================================
void CEnemy::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// �S�Ă̒l������������
	SetPos(pos);				// �ʒu
	SetPosOld(GetPos());		// �O��̈ʒu
	SetRot(rot);				// ����
	SetScale(NONE_SCALE);		// �g�嗦

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
	}

	// ���[�V�����̃��Z�b�g����
	m_pMotion->ResetMotion(MOTIONTYPE_NEUTRAL);

	// �S�Ă̒l��ݒ肷��
	m_type = type;					// ���
	m_collSize = COLLSIZE[m_type];	// �����蔻��̃T�C�Y
	m_nLife = LIFE[m_type];			// �̗�
}

//===========================================
// ���S���̏���
//===========================================
void CEnemy::Death(void)
{
	if (m_nLife <= 0)
	{ // �̗͂�0�ȉ��ɂȂ����ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 pos = GetPos();

		// �ʒu��^�񒆂ɂ���
		pos.y += (m_collSize.y * 0.5f);

		// �A�j���[�V�������A�N�V�����𐶐�
		CAnimReaction::Create(pos, DEATH_EXPLOSION, NONE_D3DXCOLOR, CAnimReaction::TYPE::TYPE_GUNEXPLOSION, 4, 1);

		// �I������
		Uninit();
	}
}

//===========================================
// ��������
//===========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// �G�̃C���X�^���X�𐶐�
	CEnemy* pEnemy = nullptr;

	if (pEnemy == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case CEnemy::TYPE_TORDLE:		// �^�[�h��

			// �^�[�h���𐶐�����
			pEnemy = new CTordle;

			break;

		case CEnemy::TYPE_IWAKARI:		// �C���J��

			// �C���J���𐶐�����
			pEnemy = new CIwakari;

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return pEnemy;
	}

	if (pEnemy != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEnemy->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEnemy->SetData(pos, rot, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G�̃|�C���^��Ԃ�
	return pEnemy;
}

//===========================================
// ���[�V�����̎擾����
//===========================================
CMotion* CEnemy::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//===========================================
// ���[�V�����̐�������
//===========================================
void CEnemy::CreateMotion(void)
{
	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �̏ꍇ

		// ���[�V�����𐶐�����
		m_pMotion = CMotion::Create();
	}
}

//===========================================
// �����蔻��̃T�C�Y�̐ݒ菈��
//===========================================
void CEnemy::SetCollSize(const D3DXVECTOR3& size)
{
	// �����蔻��̃T�C�Y��ݒ肷��
	m_collSize = size;
}

//===========================================
// �����蔻��̃T�C�Y�̎擾����
//===========================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// �����蔻��̃T�C�Y���擾����
	return m_collSize;
}

//===========================================
// �̗͂̐ݒ菈��
//===========================================
void CEnemy::SetLife(const int nLife)
{
	// �̗͂�ݒ肷��
	m_nLife = nLife;
}

//===========================================
// �̗͂̎擾����
//===========================================
int CEnemy::GetLife(void) const
{
	// �̗͂�Ԃ�
	return m_nLife;
}

//===========================================
// ���X�g�̎擾����
//===========================================
CListManager<CEnemy*> CEnemy::GetList(void)
{
	// ���X�g�̏���Ԃ�
	return m_list;
}

//===========================================
// �؂Ƃ̓����蔻��
//===========================================
void CEnemy::TreeCollision(void)
{
	// �ʒu�Ɣ��a���擾����
	D3DXVECTOR3 pos = GetPos();
	float fRadius = m_collSize.x;

	// �؂Ƃ̓����蔻��
	collision::TreeCollision(&pos, fRadius);

	// �ʒu��K�p����
	SetPos(pos);
}

//===========================================
// ��Ƃ̓����蔻��
//===========================================
void CEnemy::RockCollision(void)
{

}

//===========================================
// �u���b�N�Ƃ̓����蔻��
//===========================================
void CEnemy::BlockCollision(void)
{
	// ���[�J���ϐ��錾
	collision::SCollision coll = { false,false,false,false,false,false };		// �����蔻��̕ϐ�
	D3DXVECTOR3 pos = GetPos();							// �ʒu���擾����
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-m_collSize.x, 0.0f, -m_collSize.z);		// �ŏ��l���擾����
	D3DXVECTOR3 vtxMax = m_collSize;					// �ő�l���擾����
	CListManager<CBlock*> list = CBlock::GetList();
	CBlock* pBlock = nullptr;		// �擪�̒l
	CBlock* pBlockEnd = nullptr;	// �����̒l
	int nIdx = 0;

	// while������
	if (list.IsEmpty() == false)
	{ // �󔒂���Ȃ��ꍇ

		// �擪�̒l���擾����
		pBlock = list.GetTop();

		// �����̒l���擾����
		pBlockEnd = list.GetEnd();

		while (true)
		{ // �������[�v

			// �Z�ʑ̂̓����蔻��
			coll = collision::HexahedronClush
			(
				&pos,
				pBlock->GetPos(),
				GetPosOld(),
				pBlock->GetPosOld(),
				vtxMin,
				pBlock->GetVtxMin(),
				vtxMax,
				pBlock->GetVtxMax()
			);

			if (pBlock == pBlockEnd)
			{ // �����ɒB�����ꍇ

				// while���𔲂��o��
				break;
			}

			// ���̃I�u�W�F�N�g��������
			pBlock = list.GetData(nIdx + 1);

			// �C���f�b�N�X�����Z����
			nIdx++;
		}
	}

	// �ʒu��K�p����
	SetPos(pos);
}