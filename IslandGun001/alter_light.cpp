//============================================
//
// �Ւd�̌��̃��C������[alter_light.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "alter_light.h"
#include "renderer.h"
#include "texture.h"

//--------------------------------------------
// �萔��`
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 INIT_SIZE = D3DXVECTOR3(60.0f, 60.0f, 0.0f);		// �����T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\BossLight.png";				// �e�N�X�`��
}

//===========================================
// �R���X�g���N�^
//===========================================
CAlterLight::CAlterLight() : CBillboard(CObject::TYPE_ALTERLIGHT, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
}

//===========================================
// �f�X�g���N�^
//===========================================
CAlterLight::~CAlterLight()
{

}

//===========================================
// ����������
//===========================================
HRESULT CAlterLight::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CAlterLight::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CAlterLight::Update(void)
{
	// �T�C�Y���擾
	D3DXVECTOR3 size = GetSize();

	// �T�C�Y���g�傷��
	size.x += 5.0f;
	size.y += 5.0f;

	// �T�C�Y��K�p
	SetSize(size);

	// ���_���W�̐ݒ菈��
	SetVertex();

	// �X�V����
	CBillboard::Update();
}

//===========================================
// �`�揈��
//===========================================
void CAlterLight::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff(false);
}

//===========================================
// �ݒ菈��
//===========================================
void CAlterLight::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);				// �ʒu
	SetPosOld(pos);				// �O��̈ʒu
	SetRot(0.0f);				// ����
	SetSize(INIT_SIZE);			// �T�C�Y�ݒ�
	SetAngle();					// ����
	SetLength();				// ����
	SetEnableLookY(true);		// Y����

	// ���_���̐ݒ菈��
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//===========================================
// ��������
//===========================================
CAlterLight* CAlterLight::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAlterLight* pLight = nullptr;		// ���̃C���X�^���X�𐶐�

	if (pLight == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLight = new CAlterLight;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLight != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pLight->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLight->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���̃|�C���^��Ԃ�
	return pLight;
}