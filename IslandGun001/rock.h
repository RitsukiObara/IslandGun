//===================================
//
// ��w�b�_�[[rock.h]
// Author ��������
//
//===================================
#ifndef _ROCK_H_
#define _ROCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��)
//-----------------------------------
class CRock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CRock(CObject::TYPE type = TYPE_ROCK, PRIORITY priority = PRIORITY_BLOCK);				// �I�[�o�[���[�h�R���X�g���N�^
	~CRock();		// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CRock* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CRock* pNext);		// ��̃|�C���^�̐ݒ菈��
	CRock* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CRock* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// ���̐ݒ菈��
	void Break(void);				// �j�󏈗�

	// �ÓI�����o�֐�
	static CRock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);		// ��������

private:		// ���������A�N�Z�X�ł���
	
	// �����o�ϐ�
	int m_nBreakLevel;	// �j�󃌃x��

	// ���X�g�\���֌W
	CRock* m_pPrev;		// �O�ւ̃|�C���^
	CRock* m_pNext;		// ���ւ̃|�C���^
};

#endif