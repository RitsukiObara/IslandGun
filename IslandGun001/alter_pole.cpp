//===========================================
//
// �Β��̃��C������[alter_pole.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "alter_pole.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\AlterPole.x";		// ���f���̖��O
}

//==============================
// �R���X�g���N�^
//==============================
CAlterPole::CAlterPole() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_bEmpty = true;			// �󔒏�
}

//==============================
// �f�X�g���N�^
//==============================
CAlterPole::~CAlterPole()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CAlterPole::Init(void)
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
void CAlterPole::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CAlterPole::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CAlterPole::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAlterPole::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_bEmpty = true;				// �󔒏�
}

//=======================================
// ��������
//=======================================
CAlterPole* CAlterPole::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAlterPole* pPole = nullptr;		// �C���X�^���X�𐶐�

	if (pPole == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �u���b�N�𐶐�����
		pPole = new CAlterPole;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPole != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPole->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPole->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Β��̃|�C���^��Ԃ�
	return pPole;
}

//=======================================
// �󔒏󋵂̐ݒ菈��
//=======================================
void CAlterPole::SetEnableEmpty(const bool bEmpty)
{
	// �󔒏󋵂�ݒ肷��
	m_bEmpty = bEmpty;
}

//=======================================
// �󔒏󋵂̎擾����
//=======================================
bool CAlterPole::IsEmpty(void) const
{
	// �󔒏󋵂�Ԃ�
	return m_bEmpty;
}