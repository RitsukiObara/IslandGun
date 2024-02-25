//===========================================
//
// �h�A�̃��C������[door.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "door.h"
#include "useful.h"

#include "input.h"

//-------------------------------------------
// �萔��`
//-------------------------------------------
namespace
{
	const char* DOOR_MODEL = "data\\MODEL\\Door.x";						// �h�A���f���̖��O
	const char* FRAME_MODEL = "data\\MODEL\\DoorFrame.x";				// �h�A�t���[�����f���̖��O
	const D3DXVECTOR3 DOOR_OFFSET = D3DXVECTOR3(60.7f, 0.0f, 0.0f);		// �h�A�̃I�t�Z�b�g
}

//==============================
// �R���X�g���N�^
//==============================
CDoor::CDoor() : CModel(CObject::TYPE_DOOR, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pDoor = nullptr;			// �h�A�̃��f��
}

//==============================
// �f�X�g���N�^
//==============================
CDoor::~CDoor()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CDoor::Init(void)
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
void CDoor::Uninit(void)
{
	if (m_pDoor != nullptr)
	{ // �h�A�� NULL ����Ȃ��ꍇ

		// �h�A�̏I������
		m_pDoor->Uninit();
		m_pDoor = nullptr;
	}

	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CDoor::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CDoor::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pDoor != nullptr)
	{ // �h�A�� NULL ����Ȃ��ꍇ

		// �h�A�̕`�揈��
		m_pDoor->DrawMatrix(GetMatrix());
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CDoor::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(FRAME_MODEL));	// ���f�����

	if (m_pDoor == nullptr)
	{ // �h�A�� NULL ����Ȃ��ꍇ

		// �h�A�̐���
		m_pDoor = CModel::Create(TYPE_NONE, PRIORITY_ENTITY);

		// ���̐ݒ菈��
		m_pDoor->SetPos(DOOR_OFFSET);		// �ʒu
		m_pDoor->SetPosOld(DOOR_OFFSET);	// �O��̈ʒu
		m_pDoor->SetRot(NONE_D3DXVECTOR3);	// ����
		m_pDoor->SetScale(NONE_SCALE);		// �g�嗦
		m_pDoor->SetFileData(CManager::Get()->GetXFile()->Regist(DOOR_MODEL));	// ���f�����
	}
}

//=======================================
// ��������
//=======================================
CDoor* CDoor::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CDoor* pDoor = nullptr;		// �C���X�^���X�𐶐�

	if (pDoor == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pDoor = new CDoor;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pDoor != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pDoor->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pDoor->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �h�A�̃|�C���^��Ԃ�
	return pDoor;
}