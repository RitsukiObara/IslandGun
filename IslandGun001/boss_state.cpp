//================================================================================================================
//
// �{�X�̏�ԏ��� [boss_state.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_state.h"
#include "motion.h"

#include "game.h"
#include "player.h"
#include "ripple.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	// �o���Ԋ֌W
	const float APPEAR_LENGTH = 8000.0f;		// ����
	const float APPEAR_HEIGHT = 2000.0f;		// �������x
	const float APPEAR_SLOPE = -0.9f;			// �X��
	const float APPEAR_ADD_ROT = 0.05f;			// �����̒ǉ���
	const float APPEAR_SUB_LENGTH = 20.0f;		// �����̌��Z��
	const float APPEAR_SUB_HEIGHT = 5.0f;		// ���x�̌��Z��
	const float APPEAR_SUB_SLOPE = 0.00225f;	// �X���̌��Z��
	const int APPEAR_RIPPLE_FREQ = 6;			// �g��̏o��p�x
	const float APPEAR_RIPPLE_HEIGHT = 600.0f;	// �g��̍��x
	const D3DXVECTOR3 RIPPLE_SCALE = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	// �g��̊g�嗦

	// ���������Ԋ֌W
	const float TURN_ROT_CORRECT = 0.08f;		// �����̕␳�{��
	const int TURN_COUNT = 140;					// ���������Ԃ̃J�E���g��
}

//----------------------------------------------------------------------------------------------------------------
// ��{�N���X
//----------------------------------------------------------------------------------------------------------------
//==========================
// �R���X�g���N�^
//==========================
CBossState::CBossState()
{

}

//==========================
// �f�X�g���N�^
//==========================
CBossState::~CBossState()
{

}

//==========================
// �I������
//==========================
void CBossState::Uninit()
{
	// ���g���폜����
	delete this;
}

//----------------------------------------------------------------------------------------------------------------
// ��s���
//----------------------------------------------------------------------------------------------------------------
//==========================
// �R���X�g���N�^
//==========================
CBossAppearState::CBossAppearState()
{
	// �S�Ă̒l���N���A����
	m_fLangeRot = 0.0f;			// ��������
	m_fLength = APPEAR_LENGTH;	// ����
	m_fHeight = APPEAR_HEIGHT;	// ���x
}

//==========================
// �f�X�g���N�^
//==========================
CBossAppearState::~CBossAppearState()
{

}

