//============================================================
//
// Xファイルヘッダー [xfile.h]
// Author：小原立暉
//
//============================================================
#ifndef _XFILE_H_	// このマクロ定義がされていない場合
#define _XFILE_H_	// 二重インクルード防止のマクロを定義する

//------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// モデルの最小の頂点座標の初期値
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// モデルの最大の頂点座標の初期値
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// モデルサイズの初期値
#define INIT_PLAYER		(CXFile::TYPE_PLAYERWAIST)						// プレイヤーの最初のモデル
#define INIT_TORDLE		(CXFile::TYPE_TORDLEBODY)						// タードルの最初のモデル

//------------------------------------------------------------
// クラス定義(Xファイル)
//------------------------------------------------------------
class CXFile
{
public:			// 誰でもアクセスできる

	//************************************************************
	//	列挙型定義 (TYPE)
	//************************************************************
	enum TYPE
	{
		// 演出モデル
		TYPE_FRAC_SCREW,		// ネジ(破片)
		TYPE_FRAC_GEAR,			// 歯車(破片)
		TYPE_FRAC_RING,			// 輪(破片)
		TYPE_FRAC_WOOD,			// 木片(破片)
		TYPE_RIPPLE,			// 波紋

		// ゲームモデル
		TYPE_COIN,				// 小判
		TYPE_HANDGUN,			// 拳銃
		TYPE_DAGGER,			// ダガー
		TYPE_GOLDBONE,			// 金の骨
		TYPE_PALMTREE,			// ヤシの木
		TYPE_PALMFRUIT,			// ヤシの実
		TYPE_PALMITEM,			// ヤシの実(アイテム体)
		TYPE_ROCK,				// 岩

		// プレイヤーモデル
		TYPE_PLAYERWAIST,		// 腰
		TYPE_PLAYERBODY,		// 体
		TYPE_PLAYERNECK,		// 首
		TYPE_PLAYERCLOAK,		// マント
		TYPE_PLAYERHEAD,		// 頭
		TYPE_PLAYERRIGHTARM,	// 右腕
		TYPE_PLAYERLEFTARM,		// 左腕
		TYPE_PLAYERRIGHTUPPER,	// 右上腕
		TYPE_PLAYERLEFTUPPER,	// 左上腕
		TYPE_PLAYERRIGHTHAND,	// 右手
		TYPE_PLAYERLEFTHAND,	// 左手
		TYPE_PLAYERRIGHTLEG,	// 右脚
		TYPE_PLAYERLEFTLEG,		// 左脚
		TYPE_PLAYERRIGHTSHIN,	// 右脛
		TYPE_PLAYERLEFTSHIN,	// 左脛
		TYPE_PLAYERRIGHTFOOT,	// 右足
		TYPE_PLAYERLEFTFOOT,	// 左足

		// タードルモデル
		TYPE_TORDLEBODY,		// タードルの体
		TYPE_TORDLEHEAD,		// タードルの頭
		TYPE_TORDLERFLEG,		// タードルの右前足
		TYPE_TORDLELFLEG,		// タードルの左前足
		TYPE_TORDLERBLEG,		// タードルの右後ろ足
		TYPE_TORDLELBLEG,		// タードルの左後ろ足

		TYPE_MAX,				// 全モデルの総数
	};

	//************************************************************
	//	構造体定義 (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// メッシュ (頂点情報) へのポインタ
		LPD3DXBUFFER pBuffMat;					// マテリアルへのポインタ
		DWORD		 dwNumMat;					// マテリアルの数
		D3DXVECTOR3	 vtxMin;					// 最小の頂点座標
		D3DXVECTOR3	 vtxMax;					// 最大の頂点座標
		D3DXVECTOR3	 collsize;					// 当たり判定のサイズ
		D3DXVECTOR3* vtxPos;					// 頂点の位置
		float		 fRadius;					// 半径
		int			 nNumFace;					// 面の数
		int			 m_nTexIdx[MAX_MATERIAL];	// テクスチャのインデックス
	};

	CXFile();			// コンストラクタ
	~CXFile();			// デストラクタ

	// メンバ関数
	static HRESULT Init(void);		// Xファイルの初期化処理
	static void Uninit(void);		// Xファイルの終了処理

	// セット・ゲット関数
	static SXFile GetXFile(TYPE type);	// Xファイルの取得処理

private:

	// メンバ関数
	static HRESULT LoadXFile(void);		// xファイルの読み込み
	static void SetCollision(void);		// 当たり判定の作成
	static HRESULT LoadTexture(void);	// テクスチャの読み込み

	// 静的メンバ変数
	static const char *c_apModelData[CXFile::TYPE_MAX];			// モデルの名前
	static SXFile m_apModel[CXFile::TYPE_MAX];					// モデルの情報
};

#endif