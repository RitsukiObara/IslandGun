//===========================================
//
// ���̍��̃��C������[gold_bone.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "gold_bone.h"
#include "renderer.h"
#include "useful.h"

#include "gold_bone_manager.h"

//==============================
// �R���X�g���N�^
//==============================
CGoldBone::CGoldBone() : CModel(CObject::TYPE_GOLDBONE, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;	// �ړ���

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;			// �O�̃|�C���^
	m_pNext = nullptr;			// ���̃|�C���^

	if (CGoldBoneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CGoldBoneManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CGoldBone::~CGoldBone()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CGoldBone::SetPrev(CGoldBone* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CGoldBone::SetNext(CGoldBone* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CGoldBone* CGoldBone::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CGoldBone* CGoldBone::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CGoldBone::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CGoldBone::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CGoldBoneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CGoldBoneManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CGoldBone::Update(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ړ�������
	pos += m_move;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CGoldBone::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CGoldBone::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_GOLDBONE);		// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_move = move;	// �ړ���
}

//=======================================
// ��������
//=======================================
CGoldBone* CGoldBone::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CGoldBone* pBone = nullptr;	// �C���X�^���X�𐶐�

	if (pBone == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pBone = new CGoldBone;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBone != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBone->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBone->SetData(pos, move);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���̍��̃|�C���^��Ԃ�
	return pBone;
}

//=======================================
// �q�b�g����
//=======================================
void CGoldBone::Hit(void)
{

}

//=======================================
// �擾��ԏ���
//=======================================
void CGoldBone::Get(void)
{

}