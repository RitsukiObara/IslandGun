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

#include "enemy_manager.h"
#include "motion.h"
#include "anim_reaction.h"

// �}�N����`
namespace
{
	const D3DXVECTOR3 COLLSIZE[CEnemy::TYPE_MAX] =		// �����蔻��̃T�C�Y
	{
		D3DXVECTOR3(70.0f,140.0f,70.0f)
	};
}

//================================
// �R���X�g���N�^
//================================
CEnemy::CEnemy() : CCharacter(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V����

	m_type = TYPE_TORDLE;			// ���
	m_CollSize = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃A�E�g�{�[���ւ̃|�C���^
	m_pNext = nullptr;		// ���̃A�E�g�{�[���ւ̃|�C���^

	if (CEnemyManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CEnemyManager::Get()->Regist(this);
	}
}

//================================
// �f�X�g���N�^
//================================
CEnemy::~CEnemy()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CEnemy::SetPrev(CEnemy* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CEnemy::SetNext(CEnemy* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CEnemy* CEnemy::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CEnemy* CEnemy::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
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
	SetNumModel(17);

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
		m_pMotion->Load("data\\TXT\\PlayerMotion.txt");
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

	if (CEnemyManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CEnemyManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//================================
// �X�V����
//================================
void CEnemy::Update(void)
{
	// ���[�V�����̍X�V����
	m_pMotion->Update();
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
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// �f�[�^�̐ݒ菈��
	}

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

		// ���������m�ۂ���
		pEnemy = new CEnemy;
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
// �����蔻��̃T�C�Y�̎擾����
//===========================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// �����蔻��̃T�C�Y���擾����
	return m_CollSize;
}