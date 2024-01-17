//============================================
//
// �v���C���[�̃��C������[player.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "useful.h"

#include "player.h"
#include "player_action.h"
#include "handgun.h"
#include "aim.h"

#include "collision.h"
#include "camera.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "motion.h"
#include "bullet.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
namespace
{
	const float GRAVITY = 1.0f;						// �d��
	const float LAND_GRAVITY = -50.0f;				// ���n���̏d��
	const float JUMP = 23.0f;						// �W�����v��
	const float SPEED = 10.0f;						// ���x
	const float INIT_POSV_CAMERA_Y = 250.0f;		// �J�����̎��_��Y���W
	const float ROT_CORRECT = 0.2f;					// �����̕␳�{��
	const float CAMERA_ROT_CORRECT = 0.000003f;		// �J�����̌����̕␳�{��
	const float CAMERA_HEIGHT = 0.0005f;			// �J�����̍����̔{��
	const float CAMERA_MAX_HEIGHT = 500.0f;			// �J�����̍����̍ő�l
	const float CAMERA_MIN_HEIGHT = 0.0f;			// �J�����̍����̍ŏ��l
	const float CAMERA_ELEVATION_HEIGHT = 30.0f;	// �J�����̋N���n�ʂ̍���
	const D3DXVECTOR3 COLLISION_SIZE = D3DXVECTOR3(40.0f, 130.0f, 40.0f);		// �����蔻�莞�̃T�C�Y
	const float SHOT_SHIFT_ROT[NUM_HANDGUN] =		// �ˌ����̂��炷����
	{
		(D3DX_PI * 0.06f),
		(-D3DX_PI * 0.06f)
	};
	const float SHOT_SHIFT_LENGTH = 95.0f;			// �ˌ����̂��炷��
	const float SHOT_ADD_HEIGHT = 160.0f;			// �ˌ����̍����̒ǉ���
	const float SHOT_ADD_ROT = 0.9f;				// �ˌ����̌����̉��Z��
}

//=========================================
// �R���X�g���N�^
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;					// ���[�V�����̏��
	m_pAction = nullptr;					// �v���C���[�̍s���̏��
	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		m_apHandGun[nCntGun] = nullptr;		// ���e�̏��
	}
	m_pAim = nullptr;						// �G�C���̏��

	m_rotDest = NONE_D3DXVECTOR3;			// �ڕW�̌���
	m_move = NONE_D3DXVECTOR3;				// �ړ���
	m_state = STATE_NONE;					// ���
	m_nStateCount = 0;						// ��ԃJ�E���g
	m_nShotCount = 0;						// �ˌ��J�E���g
	m_fSpeed = SPEED;						// ���x
	m_fAlpha = 1.0f;						// �̂̓����x
	m_fStickRot = 0.0f;						// �X�e�B�b�N�̌���
	m_bMove = false;						// �ړ���
	m_bJump = false;						// �W�����v��
}

//=========================================
// �f�X�g���N�^
//=========================================
CPlayer::~CPlayer()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(17);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		m_pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		m_pMotion->Load("data\\TXT\\PlayerMotion.txt");
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	if (m_pAction == nullptr)
	{ // �s���̏�� NULL �̏ꍇ

		// �v���C���[�A�N�V�����̐�������
		m_pAction = CPlayerAction::Create();
	}

	// �S�Ă̒l������������
	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		m_apHandGun[nCntGun] = nullptr;	// ���e�̏��
	}
	m_pAim = nullptr;				// �G�C���̏��

	m_rotDest = NONE_D3DXVECTOR3;	// �ڕW�̌���
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_nShotCount = 0;				// �ˌ��J�E���g
	m_fSpeed = SPEED;				// ���x
	m_fAlpha = 1.0f;				// �̂̓����x
	m_fStickRot = 0.0f;				// �X�e�B�b�N�̌���
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̃��������J������
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pAction != nullptr)
	{ // �s���� NULL ����Ȃ��ꍇ

		// �s���̃��������J������
		m_pAction->Uninit();
		m_pAction = nullptr;
	}

	if (m_pAim != nullptr)
	{ // �G�C���� NULL ����Ȃ��ꍇ

		// �G�C���̃��������J������
		m_pAim->Uninit();
		m_pAim = nullptr;
	}

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (m_apHandGun[nCntGun] != nullptr)
		{ // ���e�̏�� NULL ����Ȃ��ꍇ

			// ���e�̏I������
			m_apHandGun[nCntGun]->Uninit();
			m_apHandGun[nCntGun] = nullptr;
		}
	}

	// �I������
	CCharacter::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CPlayer::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// ���쏈��
	Control();

	// �ړ�����
	Move();

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �s���̍X�V����
	m_pAction->Update(this);

	// �����Ƃ̓����蔻��
	collision::CoinCollision(GetPos(), COLLISION_SIZE);

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();

	for (int nCntGun = 0; nCntGun < NUM_HANDGUN; nCntGun++)
	{
		if (m_apHandGun[nCntGun] != nullptr)
		{ // ���e�̏�� NULL ����Ȃ��ꍇ

			// ���e�̕`�揈��
			m_apHandGun[nCntGun]->Draw();
		}
	}

	if (m_pAim != nullptr)
	{ // �G�C���̏�� NULL ����Ȃ��ꍇ

		// �G�C���̕`�揈��
		m_pAim->Draw();
	}
}

