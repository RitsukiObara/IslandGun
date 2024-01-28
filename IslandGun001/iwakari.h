//===================================
//
// �C���J���w�b�_�[[iwakari.h]
// Author ��������
//
//===================================
#ifndef _IWAKARI_H_
#define _IWAKARI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "enemy.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CIwakariShell;		// �C���J���̊k

//-----------------------------------
// �N���X��`(CIwakari)
//-----------------------------------
class CIwakari : public CEnemy
{
public:					// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,	// �ʏ���
		STATE_MOVE,		// �ړ����
		STATE_MAX		// ���̗񋓌^�̑���
	};

	CIwakari();			// �R���X�g���N�^
	~CIwakari();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type) override;		// ���̐ݒ菈��
	void Hit(const D3DXVECTOR3& pos) override;		// �q�b�g����

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Chase(void);			// �ǐՏ���
	void Move(void);			// �ړ�����
	void RotMove(void);			// �����̈ړ�����

	// �����o�ϐ�
	CIwakariShell* m_pShell;	// �k�̏��
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_rotDest;		// �ڕW�̌���
	STATE m_state;				// ���
};

#endif