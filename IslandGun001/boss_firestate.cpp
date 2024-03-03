//================================================================================================================
//
// �{�X�̉��U����ԏ��� [boss_firestate.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_firestate.h"
#include "motion.h"

#include "game.h"
#include "player.h"
#include "fire_warning.h"

#include "boss_nonestate.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const float CHASE_CORRECT = 0.01f;		// �ǐՂ̕␳��
	const int FIRE_CREATE_COUNT = 30;		// �����o���J�E���g��
	const int FIRE_CREATE_RANGE = 180;		// �����o���Ă���Ԃ̃J�E���g��
	const int FINISH_COUNT = 240;			// �I���J�E���g
}

//==========================
// �R���X�g���N�^
//==========================
CBossFireState::CBossFireState()
{
	// �S�Ă̒l���N���A����
	m_nCount = 0;					// �o�߃J�E���g
}

//==========================
// �f�X�g���N�^
//==========================
CBossFireState::~CBossFireState()
{

}

//==========================
// ��ԏ���
//==========================
void CBossFireState::Process(CBoss* pBoss)
{
	// �J�E���g�����Z����
	m_nCount++;

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nCount % FIRE_CREATE_COUNT == 0 &&
		m_nCount <= FIRE_CREATE_RANGE &&
		pPlayer != nullptr)
	{ // �o�߃J�E���g����萔�o�߂����ꍇ

		// �����ӂ̐���
		CFireWarning::Create(pPlayer->GetPos());
	}

	if (m_nCount == FIRE_CREATE_RANGE)
	{ // �J�E���g����萔�̏ꍇ

		if (pBoss->GetMotion()->GetType() != CBoss::MOTIONTYPE_NEUTRAL)
		{ // �ʏ탂�[�V�����ȊO�̏ꍇ

			// �ʏ탂�[�V�����ɂ���
			pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_NEUTRAL);
		}
	}

	if (m_nCount >= FINISH_COUNT)
	{ // �I���J�E���g�o�߂����ꍇ

		// ��Ԑ؂�ւ�����
		pBoss->ChangeState(new CBossNoneState);
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossFireState::SetData(CBoss* pBoss)
{
	if (pBoss->GetMotion()->GetType() != CBoss::MOTIONTYPE_STOMP)
	{ // �����݃��[�V�����ȊO�̏ꍇ

		// �����݃��[�V�����ɂ���
		pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_STOMP);
	}
}