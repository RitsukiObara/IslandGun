//===================================
//
// �Ŕw�b�_�[[signboard.h]
// Author ��������
//
//===================================
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�Ŕ�)
//-----------------------------------
class CSignboard : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_JUMP = 0,		// �W�����v�̐���
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CSignboard();			// �R���X�g���N�^
	~CSignboard();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSignboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���
};

#endif