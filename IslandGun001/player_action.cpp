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

#include "player.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const float DODGE_SPEED = 80.0f;		// �����Ԃ̑��x
	const int DODGE_COUNT = 3;				// �����Ԃ̃J�E���g��
}

//=========================
// �R���X�g���N�^
//=========================
CPlayerAction::CPlayerAction()
{
	// �S�Ă̒l���N���A����
	m_action = ACTION_NONE;		// �s��
	m_nActionCount = 0;			// �s���J�E���g
	m_fDodgeRot = 0.0f;			// ����������
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
	// �S�Ă̒l������������
	m_action = ACTION_NONE;		// �s��
	m_nActionCount = 0;			// �s���J�E���g
	m_fDodgeRot = 0.0f;			// ����������

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
	switch (m_action)
	{
	case CPlayerAction::ACTION_NONE:	// �ʏ���

		// �ʏ��ԏ���
		NoneProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SHOT:	// �ˌ����

		// �ˌ����
		ShotProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_DAGGER:	// �_�K�[���

		// �_�K�[��ԏ���
		DaggerPrecess(pPlayer);

		break;

	case CPlayerAction::ACTION_DODGE:	// ������

		// �����ԏ���
		DodgeProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SHOTGUN:	// �U�e(J+�e)���

		// �U�e��ԏ���
		ShotgunProcess(pPlayer);

		break;

	case CPlayerAction::ACTION_SWOOP:	// �}�~��(J+�_�K�[)���

		// �}�~����ԏ���
		SwoopProcess(pPlayer);

		break;

	default:

		// ��~
		assert(false);

		break;
	}
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

//=========================
// �s���̐ݒ菈��
//=========================
void CPlayerAction::SetAction(const ACTION action)
{
	// �s����ݒ肷��
	m_action = action;

	// �s���J�E���g�����Z�b�g����
	m_nActionCount = 0;
}

//=========================
// �s���̎擾����
//=========================
CPlayerAction::ACTION CPlayerAction::GetAction(void) const
{
	// �s����Ԃ�
	return m_action;
}

//=========================
// �����������̐ݒ菈��
//=========================
void CPlayerAction::SetDodgeRot(const float fRot)
{
	// ������������ݒ肷��
	m_fDodgeRot = fRot;
}

//=========================
// �ʏ��ԏ���
//=========================
void CPlayerAction::NoneProcess(CPlayer* pPlayer)
{

}

//=========================
// �ˌ���ԏ���
//=========================
void CPlayerAction::ShotProcess(CPlayer* pPlayer)
{
	// �������擾����
	D3DXVECTOR3 rotDest = pPlayer->GetRotDest();
	D3DXVECTOR3 rotCamera = CManager::Get()->GetCamera()->GetRot();

	// �J�����̌����𓯂������𑵂���
	rotDest.y = rotCamera.y;

	// ������K�p����
	pPlayer->SetRotDest(rotDest);

	// �r��^�������L�΂�
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERRIGHTARM - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERLEFTARM - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERRIGHTUPPER - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pPlayer->GetHierarchy(CXFile::TYPE_PLAYERLEFTUPPER - INIT_PLAYER)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================
// �_�K�[��ԏ���
//=========================
void CPlayerAction::DaggerPrecess(CPlayer* pPlayer)
{

}

//=========================
// �����ԏ���
//=========================
void CPlayerAction::DodgeProcess(CPlayer* pPlayer)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = pPlayer->GetPos();

	pos.x += sinf(m_fDodgeRot) * DODGE_SPEED;
	pos.z += cosf(m_fDodgeRot) * DODGE_SPEED;

	// �ʒu��K�p����
	pPlayer->SetPos(pos);

	// �s���J�E���g�����Z����
	m_nActionCount++;

	if (m_nActionCount >= DODGE_COUNT)
	{ // �s���J�E���g����萔�ȏ�ɂȂ����ꍇ

		// �s����ݒ肷��
		SetAction(ACTION_NONE);
	}
}

//=========================
// �U�e(J+�e)���
//=========================
void CPlayerAction::ShotgunProcess(CPlayer* pPlayer)
{

}

//=========================
// �}�~����ԏ���
//=========================
void CPlayerAction::SwoopProcess(CPlayer* pPlayer)
{

}