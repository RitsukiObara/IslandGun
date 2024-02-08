//================================================================================================================
//
// �{�X�̗Y�����я�ԏ��� [boss_howlingstate.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_howlingstate.h"
#include "motion.h"

#include "manager.h"
#include "camera.h"

#include "boss_nonestate.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const int HOWLING_COUNT = 50;				// �Y�����т܂ł̃J�E���g
	const int HOWLING_CAMERA_COUNT = 63;		// �Y�����уJ�����܂ł̃J�E���g
	const int NONESTATE_COUNT = 240;			// �ʏ��Ԃ܂ł̃J�E���g
}

//==========================
// �R���X�g���N�^
//==========================
CBossHowlingState::CBossHowlingState()
{
	// �S�Ă̒l���N���A����
	m_nCount = 0;		// �o�߃J�E���g
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
	// �o�߃J�E���g�����Z����
	m_nCount++;

	if (m_nCount >= HOWLING_COUNT)
	{ // ��莞�Ԍo�߂����ꍇ

		if (pBoss->GetMotion()->GetType() != CBoss::MOTIONTYPE_HOWLING)
		{ // �Y�����у��[�V��������Ȃ��ꍇ

			// �Y�����у��[�V������ݒ肷��
			pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_HOWLING);
		}
	}

	if (m_nCount >= HOWLING_CAMERA_COUNT)
	{ // ��莞�Ԍo�߂����ꍇ

		if (CManager::Get()->GetCamera()->GetType() != CCamera::TYPE_BOSSHOWLING)
		{ // �Y�����я�ԈȊO�̏ꍇ

			// �Y�����уJ�����ɂ���
			CManager::Get()->GetCamera()->SetType(CCamera::TYPE_BOSSHOWLING);
		}
	}

	if (m_nCount >= NONESTATE_COUNT)
	{ // ��莞�Ԍo�߂����ꍇ

		// �ʏ��Ԃɂ���
		pBoss->ChangeState(new CBossNoneState);

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossHowlingState::SetData(CBoss* pBoss)
{
	// �S�Ă̒l��ݒ肷��
	m_nCount = 0;		// �o�߃J�E���g

	// �z�o�����O���[�V������ݒ肷��
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_LANDING);

	// �U���J�����ɂ���
	CManager::Get()->GetCamera()->SetType(CCamera::TYPE_VIBRATE);
}