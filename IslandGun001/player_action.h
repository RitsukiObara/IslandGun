//===================================
//
// �v���C���[�̍s���w�b�_�[[player_action.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_ACTION_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_ACTION_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CPlayer;		// �v���C���[

//-----------------------------------
// �N���X��`(�v���C���[�̍s��)
//-----------------------------------
class CPlayerAction
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�s��)
	enum ACTION
	{
		ACTION_NONE = 0,	// �ʏ���
		ACTION_SHOT,		// �ˌ����
		ACTION_DAGGER,		// �_�K�[���
		ACTION_DODGE,		// ������
		ACTION_SHOTGUN,		// �U�e(J+�e)���
		ACTION_SWOOP,		// �}�~��(J+�_�K�[)���
		ACTION_MAX			// ���̗񋓌^�̑���
	};

	CPlayerAction();		// �R���X�g���N�^
	~CPlayerAction();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(CPlayer* pPlayer);		// �X�V����

	// �ÓI�����o�֐�
	static CPlayerAction* Create(void);		// ��������

private:		// �N�ł��A�N�Z�X�ł���

	// �����o�ϐ�
	ACTION m_action;		// �s��
};

#endif