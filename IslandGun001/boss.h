//===================================
//
// ボスヘッダー[boss.h]
// Author 小原立暉
//
//===================================
#ifndef _BOSS_H_
#define _BOSS_H_

//***********************************
// インクルードファイル
//***********************************
#include "character.h"
#include "list_manager.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CMotion;		// モーション
class CBossState;	// ボスの状態

//-----------------------------------
// クラス定義(CBoss)
//-----------------------------------
class CBoss : public CCharacter
{
public:					// 誰でもアクセスできる

	// 列挙型定義(モーションの種類)
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// 通常モーション
		MOTIONTYPE_FLY,				// 飛行モーション
		MOTIONTYPE_HOVERING,		// ホバリングモーション
		MOTIONTYPE_MAX				// この列挙型の総数
	};

	CBoss();		// コンストラクタ
	~CBoss();		// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 情報の設定処理

	void ChangeState(CBossState* pNext);	// 状態の遷移処理

	// セット・ゲット関係
	CMotion* GetMotion(void);		// モーションの取得処理

	// 静的メンバ関数
	static CBoss* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 生成処理

	static CListManager<CBoss*> GetList(void);			// リストの取得処理

private:				// 自分だけアクセスできる

	// メンバ関数
	void ElevationCollision(void);			// 起伏地面との当たり判定

	// メンバ変数
	CMotion* m_pMotion;		// モーションの情報
	CBossState* m_pState;	// 状態の情報

	D3DXVECTOR3 m_move;		// 移動量

	// 静的メンバ変数
	static CListManager<CBoss*> m_list;		// リスト
};

#endif