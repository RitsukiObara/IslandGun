//===========================================
//
// �Ւd�̃��C������[alter.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "alter.h"
#include "texture.h"
#include "useful.h"

#include "game.h"
#include "alter_pole.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Alter.x";			// ���f���̖��O
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	const D3DXVECTOR3 POLE_POS[CAlter::NUM_POLE] =		// �Β��̈ʒu
	{
		D3DXVECTOR3(0.0f,0.0f,-450.0f),
		D3DXVECTOR3(450.0f,0.0f,0.0f),
		D3DXVECTOR3(-450.0f,0.0f,0.0f),
	};
}

//==============================
// �R���X�g���N�^
//==============================
CAlter::CAlter() : CModel(TYPE_ALTER, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		m_apPole[nCnt] = nullptr;		// �Β��̏��
	}
}

//==============================
// �f�X�g���N�^
//==============================
CAlter::~CAlter()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CAlter::Init(void)
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
void CAlter::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // �Β��̏�� NULL ����Ȃ��ꍇ

			// �I������
			m_apPole[nCnt]->Uninit();
			m_apPole[nCnt] = nullptr;
		}
	}

	// �I������
	CModel::Uninit();

	// �Ւd��NULL������
	CGame::DeleteAlter();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CAlter::Update(void)
{
	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // �Β��̏�� NULL ����Ȃ��ꍇ

			// �X�V����
			m_apPole[nCnt]->Update();
		}
	}
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CAlter::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] != nullptr)
		{ // �Β��̏�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apPole[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAlter::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(POS);					// �ʒu
	SetPosOld(POS);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f���̏��

	for (int nCnt = 0; nCnt < NUM_POLE; nCnt++)
	{
		if (m_apPole[nCnt] == nullptr)
		{ // �Β��� NULL �������ꍇ

			// �Β��𐶐�
			m_apPole[nCnt] = CAlterPole::Create(POLE_POS[nCnt]);
		}
	}
}

//=======================================
// ��������
//=======================================
CAlter* CAlter::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAlter* pAlter = nullptr;		// �C���X�^���X�𐶐�

	if (pAlter == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �u���b�N�𐶐�����
		pAlter = new CAlter;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAlter != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAlter->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAlter->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Ւd�̃|�C���^��Ԃ�
	return pAlter;
}

//=======================================
// �Β��̎擾����
//=======================================
CAlterPole* CAlter::GetPole(const int nIdx) const
{
	if (nIdx >= NUM_POLE)
	{ // �C���f�b�N�X���ő吔�ȏ�̏ꍇ

		// ��~
		assert(false);
	}

	// �Β��̏���Ԃ�
	return m_apPole[nIdx];
}