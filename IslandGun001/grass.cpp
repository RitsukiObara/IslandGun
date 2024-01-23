//=======================================
//
// ������[grass.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "grass.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Grass001.png";		// �e�N�X�`��
}

//---------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------
CListManager<CGrass*> CGrass::m_list = {};		// ���X�g

//=========================
// �R���X�g���N�^
//=========================
CGrass::CGrass() : CObject3D(CObject::TYPE_CONFETTI, CObject::PRIORITY_BLOCK)
{
	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//=========================
// �f�X�g���N�^
//=========================
CGrass::~CGrass()
{

}

//=========================
// ����������
//=========================
HRESULT CGrass::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CGrass::Uninit(void)
{
	// �I��
	CObject3D::Uninit();

	// ������������
	m_list.Pull(this);
}

//=========================
// �X�V����
//=========================
void CGrass::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CGrass::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �J�����O�̐ݒ��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`�揈��
	CObject3D::DrawLightOff();

	// �J�����O�̐ݒ��ON�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// ���̐ݒ菈��
//=========================
void CGrass::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);					// �ʒu�ݒ�
	SetPosOld(pos);					// �ʒu�ݒ�
	SetRot(rot);					// �����ݒ�
	SetSize(size);					// �T�C�Y�ݒ�

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// ��������
//=========================
CGrass* CGrass::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CGrass* pGrass = nullptr;	// ���̃C���X�^���X�𐶐�

	if (pGrass == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pGrass = new CGrass;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pGrass != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pGrass->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pGrass->SetData(pos, rot, size);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���̃|�C���^��Ԃ�
	return pGrass;
}

//=========================
// ���X�g�̎擾����
//=========================
CListManager<CGrass*> CGrass::GetList(void)
{
	// ���X�g�}�l�[�W���[��Ԃ�
	return m_list;
}