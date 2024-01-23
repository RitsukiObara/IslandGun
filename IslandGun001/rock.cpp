//===========================================
//
// ��̃��C������[rock.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "rock.h"
#include "texture.h"
#include "useful.h"

#include "rock_manager.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const int MAX_BREAK_LEVEL = 3;				// �j�󃌃x���̍ő�l
	const char* MODEL = "data\\MODEL\\Rock.x";	// ���f���̖��O
	const char* TEXTURE[MAX_BREAK_LEVEL] =		// �j�󃌃x�����Ƃ̃e�N�X�`��
	{
		"data\\TEXTURE\\Rock001.png",
		"data\\TEXTURE\\Rock002.png",
		"data\\TEXTURE\\Rock003.png",
	};
	const int TEXTURE_IDX = 0;					// �ς���e�N�X�`���̔ԍ�
}

//==============================
// �R���X�g���N�^
//==============================
CRock::CRock() : CModel(TYPE_ROCK, PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_nBreakLevel = 0;			// �j�󃌃x��

	m_pPrev = nullptr;			// �O�̃|�C���^
	m_pNext = nullptr;			// ���̃|�C���^

	if (CRockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CRockManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CRock::~CRock()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CRock::SetPrev(CRock* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CRock::SetNext(CRock* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CRock* CRock::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CRock* CRock::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CRock::Init(void)
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
void CRock::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CRockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CRockManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CRock::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CRock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(rot);					// ����
	SetScale(scale);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_nBreakLevel = 0;			// �j�󃌃x��

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[m_nBreakLevel]), TEXTURE_IDX);
}

//=====================================
// �j�󏈗�
//=====================================
void CRock::Break(void)
{
	// �j�󃌃x�������Z����
	m_nBreakLevel++;

	if (m_nBreakLevel >= MAX_BREAK_LEVEL)
	{ // �j�󃌃x�����ő吔�ȏ�̏ꍇ

		// �j�Ђ΂�T��
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[m_nBreakLevel]), TEXTURE_IDX);
	}
}

//=======================================
// ��������
//=======================================
CRock* CRock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRock* pRock = nullptr;		// �C���X�^���X�𐶐�

	if (pRock == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��𐶐�����
		pRock = new CRock;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRock != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRock->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRock->SetData(pos, rot, scale);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��̃|�C���^��Ԃ�
	return pRock;
}