//===================================
//
// �؃w�b�_�[[tree.h]
// Author ��������
//
//===================================
#ifndef _TREE_H_
#define _TREE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��)
//-----------------------------------
class CTree : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTree();					// �R���X�g���N�^
	~CTree();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CTree* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CTree* pNext);	// ��̃|�C���^�̐ݒ菈��
	CTree* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CTree* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTree* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	
	// ���X�g�\���֌W
	CTree* m_pPrev;		// �O�ւ̃|�C���^
	CTree* m_pNext;		// ���ւ̃|�C���^
};

#endif