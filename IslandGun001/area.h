//===================================
//
// エリアヘッダー[area.h]
// Author 小原立暉
//
//===================================
#ifndef _AREA_H_
#define _AREA_H_

//-----------------------------------
// 名前空間(エリア)
//-----------------------------------
namespace area
{
	// 関数
	int SetFieldIdx(const D3DXVECTOR3& pos);		// 区分の設定処理
	bool IndexCheck(const int nIdx);				// 番号の判定処理

	// 定数定義
	const int NUM_AREA = 32;		// 区分の数
	const D3DXVECTOR3 AREA_RANGE[NUM_AREA][2] =		// それぞれのエリアの範囲
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
	const int NUM_COLL = 9;			// 当たり判定を通す回数
	const int COLL_ADD_IDX[NUM_COLL] =			// 当たり判定の時の番号の加算数
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