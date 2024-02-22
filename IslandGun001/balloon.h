//===================================
//
// ���D�w�b�_�[[balloon.h]
// Author ��������
//
//===================================
#ifndef _BALLOON_H_
#define _BALLOON_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"
#include "list_manager.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;			// ���f��
class CBalloonRope;		// ���D�̕R

//-----------------------------------
// �N���X��`(���D)
//-----------------------------------
class CBalloon : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CBalloon();			// �R���X�g���N�^
	~CBalloon();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��
	void Hit(void);					// �q�b�g����

	// �ÓI�����o�֐�
	static CBalloon* Create(const D3DXVECTOR3& pos);		// ��������

	static CListManager<CBalloon*> GetList(void);		// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CModel* m_pBalloon;		// ���D�̃��f��
	CBalloonRope* m_pRope;	// �R�̏��

	D3DXVECTOR3 m_pos;		// �ʒu

	// �ÓI�����o�ϐ�
	static CListManager<CBalloon*> m_list;		// ���X�g���
};

#endif