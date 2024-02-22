//============================================
//
// �Ŕ̐�������[signboard_explain.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "signboard_explain.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �萔��`
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 SCREEN_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �w�i�̈ʒu
	const D3DXVECTOR3 SCREEN_SIZE = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �w�i�̃T�C�Y
	const D3DXVECTOR3 EXPLAIN_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -200.0f, 0.0f);					// �����̈ʒu
	const D3DXVECTOR3 EXPLAIN_SIZE = D3DXVECTOR3(200.0f, 200.0f, 0.0f);									// �����̃T�C�Y
	const char* EXPLAIN_TEXTURE[CSignboard::TYPE_MAX] = 	// �����̃e�N�X�`��
	{
		""
	};
	const D3DXCOLOR SCREEN_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �w�i�̐F
	const float SCREEN_ADD_ALPHA = 0.01f;			// �w�i�̓����x�̉��Z��
	const float SCREEN_MAX_ALPHA = 0.5f;			// �w�i�̓����x�̍ő吔
}

//============================
// �R���X�g���N�^
//============================
CSignboardExpl::CSignboardExpl() : CObject(CObject::TYPE_SIGNEXPLAIN, DIM_2D, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_screen.pScreen = nullptr;		// ��ʂ̏��
	m_screen.fAlpha = 0.0f;			// �����x
	m_pExplain = nullptr;			// �����̃|���S��
}

//============================
// �f�X�g���N�^
//============================
CSignboardExpl::~CSignboardExpl()
{

}

//============================
// ����������
//============================
HRESULT CSignboardExpl::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CSignboardExpl::Uninit(void)
{
	if (m_screen.pScreen != nullptr)
	{ // �w�i�� NULL ����Ȃ��ꍇ

		// �w�i�̏I������
		m_screen.pScreen->Uninit();
		m_screen.pScreen = nullptr;
	}

	if (m_pExplain != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// �����̏I������
		m_pExplain->Uninit();
		m_pExplain = nullptr;
	}

	// �j������
	Release();
}

//============================
// �X�V����
//============================
void CSignboardExpl::Update(void)
{
	// �ϓ��ȕ␳����
	useful::FrameCorrect(SCREEN_MAX_ALPHA, &m_screen.fAlpha, SCREEN_ADD_ALPHA);

	D3DXVECTOR3 pos = m_pExplain->GetPos();

	useful::FrameCorrect(SCREEN_HEIGHT * 0.5f, &pos.y, 10.0f);

	m_pExplain->SetPos(pos);

	// ���_�J���[�̐ݒ菈��
	m_screen.pScreen->SetVtxColor(D3DXCOLOR(SCREEN_COL.r, SCREEN_COL.g, SCREEN_COL.b, m_screen.fAlpha));
}

//============================
// �`�揈��
//============================
void CSignboardExpl::Draw(void)
{
	if (m_screen.pScreen != nullptr)
	{ // �w�i�� NULL ����Ȃ��ꍇ

		// �w�i�̕`�揈��
		m_screen.pScreen->Draw();
	}

	if (m_pExplain != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// �����̕`�揈��
		m_pExplain->Draw();
	}
}

//============================
// ���̐ݒ菈��
//============================
void CSignboardExpl::SetData(const CSignboard::TYPE type)
{
	if (m_screen.pScreen == nullptr)
	{ // �w�i�� NULL �̏ꍇ

		// �w�i�𐶐�
		m_screen.pScreen = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

		// ���̐ݒ菈��
		m_screen.pScreen->SetPos(SCREEN_POS);		// �ʒu
		m_screen.pScreen->SetPosOld(SCREEN_POS);	// �O��̈ʒu
		m_screen.pScreen->SetRot(NONE_D3DXVECTOR3);	// ����
		m_screen.pScreen->SetSize(SCREEN_SIZE);		// �T�C�Y
		m_screen.pScreen->SetAngle();				// ����
		m_screen.pScreen->SetLength();				// ����

		// ���_���W�̐ݒ菈��
		m_screen.pScreen->SetVertex();

		// ���_�J���[�̐ݒ菈��
		m_screen.pScreen->SetVtxColor(D3DXCOLOR(SCREEN_COL.r, SCREEN_COL.g, SCREEN_COL.b, m_screen.fAlpha));
	}
	m_screen.fAlpha = 0.0f;

	if (m_pExplain != nullptr)
	{ // ������ NULL �̏ꍇ

		// �����𐶐�
		m_pExplain = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

		// ���̐ݒ菈��
		m_pExplain->SetPos(EXPLAIN_POS);		// �ʒu
		m_pExplain->SetPosOld(EXPLAIN_POS);		// �O��̈ʒu
		m_pExplain->SetRot(NONE_D3DXVECTOR3);	// ����
		m_pExplain->SetSize(EXPLAIN_SIZE);		// �T�C�Y
		m_pExplain->SetAngle();					// ����
		m_pExplain->SetLength();				// ����

		// �e�N�X�`���̐ݒ菈��
		m_pExplain->BindTexture(CManager::Get()->GetTexture()->Regist(EXPLAIN_TEXTURE[type]));

		// ���_���W�̐ݒ菈��
		m_pExplain->SetVertex();
	}
}

//============================
//��������
//============================
CSignboardExpl* CSignboardExpl::Create(const CSignboard::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSignboardExpl* pExplain = nullptr;			// �����̃C���X�^���X�𐶐�

	if (pExplain == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pExplain = new CSignboardExpl;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pExplain != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pExplain->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pExplain->SetData(type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �����̃|�C���^��Ԃ�
	return pExplain;
}