//===========================================
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CPlayer::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//===========================================
// �s���̏��̎擾����
//===========================================
CPlayerAction* CPlayer::GetAction(void) const
{
	// �s���̏���Ԃ�
	return m_pAction;
}

//=======================================
// ���̐ݒ菈��
//=======================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l������������
	SetPos(pos);					// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// �f�[�^�̐ݒ菈��
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// ���e�̏��𐶐�����
	m_apHandGun[0] = CHandgun::Create(D3DXVECTOR3(pos.x - 10.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), GetHierarchy(CXFile::TYPE_PLAYERRIGHTHAND - INIT_PLAYER)->GetMatrixP());
	m_apHandGun[1] = CHandgun::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), GetHierarchy(CXFile::TYPE_PLAYERLEFTHAND - INIT_PLAYER)->GetMatrixP());

	// �G�C���𐶐�����
	m_pAim = CAim::Create(GetPos(), CManager::Get()->GetCamera()->GetRot());

	// �S�Ă̒l��ݒ肷��
	m_rotDest = NONE_D3DXVECTOR3;	// �ڕW�̌���
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_nShotCount = 0;				// �ˌ��J�E���g
	m_fSpeed = SPEED;				// ���x
	m_fAlpha = 1.0f;				// �̂̓����x
	m_fStickRot = 0.0f;				// �X�e�B�b�N�̌���
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��
}

//===========================================
// ��������
//===========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	// �v���C���[�̃C���X�^���X�𐶐�
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���������m�ۂ���
		pPlayer = new CPlayer;
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

//=======================================
// �ړI�̌����̐ݒ菈��
//=======================================
void CPlayer::SetRotDest(const D3DXVECTOR3& rot)
{
	// �ړI�̌�����ݒ肷��
	m_rotDest = rot;
}

//=======================================
// �ړI�̌����̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetRotDest(void) const
{
	// �ړI�̌�����Ԃ�
	return m_rotDest;
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �N���n�ʂ̓����蔻�菈��
//=======================================
void CPlayer::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	float fHeight = 0.0f;			// ����
	bool bJump = true;				// �W�����v��
	bool bRange = false;			// �͈͓���

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos, bRange);

		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			// �d�͂�ݒ肷��
			m_move.y = LAND_GRAVITY;

			// �W�����v�󋵂� false �ɂ���
			bJump = false;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �W�����v�󋵂�������
	m_bJump = bJump;

	// �ʒu���X�V����
	SetPos(pos);
}

//=======================================
// ���쏈��
//=======================================
void CPlayer::Control(void)
{
	// �J�����̑��쏈��
	CameraControl();

	if (m_pAction->GetAction() != CPlayerAction::ACTION_DODGE)
	{ // �����ԈȊO�̏ꍇ

		// �����̈ړ�����
		RotMove();

		// �W�����v����
		Jump();

		// �U������
		Attack();
	}

	// �������
	Avoid();
}

//=======================================
// �ړ�����
//=======================================
void CPlayer::Move(void)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �����̕␳����
	useful::RotCorrect(m_rotDest.y, &rot.y, ROT_CORRECT);

	// �ʒu���ړ�������
	pos.x += m_move.x;
	pos.z += m_move.z;

	// �d�͂�������
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);

	// �ʒu�ƌ�����K�p����
	SetPos(pos);
	SetRot(rot);
}

