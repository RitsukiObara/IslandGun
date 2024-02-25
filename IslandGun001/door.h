//===================================
//
// �h�A�w�b�_�[[door.h]
// Author ��������
//
//===================================
#ifndef _DOOR_H_
#define _DOOR_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�h�A)
//-----------------------------------
class CDoor : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CDoor();		// �R���X�g���N�^
	~CDoor();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CDoor* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CModel* m_pDoor;	// �h�A�{�̂̏��
};

#endif