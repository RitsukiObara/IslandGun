//================================================================================================================
//
// �{�X�̒ʏ��ԏ��� [boss_nonestate.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_nonestate.h"
#include "motion.h"

#include "game.h"
#include "player.h"

#include "boss_flystate.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const int STATECHANGE_COUNT = 90;		// ��Ԃ��ω�����J�E���g��
	const float GRAVITY = 0.1f;				// �d��
}

//==========================
// �R���X�g���N�^
//==========================
CBossNoneState::CBossNoneState()
{
	// �S�Ă̒l���N���A����
	m_fGravity = 0.0f;		// �d��
	m_nCount = 0;			// �o�߃J�E���g
}

//==========================
// �f�X�g���N�^
//==========================
CBossNoneState::~CBossNoneState()
{

}

//==========================
// ��ԏ���
//==========================
void CBossNoneState::Process(CBoss* pBoss)
{
	{ // �d�͏���

		// �ʒu���擾����
		D3DXVECTOR3 pos = pBoss->GetPos();

		// �d�͏���
		useful::Gravity(&m_fGravity, &pos.y, GRAVITY);

		// �ʒu��K�p����
		pBoss->SetPos(pos);
	}

	// �o�߃J�E���g�����Z����
	m_nCount++;

	// �N���n�ʂ̓����蔻��
	pBoss->ElevationCollision();

	if (m_nCount >= STATECHANGE_COUNT)
	{ // ��莞�Ԍo�߂����ꍇ

		// ��s��Ԃɂ���
		pBoss->ChangeState(new CBossFlyState);

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossNoneState::SetData(CBoss* pBoss)
{
	// �S�Ă̒l��ݒ肷��
	m_fGravity = 0.0f;		// �d��
	m_nCount = 0;			// �o�߃J�E���g

	// �ҋ@���[�V������ݒ肷��
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_NEUTRAL);
}