//==================================================================
//
// �{�X�̔��j��ԏ��� [boss_explosionstate.cpp]
// Author�F��������
//
//==================================================================
//******************************************************************
//	�C���N���[�h�t�@�C��
//******************************************************************
#include "useful.h"
#include "boss.h"
#include "boss_explosionstate.h"
#include "manager.h"
#include "motion.h"

#include "game.h"
#include "boss_ripple.h"

//------------------------------------------------------------------
// �萔��`
//------------------------------------------------------------------
namespace
{
	const int FINISH_COUNT = 100;		// �I���J�E���g
}

//==========================
// �R���X�g���N�^
//==========================
CBossExplosionState::CBossExplosionState()
{
	// �S�Ă̒l���N���A����
	m_nCount = 0;		// �J�E���g
}

//==========================
// �f�X�g���N�^
//==========================
CBossExplosionState::~CBossExplosionState()
{

}

//==========================
// ��Ԃ̐ݒ菈��
//==========================
void CBossExplosionState::Process(CBoss* pBoss)
{
	// �J�E���g�����Z����
	m_nCount++;

	if (m_nCount >= FINISH_COUNT)
	{ // ��莞�Ԍo�߂̏ꍇ

		// �{�X�̔��j�g��𐶐�
		CBossRipple::Create(pBoss->GetPos());

		// �I����Ԃɂ���
		CGame::SetState(CGame::STATE_FINISH);
	}
}

//==========================
// ���̐ݒ菈��
//==========================
void CBossExplosionState::SetData(CBoss* pBoss)
{
	// �S�Ă̒l��ݒ肷��
	m_nCount = 0;		// �J�E���g
}