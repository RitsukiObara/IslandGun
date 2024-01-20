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

//==============================
// �R���X�g���N�^
//==============================
CTree::CTree() : CModel(CObject::TYPE_GOLDBONE, CObject::PRIORITY_ENTITY)
{
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
void CTree::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_PALMTREE);		// ���f���̏��
}

//=======================================
// ��������
//=======================================
CTree* CTree::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTree* pCoin = nullptr;	// �C���X�^���X�𐶐�

	if (pCoin == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pCoin = new CTree;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCoin != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCoin->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCoin->SetData(pos, move);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pCoin;
}