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

//-----------------------------------
// �N���X��`(CEnemy)
//-----------------------------------
class CEnemy : public CCharacter
{
public:					// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_TORDLE = 0,	// �n�������G(�^�[�h��)
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CEnemy();				// �R���X�g���N�^
	virtual ~CEnemy();		// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CEnemy* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CEnemy* pNext);	// ��̃|�C���^�̐ݒ菈��
	CEnemy* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CEnemy* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void) override;	// ����������
	virtual void Uninit(void) override;		// �I������
	virtual void Update(void) override;		// �X�V����
	virtual void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

private:				// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���

	// ���X�g�\���֌W
	CEnemy* m_pPrev;	// �O�ւ̃|�C���^
	CEnemy* m_pNext;	// ���ւ̃|�C���^
};

#endif