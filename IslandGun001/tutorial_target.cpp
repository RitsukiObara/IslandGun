//===========================================
//
// �I�̃��C������[tutorial_target.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "tutorial_target.h"
#include "renderer.h"
#include "useful.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Target.x";		// ���f���̖��O
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CTarget*> CTarget::m_list = {};			// ���X�g���

//==============================
// �R���X�g���N�^
//==============================
CTarget::CTarget() : CModel(CObject::TYPE_TARGET, CObject::PRIORITY_ENTITY)
{

}

//==============================
// �f�X�g���N�^
//==============================
CTarget::~CTarget()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CTarget::Init(void)
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
// �j�Ђ̏I������
//========================================
void CTarget::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CTarget::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CTarget::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTarget::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f�����
}

//=======================================
// �q�b�g����
//=======================================
void CTarget::Hit(void)
{

}

//=======================================
// ��������
//=======================================
CTarget* CTarget::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTarget* pTarget = nullptr;	// �C���X�^���X�𐶐�

	if (pTarget == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pTarget = new CTarget;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTarget != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTarget->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTarget->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�̃|�C���^��Ԃ�
	return pTarget;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CTarget*> CTarget::GetList(void)
{
	// ���X�g�\���̏���Ԃ�
	return m_list;
}