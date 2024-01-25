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

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const int MAX_BREAK_LEVEL = 3;				// �j�󃌃x���̍ő�l
	const char* MODEL[CRock::TYPE_MAX] =		// ���f���̖��O
	{
		"data\\MODEL\\Rock001.x",				// �_�炩����
		"data\\MODEL\\Rock002.x"				// �d����
	};
	const char* TEXTURE[MAX_BREAK_LEVEL] =		// �j�󃌃x�����Ƃ̃e�N�X�`��
	{
		"data\\TEXTURE\\Rock001.png",
		"data\\TEXTURE\\Rock002.png",
		"data\\TEXTURE\\Rock003.png",
	};
	const int TEXTURE_IDX = 0;					// �ς���e�N�X�`���̔ԍ�
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CRock*> CRock::m_list = {};		// ���X�g

//==============================
// �R���X�g���N�^
//==============================
CRock::CRock() : CModel(TYPE_ROCK, PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_SOFT;			// ���
	m_nBreakLevel = 0;			// �j�󃌃x��

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//==============================
// �f�X�g���N�^
//==============================
CRock::~CRock()
{

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

	// ������������
	m_list.Pull(this);
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
void CRock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(rot);					// ����
	SetScale(scale);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL[type]));	// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_type = type;				// ���
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
CRock* CRock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
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
		pRock->SetData(pos, rot, scale, type);
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

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CRock*> CRock::GetList(void)
{
	// ���X�g�}�l�[�W���[��Ԃ�
	return m_list;
}