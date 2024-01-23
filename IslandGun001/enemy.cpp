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
#include "anim_reaction.h"

#include "tordle.h"
#include "collision.h"
#include "block.h"

//------------------------------------------------------------
// �������O���
//------------------------------------------------------------
namespace
{
	const D3DXVECTOR3 COLLSIZE[CEnemy::TYPE_MAX] =		// �����蔻��̃T�C�Y
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
	m_CollSize = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y

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
// ����������
//================================
HRESULT CEnemy::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(6);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		m_pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		m_pMotion->Load(CMotion::STYLE_TORDLE);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(0);

	// �S�Ă̒l������������
	m_type = TYPE_TORDLE;			// ���
	m_CollSize = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y

	// �l��Ԃ�
	return S_OK;
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
		GetHierarchy(nCntData)->SetFileData(CMotion::GetSaveData(CMotion::STYLE_TORDLE, nCntData));	// �f�[�^�̐ݒ菈��
	}

	// ���[�V�����̃��Z�b�g����
	m_pMotion->ResetMotion(MOTIONTYPE_NEUTRAL);

	// �S�Ă̒l��ݒ肷��
	m_type = type;					// ���
	m_CollSize = COLLSIZE[m_type];	// �����蔻��̃T�C�Y
}

//===========================================
// �q�b�g����
//===========================================
void CEnemy::Hit(const D3DXVECTOR3& pos)
{
	// �A�j���[�V�������A�N�V�����𐶐�
	CAnimReaction::Create(pos, D3DXVECTOR3(180.0f, 180.0f, 0.0f), NONE_D3DXCOLOR, CAnimReaction::TYPE::TYPE_GUNEXPLOSION, 4, 1);

	// �I������
	Uninit();
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
// �����蔻��̃T�C�Y�̎擾����
//===========================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// �����蔻��̃T�C�Y���擾����
	return m_CollSize;
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
	float fRadius = m_CollSize.x;

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
	collision::SCollision coll = { false,false,false,false,false,false };				// �����蔻��̕ϐ�
	D3DXVECTOR3 pos = GetPos();							// �ʒu���擾����
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-m_CollSize.x, 0.0f, -m_CollSize.z);		// �ŏ��l���擾����
	D3DXVECTOR3 vtxMax = m_CollSize;					// �ő�l���擾����
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
				pBlock->GetFileData().vtxMin,
				vtxMax,
				pBlock->GetFileData().vtxMax
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