//===========================================
//
// ���e�̔����̃��C������[bomb_explosion.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "bomb_explosion.h"
#include "texture.h"
#include "useful.h"

#include "mesh_tornado.h"
#include "rock.h"

//-------------------------------------------
// �萔��`
//-------------------------------------------
namespace
{
	const char* BOMB_TEXTURE = "data\\TEXTURE\\BombExplosion.png";		// �����̃e�N�X�`��
	const int DIVI_CIRCUM = 16;				// �����̉~���̕�����
	const int DIVI_HEIGHT = 16;				// �����̏c�̕�����
	const float CIRCUM = 100.0f;			// �~���̑傫��
	const float HEIGHT = 100.0f;			// �c�̑傫��

	const float EXTEND_SCALE = 40.0f;		// �g���Ԃ̃X�P�[�����Z��
	const int SUB_ALPHA_COUNT = 15;			// �����x�����Z���n�߂�J�E���g��

	const float CLEAR_SCALE = 20.0f;		// ��������Ԃ̃X�P�[�����Z��
	const float SUB_ALPHA = 0.15f;			// �����x�̌��Z��
	const int DEATH_COUNT = 5;				// �����܂ł̃J�E���g��
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CBombExplosion*> CBombExplosion::m_list = {};			// ���X�g

//==============================
// �R���X�g���N�^
//==============================
CBombExplosion::CBombExplosion() : CMeshSphere(PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pSmoke = nullptr;		// ���̏��
	m_state = STATE_EXTEND;	// ���
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_fAlpha = 0.0f;		// �����x

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//==============================
// �f�X�g���N�^
//==============================
CBombExplosion::~CBombExplosion()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CBombExplosion::Init(void)
{
	if (FAILED(CMeshSphere::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ��ނ𔚔��ɐݒ�
	CObject::SetType(TYPE_BOMBEXPLOSION);

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CBombExplosion::Uninit(void)
{
	if (m_pSmoke != nullptr)
	{ // ���� NULL ����Ȃ��ꍇ

		// �I������
		m_pSmoke->Uninit();
		m_pSmoke = nullptr;
	}

	// �I������
	CMeshSphere::Uninit();

	// ������������
	m_list.Pull(this);
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CBombExplosion::Update(void)
{
	// �J�E���g�����Z����
	m_nStateCount++;

	switch (m_state)
	{
	case CBombExplosion::STATE_EXTEND:

		// �g�又��
		AddScale(EXTEND_SCALE);

		if (m_nStateCount >= SUB_ALPHA_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// ��������Ԃɂ���
			m_state = STATE_CLEAR;

			// ��ԃJ�E���g�����Z�b�g
			m_nStateCount = 0;
		}

		break;

	case CBombExplosion::STATE_CLEAR:

		// �g�又��
		AddScale(CLEAR_SCALE);

		// �����x��������
		m_fAlpha -= SUB_ALPHA;

		// �F�̐ݒ菈��
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

		if (m_nStateCount >= DEATH_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// ��̓����蔻��
			RockHit();

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CBombExplosion::Draw(void)
{
	// �`�揈��
	CMeshSphere::Draw();

	if (m_pSmoke != nullptr)
	{ // ���ΐ��� NULL ����Ȃ��ꍇ

		// ���ΐ��̕`�揈��
		m_pSmoke->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBombExplosion::SetData(const D3DXVECTOR3& pos)
{
	SGrid gridBomb;
	//SGrid gridSmoke;

	// �������ݒ肷��
	gridBomb.nWidth = DIVI_CIRCUM;
	gridBomb.nHeight = DIVI_HEIGHT;

	// ���̐ݒ菈��
	CMeshSphere::SetData(pos, NONE_D3DXVECTOR3, CIRCUM, HEIGHT, gridBomb);

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));

	SetLighting(true);		// ���C�e�B���O��
	SetCulling(true);		// �J�����O��

	// �S�Ă̒l��ݒ肷��
	//m_pSmoke = CMeshTornado::Create()		// ���̏��
	m_state = STATE_EXTEND;					// ���
	m_nStateCount = 0;						// ��ԃJ�E���g
	m_fAlpha = 1.0f;						// �����x

	// ��̓����蔻��
	RockHit();
}

//=======================================
// ��������
//=======================================
CBombExplosion* CBombExplosion::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBombExplosion* pBomb = nullptr;			// ���e�Ԃ𐶐�

	if (pBomb == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �u���b�N�𐶐�����
		pBomb = new CBombExplosion;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBomb != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pBomb->SetData(pos);

		// ����������
		if (FAILED(pBomb->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���e�̃|�C���^��Ԃ�
	return pBomb;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CBombExplosion*> CBombExplosion::GetList(void)
{
	// ���X�g�}�l�[�W���[��Ԃ�
	return m_list;
}

//=======================================
// �g�又��
//=======================================
void CBombExplosion::AddScale(const float fAdd)
{
	// ���E�������擾
	float fCircum = GetCircum();
	float fHeight = GetHeight();

	// �����L����
	fCircum += fAdd;
	fHeight += fAdd;

	// ���ʂ�K�p
	SetCircum(fCircum);
	SetHeight(fHeight);
}

//=======================================
// ��̓����蔻��
//=======================================
void CBombExplosion::RockHit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾
	float fRadius = GetCircum();		// �~�����擾
	float fHeight = GetHeight();		// �������擾

	D3DXVECTOR3 posRock = NONE_D3DXVECTOR3;		// ��̈ʒu
	float fRadiusRock = 0.0f;					// ��̔��a
	float fTopRock = 0.0f;						// ��̏�̍���
	float fBottomRock = 0.0f;					// ��̉��̍���

	CListManager<CRock*> list = CRock::GetList();
	CRock* pRock = nullptr;			// �擪�̒l
	CRock* pRockEnd = nullptr;		// �����̒l
	int nIdx = 0;

	if (list.IsEmpty() == false)
	{ // �󔒂���Ȃ��ꍇ

		// �擪�̒l���擾����
		pRock = list.GetTop();

		// �����̒l���擾����
		pRockEnd = list.GetEnd();

		while (true)
		{ // �������[�v

			if (pRock->GetType() == CRock::TYPE_BREAK)
			{ // �j��ł����̏ꍇ

				// ��̈ʒu���擾����
				posRock = pRock->GetPos();

				// ��̔��a���擾����
				fRadiusRock = pRock->GetRadius();

				// ��̏�̍������擾����
				fTopRock = pRock->GetTopHeight();

				// ��̉��̍������擾����
				fBottomRock = pRock->GetBottomHeight();

				if (pos.y <= posRock.y + fTopRock &&
					pos.y + fHeight >= posRock.y + fBottomRock &&
					useful::CircleCollisionXZ(pos, posRock, fRadius, fRadiusRock) == true)
				{ // �͈͓��ɂ����ꍇ

					// �j�󏈗�
					pRock->Break();
				}
			}

			if (pRock == pRockEnd)
			{ // �����ɒB�����ꍇ

				// while���𔲂��o��
				break;
			}

			// ���̃I�u�W�F�N�g��������
			pRock = list.GetData(nIdx + 1);

			// �C���f�b�N�X�����Z����
			nIdx++;
		}
	}
}