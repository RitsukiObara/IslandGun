//============================================
//
// �R���e�B�j���[UI����[continueUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "continueUI.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "useful.h"

#include "object2D.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "game_score.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const char* TEXTURE[CContinueUI::TYPE_MAX] =			// �e�N�X�`��
	{
		nullptr,
		"data\\TEXTURE\\ContGround.png",
		"data\\TEXTURE\\ContQuery.png",
		"data\\TEXTURE\\ContYes.png",
		"data\\TEXTURE\\ContNo.png",
	};
	const D3DXVECTOR3 POS[CContinueUI::TYPE_MAX] =			// �ʒu
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f),
		D3DXVECTOR3(390.0f,450.0f,0.0f),
		D3DXVECTOR3(890.0f,450.0f,0.0f),
	};
	const D3DXVECTOR3 POLY_SIZE[CContinueUI::TYPE_MAX] =	// �T�C�Y
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(550.0f,330.0f,0.0f),
		D3DXVECTOR3(500.0f,80.0f,0.0f),
		D3DXVECTOR3(160.0f,80.0f,0.0f),
		D3DXVECTOR3(160.0f,80.0f,0.0f),
	};
	const D3DXCOLOR SCREEN_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);		// �w�i�̐F
	const int CONTINUE_LIFE = 100;			// �R���e�B�j���[�����Ƃ��̗̑�
}

//========================
// �R���X�g���N�^
//========================
CContinueUI::CContinueUI() : CObject(TYPE_CONTINUEUI, DIM_2D, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;		// �|���S���̏��
	}
	m_select = SELECT_YES;		// �I����
}

//========================
// �f�X�g���N�^
//========================
CContinueUI::~CContinueUI()
{

}

//========================
// ����������
//========================
HRESULT CContinueUI::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CContinueUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // �|���S���̏�� NULL ����Ȃ��ꍇ

			// �|���S���̏I������
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CContinueUI::Update(void)
{
	if (Decide() == true)
	{ // ���肵���ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//========================
// �`�揈��
//========================
void CContinueUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apObject[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CContinueUI::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// �|���S���𐶐�
			m_apObject[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// �ݒ菈��
			m_apObject[nCnt]->SetPos(POS[nCnt]);			// �ʒu
			m_apObject[nCnt]->SetPosOld(POS[nCnt]);			// �O��̈ʒu
			m_apObject[nCnt]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apObject[nCnt]->SetSize(POLY_SIZE[nCnt]);		// �T�C�Y
			m_apObject[nCnt]->SetAngle();					// ����
			m_apObject[nCnt]->SetLength();					// ����

			// �e�N�X�`���̊��蓖�ď���
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[nCnt]));

			// ���_���W�̐ݒ菈��
			m_apObject[nCnt]->SetVertex();

			if (nCnt == TYPE::TYPE_SCREEN)
			{ // �w�i�̏ꍇ

				// �F��ݒ肷��
				m_apObject[nCnt]->SetVtxColor(SCREEN_COL);
			}
		}
	}
	m_select = SELECT_YES;		// �I����
}

//========================
// ��������
//========================
CContinueUI* CContinueUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CContinueUI* pUI = nullptr;			// UI�̃C���X�^���X�𐶐�

	if (pUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pUI = new CContinueUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pUI->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// UI�̃|�C���^��Ԃ�
	return pUI;
}

//========================
// ���菈��
//========================
bool CContinueUI::Decide(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // ����L�[���������ꍇ

		switch (m_select)
		{
		case CContinueUI::SELECT_YES:

			// �R���e�B�j���[����
			Continue();

			break;


		case CContinueUI::SELECT_NO:


			break;

		default:

			// ��~����
			assert(false);

			break;
		}

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//========================
// �R���e�B�j���[����
//========================
void CContinueUI::Continue(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();		// �v���C���[�̏��
	CGameScore* pScore = CGame::GetGameScore();	// �Q�[���X�R�A�̏��

	if (pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �̗͂�ݒ肷��
		pPlayer->SetLife(CONTINUE_LIFE);

		// �v���C���[�𖳓G��Ԃɐݒ�
		CPlayer::SState state = pPlayer->GetState();
		state.state = CPlayer::STATE_INVINSIBLE;
		pPlayer->SetState(state);

		// �v���C���[�h�ɂ���
		CGame::SetState(CGame::STATE_PLAY);

		// �ʏ�J�����ɂ���
		CManager::Get()->GetCamera()->SetType(CCamera::TYPE_NONE);

		// �X�R�A�����炷
		pScore->SetScore(pScore->GetScore() - 200);
	}
}