//===========================================
//
// �v���C���[�̍s���̃��C������[player_action.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "player_action.h"
#include "renderer.h"

//=========================
// �R���X�g���N�^
//=========================
CPlayerAction::CPlayerAction()
{

}

//=========================
// �f�X�g���N�^
//=========================
CPlayerAction::~CPlayerAction()
{

}

//=========================
// ���C�g�̏���������
//=========================
HRESULT CPlayerAction::Init(void)
{


	// ������Ԃ�
	return S_OK;
}

//=========================
// ���C�g�̏I������
//=========================
void CPlayerAction::Uninit(void)
{
	// ���g����������
	delete this;
}

//=========================
// ���C�g�̍X�V����
//=========================
void CPlayerAction::Update(CPlayer* pPlayer)
{

}

//=========================
// ��������
//=========================
CPlayerAction* CPlayerAction::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPlayerAction* pAction = nullptr;		// �s���̃C���X�^���X�𐶐�

	if (pAction == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pAction = new CPlayerAction;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAction != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAction->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �s���̃|�C���^��Ԃ�
	return pAction;
}