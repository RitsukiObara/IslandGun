//===================================
//
// �e�w�b�_�[[bullet.h]
// Author ��������
//
//===================================
#ifndef _BULLET_H_
#define _BULLET_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"
#include "list_manager.h"

//-----------------------------------
// �N���X��`(CBullet)
//-----------------------------------
class CBullet : public CBillboard
{
public:

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HANDGUN = 0,	// �񒚌��e
		TYPE_SHOTGUN,		// �U�e
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CBullet();				// �R���X�g���N�^
	~CBullet();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

	static CListManager<CBullet*> GetList(void);			// ���X�g�̎擾����

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	TYPE m_type;			// ���
	int m_nLife;			// ����

	// �ÓI�����o�ϐ�
	static CListManager<CBullet*> m_list;		// ���X�g
};

#endif