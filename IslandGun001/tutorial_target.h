//===================================
//
// �I�w�b�_�[[tutorial_target.h]
// Author ��������
//
//===================================
#ifndef _TUTORIAL_TARGET_H_
#define _TUTORIAL_TARGET_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// �N���X��`(�^�[�Q�b�g)
//-----------------------------------
class CTarget : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTarget();			// �R���X�g���N�^
	~CTarget();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��
	void Hit(void);					// �q�b�g����

	// �ÓI�����o�֐�
	static CTarget* Create(const D3DXVECTOR3& pos);		// ��������

	static CListManager<CTarget*> GetList(void);		// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���

	// �ÓI�����o�ϐ�
	static CListManager<CTarget*> m_list;		// ���X�g���
};

#endif