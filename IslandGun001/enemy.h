//===================================
//
// 敵ヘッダー[enemy.h]
// Author 小原立暉
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// インクルードファイル
//***********************************
#include "character.h"

//-----------------------------------
// クラス定義(CEnemy)
//-----------------------------------
class CEnemy : public CCharacter
{
public:					// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_TORDLE = 0,	// 地上を歩く敵(タードル)
		TYPE_MAX			// この列挙型の総数
	};

	CEnemy();				// コンストラクタ
	virtual ~CEnemy();		// デストラクタ

	// リスト構造関係
	void SetPrev(CEnemy* pPrev);	// 前のポインタの設定処理
	void SetNext(CEnemy* pNext);	// 後のポインタの設定処理
	CEnemy* GetPrev(void) const;	// 前のポインタの設定処理
	CEnemy* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	virtual HRESULT Init(void) override;	// 初期化処理
	virtual void Uninit(void) override;		// 終了処理
	virtual void Update(void) override;		// 更新処理
	virtual void Draw(void) override;		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 情報の設定処理

	// 静的メンバ関数
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 生成処理

private:				// 自分だけアクセスできる

	// メンバ変数
	TYPE m_type;		// 種類

	// リスト構造関係
	CEnemy* m_pPrev;	// 前へのポインタ
	CEnemy* m_pNext;	// 次へのポインタ
};

#endif