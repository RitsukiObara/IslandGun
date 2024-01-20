//===================================
//
// ���̍��w�b�_�[[gold_bone.h]
// Author ��������
//
//===================================
#ifndef _GOLD_BONE_H_
#define _GOLD_BONE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(���̍�)
//-----------------------------------
class CGoldBone : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CGoldBone();					// �R���X�g���N�^
	~CGoldBone();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CGoldBone* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CGoldBone* pNext);	// ��̃|�C���^�̐ݒ菈��
	CGoldBone* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CGoldBone* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move);				// ���̐ݒ菈��
	void Hit(void);					// �q�b�g����

	// �ÓI�����o�֐�
	static CGoldBone* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Get(void);			// �擾��ԏ���

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	
	// ���X�g�\���֌W
	CGoldBone* m_pPrev;		// �O�ւ̃|�C���^
	CGoldBone* m_pNext;		// ���ւ̃|�C���^
};

#endif