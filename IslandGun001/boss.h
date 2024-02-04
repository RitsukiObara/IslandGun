//===================================
//
// �{�X�w�b�_�[[boss.h]
// Author ��������
//
//===================================
#ifndef _BOSS_H_
#define _BOSS_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "character.h"
#include "list_manager.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CMotion;		// ���[�V����
class CBossState;	// �{�X�̏��

//-----------------------------------
// �N���X��`(CBoss)
//-----------------------------------
class CBoss : public CCharacter
{
public:					// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���[�V�����̎��)
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ʏ탂�[�V����
		MOTIONTYPE_FLY,				// ��s���[�V����
		MOTIONTYPE_HOVERING,		// �z�o�����O���[�V����
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	CBoss();		// �R���X�g���N�^
	~CBoss();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ���̐ݒ菈��

	void ChangeState(CBossState* pNext);	// ��Ԃ̑J�ڏ���

	// �Z�b�g�E�Q�b�g�֌W
	CMotion* GetMotion(void);		// ���[�V�����̎擾����

	// �ÓI�����o�֐�
	static CBoss* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

	static CListManager<CBoss*> GetList(void);			// ���X�g�̎擾����

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void ElevationCollision(void);			// �N���n�ʂƂ̓����蔻��

	// �����o�ϐ�
	CMotion* m_pMotion;		// ���[�V�����̏��
	CBossState* m_pState;	// ��Ԃ̏��

	D3DXVECTOR3 m_move;		// �ړ���

	// �ÓI�����o�ϐ�
	static CListManager<CBoss*> m_list;		// ���X�g
};

#endif