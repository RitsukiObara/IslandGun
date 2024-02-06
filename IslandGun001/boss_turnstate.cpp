//================================================================================================================
//
// �{�X�̌��������ԏ��� [boss_turnstate.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_turnstate.h"
#include "motion.h"

#include "game.h"
#include "player.h"
#include "boss_howlingstate.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const float TURN_ROT_CORRECT = 0.08f;		// �����̕␳�{��
	const int TURN_COUNT = 100;					// ���������Ԃ̃J�E���g��
	const float TURN_SUB_HEIGHT = 10.0f;		// ���x�̌��Z��
}
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

			// ���x�����Z����
			pos.y -= TURN_SUB_HEIGHT;

			// �ʒu�̐ݒ菈��
			pBoss->SetPos(pos);

			// �N���n�ʂƂ̓����蔻��
			if (pBoss->ElevationCollision() == true)
			{ // �n�ʂɒ��n�����ꍇ

				// ������␳����
				rot.y = fRotDest;

				// ������K�p����
				pBoss->SetRot(rot);

				// ���i����Ԃɂ���
				pBoss->ChangeState(new CBossHowlingState());
			}

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