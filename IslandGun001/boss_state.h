//===================================
//
// �{�X�̏�ԃw�b�_�[[boss_state.h]
// Author ��������
//
//===================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_
//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CBoss;		// �{�X

// �N���X��`(�{�X�̏�Ԃ̊�{�N���X)
class CBossState
{
public:

	CBossState();			// �R���X�g���N�^
	virtual ~CBossState();	// �f�X�g���N�^

	void Uninit();			// �I������

	virtual void Process(CBoss* pBoss) = 0;	// ��ԏ���
	virtual void SetData(CBoss* pBoss) = 0;	// ���̐ݒ菈��
};

// �N���X��`(�{�X�̏o����ԃN���X)
class CBossAppearState : public CBossState
{
public:

	CBossAppearState();		// �R���X�g���N�^
	~CBossAppearState();	// �f�X�g���N�^

	void Process(CBoss* pBoss) override;		// ��ԏ���
	void SetData(CBoss* pBoss) override;		// ���̐ݒ菈��

private:

	// �����o�֐�
	void Length(void);			// �����֌W����
	void PosRot(CBoss* pBoss);	// �ʒu�����ݒ菈��
	void Ripple(CBoss* pBoss);	// �g��̐ݒu����

	// �����o�ϐ�
	int m_nCount;			// �o�߃J�E���g
	float m_fLangeRot;		// ��������
	float m_fLength;		// ����
	float m_fHeight;		// ���x
};

// �N���X��`(�{�X�̌��������ԃN���X)
class CBossTurnState : public CBossState
{
public:

	CBossTurnState();	// �R���X�g���N�^
	~CBossTurnState();	// �f�X�g���N�^

	void Process(CBoss* pBoss) override;		// ��ԏ���
	void SetData(CBoss* pBoss) override;		// ���̐ݒ菈��

private:

	// �����o�ϐ�
	int m_nCount;		// �o�߃J�E���g
};

// �N���X��`(�{�X�̉��i����ԃN���X)
class CBossHowlingState : public CBossState
{
public:

	CBossHowlingState();	// �R���X�g���N�^
	~CBossHowlingState();	// �f�X�g���N�^

	void Process(CBoss* pBoss) override;		// ��ԏ���
	void SetData(CBoss* pBoss) override;		// ���̐ݒ菈��

private:

};

#endif