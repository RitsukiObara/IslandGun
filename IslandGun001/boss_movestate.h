//===================================
//
// �{�X�̈ړ���ԃw�b�_�[[boss_movestate.h]
// Author ��������
//
//===================================
#ifndef _BOSS_MOVE_STATE_H_
#define _BOSS_MOVE_STATE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "boss_state.h"

// �N���X��`(�{�X�̈ړ���ԃN���X)
class CBossMoveState : public CBossState
{
public:

	CBossMoveState();	// �R���X�g���N�^
	~CBossMoveState();	// �f�X�g���N�^

	void Process(CBoss* pBoss) override;		// ��ԏ���
	void SetData(CBoss* pBoss) override;		// ���̐ݒ菈��

private:

	// �����o�֐�
};

#endif