//=======================================
// �����̐ݒ菈��
//=======================================
void CPlayer::RotMove(void)
{
	// ���[�J���ϐ���錾����
	float fStickRotX = 0.0f;	// �X�e�B�b�N��X���W
	float fStickRotY = 0.0f;	// �X�e�B�b�N��Y���W
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();	// �J�����̌���

	// �X�e�B�b�N�̌��������
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));

	if (fStickRotY != 0 ||
		fStickRotX != 0)
	{ // �E�X�e�B�b�N���ǂ������ɓ|�����ꍇ

		// �X�e�B�b�N�̌�����ݒ肷��
		m_fStickRot = atan2f(fStickRotX, fStickRotY);

		// �����̐��K��
		useful::RotNormalize(&m_fStickRot);

		// �����ɃJ�����̌��������Z����
		m_fStickRot += CameraRot.y;

		if (m_pAction->GetAction() != CPlayerAction::ACTION_SHOT)
		{ // �ˌ���ԈȊO�̏ꍇ

			// �����̐��K��
			useful::RotNormalize(&m_fStickRot);

			// ������ݒ肷��
			m_rotDest.y = m_fStickRot;
		}

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(m_fStickRot) * m_fSpeed;
		m_move.z = cosf(m_fStickRot) * m_fSpeed;

		if (m_pMotion->GetType() != MOTIONTYPE_MOVE)
		{ // �ړ����[�V��������Ȃ������ꍇ

			// �ړ����[�V������ݒ肷��
			m_pMotion->Set(MOTIONTYPE_MOVE);
		}
	}
	else
	{ // ��L�ȊO

		// �ړ��ʂ�ݒ肷��
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		if (m_pMotion->GetType() != MOTIONTYPE_NEUTRAL)
		{ // �ړ����[�V��������Ȃ������ꍇ

			// �ړ����[�V������ݒ肷��
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//=======================================
// �W�����v����
//=======================================
void CPlayer::Jump(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		// �ړ��ʂ�ݒ肷��
		m_move.y = JUMP;

		// �W�����v���Ă���
		m_bJump = true;
	}
}

//=======================================
// �J�����̑��쏈��
//=======================================
void CPlayer::CameraControl(void)
{
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// �J�����̌������擾����
	float fStickRotX, fStickRotY;		// �X�e�B�b�N�̌���

	// �E�X�e�B�b�N�̌X���x���擾����
	fStickRotX = CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0);
	fStickRotY = CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0);

	// �J�����̌��������Z����
	CameraRot.y += (fStickRotX * CAMERA_ROT_CORRECT);

	// �����̐��K��
	useful::RotNormalize(&CameraRot.y);

	// �J�����̌��������Z����
	CameraRot.x -= (fStickRotY * CAMERA_ROT_CORRECT);

	if (CameraRot.x >= D3DX_PI - 0.01f)
	{ // ���������𒴂����ꍇ

		CameraRot.x = D3DX_PI - 0.01f;
	}
	else if (CameraRot.x <= 0.0f + 0.01f)
	{ // ���������𒴂����ꍇ

		CameraRot.x = 0.0f + 0.01f;
	}

	if (m_pAim != nullptr)
	{ // �G�C���� NULL ����Ȃ��ꍇ

		D3DXVECTOR3 pos;

		// �ʒu��ݒ肷��
		pos.x = GetPos().x + sinf(CameraRot.y) * SHOT_SHIFT_LENGTH;
		pos.y = GetPos().y + SHOT_ADD_HEIGHT;
		pos.z = GetPos().z + cosf(CameraRot.y) * SHOT_SHIFT_LENGTH;

		// �G�C���̐ݒu����
		m_pAim->SetAim(pos, D3DXVECTOR3(CameraRot.x - SHOT_ADD_ROT, CameraRot.y, CameraRot.z));
	}

	//// �N���n�ʂƃJ�����̓����蔻��
	//ElevationCamera();

	// ������K�p����
	CManager::Get()->GetCamera()->SetRot(CameraRot);
}

//=======================================
// �N���n�ʂƃJ�����̓����蔻��
//=======================================
void CPlayer::ElevationCamera(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 posV = CManager::Get()->GetCamera()->GetPosV();	// �ʒu���擾����
	float fHeight = 0.0f;			// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(posV) + CAMERA_ELEVATION_HEIGHT;

		if (posV.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			posV.y = fHeight;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	CManager::Get()->GetCamera()->SetPosV(posV);
}

//=======================================
// �U������
//=======================================
void CPlayer::Attack(void)
{
	if (CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY_X, 0) == true)
	{ // X�L�[���������ꍇ

		// �ˌ���Ԃɂ���
		m_pAction->SetAction(CPlayerAction::ACTION_SHOT);

		if (m_nShotCount % 10 == 0)
		{ // ���J�E���g���Ƃ�

			D3DXVECTOR3 pos;		// �e�̏o��ʒu��錾
			D3DXVECTOR3 rot;		// �e�̏o�������錾

			// ������ݒ肷��
			rot = CManager::Get()->GetCamera()->GetRot();

			// �����������グ��(�J�����ʂ肾�Ǝˌ������ɂ�������)
			rot.x -= SHOT_ADD_ROT;

			// �����̐��K��
			useful::RotNormalize(&rot.x);

			for (int nCnt = 0; nCnt < NUM_HANDGUN; nCnt++)
			{
				// �ʒu��ݒ肷��
				pos.x = GetPos().x + sinf(GetRot().y + SHOT_SHIFT_ROT[nCnt]) * SHOT_SHIFT_LENGTH;
				pos.y = GetPos().y + SHOT_ADD_HEIGHT;
				pos.z = GetPos().z + cosf(GetRot().y + SHOT_SHIFT_ROT[nCnt]) * SHOT_SHIFT_LENGTH;

				// �e�o���o��
				CBullet::Create(pos, rot, CBullet::TYPE::TYPE_HANDGUN);
			}
		}

		// �ˌ��J�E���g�����Z����
		m_nShotCount++;
	}
	else
	{ // ��L�ȊO

		// �ʏ��Ԃɂ���
		m_pAction->SetAction(CPlayerAction::ACTION_NONE);

		// �ˌ��J�E���g��0�ɂ���
		m_nShotCount = 0;
	}
}

//=======================================
// �������
//=======================================
void CPlayer::Avoid(void)
{
	if (m_bJump == false &&
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true)
	{ // �n���B�L�[���������ꍇ

		// �����Ԃɂ���
		m_pAction->SetAction(CPlayerAction::ACTION_DODGE);

		// ������������ݒ肷��
		m_pAction->SetDodgeRot(m_fStickRot);
	}
}