//==========================
// ��Ԃ̐ݒ菈��
//==========================
void CBossAppearState::Process(CBoss* pBoss)
{
	// �J�E���g�����Z����
	m_nCount++;

	// �����֌W����
	Length();

	if (m_fLength <= 0.0f)
	{ // ������ 0.0f �ȉ��ɂȂ����ꍇ

		// �ʒu��K�p����
		pBoss->SetPos(NONE_D3DXVECTOR3);

		// ���������Ԃɂ���
		pBoss->ChangeState(new CBossTurnState());

		// ���̐�̏������s��Ȃ�
		return;
	}

	// �ʒu�����ݒ菈��
	PosRot(pBoss);

	// �g��̐ݒu����
	Ripple(pBoss);
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossAppearState::SetData(CBoss* pBoss)
{
	// �S�Ă̒l��ݒ肷��
	m_fLangeRot = 0.0f;			// ��������
	m_fLength = APPEAR_LENGTH;	// ����
	m_fHeight = APPEAR_HEIGHT;	// ���x

	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// �ʒu��ݒ肷��
	pos.x = sinf(m_fLangeRot) * m_fLength;
	pos.y = m_fHeight;
	pos.z = cosf(m_fLangeRot) * m_fLength;

	// ������ݒ肷��
	rot.y = m_fLangeRot + (D3DX_PI * 0.5f);
	rot.z = APPEAR_SLOPE;

	// �ʒu�ƌ�����K�p����
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// �����֌W����
//==========================
void CBossAppearState::Length(void)
{
	// ���������Z����
	m_fLangeRot += APPEAR_ADD_ROT;

	// �����̐��K��
	useful::RotNormalize(&m_fLangeRot);

	// ���������Z����
	m_fLength -= APPEAR_SUB_LENGTH;

	// ���x�����Z����
	m_fHeight -= APPEAR_SUB_HEIGHT;
}

//==========================
// �ʒu�����ݒ菈��
//==========================
void CBossAppearState::PosRot(CBoss* pBoss)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// �ʒu��ݒ肷��
	pos.x = sinf(m_fLangeRot) * m_fLength;
	pos.y = m_fHeight;
	pos.z = cosf(m_fLangeRot) * m_fLength;

	// ������ݒ肷��
	rot.y = m_fLangeRot + (D3DX_PI * 0.5f);
	rot.z += APPEAR_SUB_SLOPE;

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	// �ʒu�ƌ�����K�p����
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// �g��̐ݒu����
//==========================
void CBossAppearState::Ripple(CBoss* pBoss)
{
	if (m_nCount % APPEAR_RIPPLE_FREQ == 0)
	{ // ���J�E���g���Ƃ�

		// �ʒu�ƌ������擾����
		D3DXVECTOR3 pos = pBoss->GetPos();
		D3DXVECTOR3 rot = pBoss->GetRot();

		// �g��̐�������
		CRipple::Create
		(
			D3DXVECTOR3(pos.x, pos.y + APPEAR_RIPPLE_HEIGHT, pos.z),
			D3DXVECTOR3(D3DX_PI * 0.5f, rot.y, D3DX_PI),
			RIPPLE_SCALE
		);
	}
}

//----------------------------------------------------------------------------------------------------------------
// ����������
//----------------------------------------------------------------------------------------------------------------
//==========================
// �R���X�g���N�^
//==========================
CBossTurnState::CBossTurnState()
{
	// �S�Ă̒l���N���A����
	m_nCount = 0;		// �o�߃J�E���g
}

//==========================
// �f�X�g���N�^
//==========================
CBossTurnState::~CBossTurnState()
{

}

//==========================
// ��ԏ���
//==========================
void CBossTurnState::Process(CBoss* pBoss)
{
	// �v���C���[�̏����擾����
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �J�E���g�����Z����
		m_nCount++;

		// �������擾����
		D3DXVECTOR3 rot = pBoss->GetRot();
		D3DXVECTOR3 pos = pBoss->GetPos();
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
		float fRotDest = atan2f(posPlayer.x - pos.x, posPlayer.z - pos.z);

		// �����̕␳����
		useful::RotCorrect(fRotDest, &rot.y, TURN_ROT_CORRECT);

		// �����̐��K��
		useful::RotNormalize(&rot.y);

		// ������K�p����
		pBoss->SetRot(rot);

		if (m_nCount >= TURN_COUNT)
		{ // ��萔�o�߂����ꍇ

			// ������␳����
			rot.y = fRotDest;

			// ������K�p����
			pBoss->SetRot(rot);

			// ���i����Ԃɂ���
			pBoss->ChangeState(new CBossHowlingState());

			// ���̐�̏������s��Ȃ�
			return;
		}
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossTurnState::SetData(CBoss* pBoss)
{
	// �S�Ă̒l��ݒ肷��
	m_nCount = 0;		// �o�߃J�E���g

	// �z�o�����O���[�V������ݒ肷��
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_HOVERING);
}

//----------------------------------------------------------------------------------------------------------------
// ���i�����
//----------------------------------------------------------------------------------------------------------------
//==========================
// �R���X�g���N�^
//==========================
CBossHowlingState::CBossHowlingState()
{

}

//==========================
// �f�X�g���N�^
//==========================
CBossHowlingState::~CBossHowlingState()
{

}

//==========================
// ��ԏ���
//==========================
void CBossHowlingState::Process(CBoss* pBoss)
{

}

//==========================
// ���̐ݒ菈��
//==========================
void CBossHowlingState::SetData(CBoss* pBoss)
{

}