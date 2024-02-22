//===========================================
//
// ���D�̃��C������[balloon.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "balloon.h"
#include "renderer.h"
#include "useful.h"

#include "model.h"
#include "balloon_rope.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const char* MODEL = "data\\MODEL\\Balloon.x";		// ���D���f���̖��O
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CBalloon*> CBalloon::m_list = {};			// ���X�g���

//==============================
// �R���X�g���N�^
//==============================
CBalloon::CBalloon() : CObject(CObject::TYPE_TARGET, DIM_3D, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pos = NONE_D3DXVECTOR3;	// �ʒu
	m_pBalloon = nullptr;		// ���D�̃��f��
	m_pRope = nullptr;			// �R�̃��f��
}

//==============================
// �f�X�g���N�^
//==============================
CBalloon::~CBalloon()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CBalloon::Init(void)
{
	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CBalloon::Uninit(void)
{
	if (m_pBalloon != nullptr)
	{ // ���D�� NULL ����Ȃ��ꍇ

		// ���D�̏I������
		m_pBalloon->Uninit();
		m_pBalloon = nullptr;
	}

	if (m_pRope != nullptr)
	{ // �R�� NULL ����Ȃ��ꍇ

		// �R�̏I������
		m_pRope->Uninit();
		m_pRope = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CBalloon::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CBalloon::Draw(void)
{
	if (m_pBalloon != nullptr)
	{ // ���D�� NULL ����Ȃ��ꍇ

		// ���D�̕`�揈��
		m_pBalloon->Draw();
	}

	if (m_pRope != nullptr)
	{ // �R�� NULL ����Ȃ��ꍇ

		// �R�̕`�揈��
		m_pRope->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBalloon::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l��ݒ肷��
	m_pos = pos;	// �ʒu

	if (m_pBalloon == nullptr)
	{ // ���D�� NULL �̏ꍇ

		// ���D�𐶐�
		m_pBalloon = CModel::Create(TYPE_NONE, PRIORITY_ENTITY);

		// ���̐ݒ菈��
		m_pBalloon->SetPos(pos);
		m_pBalloon->SetPosOld(pos);
		m_pBalloon->SetRot(NONE_D3DXVECTOR3);
		m_pBalloon->SetScale(NONE_SCALE);
		m_pBalloon->SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
	}

	if (m_pRope == nullptr)
	{ // �R�� NULL �̏ꍇ

		// ���D�𐶐�
		m_pRope = CBalloonRope::Create(m_pBalloon->GetMatrixPoint());
	}
}

//=======================================
// �q�b�g����
//=======================================
void CBalloon::Hit(void)
{

}

//=======================================
// ��������
//=======================================
CBalloon* CBalloon::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBalloon* pTarget = nullptr;	// �C���X�^���X�𐶐�

	if (pTarget == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pTarget = new CBalloon;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTarget != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTarget->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTarget->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�̃|�C���^��Ԃ�
	return pTarget;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CBalloon*> CBalloon::GetList(void)
{
	// ���X�g�\���̏���Ԃ�
	return m_list;
}