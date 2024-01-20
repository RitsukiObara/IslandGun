//============================================
//
// �؃}�l�[�W���[�w�b�_�[[tree_manager.h]
// Author�F��������
//
//============================================
#ifndef _TREE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _TREE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CTree;		// ��

//--------------------------------------------
// �N���X(�؃}�l�[�W���[�N���X)
//--------------------------------------------
class CTreeManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CTreeManager();			// �R���X�g���N�^
	~CTreeManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CTree* pThis);		// �o�^����
	void Uninit(void);						// �I������

	CTree* GetTop(void);				// �擪�̎擾����
	void Pull(CTree* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CTreeManager* Create(void);		// ��������
	static CTreeManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CTree* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CTreeManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif