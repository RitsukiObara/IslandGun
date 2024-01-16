//===================================
//
// �����w�b�_�[[coin.h]
// Author ��������
//
//===================================
#ifndef _COIN_H_
#define _COIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CCoin : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ��� 
		STATE_GET,			// �擾���
		STATE_DEATH,		// ���S���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CCoin();					// �R���X�g���N�^
	~CCoin();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CCoin* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CCoin* pNext);	// ��̃|�C���^�̐ݒ菈��
	CCoin* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CCoin* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��
	void Hit(void);					// �q�b�g����

	// �ÓI�����o�֐�
	static CCoin* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Get(void);			// �擾��ԏ���
	void Cycle(void);		// ��]����

	// �����o�ϐ�
	STATE m_state;			// ���
	int m_nDeathCount;		// ���S�J�E���g
	float m_fCycleSpeed;	// ��]���x
	float m_fHeightDest;	// �ڕW�̍���

	// ���X�g�\���֌W
	CCoin* m_pPrev;	// �O�ւ̃|�C���^
	CCoin* m_pNext;	// ���ւ̃|�C���^
};

#endif