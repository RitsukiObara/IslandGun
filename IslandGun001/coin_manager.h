//============================================
//
// �����}�l�[�W���[�w�b�_�[[coin_manager.h]
// Author�F��������
//
//============================================
#ifndef _COIN_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _COIN_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CCoin;		// �N��

//--------------------------------------------
// �N���X(�N���}�l�[�W���[�N���X)
//--------------------------------------------
class CCoinManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CCoinManager();			// �R���X�g���N�^
	~CCoinManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CCoin* pThis);		// �o�^����
	void Uninit(void);						// �I������

	CCoin* GetTop(void);				// �擪�̎擾����
	void Pull(CCoin* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CCoinManager* Create(void);		// ��������
	static CCoinManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CCoin* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CCoinManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif