//**************************************************
// 
// Hackathon ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// 列挙型
//==================================================
typedef enum
{
	TEXTURE_Number_000 = 0,	// 数字000
	TEXTURE_Number_001,		// 数字001
	TEXTURE_Number_002,		// 数字002
	TEXTURE_Number_003,		// 数字003
	TEXTURE_Number_004,		// 数字004
	TEXTURE_Number_005,		// 数字005
	TEXTURE_Number_006,		// 数字006
	TEXTURE_Number_007,		// 数字007
	TEXTURE_Number_008,		// 数字008
	TEXTURE_Number_009,		// 数字009
	TEXTURE_Number_010,		// 数字010
	TEXTURE_Roulette,		// タイトルロゴ
	TEXTURE_BG,				// 背景
	TEXTURE_GameStart_008,	// スタート
	TEXTURE_MAX,
	TEXTURE_NONE,	// 使用しない
}TEXTURE;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void LoadTextureAll(void);

//--------------------------------------------------
// 読み込み
// 引数  : TEXTURE inTexture / 列挙型 種類
//--------------------------------------------------
void LoadTexture(TEXTURE inTexture);

//--------------------------------------------------
// 全ての終了
//--------------------------------------------------
void UnloadTextureAll(void);

//--------------------------------------------------
// 終了
// 引数  : TEXTURE inTexture / 列挙型 種類
//--------------------------------------------------
void UnloadTexture(TEXTURE inTexture);

//--------------------------------------------------
// 取得
// 引数  : TEXTURE inTexture / 列挙型 種類
// 返値  : LPDIRECT3DTEXTURE9 / テクスチャ
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);

#endif // !_TEXTURE_H_
