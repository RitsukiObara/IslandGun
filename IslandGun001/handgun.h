//===================================
//
// ���e�w�b�_�[[handgun.h]
// Author ��������
//
//===================================
#ifndef _HANDGUN_H_
#define _HANDGUN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(���e)
//-----------------------------------
class CHandgun : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CHandgun();			// �R���X�g���N�^
	~CHandgun();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, D3DXMATRIX* mtx);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CHandgun* Create(const D3DXVECTOR3& pos, D3DXMATRIX* mtx);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXMATRIX* m_pMtxParent;		// �e�̃}�g���b�N�X
};

#endif