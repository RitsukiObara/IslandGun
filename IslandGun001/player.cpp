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
	const float CAMERA_ROT_CORRECT = 0.000004f;		// �J�����̌����̕␳�{��
	const float CAMERA_HEIGHT = 0.0005f;			// �J�����̍����̔{��
	const float CAMERA_MAX_HEIGHT = 500.0f;			// �J�����̍����̍ő�l
	const float CAMERA_MIN_HEIGHT = 0.0f;			// �J�����̍����̍ŏ��l
	const float CAMERA_ELEVATION_HEIGHT = 30.0f;	// �J�����̋N���n�ʂ̍���
}

//=========================================
// �R���X�g���N�^
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;					// ���[�V�����̏��
	m_pAction = nullptr;					// �v���C���[�̍s���̏��
	m_rotDest = NONE_D3DXVECTOR3;			// �ڕW�̌���
	m_move = NONE_D3DXVECTOR3;				// �ړ���
	m_state = STATE_NONE;					// ���
	m_nStateCount = 0;						// ��ԃJ�E���g
	m_nDodge = 0;							// ����J�E���g
	m_fSpeed = SPEED;						// ���x
	m_fAlpha = 1.0f;						// �̂̓����x
	m_fCameraHeight = INIT_POSV_CAMERA_Y;	// �J�����̍���
	m_bMove = false;						// �ړ���
	m_bJump = false;						// �W�����v��
	m_bDodge = false;						// �����
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
	SetNumModel(16);

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
	m_pMotion->Set(MOTIONTYPE_APPEAR);

	if (m_pAction == nullptr)
	{ // �s���̏�� NULL �̏ꍇ

		// �v���C���[�A�N�V�����̐�������
		m_pAction = CPlayerAction::Create();
	}

	// �S�Ă̒l������������
	m_rotDest = NONE_D3DXVECTOR3;	// �ڕW�̌���
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_NONE;			// ���
	m_nStateCount = 0;				// ��ԃJ�E���g
	m_nDodge = 0;					// ����J�E���g
	m_fSpeed = SPEED;				// ���x
	m_fAlpha = 1.0f;				// �̂̓����x
	m_bMove = false;				// �ړ���
	m_bJump = false;				// �W�����v��
	m_bDodge = false;				// �����

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CPlayer::Uninit(void)
{
	// ���[�V�����̃��������J������
	delete m_pMotion;
	m_pMotion = nullptr;

	// �s���̃��������J������
	m_pAction->Uninit();
	m_pAction = nullptr;

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

	// �J�����̑��쏈��
	CameraControl();

	// ���쏈��
	Control();

	// �ړ�����
	Move();

	// �s���̍X�V����
	m_pAction->Update(this);

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �N���n�ʂƂ̓����蔻�菈��
	ElevationCollision();

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_X, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetRepeat(CInputGamePad::JOYKEY_X, 0, 10) == true)
	{ // X�L�[���������ꍇ

		// �e�o���o��
		CBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 80.0f, GetPos().z), GetRot().y + 0.01f, CBullet::TYPE::TYPE_HANDGUN);
		CBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 80.0f, GetPos().z), GetRot().y - 0.01f, CBullet::TYPE::TYPE_HANDGUN);
	}
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//===========================================
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CPlayer::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
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

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
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
// �J�����̍����̐ݒ菈��
//=======================================
void CPlayer::SetCameraHeight(const float fHeight)
{
	// �J�����̍�����ݒ肷��
	m_fCameraHeight = fHeight;
}

//=======================================
// �J�����̍����̎擾����
//=======================================
float CPlayer::GetCameraHeight(void) const
{
	// �J�����̍�����Ԃ�
	return m_fCameraHeight;
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
	// �����̈ړ�����
	RotMove();

	// �W�����v����
	Jump();
}

//=======================================
// �ړ�����
//=======================================
void CPlayer::Move(void)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();

	// �����̐��K��
	useful::RotCorrect(m_rotDest.y, &rot.y, ROT_CORRECT);

	if (m_bMove == true)
	{ // �ړ��󋵂� true �̏ꍇ

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(m_rotDest.y) * m_fSpeed;
		m_move.z = cosf(m_rotDest.y) * m_fSpeed;
	}
	else
	{ // ��L�ȊO

		// �ړ��ʂ����Z�b�g����
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}

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
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// �J�����̌���
	float fStickRotX = 0.0f;		// �X�e�B�b�N��X���W
	float fStickRotY = 0.0f;		// �X�e�B�b�N��Y���W
	float fStickRot = 0.0f;			// �X�e�B�b�N�̌���

	// �X�e�B�b�N�̌��������
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));

	if (CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0) != 0 ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0) != 0)
	{ // �E�X�e�B�b�N���ǂ������ɓ|�����ꍇ

		// �X�e�B�b�N�̌�����ݒ肷��
		fStickRot = atan2f(fStickRotX, fStickRotY);

		// �����̐��K��
		useful::RotNormalize(&fStickRot);

		// �������X�e�B�b�N�̕����ɂ���
		m_rotDest.y = fStickRot + CameraRot.y;

		// �����̐��K��
		useful::RotNormalize(&m_rotDest.y);

		// �ړ��󋵂� true �ɂ���
		m_bMove = true;
	}
	else
	{ // ��L�ȊO

		// �ړ��󋵂� false �ɂ���
		m_bMove = false;
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

	// �J�����̍��������Z����
	m_fCameraHeight -= (fStickRotY * CAMERA_HEIGHT);

	if (m_fCameraHeight >= CAMERA_MAX_HEIGHT)
	{ // �J�����̍�������萔�𒴂����ꍇ

		// �J�����̍�����␳����
		m_fCameraHeight = CAMERA_MAX_HEIGHT;
	}

	if (m_fCameraHeight <= CAMERA_MIN_HEIGHT)
	{ // �J�����̍�������萔�𒴂����ꍇ

		// �J�����̍�����␳����
		m_fCameraHeight = CAMERA_MIN_HEIGHT;
	}

	// �N���n�ʂƃJ�����̓����蔻��
	ElevationCamera();

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