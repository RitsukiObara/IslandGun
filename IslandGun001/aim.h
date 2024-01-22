//===================================
//
// �G�C���w�b�_�[[aim.h]
// Author ��������
//
//===================================
#ifndef _AIM_H_
#define _AIM_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(CAim)
//-----------------------------------
class CAim : public CBillboard
{
public:

	CAim();			// �R���X�g���N�^
	~CAim();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��

	void SetAim(const D3DXVECTOR3& pos);			// �G�C���̐ݒu����

	// �ÓI�����o�֐�
	static CAim* Create(const D3DXVECTOR3& pos);	// ��������

private:

	// �����o�ϐ�
};

#endif