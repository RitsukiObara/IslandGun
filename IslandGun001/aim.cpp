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
	const float RADIUS = 40.0f;		// ���a
	const float SHIFT = 100.0f;		// ���炷��
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
void CAim::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
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
	SetAim(pos, rot);

	// ���_���̏�����
	SetVertex();
}

//=========================
// ��������
//=========================
CAim* CAim::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
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
		pAim->SetData(pos, rot);
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
void CAim::SetAim(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// �G�C���̈ʒu��錾����
	D3DXVECTOR3 posAim;

	// �ʒu��ݒ肷��
	posAim.x = pos.x + sinf(rot.y) * SHIFT;
	posAim.y = pos.y + cosf(rot.x) * SHIFT;
	posAim.z = pos.z + cosf(rot.y) * SHIFT;

	// �ʒu��K�p����
	SetPos(posAim);

	// ���_���̏�����
	SetVertex();
}