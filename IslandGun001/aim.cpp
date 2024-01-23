//=======================================
//
// エイムのメイン処理[aim.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "aim.h"
#include "texture.h"
#include "collision.h"
#include "useful.h"

#include "enemy.h"

//---------------------------------------
// 無名名前空間
//---------------------------------------
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\Aim.png";		// テクスチャ
	const float RADIUS = 80.0f;		// 半径
	const float ROT_MOVE = 0.01f;	// 向きの移動量
	const D3DXCOLOR HIT_COL = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);		// 敵に照準が合っている時の色
}

//=========================
// コンストラクタ
//=========================
CAim::CAim() : CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
}

//=========================
// デストラクタ
//=========================
CAim::~CAim()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CAim::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CAim::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CAim::Update(void)
{
	// 向きを取得する
	float fRot = GetRot();

	// 向きを加算する
	fRot += ROT_MOVE;

	// 向きの正規化
	useful::RotNormalize(&fRot);

	// 向きを適用する
	SetRot(fRot);

	// 頂点座標の設定処理
	SetVertexRot();

	// 敵との当たり判定処理
	EnemyCollision();
}

//=========================
// 描画処理
//=========================
void CAim::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff(false);
}

//=========================
// 情報の設定処理
//=========================
void CAim::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetRot(0.0f);			// 向き
	SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	// サイズ
	SetAngle();				// 方向の設定処理
	SetLength();			// 長さの設定処理
	SetEnableLookY(true);	// Y軸状況

	// エイムの設置処理
	SetAim(pos);

	// 頂点情報の初期化
	SetVertexRot();

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// 生成処理
//=========================
CAim* CAim::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CAim* pAim = nullptr;	// エイムのインスタンスを生成

	if (pAim == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pAim = new CAim;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAim != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAim->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAim->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エイムのポインタを返す
	return pAim;
}

//=========================
// エイムの設置処理
//=========================
void CAim::SetAim(const D3DXVECTOR3& pos)
{
	// エイムの位置を宣言する
	D3DXVECTOR3 posAim;

	// 位置を設定する
	posAim = pos;

	// 位置を適用する
	SetPos(posAim);

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 敵との当たり判定
//=========================
void CAim::EnemyCollision(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を適用する
	D3DXVECTOR3 size = GetSize();	// サイズを適用する
	D3DXVECTOR3 posEnemy = NONE_D3DXVECTOR3;	// 敵の位置を適用する
	CListManager<CEnemy*> list = CEnemy::GetList();		// 敵のリスト
	CEnemy* pEnemy = nullptr;		// 先頭の敵
	CEnemy* pEnemyEnd = nullptr;	// 末尾の値
	int nIdx = 0;					// 敵の番号
	bool bColl = false;				// 当たり判定状況

	// while文処理
	if (list.IsEmpty() == false)
	{ // 空白じゃない場合

		// 先頭の値を取得する
		pEnemy = list.GetTop();

		// 末尾の値を取得する
		pEnemyEnd = list.GetEnd();

		while (true)
		{ // 無限ループ

			// 敵の位置を取得する
			posEnemy = pEnemy->GetPos();

			if (useful::CircleCollisionXZ(pos, posEnemy, size.x, pEnemy->GetCollSize().x) == true &&
				pos.y >= posEnemy.y &&
				pos.y <= posEnemy.y + pEnemy->GetCollSize().y)
			{ // 敵と重なった場合

				// 当たり判定状況を true にする
				bColl = true;

				break;
			}

			if (pEnemy == pEnemyEnd)
			{ // 末尾に達した場合

				// while文を抜け出す
				break;
			}

			// 次のオブジェクトを代入する
			pEnemy = list.GetData(nIdx + 1);

			// インデックスを加算する
			nIdx++;
		}
	}

	if (bColl == true)
	{ // 当たっている場合

		// 色を付ける
		SetVtxColor(HIT_COL);
	}
	else
	{ // 上記以外

		// 色を通常に戻す
		SetVtxColor(NONE_D3DXCOLOR);
	}
}