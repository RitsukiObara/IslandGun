//===================================
//
// ���e�w�b�_�[[bomb.h]
// Author ��������
//
//===================================
#ifndef _BOMB_H_
#define _BOMB_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CBombFuse;		// ���ΐ�

//-----------------------------------
// �N���X��`(���e)
//-----------------------------------
class CBomb : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CBomb();			// �R���X�g���N�^
	~CBomb();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBomb* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

	static CListManager<CBomb*> GetList(void);			// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CBombFuse* m_pFuse;			// ���ΐ��̏��

	// �ÓI�����o�ϐ�
	static CListManager<CBomb*> m_list;		// ���X�g
};

#endif