//===================================
//
// �{�X�̂��܂�������ԃw�b�_�[[boss_windstate.h]
// Author ��������
//
//===================================
#ifndef _BOSS_WIND_STATE_H_
#define _BOSS_WIND_STATE_H_
//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "boss_state.h"

// �N���X��`(�{�X�̂��܂�������ԃN���X)
class CBossWindState : public CBossState
{
public:

	// �s����
	enum ACTION
	{
		ACTION_MOVE = 0,	// �ړ��s��
		ACTION_POSITION,	// �ʒu�ɂ��s��
		ACTION_WIND,		// ���܂������s��
		ACTION_MAX			// ���̗񋓌^�̑���
	};

	CBossWindState();		// �R���X�g���N�^
	~CBossWindState();		// �f�X�g���N�^

	void Process(CBoss* pBoss) override;		// ��ԏ���
	void SetData(CBoss* pBoss) override;		// ���̐ݒ菈��

private:

	// �����o�֐�
	void Chase(CBoss* pBoss);		// �ǐՏ���
	void Move(CBoss* pBoss);		// �ړ�����
	void Position(CBoss* pBoss);	// ��ʒu��������
	void Wind(CBoss* pBoss);		// ������

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;	// �ړI�̌���
	ACTION m_action;		// �s����
	int m_nCount;			// �o�߃J�E���g
};

#endif