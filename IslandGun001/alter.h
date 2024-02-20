//===================================
//
// �Ւd�w�b�_�[[alter.h]
// Author ��������
//
//===================================
#ifndef _ALTER_H_
#define _ALTER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "gold_bone.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CAlterPole;		// �Β�

//-----------------------------------
// �N���X��`(�Ւd)
//-----------------------------------
class CAlter : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_CHARGE,		// �`���[�W���
		STATE_BOSSAPPEAR,	// �{�X�̏o�����
		STATE_WAIT,			// �ҋ@���
		STATE_BREAK,		// �j����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CAlter();			// �R���X�g���N�^
	~CAlter();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	CAlterPole* GetPole(const int nIdx) const;	// �Β��̎擾����

	// �ÓI�����o�֐�
	static CAlter* Create(void);	// ��������

	// �萔��`
	static const int NUM_POLE = 3;	// �Β��̐�

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	STATE m_state;					// ���
	CAlterPole* m_apPole[NUM_POLE];	// �Β��̏��
};

#endif