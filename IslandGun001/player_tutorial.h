//============================================
//
// �`���[�g���A���v���C���[�w�b�_�[[player_tutorial.h]
// Author�F��������
//
//============================================
#ifndef _PLAYER_TUTORIAL_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_TUTORIAL_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"

//--------------------------------------------
// �N���X(�`���[�g���A���v���C���[�N���X)
//--------------------------------------------
class CTutorialPlayer : public CPlayer
{
public:			// �N�ł��A�N�Z�X�ł���

	CTutorialPlayer();				// �R���X�g���N�^
	~CTutorialPlayer();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTutorialPlayer* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif