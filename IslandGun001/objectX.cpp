//============================================================
//
// X�t�@�C������ [xfile.cpp]
// Author�F��������
//
//============================================================
//************************************************************
// �C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "texture.h"

//------------------------------------------------------------
// �R���X�g��`
//------------------------------------------------------------
const char* CXFile::c_apModelData[CXFile::TYPE_MAX] =		// ���f���̖��O
{
	// ���o���f��
	"data\\MODEL\\Platform\\FracScrew.x",		// �l�W(�j��)
	"data\\MODEL\\Platform\\FracGear.x",		// ����(�j��)
	"data\\MODEL\\Platform\\FracRing.x",		// ��(�j��)
	"data\\MODEL\\Platform\\FracWood.x",		// �ؕ�(�j��)
	"data\\MODEL\\Platform\\Ripple.x",			// �g��

	// �Q�[�����f��
	"data\\MODEL\\Coin.x",				// ����
	"data\\MODEL\\Pistol.x",			// ���e
	"data\\MODEL\\Dagger.x",			// �_�K�[
	"data\\MODEL\\GoldBone.x",			// ���̍�
	"data\\MODEL\\PalmTree.x",			// ���V�̖�
	"data\\MODEL\\PalmFruit.x",			// ���V�̎�
	"data\\MODEL\\PalmItem.x",			// ���V�̎�(�A�C�e����)

	// �v���C���[���f��
	"data/MODEL/PlayerWaist.x",			// �v���C���[�̍�
	"data/MODEL/PlayerBody.x",			// �v���C���[�̑�
	"data/MODEL/PlayerNeck.x",			// �v���C���[�̎�
	"data/MODEL/PlayerCloak.x",			// �v���C���[�̃}���g
	"data/MODEL/PlayerHead.x",			// �v���C���[�̓�
	"data/MODEL/PlayerRArm.x",			// �v���C���[�̉E��r
	"data/MODEL/PlayerLArm.x",			// �v���C���[�̍���r
	"data/MODEL/PlayerRUpper.x",		// �v���C���[�̉E�r
	"data/MODEL/PlayerLUpper.x",		// �v���C���[�̍��r
	"data/MODEL/PlayerRHand.x",			// �v���C���[�̉E��
	"data/MODEL/PlayerLHand.x",			// �v���C���[�̍���
	"data/MODEL/PlayerRLeg.x",			// �v���C���[�̉E�r
	"data/MODEL/PlayerLLeg.x",			// �v���C���[�̍��r
	"data/MODEL/PlayerRShin.x",			// �v���C���[�̉E��
	"data/MODEL/PlayerLShin.x",			// �v���C���[�̍���
	"data/MODEL/PlayerRFoot.x",			// �v���C���[�̉E��
	"data/MODEL/PlayerLFoot.x",			// �v���C���[�̍���
};

//------------------------------------------------------------
// ���f���̏��
//------------------------------------------------------------
CXFile::SXFile CXFile::m_apModel[CXFile::TYPE_MAX] = {};

//============================================================
// �R���X�g���N�^
//============================================================
CXFile::CXFile()
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// ���f���̏�������������
		m_apModel[nCnt].pMesh = nullptr;			// ���b�V�� (���_���) �ւ̃|�C���^
		m_apModel[nCnt].pBuffMat = nullptr;			// �}�e���A���ւ̃|�C���^
		m_apModel[nCnt].dwNumMat = 0;				// �}�e���A���̐�
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// �ŏ��̒��_���W
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// �ő�̒��_���W
		m_apModel[nCnt].collsize = INIT_SIZE;		// �����蔻��̃T�C�Y
		m_apModel[nCnt].vtxPos = nullptr;			// ���_�̈ʒu
		m_apModel[nCnt].fRadius = 0.0f;				// ���a
		m_apModel[nCnt].nNumFace = 0;				// �ʂ̐�

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
		}
	}
}

//============================================================
// �f�X�g���N�^
//============================================================
CXFile::~CXFile()
{

}

