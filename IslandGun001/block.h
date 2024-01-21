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

//-----------------------------------
// �N���X��`(�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CBlock();			// �R���X�g���N�^
	~CBlock();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CBlock* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBlock* pNext);		// ��̃|�C���^�̐ݒ菈��
	CBlock* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CBlock* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���
	
	// ���X�g�\���֌W
	CBlock* m_pPrev;		// �O�ւ̃|�C���^
	CBlock* m_pNext;		// ���ւ̃|�C���^
};

#endif