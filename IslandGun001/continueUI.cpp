//============================================
//
// �R���e�B�j���[UI����[continueUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "continueUI.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "object2D.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const char* TEXTURE[CContinueUI::TYPE_MAX] =
	{
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
		"data\\TEXTURE\\",
	};
	const D3DXVECTOR3 POS[CContinueUI::TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f),
		D3DXVECTOR3(390.0f,450.0f,0.0f),
		D3DXVECTOR3(890.0f,450.0f,0.0f),
	};
	const D3DXVECTOR3 POLY_SIZE[CContinueUI::TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(500.0f,300.0f,0.0f),
		D3DXVECTOR3(450.0f,100.0f,0.0f),
		D3DXVECTOR3(100.0f,50.0f,0.0f),
		D3DXVECTOR3(100.0f,50.0f,0.0f),
	};
}

//========================
// �R���X�g���N�^
//========================
CContinueUI::CContinueUI() : CObject(TYPE_CONTINUEUI, DIM_2D, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;		// �|���S���̏��
	}
}

//========================
// �f�X�g���N�^
//========================
CContinueUI::~CContinueUI()
{

}

//========================
// ����������
//========================
HRESULT CContinueUI::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CContinueUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // �|���S���̏�� NULL ����Ȃ��ꍇ

			// �|���S���̏I������
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CContinueUI::Update(void)
{

}

//========================
// �`�揈��
//========================
void CContinueUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apObject[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CContinueUI::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // �|���S���� NULL ����Ȃ��ꍇ

			// �|���S���𐶐�
			m_apObject[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// �ݒ菈��
			m_apObject[nCnt]->SetPos(POS[nCnt]);			// �ʒu
			m_apObject[nCnt]->SetPosOld(POS[nCnt]);			// �O��̈ʒu
			m_apObject[nCnt]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apObject[nCnt]->SetSize(POLY_SIZE[nCnt]);		// �T�C�Y
			m_apObject[nCnt]->SetAngle();					// ����
			m_apObject[nCnt]->SetLength();					// ����

			// �e�N�X�`���̊��蓖�ď���
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE[nCnt]));

			// ���_���W�̐ݒ菈��
			m_apObject[nCnt]->SetVertex();

			switch (nCnt)
			{
			case TYPE::TYPE_SCREEN:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

				break;

			case TYPE::TYPE_GROUND:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				break;

			case TYPE::TYPE_QUERY:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

				break;

			case TYPE::TYPE_YES:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

				break;

			case TYPE::TYPE_NO:

				m_apObject[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				break;
			}
		}
	}
}

//========================
// ��������
//========================
CContinueUI* CContinueUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CContinueUI* pUI = nullptr;			// UI�̃C���X�^���X�𐶐�

	if (pUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pUI = new CContinueUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pUI->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// UI�̃|�C���^��Ԃ�
	return pUI;
}