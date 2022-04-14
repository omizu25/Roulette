//**************************************************
// 
// Hackathon ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定数
//==================================================
namespace
{
const char *s_FileName[] =
{// テクスチャのパス	
	"data/TEXTURE/Number_000.png",	// 数字000
	"data/TEXTURE/Number_001.png",	// 数字001
	"data/TEXTURE/Number_002.png",	// 数字002
	"data/TEXTURE/Number_003.png",	// 数字003
	"data/TEXTURE/Number_004.png",	// 数字004
	"data/TEXTURE/Number_005.png",	// 数字005
	"data/TEXTURE/Number_006.png",	// 数字006
	"data/TEXTURE/Number_007.png",	// 数字007
	"data/TEXTURE/Number_008.png",	// 数字008
	"data/TEXTURE/Number_009.png",	// 数字009
	"data/TEXTURE/Number_010.png",	// 数字010
	"data/TEXTURE/Roulette.png",	// タイトルロゴ
};
}// namespaceはここまで

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// スタティック変数
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespaceはここまで

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void LoadTexture(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return NULL;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	return s_pTexture[inTexture];
}
