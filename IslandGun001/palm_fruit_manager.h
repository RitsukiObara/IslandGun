//============================================
//
// ���V�̎��}�l�[�W���[�w�b�_�[[palm_fruit_manager.h]
// Author�F��������
//
//============================================
#ifndef _PALM_FRUIT_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _PALM_FRUIT_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CPalmFruit;		// ���V�̎�

//--------------------------------------------
// �N���X(���V�̎��}�l�[�W���[�N���X)
//--------------------------------------------
class CPalmFruitManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CPalmFruitManager();			// �R���X�g���N�^
	~CPalmFruitManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CPalmFruit* pThis);		// �o�^����
	void Uninit(void);						// �I������

	CPalmFruit* GetTop(void);				// �擪�̎擾����
	void Pull(CPalmFruit* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CPalmFruitManager* Create(void);		// ��������
	static CPalmFruitManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CPalmFruit* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CPalmFruitManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif