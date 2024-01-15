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

	// ���X�g�\���֌W
	void SetPrev(CBullet* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBullet* pNext);	// ��̃|�C���^�̐ݒ菈��
	CBullet* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CBullet* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const float fRot, const TYPE type);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3& pos, const float fRot, const TYPE type);		// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	TYPE m_type;			// ���
	int m_nLife;			// ����
	float m_fRot;			// ���ł�������

	// ���X�g�\���֌W
	CBullet* m_pPrev;		// �O�ւ̃|�C���^
	CBullet* m_pNext;		// ���ւ̃|�C���^
};

#endif