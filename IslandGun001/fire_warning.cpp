//============================================
//
// �����ӂ̃��C������[fire_warning.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "fire_warning.h"
#include "renderer.h"
#include "manager.h"
#include "useful.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const int NUM_ANGLE = 8;		// �p�x�̐�
	const float RADIUS = 200.0f;	// ���a
	const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);		// �F�̏����l
	const float INIT_COL_ANGLE = D3DX_PI;	// �F�̌����̏����l
	const float ADD_COL_ANGLE = 0.005f;		// �F�̌����̉��Z��
}

//=========================================
// �R���X�g���N�^
//=========================================
CFireWarning::CFireWarning() : CObject3DFan(TYPE_FIREWARNING, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_col = INIT_COL;				// �F
	m_fColAngle = INIT_COL_ANGLE;	// �F�̌���
	m_fAddColAngle = 0.0f;			// �F�̌����̉��Z��
}

//=========================================
// �f�X�g���N�^
//=========================================
CFireWarning::~CFireWarning()
{

}

//===========================================
// �I�u�W�F�N�g3D�̏���������
//===========================================
HRESULT CFireWarning::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �I�u�W�F�N�g3D�̏I������
//===========================================
void CFireWarning::Uninit(void)
{
	// �I������
	CObject3DFan::Uninit();
}

//===========================================
// �I�u�W�F�N�g3D�̍X�V����
//===========================================
void CFireWarning::Update(void)
{
	// �F��ݒ肷��
	m_fAddColAngle += ADD_COL_ANGLE;
	m_fColAngle += m_fAddColAngle;
	useful::RotNormalize(&m_fColAngle);
	m_col.g = sinf(m_fColAngle) * INIT_COL.g;
	
	// ���_�̐ݒ菈��
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(m_col);
}

//===========================================
// �I�u�W�F�N�g3D�̕`�揈��
//===========================================
void CFireWarning::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Z�e�X�g�̗L��/�����ݒ�

	// �`�揈��
	CObject3DFan::Draw();

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�e�X�g�̗L��/�����ݒ�
}

//===========================================
// ���̐ݒ菈��
//===========================================
void CFireWarning::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetNumAngle(NUM_ANGLE);			// �p�x�̑���
	SetRadius(RADIUS);				// ���a

	// �S�Ă̒l��ݒ肷��
	m_col = INIT_COL;				// �F
	m_fColAngle = INIT_COL_ANGLE;	// �F�̌���
	m_fAddColAngle = 0.0f;			// �F�̌����̉��Z��
}

//===========================================
// ��������
//===========================================
CFireWarning* CFireWarning::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFireWarning* pWarning = nullptr;	// �����ӂ̃C���X�^���X�𐶐�

	if (pWarning == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pWarning = new CFireWarning;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pWarning != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pWarning->SetData(pos);

		// ����������
		if (FAILED(pWarning->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �����ӂ̃|�C���^��Ԃ�
	return pWarning;
}