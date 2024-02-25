//============================================
//
// �`���[�g���A����ʂ̃��C������[tutorial.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "fade.h"
#include "renderer.h"

#include "objectElevation.h"
#include "Objectmesh.h"
#include "motion.h"
#include "file.h"
#include "skybox.h"

#include "player_tutorial.h"
#include "balloon_spawner.h"
#include "signboard.h"
#include "door.h"

//--------------------------------------------
// �萔��`
//--------------------------------------------
namespace
{
	const int TRANS_COUNT = 120;			// �J�ڂ܂ł̃J�E���g��
}

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CTutorialPlayer* CTutorial::m_pPlayer = nullptr;		// �v���C���[�̏��
CSignboard* CTutorial::m_pLook = nullptr;				// ���݌��Ă�Ŕ�
bool CTutorial::m_bExpl = false;						// ������

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial()
{
	// �S�Ă̏����N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g
	m_pPlayer = nullptr;		// �v���C���[�̏��
	m_pLook = nullptr;			// ���݌��Ă�Ŕ�
	m_bExpl = false;			// ������
}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���[�V�����̓ǂݍ��ݏ���
	CMotion::Load(CMotion::STYLE_PLAYER);		// �v���C���[
	CMotion::Load(CMotion::STYLE_TORDLE);		// �^�[�h��
	CMotion::Load(CMotion::STYLE_IWAKARI);		// �C���J��
	CMotion::Load(CMotion::STYLE_BOSS);			// �{�X

	// �}�b�v�̐���
	CManager::Get()->GetFile()->SetEnemy();
	CManager::Get()->GetFile()->SetCoin();
	CManager::Get()->GetFile()->SetGoldBone();
	CManager::Get()->GetFile()->SetTree();
	CManager::Get()->GetFile()->SetRock();
	CManager::Get()->GetFile()->SetBlock();
	CManager::Get()->GetFile()->SetBangFlower();
	CManager::Get()->GetFile()->SetWall();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �v���C���[�𐶐�
	m_pPlayer = CTutorialPlayer::Create(NONE_D3DXVECTOR3);

	CBalloonSpawner::Create(D3DXVECTOR3(300.0f, 600.0f, 0.0f));

	CSignboard::Create(D3DXVECTOR3(3000.0f, 50.0f, 3000.0f), NONE_D3DXVECTOR3, CSignboard::TYPE::TYPE_JUMP);

	CDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 400.0f));

	// �S�Ă̒l���N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	// �S�Ă̒l���N���A����
	m_pPlayer = nullptr;		// �v���C���[�̃|�C���^
	m_pLook = nullptr;			// ���݌��Ă�Ŕ�
	m_bExpl = false;			// ������

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
{
	//// �I���J�E���g�����Z����
	//m_nEndCount++;

	//if (m_nEndCount >= TRANS_COUNT)
	//{ // �X�L�b�v���܂��́A�I�����̏ꍇ

	//	// �Q�[�����[�h�ɂ���
	//	CManager::Get()->GetFade()->SetFade(MODE_GAME);
	//}

	if (m_bExpl == false)
	{ // �����󋵂���Ȃ��ꍇ

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �X�V����
			CManager::Get()->GetRenderer()->Update();
		}
	}
	else
	{ // ��L�ȊO

		// �Ŕ̐����̂ݍX�V
		CObject::AnyUpdate(CObject::TYPE_SIGNEXPLAIN);
	}
}

//======================================
//�`�揈��
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// �v���C���[�̎擾����
//======================================
CTutorialPlayer* CTutorial::GetPlayer(void)
{
	// �v���C���[�̏���Ԃ�
	return m_pPlayer;
}

//======================================
// �����󋵂̐ݒ菈��
//======================================
void CTutorial::SetEnableExplain(const bool bExpl)
{
	// �����󋵂�ݒ肷��
	m_bExpl = bExpl;
}

//======================================
// �����󋵂̎擾����
//======================================
bool CTutorial::IsExplain(void)
{
	// �����󋵂�Ԃ�
	return m_bExpl;
}

//======================================
// �Ŕ̐ݒ菈��
//======================================
void CTutorial::SetLookSign(CSignboard* pSign)
{
	// �Ŕ̏���ݒ肷��
	m_pLook = pSign;
}

//======================================
// �Ŕ̎擾����
//======================================
CSignboard* CTutorial::GetLookSign(void)
{
	// �Ŕ̏���Ԃ�
	return m_pLook;
}

//======================================
// �v���C���[�̃v���C���[��NULL������
//======================================
void CTutorial::DeletePlayer(void)
{
	// �v���C���[�� NULL �ɂ���
	m_pPlayer = nullptr;
}