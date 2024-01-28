//===================================
//
// �C���J���̊k�w�b�_�[[iwakari_shell.h]
// Author ��������
//
//===================================
#ifndef _IWAKARI_SHELL_H_
#define _IWAKARI_SHELL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�C���J���̊k)
//-----------------------------------
class CIwakariShell : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CIwakariShell();				// �R���X�g���N�^
	~CIwakariShell();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CIwakariShell* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif