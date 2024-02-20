//===================================
//
// �Β��w�b�_�[[alter_pole.h]
// Author ��������
//
//===================================
#ifndef _ALTER_POLE_H_
#define _ALTER_POLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�Β�)
//-----------------------------------
class CAlterPole : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CAlterPole();			// �R���X�g���N�^
	~CAlterPole();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetEnableEmpty(const bool bEmpty);		// �󔒏󋵂̐ݒ菈��
	bool IsEmpty(void) const;					// �󔒏󋵂̎擾����

	// �ÓI�����o�֐�
	static CAlterPole* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	bool m_bEmpty;		// �󔒏�
};

#endif