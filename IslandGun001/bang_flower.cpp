//===========================================
//
// ���e�Ԃ̃��C������[bang_flower.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "bang_flower.h"
#include "texture.h"
#include "useful.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\BombFlower.x";		// ���f���̖��O
}

//==============================
// �R���X�g���N�^
//==============================
CBangFlower::CBangFlower() : CModel(TYPE_BANGFLOWER, PRIORITY_ENTITY)
{

}

//==============================
// �f�X�g���N�^
//==============================
CBangFlower::~CBangFlower()
{

}

//==============================
//���e�Ԃ̏���������
//==============================
HRESULT CBangFlower::Init(void)
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
//���e�Ԃ̏I������
//========================================
void CBangFlower::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//========================================
//���e�Ԃ̍X�V����
//========================================
void CBangFlower::Update(void)
{

}

//=====================================
//���e�Ԃ̕`�揈��
//=====================================
void CBangFlower::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBangFlower::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(scale);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));	// ���f���̏��
}

//=======================================
// ��������
//=======================================
CBangFlower* CBangFlower::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBangFlower* pBangFlower = nullptr;		// �C���X�^���X�𐶐�

	if (pBangFlower == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ���e�Ԃ𐶐�����
		pBangFlower = new CBangFlower;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBangFlower != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBangFlower->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBangFlower->SetData(pos, scale);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���e�Ԃ̃|�C���^��Ԃ�
	return pBangFlower;
}