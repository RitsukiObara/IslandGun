//===================================
//
// ヤシの実ヘッダー[palm_fruit.h]
// Author 小原立暉
//
//===================================
#ifndef _PALM_FRUIT_H_
#define _PALM_FRUIT_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(ヤシの実)
//-----------------------------------
class CPalmFruit : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,	// 通常状態
		STATE_FALL,		// 落下状態
		STATE_BOUND,	// バウンド状態
		STATE_STOP,		// 停止状態
		STATE_MAX		// この列挙型の総数
	};

	CPalmFruit();					// コンストラクタ
	~CPalmFruit();					// デストラクタ

	// リスト構造関係
	void SetPrev(CPalmFruit* pPrev);	// 前のポインタの設定処理
	void SetNext(CPalmFruit* pNext);	// 後のポインタの設定処理
	CPalmFruit* GetPrev(void) const;	// 前のポインタの設定処理
	CPalmFruit* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理
	void Hit(void);					// ヒット処理

	// セット・ゲット関係
	void SetMove(const D3DXVECTOR3& move);	// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;		// 移動量の取得処理
	void SetState(const STATE state);		// 状態の設定処理
	STATE GetState(void) const;				// 状態の取得処理

	// 静的メンバ関数
	static CPalmFruit* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// 生成処理

private:		// 自分だけアクセスできる
	
	// メンバ関数
	void Move(void);				// 移動処理
	void Gravity(void);				// 重力処理
	bool ElevationCollision(void);	// 起伏地面の当たり判定処理

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態

	// リスト構造関係
	CPalmFruit* m_pPrev;		// 前へのポインタ
	CPalmFruit* m_pNext;		// 次へのポインタ
};

#endif