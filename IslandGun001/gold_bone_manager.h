//============================================
//
// ���̍��}�l�[�W���[�w�b�_�[[gold_bone_manager.h]
// Author�F��������
//
//============================================
#ifndef _GOLD_BONE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _GOLD_BONE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CGoldBone;		// ���̍�

//--------------------------------------------
// �N���X(���̍��}�l�[�W���[�N���X)
//--------------------------------------------
class CGoldBoneManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CGoldBoneManager();			// �R���X�g���N�^
	~CGoldBoneManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CGoldBone* pThis);		// �o�^����
	void Uninit(void);						// �I������

	CGoldBone* GetTop(void);				// �擪�̎擾����
	void Pull(CGoldBone* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CGoldBoneManager* Create(void);		// ��������
	static CGoldBoneManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CGoldBone* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CGoldBoneManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif