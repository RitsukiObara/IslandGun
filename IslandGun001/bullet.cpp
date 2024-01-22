//=======================================
//
// �e�̃��C������[bullet.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "bullet_manager.h"
#include "locus3D.h"
#include "collision.h"

//=======================================
// �������O���
//=======================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Bullet.png";		// �e�̃e�N�X�`��
	const D3DXVECTOR3 RADIUS[CBullet::TYPE_MAX] =
	{
		D3DXVECTOR3(20.0f,20.0f,0.0f),		// �񒚌��e
		D3DXVECTOR3(10.0f,10.0f,0.0f),		// �U�e�e
	};
	const float SPEED = 45.0f;		// ���x
	const int LIFE = 90;			// ����
}

//=========================
// �R���X�g���N�^
//=========================
CBullet::CBullet() : CBillboard(CObject::TYPE_BULLET, CObject::PRIORITY_SHADOW)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;	// �ړ���
	m_type = TYPE_HANDGUN;		// ���
	m_nLife = LIFE;				// ����

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃A�E�g�{�[���ւ̃|�C���^
	m_pNext = nullptr;		// ���̃A�E�g�{�[���ւ̃|�C���^

	if (CBulletManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CBulletManager::Get()->Regist(this);
	}
}

//=========================
// �f�X�g���N�^
//=========================
CBullet::~CBullet()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CBullet::SetPrev(CBullet* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CBullet::SetNext(CBullet* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CBullet* CBullet::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CBullet* CBullet::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//=========================
// ����������
//=========================
HRESULT CBullet::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;	// �ړ���
	m_type = TYPE_HANDGUN;		// ���
	m_nLife = LIFE;				// ����

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CBullet::Uninit(void)
{
	// �I��
	CBillboard::Uninit();

	if (CBulletManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CBulletManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=========================
// �X�V����
//=========================
void CBullet::Update(void)
{
	// �O��̈ʒu��ۑ�����
	SetPosOld(GetPos());

	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ړ��ʂ�ݒ肷��
	pos += m_move;

	// �ʒu��K�p����
	SetPos(pos);

	// ���������Z����
	m_nLife--;

	if (m_nLife % 2 == 0)
	{ // ��莞�Ԃ��Ƃ�

		// �c���̐���
		CLocus3D::Create(GetPos(), GetSize(), 0.5f, 20, GetTexIdx(), true, true);
	}

	if (m_nLife <= 0)
	{ // ������0�ɂȂ����ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// �G�Əe�̓����蔻��
	if (collision::EnemyHitToGun(GetPos(), GetPosOld(), GetSize()) == true)
	{ // �G�ɓ��������ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CBullet::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff(true);
}

//=========================
// ���̐ݒ菈��
//=========================
void CBullet::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(0.0f);			// ����
	SetSize(RADIUS[type]);	// �T�C�Y
	SetAngle();				// ����
	SetLength();			// ����
	SetEnableLookY(true);	// Y����

	// �S�Ă̒l��ݒ肷��
	m_type = type;			// ���
	m_nLife = LIFE;			// ����

	// �ړ��ʂ�ݒ肷��
	m_move.x = sinf(rot.y) * SPEED;	// X��
	m_move.y = cosf(rot.x) * SPEED;	// Y��
	m_move.z = cosf(rot.y) * SPEED;	// Z��

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// ��������
//=========================
CBullet* CBullet::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBullet* pBullet = nullptr;	// �e�̃C���X�^���X�𐶐�

	if (pBullet == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pBullet = new CBullet;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBullet != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBullet->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBullet->SetData(pos, rot, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �e�̃|�C���^��Ԃ�
	return pBullet;
}