//===========================================
//
// �؂̃��C������[tree.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "tree.h"
#include "renderer.h"
#include "useful.h"

#include "tree_manager.h"

#include "palm_tree.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const CXFile::TYPE FILE_TYPE[CTree::TYPE_MAX] =		// X�t�@�C���̎��
	{
		CXFile::TYPE_PALMTREE,			// ���V�̖�
	};
}

//==============================
// �R���X�g���N�^
//==============================
CTree::CTree(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_PALM;		// ���

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;			// �O�̃|�C���^
	m_pNext = nullptr;			// ���̃|�C���^

	if (CTreeManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CTreeManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CTree::~CTree()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CTree::SetPrev(CTree* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CTree::SetNext(CTree* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CTree* CTree::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CTree* CTree::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CTree::Init(void)
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
void CTree::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CTreeManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CTreeManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CTree::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CTree::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTree::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(rot);					// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(FILE_TYPE[type]);	// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_type = type;		// ���
}

//=====================================
// �q�b�g����
//=====================================
void CTree::Hit(void)
{

}

//=======================================
// ��������
//=======================================
CTree* CTree::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTree* pTree = nullptr;	// �C���X�^���X�𐶐�

	if (pTree == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case CTree::TYPE_PALM:		// ���V�̖�

			// ���V�̖؂𐶐�����
			pTree = new CPalmTree;

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTree != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTree->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTree->SetData(pos, rot, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �؂̃|�C���^��Ԃ�
	return pTree;
}

//=======================================
// ��ނ̎擾����
//=======================================
CTree::TYPE CTree::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}