//============================================================
// ���f���̏���������
//============================================================
HRESULT CXFile::Init(void)
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// ���f���̏�������������
		m_apModel[nCnt].pMesh = nullptr;			// ���b�V�� (���_���) �ւ̃|�C���^
		m_apModel[nCnt].pBuffMat = nullptr;			// �}�e���A���ւ̃|�C���^
		m_apModel[nCnt].dwNumMat = 0;				// �}�e���A���̐�
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// �ŏ��̒��_���W
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// �ő�̒��_���W
		m_apModel[nCnt].collsize = INIT_SIZE;		// �����蔻��̃T�C�Y
		m_apModel[nCnt].vtxPos = nullptr;			// ���_�̈ʒu
		m_apModel[nCnt].fRadius = 0.0f;				// ���a
		m_apModel[nCnt].nNumFace = 0;				// �ʂ̐�

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
		}
	}

	// x�t�@�C���̓ǂݍ���
	if (FAILED(LoadXFile()))
	{ // x�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����蔻��̍쐬
	SetCollision();

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(LoadTexture()))
	{ // �e�N�X�`���̓ǂݍ��݂Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
// ���f���̏I������
//============================================================
void CXFile::Uninit(void)
{
	// �e�N�X�`���̔j��
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pMesh) �� NULL ����Ȃ��ꍇ

			m_apModel[nCntModel].pMesh->Release();
			m_apModel[nCntModel].pMesh = nullptr;
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pBuffMat) �� NULL ����Ȃ��ꍇ

			m_apModel[nCntModel].pBuffMat->Release();
			m_apModel[nCntModel].pBuffMat = nullptr;
		}

		if (m_apModel[nCntModel].vtxPos != nullptr)
		{ // ���_���W (m_apModel[nCntModel].vtxPos) �� NULL ����Ȃ��ꍇ

			delete[] m_apModel[nCntModel].vtxPos;
			m_apModel[nCntModel].vtxPos = nullptr;
		}
	}

// �f�o�b�O���[�h
#ifdef _DEBUG

	// �e�N�X�`���̔j��
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pMesh) ��NULL�ł͂Ȃ��ꍇ

			// ��~
			assert(false);
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pBuffMat) ��NULL�ł͂Ȃ��ꍇ

			// ��~
			assert(false);
		}
	}

#endif
}

