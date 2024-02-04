//===================================
//
// ボスの状態ヘッダー[boss_state.h]
// Author 小原立暉
//
//===================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_
//***********************************
// インクルードファイル
//***********************************
#include "main.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CBoss;		// ボス

// クラス定義(ボスの状態の基本クラス)
class CBossState
{
public:

	CBossState();			// コンストラクタ
	virtual ~CBossState();	// デストラクタ

	void Uninit();			// 終了処理

	virtual void Process(CBoss* pBoss) = 0;	// 状態処理
	virtual void SetData(CBoss* pBoss) = 0;	// 情報の設定処理
};

// クラス定義(ボスの出現状態クラス)
class CBossAppearState : public CBossState
{
public:

	CBossAppearState();		// コンストラクタ
	~CBossAppearState();	// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

	// メンバ関数
	void Length(void);			// 距離関係処理
	void PosRot(CBoss* pBoss);	// 位置向き設定処理
	void Ripple(CBoss* pBoss);	// 波紋の設置処理

	// メンバ変数
	int m_nCount;			// 経過カウント
	float m_fLangeRot;		// 離れる向き
	float m_fLength;		// 距離
	float m_fHeight;		// 高度
};

// クラス定義(ボスの向き直り状態クラス)
class CBossTurnState : public CBossState
{
public:

	CBossTurnState();	// コンストラクタ
	~CBossTurnState();	// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

	// メンバ変数
	int m_nCount;		// 経過カウント
};

// クラス定義(ボスの遠吠え状態クラス)
class CBossHowlingState : public CBossState
{
public:

	CBossHowlingState();	// コンストラクタ
	~CBossHowlingState();	// デストラクタ

	void Process(CBoss* pBoss) override;		// 状態処理
	void SetData(CBoss* pBoss) override;		// 情報の設定処理

private:

};

#endif