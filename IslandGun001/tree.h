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

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_PALM = 0,		// ���V�̖�
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CTree(CObject::TYPE type = TYPE_TREE, PRIORITY priority = PRIORITY_BLOCK);				// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CTree();		// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CTree* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CTree* pNext);		// ��̃|�C���^�̐ݒ菈��
	CTree* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CTree* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void) override;	// ����������
	virtual void Uninit(void) override;		// �I������
	virtual void Update(void) override;		// �X�V����
	virtual void Draw(void) override;		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);	// ���̐ݒ菈��
	virtual void Hit(void);					// �q�b�g����

	// �Z�b�g�E�Q�b�g�֌W
	TYPE GetType(void) const;				// ��ނ̎擾����

	// �ÓI�����o�֐�
	static CTree* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���
	
	// ���X�g�\���֌W
	CTree* m_pPrev;		// �O�ւ̃|�C���^
	CTree* m_pNext;		// ���ւ̃|�C���^
};

#endif