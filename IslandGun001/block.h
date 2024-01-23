//===================================
//
// �u���b�N�w�b�_�[[block.h]
// Author ��������
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// �N���X��`(�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CBlock();			// �R���X�g���N�^
	~CBlock();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos);		// ��������

	static CListManager<CBlock*> GetList(void);			// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���
	
	// �ÓI�����o�ϐ�
	static CListManager<CBlock*> m_list;		// ���X�g
};

#endif