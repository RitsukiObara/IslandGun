//============================================
//
// �`���[�g���A����ʃw�b�_�[[tutorial.h]
// Author�F��������
//
//============================================
#ifndef _TUTORIAL_H_			//���̃}�N����`������Ă��Ȃ�������
#define _TUTORIAL_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CTutorialPlayer;			// �`���[�g���A���v���C���[

//--------------------------------------------
// �N���X(�`���[�g���A���N���X)
//--------------------------------------------
class CTutorial : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	CTutorial();		// �R���X�g���N�^
	~CTutorial();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;		// ����������
	void Uninit(void) override;			// �I������
	void Update(void) override;			// �X�V����
	void Draw(void) override;			// �`�揈��

	// �ÓI�����o�֐�
	static CTutorialPlayer* GetPlayer(void);		// �v���C���[�̎擾����
	static void SetEnableExplain(const bool bExpl);	// �����󋵂̐ݒ菈��
	static bool IsExplain(void);					// �����󋵂̎擾����

	static void DeletePlayer(void);				// �v���C���[��NULL������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nEndCount;					// �I���܂ł̃J�E���g

	// �ÓI�����o�ϐ�
	static CTutorialPlayer* m_pPlayer;	// �v���C���[�̏��
	static bool m_bExpl;				// ������
};

#endif