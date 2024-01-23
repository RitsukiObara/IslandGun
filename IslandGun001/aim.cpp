//=======================================
//
// �G�C���̃��C������[aim.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "aim.h"
#include "texture.h"
#include "collision.h"
#include "useful.h"

#include "enemy.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Aim.png";		// �e�N�X�`��
	const float RADIUS = 80.0f;		// ���a
	const float ROT_MOVE = 0.01f;	// �����̈ړ���
	const D3DXCOLOR HIT_COL = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);		// �G�ɏƏ��������Ă��鎞�̐F
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
	// �������擾����
	float fRot = GetRot();

	// ���������Z����
	fRot += ROT_MOVE;

	// �����̐��K��
	useful::RotNormalize(&fRot);

	// ������K�p����
	SetRot(fRot);

	// ���_���W�̐ݒ菈��
	SetVertexRot();

	// �G�Ƃ̓����蔻�菈��
	EnemyCollision();
}

//=========================
// �`�揈��
//=========================
void CAim::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff(false);
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
	SetVertexRot();

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

//=========================
// �G�Ƃ̓����蔻��
//=========================
void CAim::EnemyCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu��K�p����
	D3DXVECTOR3 size = GetSize();	// �T�C�Y��K�p����
	D3DXVECTOR3 posEnemy = NONE_D3DXVECTOR3;	// �G�̈ʒu��K�p����
	CListManager<CEnemy*> list = CEnemy::GetList();		// �G�̃��X�g
	CEnemy* pEnemy = nullptr;		// �擪�̓G
	CEnemy* pEnemyEnd = nullptr;	// �����̒l
	int nIdx = 0;					// �G�̔ԍ�
	bool bColl = false;				// �����蔻���

	// while������
	if (list.IsEmpty() == false)
	{ // �󔒂���Ȃ��ꍇ

		// �擪�̒l���擾����
		pEnemy = list.GetTop();

		// �����̒l���擾����
		pEnemyEnd = list.GetEnd();

		while (true)
		{ // �������[�v

			// �G�̈ʒu���擾����
			posEnemy = pEnemy->GetPos();

			if (useful::CircleCollisionXZ(pos, posEnemy, size.x, pEnemy->GetCollSize().x) == true &&
				pos.y >= posEnemy.y &&
				pos.y <= posEnemy.y + pEnemy->GetCollSize().y)
			{ // �G�Əd�Ȃ����ꍇ

				// �����蔻��󋵂� true �ɂ���
				bColl = true;

				break;
			}

			if (pEnemy == pEnemyEnd)
			{ // �����ɒB�����ꍇ

				// while���𔲂��o��
				break;
			}

			// ���̃I�u�W�F�N�g��������
			pEnemy = list.GetData(nIdx + 1);

			// �C���f�b�N�X�����Z����
			nIdx++;
		}
	}

	if (bColl == true)
	{ // �������Ă���ꍇ

		// �F��t����
		SetVtxColor(HIT_COL);
	}
	else
	{ // ��L�ȊO

		// �F��ʏ�ɖ߂�
		SetVtxColor(NONE_D3DXCOLOR);
	}
}