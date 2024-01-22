//=======================================
//
// �G�C���̃��C������[aim.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "aim.h"
#include "texture.h"
#include "useful.h"

// �������O���
namespace
{
	const float RADIUS = 80.0f;		// ���a
	const char* TEXTURE = "data\\TEXTURE\\Aim.png";		// �e�N�X�`��
}

//=========================
// �R���X�g���N�^
//=========================
CAim::CAim() : CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
}

//=========================
// �f�X�g���N�^
//=========================
CAim::~CAim()
{

}

//=========================
// ����������
//=========================
HRESULT CAim::Init(void)
{
	if (FAILED(CBillboard::Init()))
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
void CAim::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CAim::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CAim::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff(true);
}

//=========================
// ���̐ݒ菈��
//=========================
void CAim::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(0.0f);			// ����
	SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	// �T�C�Y
	SetAngle();				// �����̐ݒ菈��
	SetLength();			// �����̐ݒ菈��
	SetEnableLookY(true);	// Y����

	// �G�C���̐ݒu����
	SetAim(pos);

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// ��������
//=========================
CAim* CAim::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAim* pAim = nullptr;	// �G�C���̃C���X�^���X�𐶐�

	if (pAim == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pAim = new CAim;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAim != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAim->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAim->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G�C���̃|�C���^��Ԃ�
	return pAim;
}

//=========================
// �G�C���̐ݒu����
//=========================
void CAim::SetAim(const D3DXVECTOR3& pos)
{
	// �G�C���̈ʒu��錾����
	D3DXVECTOR3 posAim;

	// �ʒu��ݒ肷��
	posAim = pos;

	// �ʒu��K�p����
	SetPos(posAim);

	// ���_���̏�����
	SetVertex();
}