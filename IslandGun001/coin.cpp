//===========================================
//
// �����̃��C������[coin.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "coin.h"
#include "useful.h"

#include "coin_manager.h"

//==============================
// �R���X�g���N�^
//==============================
CCoin::CCoin() : CModel(CObject::TYPE_COIN, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;			// �O�̃|�C���^
	m_pNext = nullptr;			// ���̃|�C���^

	if (CCoinManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CCoinManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CCoin::~CCoin()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CCoin::SetPrev(CCoin* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CCoin::SetNext(CCoin* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CCoin* CCoin::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CCoin* CCoin::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CCoin::Init(void)
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
//�u���b�N�̏I������
//========================================
void CCoin::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CCoinManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CCoinManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CCoin::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	// ���������Z����
	rot.y += 0.01f;

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	// ������K�p����
	SetRot(rot);
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CCoin::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCoin::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);			// ����
	SetScale(NONE_SCALE);				// �g�嗦
	SetFileData(CXFile::TYPE_PLAYERHEAD);	// ���f���̏��

	// �S�Ă̒l������������
}

//=======================================
// ��������
//=======================================
CCoin* CCoin::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCoin* pCoin = nullptr;	// �C���X�^���X�𐶐�

	if (pCoin == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pCoin = new CCoin;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCoin != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCoin->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCoin->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pCoin;
}