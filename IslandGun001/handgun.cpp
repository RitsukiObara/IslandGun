//===========================================
//
// ���e�̃��C������[handgun.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "handgun.h"
#include "useful.h"

// �������O���
namespace
{
	const char* MODEL = "data\\MODEL\\Pistol.x";		// ���f���̖��O
}

//==============================
// �R���X�g���N�^
//==============================
CHandgun::CHandgun() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMtxParent = nullptr;		// �e�̃}�g���b�N�X
	m_bDisp = true;				// �`���
}

//==============================
// �f�X�g���N�^
//==============================
CHandgun::~CHandgun()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CHandgun::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CHandgun::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CHandgun::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CHandgun::Draw(void)
{
	if (m_bDisp == true)
	{ // �`��󋵂� true �̏ꍇ

		// �`�揈��
		CModel::DrawMatrix(*m_pMtxParent);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHandgun::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot, D3DXMATRIX* mtx)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(rot);						// ����
	SetScale(NONE_SCALE);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f�����

	// �S�Ă̒l���N���A����
	m_pMtxParent = mtx;		// �e�̃}�g���b�N�X
	m_bDisp = true;			// �`���
}

//=======================================
// ��������
//=======================================
CHandgun* CHandgun::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot, D3DXMATRIX* mtx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CHandgun* pGun = nullptr;	// �C���X�^���X�𐶐�

	if (pGun == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pGun = new CHandgun;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pGun != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pGun->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pGun->SetData(pos, rot, mtx);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���e�̃|�C���^��Ԃ�
	return pGun;
}

//=======================================
// �`��󋵂̐ݒ菈��
//=======================================
void CHandgun::SetEnableDisp(const bool bDisp)
{
	// �`��󋵂�ݒ肷��
	m_bDisp = bDisp;
}

//=======================================
// �`��󋵂̎擾����
//=======================================
bool CHandgun::IsDisp(void) const
{
	// �`��󋵂�ݒ肷��
	return m_bDisp;
}