//===================================
//
// ��w�b�_�[[rock.h]
// Author ��������
//
//===================================
#ifndef _ROCK_H_
#define _ROCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// �N���X��`(��)
//-----------------------------------
class CRock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_SOFT = 0,	// �_�炩����
		TYPE_HARD,		// �d����
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	CRock();			// �R���X�g���N�^
	~CRock();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type);			// ���̐ݒ菈��
	void Break(void);				// �j�󏈗�

	// �ÓI�����o�֐�
	static CRock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type);	// ��������

	static CListManager<CRock*> GetList(void);			// ���X�g�̎擾����

private:		// ���������A�N�Z�X�ł���
	
	// �����o�ϐ�
	TYPE m_type;		// ���
	int m_nBreakLevel;	// �j�󃌃x��

	// �ÓI�����o�ϐ�
	static CListManager<CRock*> m_list;		// ���X�g
};

#endif