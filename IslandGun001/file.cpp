//============================================
//
// �t�@�C���̃��C������[file.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RANKING_BIN			"data\\BIN\\Ranking.bin"		// �����L���O�̃e�L�X�g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool�^�̕\��
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// �R���X�g���N�^
//===========================================
CFile::CFile()
{
	// �S�Ă̒l���N���A����
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_RankingInfo.aRank[nCntRank] = 0;				// �����L���O�̒l
	}

	// �����󋵂��N���A����
	m_RankingInfo.bSuccess = false;		// �����L���O
}

//===========================================
// �f�X�g���N�^
//===========================================
CFile::~CFile()
{

}

//===========================================
// �Z�[�u����
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_RANKING:

		// �����L���O�̃Z�[�u����
		if (FAILED(SaveRanking()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// ���[�h����
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_RANKING:

		// �����L���O�̃��[�h����
		if (FAILED(LoadRanking()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���ʂ�Ԃ�
	return S_OK;
}

//===========================================
// �����L���O�̐ݒ菈��
//===========================================
void CFile::SetRankingInfo(int* pRank)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++, pRank++)
	{
		// �����L���O�̏���ݒ肷��
		m_RankingInfo.aRank[nCnt] = *pRank;
	}
}

//===========================================
// �����L���O�̎擾����
//===========================================
CFile::SRankingInfo CFile::GetRankingInfo(void)
{
	// �����L���O�̏���Ԃ�
	return m_RankingInfo;
}

//===========================================
// �t�@�C���̐�������
//===========================================
CFile* CFile::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFile* pFile = nullptr;		// �t�@�C���̃C���X�^���X�𐶐�

	if (pFile == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pFile = new CFile;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFile != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFile->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �t�@�C���̃|�C���^��Ԃ�
	return pFile;
}

//===========================================
// ����������
//===========================================
HRESULT CFile::Init(void)
{
	// �S�Ă̒l������������
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_RankingInfo.aRank[nCntRank] = 0;				// �����L���O�̒l
	}

	// �����󋵂�����������
	m_RankingInfo.bSuccess = false;		// �����L���O

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CFile::Uninit(void)
{
	// ���������J������
	delete this;
}

//===========================================
// �����L���O�̃Z�[�u����
//===========================================
HRESULT CFile::SaveRanking(void)
{
	FILE *pFile;												// �t�@�C���|�C���^��錾
	m_RankingInfo.bSuccess = false;								// ������

	// �t�@�C�����J��
	pFile = fopen(RANKING_BIN, "wb");			// �o�C�i���t�@�C���ɏ������ނ��߂ɊJ��

	// �t�@�C�����r����
	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		// �t�@�C�����琔�l�������o��
		fwrite(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_RankingInfo.bSuccess = true;

		// ������Ԃ�
		return S_OK;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}
}

//===========================================
// �����L���O�̃��[�h����
//===========================================
HRESULT CFile::LoadRanking(void)
{
	FILE *pFile;						// �t�@�C���|�C���^��錾
	m_RankingInfo.bSuccess = false;		// ������

	// �t�@�C�����J��
	pFile = fopen(RANKING_BIN, "rb");			// �o�C�i���t�@�C������ǂݍ��ނ��߂ɊJ��

	// �t�@�C�����r����
	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		// �t�@�C�����琔�l��ǂݍ���
		fread(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_RankingInfo.bSuccess = true;

		// ������Ԃ�
		return S_OK;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			// ���l��ݒ肷��
			m_RankingInfo.aRank[0] = 0;
		}

		// ���s��Ԃ�
		return E_FAIL;
	}
}