//============================================
//
// �t�@�C���w�b�_�[[file.h]
// Author�F��������
//
//============================================
#ifndef _FILE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _FILE_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "ranking.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// �t�@�C���̃f�[�^�̍ő吔

//--------------------------------------------
// �N���X(�t�@�C���ǂݍ��݃N���X)
//--------------------------------------------
class CFile
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_RANKING = 0,	// �����L���O
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �����L���O�̏��
	struct SRankingInfo
	{
		int aRank[MAX_RANKING];				// �����L���O�̃f�[�^
		bool bSuccess;						// ������
	};

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

	void SetRankingInfo(int* pRank);		// �����L���O�̐ݒ菈��
	SRankingInfo GetRankingInfo(void);		// �����L���O�̎擾����

	// �ÓI�����o�֐�
	static CFile* Create(void);		// ��������

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveRanking(void);		// �����L���O�̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadRanking(void);		// �����L���O�̃��[�h����

	// �����o�ϐ�
	SRankingInfo m_RankingInfo;		// �����L���O�̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif