//============================================
//
// ��}�l�[�W���[�w�b�_�[[rock_manager.h]
// Author�F��������
//
//============================================
#ifndef _ROCK_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _ROCK_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CRock;		// ��

//--------------------------------------------
// �N���X(�؃}�l�[�W���[�N���X)
//--------------------------------------------
class CRockManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CRockManager();			// �R���X�g���N�^
	~CRockManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CRock* pThis);		// �o�^����
	void Uninit(void);						// �I������

	CRock* GetTop(void);				// �擪�̎擾����
	void Pull(CRock* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CRockManager* Create(void);		// ��������
	static CRockManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CRock* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CRockManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif