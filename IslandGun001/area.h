//===================================
//
// �G���A�w�b�_�[[area.h]
// Author ��������
//
//===================================
#ifndef _AREA_H_
#define _AREA_H_

//-----------------------------------
// ���O���(�G���A)
//-----------------------------------
namespace area
{
	// �֐�
	int SetFieldIdx(const D3DXVECTOR3& pos);		// �敪�̐ݒ菈��
	bool IndexCheck(const int nIdx);				// �ԍ��̔��菈��

	// �萔��`
	const int NUM_AREA = 32;		// �敪�̐�
	const D3DXVECTOR3 AREA_RANGE[NUM_AREA][2] =		// ���ꂼ��̃G���A�͈̔�
	{
		{D3DXVECTOR3(-8000.0f,0.0f,6000.0f),D3DXVECTOR3(-4000.0f,0.0f,8000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,6000.0f),D3DXVECTOR3(0.0f,0.0f,8000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,6000.0f),D3DXVECTOR3(4000.0f,0.0f,8000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,6000.0f),D3DXVECTOR3(8000.0f,0.0f,8000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,4000.0f),D3DXVECTOR3(-4000.0f,0.0f,6000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,4000.0f),D3DXVECTOR3(0.0f,0.0f,6000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,4000.0f),D3DXVECTOR3(4000.0f,0.0f,6000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,4000.0f),D3DXVECTOR3(8000.0f,0.0f,6000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,2000.0f),D3DXVECTOR3(-4000.0f,0.0f,4000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,2000.0f),D3DXVECTOR3(0.0f,0.0f,4000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,2000.0f),D3DXVECTOR3(4000.0f,0.0f,4000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,2000.0f),D3DXVECTOR3(8000.0f,0.0f,4000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,0.0f),D3DXVECTOR3(-4000.0f,0.0f,2000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,2000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(4000.0f,0.0f,2000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,0.0f),D3DXVECTOR3(8000.0f,0.0f,2000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,-2000.0f),D3DXVECTOR3(-4000.0f,0.0f,0.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,-2000.0f),D3DXVECTOR3(0.0f,0.0f,0.0f)},
		{D3DXVECTOR3(0.0f,0.0f,-2000.0f),D3DXVECTOR3(4000.0f,0.0f,0.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,-2000.0f),D3DXVECTOR3(8000.0f,0.0f,0.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,-4000.0f),D3DXVECTOR3(-4000.0f,0.0f,-2000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,-4000.0f),D3DXVECTOR3(0.0f,0.0f,-2000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,-4000.0f),D3DXVECTOR3(4000.0f,0.0f,-2000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,-4000.0f),D3DXVECTOR3(8000.0f,0.0f,-2000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,-6000.0f),D3DXVECTOR3(-4000.0f,0.0f,-4000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,-6000.0f),D3DXVECTOR3(0.0f,0.0f,-4000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,-6000.0f),D3DXVECTOR3(4000.0f,0.0f,-4000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,-6000.0f),D3DXVECTOR3(8000.0f,0.0f,-4000.0f)},

		{D3DXVECTOR3(-8000.0f,0.0f,-8000.0f),D3DXVECTOR3(-4000.0f,0.0f,-6000.0f)},
		{D3DXVECTOR3(-4000.0f,0.0f,-8000.0f),D3DXVECTOR3(0.0f,0.0f,-6000.0f)},
		{D3DXVECTOR3(0.0f,0.0f,-8000.0f),D3DXVECTOR3(4000.0f,0.0f,-6000.0f)},
		{D3DXVECTOR3(4000.0f,0.0f,-8000.0f),D3DXVECTOR3(8000.0f,0.0f,-6000.0f)},
	};
	const int NUM_COLL = 9;			// �����蔻���ʂ���
	const int COLL_ADD_IDX[NUM_COLL] =			// �����蔻��̎��̔ԍ��̉��Z��
	{
		-5,
		-4,
		-3,
		-1,
		0,
		1,
		3,
		4,
		5,
	};
}

#endif