//===========================================
//
// ���e�̃��C������[bomb.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "bomb.h"
#include "texture.h"
#include "useful.h"

#include "bomb_fuse.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\BombBody.x";		// ���f���̖��O
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CBomb*> CBomb::m_list = {};			// ���X�g

//==============================
// �R���X�g���N�^
//==============================
CBomb::CBomb() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pFuse = nullptr;			// ���ΐ��̏��

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//==============================
// �f�X�g���N�^
//==============================
CBomb::~CBomb()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CBomb::Init(void)
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
void CBomb::Uninit(void)
{
	if (m_pFuse != nullptr)
	{ // ���ΐ��� NULL ����Ȃ��ꍇ

		// �I������
		m_pFuse->Uninit();
		m_pFuse = nullptr;
	}

	// �I������
	CModel::Uninit();

	// ������������
	m_list.Pull(this);
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CBomb::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CBomb::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pFuse != nullptr)
	{ // ���ΐ��� NULL ����Ȃ��ꍇ

		// ���ΐ��̕`�揈��
		m_pFuse->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBomb::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(rot);					// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_pFuse = CBombFuse::Create(GetMatrixPoint());		// ���ΐ��̏��
}

//=======================================
// ��������
//=======================================
CBomb* CBomb::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBomb* pBomb = nullptr;			// ���e�𐶐�

	if (pBomb == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �u���b�N�𐶐�����
		pBomb = new CBomb;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBomb != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBomb->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBomb->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���e�̃|�C���^��Ԃ�
	return pBomb;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CBomb*> CBomb::GetList(void)
{
	// ���X�g�}�l�[�W���[��Ԃ�
	return m_list;
}