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
	"data/TEXTURE/Number_000.png",		// 数字000
	"data/TEXTURE/Roulette.png",		// タイトルロゴ
	"data/TEXTURE/BG.jpg",				// 背景
	"data/TEXTURE/GameStart_008.png",	// スタート
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
// 全ての読み込み
//--------------------------------------------------
void LoadTextureAll(void)
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
// 読み込み
//--------------------------------------------------
void LoadTexture(TEXTURE inTexture)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void UnloadTextureAll(void)
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
// 解放
//--------------------------------------------------
void UnloadTexture(TEXTURE inTexture)
{
	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
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

	if (s_pTexture[inTexture] == NULL)
	{// テクスチャの読み込みがされていない
		// 読み込み
		LoadTexture(inTexture);
	}

	return s_pTexture[inTexture];
}
