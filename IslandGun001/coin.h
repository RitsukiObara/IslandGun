//===================================
//
// �����w�b�_�[[coin.h]
// Author ��������
//
//===================================
#ifndef _COIN_H_
#define _COIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CCoin : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CCoin();					// �R���X�g���N�^
	~CCoin();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CCoin* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CCoin* pNext);	// ��̃|�C���^�̐ݒ菈��
	CCoin* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CCoin* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCoin* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// ���X�g�\���֌W
	CCoin* m_pPrev;	// �O�ւ̃|�C���^
	CCoin* m_pNext;	// ���ւ̃|�C���^
};

#endif