//============================================================
//	x�t�@�C���̓ǂݍ���
//============================================================
HRESULT CXFile::LoadXFile(void)
{
	// �ϐ���錾
	HRESULT hr;		// �ُ�I���̊m�F�p

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		// x�t�@�C���̓ǂݍ���
		hr = D3DXLoadMeshFromX
		( // ����
			c_apModelData[nCntModel],		// ���f���̑��΃p�X
			D3DXMESH_SYSTEMMEM,				// ���b�V���쐬�p�I�v�V����
			pDevice,						// �f�o�C�X�ւ̃|�C���^
			NULL,							// �אڐ��f�[�^
			&m_apModel[nCntModel].pBuffMat,	// �}�e���A���ւ̃|�C���^
			NULL,							// �G�t�F�N�g�f�[�^
			&m_apModel[nCntModel].dwNumMat,	// �}�e���A���̐�
			&m_apModel[nCntModel].pMesh		// ���b�V�� (���_���) �ւ̃|�C���^
		);

		if (FAILED(hr))
		{ // x�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�����蔻��̍쐬
//============================================================
void CXFile::SetCollision(void)
{
	// �ϐ���錾
	int         nNumVtx;		// ���f���̒��_��
	DWORD       dwSizeFVF;		// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y
	BYTE        *pVtxBuff;		// ���f���̒��_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;			// ���f���̒��_���W

	// �����蔻��̍쐬
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		// ���f���̒��_�����擾
		nNumVtx = m_apModel[nCntModel].pMesh->GetNumVertices();

		// ���_�ʒu�̃��������m�ۂ���
		m_apModel[nCntModel].vtxPos = new D3DXVECTOR3[nNumVtx];

		// ���f���̖ʂ̐����擾����
		m_apModel[nCntModel].nNumFace = m_apModel[nCntModel].pMesh->GetNumFaces();

		// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(m_apModel[nCntModel].pMesh->GetFVF());

		// ���f���̒��_�o�b�t�@�����b�N
		m_apModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{ // ���f���̒��_�����J��Ԃ�

			// ���f���̒��_���W����
			vtx = *(D3DXVECTOR3*)pVtxBuff;

			// ���_���W (x) �̐ݒ�
			if (vtx.x < m_apModel[nCntModel].vtxMin.x)
			{ // ����̒��_���W (x) ���A����̒��_���W (x) �����������ꍇ

				// ����̒��_��� (x) ����
				m_apModel[nCntModel].vtxMin.x = vtx.x;
			}
			else if (vtx.x > m_apModel[nCntModel].vtxMax.x)
			{ // ����̒��_���W (x) ���A����̒��_���W (x) �����傫���ꍇ

				// ����̒��_��� (x) ����
				m_apModel[nCntModel].vtxMax.x = vtx.x;
			}

			// ���_���W (y) �̐ݒ�
			if (vtx.y < m_apModel[nCntModel].vtxMin.y)
			{ // ����̒��_���W (y) ���A����̒��_���W (y) �����������ꍇ

				// ����̒��_��� (y) ����
				m_apModel[nCntModel].vtxMin.y = vtx.y;
			}
			else if (vtx.y > m_apModel[nCntModel].vtxMax.y)
			{ // ����̒��_���W (y) ���A����̒��_���W (y) �����傫���ꍇ

				// ����̒��_��� (y) ����
				m_apModel[nCntModel].vtxMax.y = vtx.y;
			}

			// ���_���W (z) �̐ݒ�
			if (vtx.z < m_apModel[nCntModel].vtxMin.z)
			{ // ����̒��_���W (z) ���A����̒��_���W (z) �����������ꍇ

				// ����̒��_��� (z) ����
				m_apModel[nCntModel].vtxMin.z = vtx.z;
			}
			else if (vtx.z > m_apModel[nCntModel].vtxMax.z)
			{ // ����̒��_���W (z) ���A����̒��_���W (z) �����傫���ꍇ

				// ����̒��_��� (z) ����
				m_apModel[nCntModel].vtxMax.z = vtx.z;
			}

			// ���_�̈ʒu��ݒ肷��
			m_apModel[nCntModel].vtxPos[nCntVtx] = vtx;

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += dwSizeFVF;
		}

		// ���f���̒��_�o�b�t�@���A�����b�N
		m_apModel[nCntModel].pMesh->UnlockVertexBuffer();

		// ���f���T�C�Y�����߂�
		m_apModel[nCntModel].collsize = m_apModel[nCntModel].vtxMax - m_apModel[nCntModel].vtxMin;

		// ���f���̉~�̓����蔻����쐬
		m_apModel[nCntModel].fRadius = ((m_apModel[nCntModel].collsize.x * 0.5f) + (m_apModel[nCntModel].collsize.z * 0.5f)) * 0.5f;
	}
}

//============================================================
//	�e�N�X�`���̓ǂݍ���
//============================================================
HRESULT CXFile::LoadTexture(void)
{
	// �f�o�C�X���擾����
	D3DXMATERIAL     *pMat;						// �}�e���A���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���Ɏg�p���郂�f���̍ő吔���J��Ԃ�

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_apModel[nCntModel].dwNumMat; nCntMat++)
		{ // �}�e���A���̐����J��Ԃ�

			if (pMat[nCntMat].pTextureFilename != nullptr)
			{ // �e�N�X�`���t�@�C�������݂���ꍇ

				// �e�N�X�`���̓ǂݍ��ݏ���
				m_apModel[nCntModel].m_nTexIdx[nCntMat] = CManager::Get()->GetTexture()->Regist(pMat[nCntMat].pTextureFilename);
			}
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
// X�t�@�C���̎擾����
//============================================================
CXFile::SXFile CXFile::GetXFile(TYPE type)
{
	if (type >= 0 && type < TYPE_MAX)
	{ // ��ނ��K����̏ꍇ

		// ���f���̏���Ԃ�
		return m_apModel[type];
	}
	else
	{ // ��ނ��K��O�̏ꍇ

		// ��~
		assert(false);

		// 0�Ԗڂ�Ԃ�
		return m_apModel[0];
	}
}