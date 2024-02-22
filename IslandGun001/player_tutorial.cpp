//============================================
//
// �`���[�g���A���v���C���[�̃��C������[player_tutorial.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "player_tutorial.h"
#include "tutorial.h"
#include "collision.h"
#include "renderer.h"

#include "player_controller.h"
#include "motion.h"
#include "player_action.h"
#include "handgun.h"
#include "aim.h"
#include "lifeUI.h"
#include "airplane.h"

// �萔��`
namespace
{
	const D3DXVECTOR3 COLLISION_SIZE = D3DXVECTOR3(40.0f, 190.0f, 40.0f);		// �����蔻�莞�̃T�C�Y
}

//=========================================
// �R���X�g���N�^
//=========================================
CTutorialPlayer::CTutorialPlayer() : CPlayer()
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorialPlayer::~CTutorialPlayer()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CTutorialPlayer::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CTutorialPlayer::Uninit(void)
{
	// �I������
	CPlayer::Uninit();

	// �v���C���[��NULL������
	CTutorial::DeletePlayer();
}

//===========================================
// �X�V����
//===========================================
void CTutorialPlayer::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	if (collision::SignboardCollision(GetPos(), COLLISION_SIZE.x) == true)
	{ // �Ŕɋ߂Â����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���쏈��
	GetController()->Control(this);

	// �ړ�����
	Move();

	if (GetMotion() != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̍X�V����
		GetMotion()->Update();
	}

	if (GetAction() != nullptr)
	{ // �s���� NULL ����Ȃ��ꍇ

		// �s���̍X�V����
		GetAction()->Update(this);
	}

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (GetHandGun(nCntGun) != nullptr)
		{ // ���e�� NULL ����Ȃ��ꍇ

			// �X�V����
			GetHandGun(nCntGun)->Update();
		}
	}

	// �ً}�̃����[�h����
	EmergentReload();

	if (GetAim() != nullptr)
	{ // �G�C���� NULL ����Ȃ��ꍇ

		// �G�C���̍X�V����
		GetAim()->Update();
	}

	if (GetLifeUI() != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// ������ݒ肷��
		GetLifeUI()->SetLife(GetLife());
	}

	// ���V�̎��Ƃ̓����蔻��
	collision::PalmFruitHit(this, COLLISION_SIZE.x, COLLISION_SIZE.y);

	// �����Ƃ̓����蔻��
	collision::CoinCollision(this, COLLISION_SIZE);

	// ���̍��Ƃ̓����蔻��
	collision::GoldBoneCollision(*this, COLLISION_SIZE);

	// �؂Ƃ̓����蔻��
	TreeCollision();

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();

	// �u���b�N�Ƃ̓����蔻�菈��
	BlockCollision();

	// ��Ƃ̓����蔻��
	RockCollision();

	// �ǂƂ̓����蔻��
	WallCollision();

	// �Ւd�Ƃ̓����蔻��
	AlterCollision();
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CTutorialPlayer::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CTutorialPlayer::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	CPlayer::SetData(pos);

	// ��s�@����������
	GetAirplane()->Uninit();
	RemoveAirplane();

	// �ʒu���Đݒ肷��
	SetPos(pos);
}

//===========================================
// ��������
//===========================================
CTutorialPlayer* CTutorialPlayer::Create(const D3DXVECTOR3& pos)
{
	// �v���C���[�̃C���X�^���X�𐶐�
	CTutorialPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pPlayer = new CTutorialPlayer;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return pPlayer;
	}

	if (pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayer->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}