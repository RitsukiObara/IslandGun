//============================================
//
// �Ւd�̌��w�b�_�[[alter_light.h]
// Author�F��������
//
//============================================
#ifndef _ALTER_LIGHT_H_			//���̃}�N����`������Ă��Ȃ�������
#define _ALTER_LIGHT_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// �N���X(�Ւd�̌��N���X)
//--------------------------------------------
class CAlterLight : public CBillboard
{
public:			// �N�ł��A�N�Z�X�ł���

	CAlterLight();		// �R���X�g���N�^
	~CAlterLight();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CAlterLight* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	float m_fAddSize;		// �T�C�Y�̒ǉ���
};

#endif