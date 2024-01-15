//============================================
//
// �e�}�l�[�W���[�w�b�_�[[bullet_manager.h]
// Author�F��������
//
//============================================
#ifndef _BULLET_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _BULLET_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CBullet;		// �e

//--------------------------------------------
// �N���X(�N���}�l�[�W���[�N���X)
//--------------------------------------------
class CBulletManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CBulletManager();			// �R���X�g���N�^
	~CBulletManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CBullet* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CBullet* GetTop(void);				// �擪�̎擾����
	void Pull(CBullet* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CBulletManager* Create(void);		// ��������
	static CBulletManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CBullet* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CBulletManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif