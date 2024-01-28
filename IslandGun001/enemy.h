//===================================
//
// �G�w�b�_�[[enemy.h]
// Author ��������
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "character.h"
#include "list_manager.h"

// �O���錾
class CMotion;		// ���[�V����

//-----------------------------------
// �N���X��`(CEnemy)
//-----------------------------------
class CEnemy : public CCharacter
{
public:					// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���[�V�����̎��)
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ʏ탂�[�V����
		MOTIONTYPE_MOVE,			// �ړ����[�V����
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_TORDLE = 0,	// �n�������G(�^�[�h��)
		TYPE_IWAKARI,		// �h��͂������G(�C���J��)
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CEnemy();				// �R���X�g���N�^
	virtual ~CEnemy();		// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0;			// ����������
	virtual void Uninit(void) override;		// �I������
	virtual void Update(void) override;		// �X�V����
	virtual void Draw(void) override;		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ���̐ݒ菈��
	virtual void Hit(const D3DXVECTOR3& pos);		// �q�b�g����

	// �Z�b�g�E�Q�b�g�֌W
	CMotion* GetMotion(void) const;			// ���[�V�����̎擾����
	void CreateMotion(void);				// ���[�V�����̐�������

	void SetCollSize(const D3DXVECTOR3& size);		// �����蔻��̃T�C�Y�̐ݒ菈��
	D3DXVECTOR3 GetCollSize(void) const;			// �����蔻��̃T�C�Y�̎擾����

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

	static CListManager<CEnemy*> GetList(void);			// ���X�g�̎擾����

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void TreeCollision(void);	// �؂Ƃ̓����蔻��
	void RockCollision(void);	// ��Ƃ̓����蔻��
	void BlockCollision(void);	// �u���b�N�Ƃ̓����蔻��

	// �����o�ϐ�
	CMotion* m_pMotion;		// ���[�V�����̏��

	TYPE m_type;			// ���
	D3DXVECTOR3 m_collSize;	// �����蔻��̃T�C�Y

	// �ÓI�����o�ϐ�
	static CListManager<CEnemy*> m_list;		// ���X�g
};

#endif