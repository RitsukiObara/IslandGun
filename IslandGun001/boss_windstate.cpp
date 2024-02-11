//================================================================================================================
//
// �{�X�̂��܂�������ԏ��� [boss_windstate.cpp]
// Author�F��������
//
//================================================================================================================
//****************************************************************************************************************
//	�C���N���[�h�t�@�C��
//****************************************************************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_windstate.h"
#include "motion.h"

#include "game.h"
#include "player.h"

//----------------------------------------------------------------------------------------------------------------
// �������O���
//----------------------------------------------------------------------------------------------------------------
namespace
{
	const float CHASE_CORRECT = 0.2f;			// �ǐՂ̕␳��
	const float MOVE_ROT = D3DX_PI * 0.5f;		// �ړ���Ԃ̌���
	const float MOVE_DEST_Y = 200.0f;			// �ړI�̈ړ���
	const float MOVE_POS_CORRECT = 0.05f;		// �ړ��󋵂̈ʒu�̕␳��
	const float MOVE_ROT_CORRECT = 0.1f;		// �ړ��󋵂̌����̕␳��
	const float MOVE_CHANGE_POS_Y = 10000.0f;	// �ʒu�ɒ�����ԂɂȂ鍂��
	const D3DXVECTOR3 POSITION_POS = D3DXVECTOR3(0.0f, 500.0f, 8000.0f);		// ��ʒu
	const int POSITION_COUNT = 40;				// ��ʒu�Ɉړ�����܂ł̃J�E���g
}

//==========================
// �R���X�g���N�^
//==========================
CBossWindState::CBossWindState()
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_action = ACTION_MOVE;			// �s����
	m_nCount = 0;					// �o�߃J�E���g
}

//==========================
// �f�X�g���N�^
//==========================
CBossWindState::~CBossWindState()
{

}

//==========================
// ��ԏ���
//==========================
void CBossWindState::Process(CBoss* pBoss)
{
	switch (m_action)
	{
	case CBossWindState::ACTION_MOVE:

		// �ړ�����
		Move(pBoss);

		break;

	case CBossWindState::ACTION_POSITION:

		// ��ʒu��������
		Position(pBoss);

		break;

	case CBossWindState::ACTION_WIND:

		// �ǐՏ���
		Chase(pBoss);

		// ���܂���������
		Wind(pBoss);

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossWindState::SetData(CBoss* pBoss)
{
	// ��s���[�V�����ɂ���
	pBoss->GetMotion()->Set(CBoss::MOTIONTYPE_FLY);

	// �ړI�̌�����ݒ肷��
	m_rotDest.x = MOVE_ROT;
}

//==========================
// �ǐՏ���
//==========================
void CBossWindState::Chase(CBoss* pBoss)
{
	// �v���C���[�̏����擾����
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �ʒu�ƌ�����錾
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
		D3DXVECTOR3 posBoss = pBoss->GetPos();
		D3DXVECTOR3 rotBoss = pBoss->GetRot();
		float fRotDest = atan2f(posPlayer.x - posBoss.x, posPlayer.z - posBoss.z);

		// �����̕␳����
		useful::RotCorrect(fRotDest, &rotBoss.y, CHASE_CORRECT);

		// ������K�p����
		pBoss->SetRot(rotBoss);
	}
}

//==========================
// �ړ�����
//==========================
void CBossWindState::Move(CBoss* pBoss)
{
	// �ʒu�ƌ������擾
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// �ړ��ʂ��ǂ�ǂ񑁂����Ă���
	useful::Correct(MOVE_DEST_Y, &m_move.y, MOVE_POS_CORRECT);

	// �ړ�����
	pos.y += m_move.y;

	if (pos.y >= MOVE_CHANGE_POS_Y)
	{ // ���̍����܂ŏオ�����ꍇ

		// �x�N�g�����Z�o����
		D3DXVECTOR3 vec = POSITION_POS - pos;

		// �ʒu��␳����
		pos.y = MOVE_CHANGE_POS_Y;

		// �ʒu�ɒ�����Ԃɂ���
		m_action = ACTION_POSITION;

		// �ړ��ʂ�ݒ肷��
		m_move.x = vec.x / POSITION_COUNT;
		m_move.y = vec.y / POSITION_COUNT;
		m_move.z = vec.z / POSITION_COUNT;

		// �x�N�g���̐��K��(�����̐ݒ�̈�)
		D3DXVec3Normalize(&vec, &vec);

		// �ړI�̌�����ݒ肷��
		m_rotDest.x = vec.y * D3DX_PI;
		m_rotDest.y = atan2f(vec.x, vec.z);
		m_rotDest.z = 0.0f;
	}

	// �����̕␳����
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);

	// �ʒu�ƌ�����K�p����
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// ��ʒu��������
//==========================
void CBossWindState::Position(CBoss* pBoss)
{
	// �o�߃J�E���g�����Z����
	m_nCount++;

	// �ʒu�ƌ������擾
	D3DXVECTOR3 pos = pBoss->GetPos();
	D3DXVECTOR3 rot = pBoss->GetRot();

	// �ړ�����
	pos += m_move;

	// �����̕␳����
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.y, &rot.y, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.z, &rot.z, MOVE_ROT_CORRECT);

	if (m_nCount >= POSITION_COUNT)
	{ // �o�߃J�E���g����萔�ɂȂ����ꍇ

		// �o�߃J�E���g�����Z�b�g����
		m_nCount = 0;

		// ���܂������s���ɂ���
		m_action = ACTION_WIND;

		// �ʒu���ʒu�ɂ���
		pos = POSITION_POS;

		// �ړI�̌�����ݒ肷��
		m_rotDest = NONE_D3DXVECTOR3;
	}

	// �ʒu�ƌ�����K�p����
	pBoss->SetPos(pos);
	pBoss->SetRot(rot);
}

//==========================
// ������
//==========================
void CBossWindState::Wind(CBoss* pBoss)
{
	// �o�߃J�E���g�����Z����
	m_nCount++;

	// �������擾
	D3DXVECTOR3 rot = pBoss->GetRot();

	// �����̕␳����
	useful::RotCorrect(m_rotDest.x, &rot.x, MOVE_ROT_CORRECT);
	useful::RotCorrect(m_rotDest.z, &rot.z, MOVE_ROT_CORRECT);

	// ������K�p����
	pBoss->SetRot(rot);
}