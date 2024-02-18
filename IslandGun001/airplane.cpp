//===========================================
//
// ��s�@�̃��C������[airplane.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "airplane.h"
#include "useful.h"

#include "propeller.h"

//-------------------------------------------
// �萔��`
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Airplane.x";		// ���f���̃p�X��
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CAirplane*> CAirplane::m_list = {};		// ���X�g

//==============================
// �R���X�g���N�^
//==============================
CAirplane::CAirplane() : CModel(CObject::TYPE_AIRPLANE, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pPropeller = nullptr;		// �v���y���̏��

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//==============================
// �f�X�g���N�^
//==============================
CAirplane::~CAirplane()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CAirplane::Init(void)
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
void CAirplane::Uninit(void)
{
	if (m_pPropeller != nullptr)
	{ // �v���y���� NULL ����Ȃ��ꍇ

		// �I������
		m_pPropeller->Uninit();
		m_pPropeller = nullptr;
	}

	// �I������
	CModel::Uninit();

	// ������������
	m_list.Pull(this);
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CAirplane::Update(void)
{
	if (m_pPropeller != nullptr)
	{ // �v���y���� NULL ����Ȃ��ꍇ

		// �X�V����
		m_pPropeller->Update();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CAirplane::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pPropeller != nullptr)
	{ // �v���y���̏�� NULL ����Ȃ��ꍇ

		// �v���y���̕`�揈��
		m_pPropeller->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAirplane::SetData(D3DXVECTOR3 pos)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);			// ����
	SetScale(NONE_SCALE);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f�����

	// �S�Ă̒l��ݒ肷��
	m_pPropeller = CPropeller::Create(GetMatrixPoint());		// �v���y���̏��
}

//=======================================
// ��������
//=======================================
CAirplane* CAirplane::Create(D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAirplane* pAirplane = nullptr;	// �C���X�^���X�𐶐�

	if (pAirplane == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pAirplane = new CAirplane;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAirplane != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAirplane->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAirplane->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��s�@�̃|�C���^��Ԃ�
	return pAirplane;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CAirplane*> CAirplane::GetList(void)
{
	// ���X�g�}�l�[�W���[�̏���Ԃ�
	return m_list;
}