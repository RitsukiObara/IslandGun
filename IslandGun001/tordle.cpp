//============================================================
//
// �^�[�h������ [tordle.cpp]
// Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "tordle.h"
#include "motion.h"
#include "manager.h"

#include "game.h"
#include "player.h"
#include "useful.h"

//------------------------------------------------------------
// �������O���
//------------------------------------------------------------
namespace
{
	const float SPEED = 3.0f;			// �ړ���
}

//================================
// �R���X�g���N�^
//================================
CTordle::CTordle() : CEnemy()
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;		// �ڕW�̌���
}

//================================
// �f�X�g���N�^
//================================
CTordle::~CTordle()
{

}

//================================
// ����������
//================================
HRESULT CTordle::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//================================
// �I������
//================================
void CTordle::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//================================
// �X�V����
//================================
void CTordle::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ǐՏ���
	Chase();

	// �����̈ړ�����
	RotMove();

	// �ړ�����
	Move();

	// �X�V����
	CEnemy::Update();
}

//================================
// �`�揈��
//================================
void CTordle::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//================================
// ���̐ݒ菈��
//================================
void CTordle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CEnemy::SetData(pos, rot, type);

	// ���[�V�����̃��Z�b�g����
	GetMotion()->ResetMotion(MOTIONTYPE_MOVE);

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;		// �ڕW�̌���
}

//===========================================
// �q�b�g����
//===========================================
void CTordle::Hit(const D3DXVECTOR3& pos)
{
	// �q�b�g����
	CEnemy::Hit(pos);
}

//===========================================
// �ǐՏ���
//===========================================
void CTordle::Chase(void)
{
	D3DXVECTOR3 pos;						// �G�̈ʒu
	D3DXVECTOR3 posPlayer;					// �v���C���[�̈ʒu
	float fRot = 0.0f;						// ����

	if (CGame::GetPlayer() != nullptr)
	{ // �v���C���[�����݂����ꍇ

		pos = GetPos();									// �ʒu���擾����
		posPlayer = CGame::GetPlayer()->GetPos();		// �v���C���[�̈ʒu���擾����

		// �������Z�o����
		fRot = atan2f((posPlayer.x - pos.x), (posPlayer.z - pos.z));

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(fRot) * SPEED;
		m_move.z = cosf(fRot) * SPEED;

		// �ڕW�̌�����ݒ肷��
		m_rotDest.y = fRot;
	}
}

//===========================================
// �ړ�����
//===========================================
void CTordle::Move(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ړ�����
	pos.x += m_move.x;
	pos.z += m_move.z;

	// �ʒu��K�p����
	SetPos(pos);
}

//===========================================
// �����̈ړ�����
//===========================================
void CTordle::RotMove(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// �����̕␳����
	useful::RotCorrect(m_rotDest.y, &rot.y, 0.1f);

	// ������K�p����
	SetRot(rot);
}