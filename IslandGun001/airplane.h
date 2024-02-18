//===================================
//
// ��s�@�w�b�_�[[airplane.h]
// Author ��������
//
//===================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CPropeller;			// �v���y��

//-----------------------------------
// �N���X��`(��s�@)
//-----------------------------------
class CAirplane : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CAirplane();			// �R���X�g���N�^
	~CAirplane();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(D3DXVECTOR3 pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CAirplane* Create(D3DXVECTOR3 pos);	// ��������

	static CListManager<CAirplane*> GetList(void);			// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CPropeller* m_pPropeller;		// �v���y���̏��

	// �ÓI�����o�ϐ�
	static CListManager<CAirplane*> m_list;		// ���X�g
};

#endif