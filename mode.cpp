//**************************************************
//
// Hackathon ( mode.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "fade.h"
#include "game.h"
#include "mode.h"
#include "rectangle.h"
#include "texture.h"
#include "title.h"
#include "utility.h"

#include <assert.h>
#include <time.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
EMode	s_mode = MODE_NONE;		// 現在のモード
EMode	s_modeNext = MODE_NONE;	// 次のモード
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitMode(void)
{
	// randの初期化
	srand((unsigned int)time(NULL));

	// テクスチャの読み込み
	LoadTexture();

	// 矩形の初期化
	InitRectangle();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitMode(void)
{
	// ゲームの終了
	UninitGame();

	// タイトルの終了
	UninitTitle();

	// 矩形の終了
	UninitRectangle();

	// テクスチャの終了
	UninitTexture();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateMode(void)
{
	switch (s_mode)
	{// どのモード？
	case MODE_TITLE:	// タイトル
		UpdateTitle();
		break;

	case MODE_GAME:		// ゲーム
		UpdateGame();
		break;

	case MODE_NONE:
		/* 処理なし */
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawMode(void)
{
	switch (s_mode)
	{// どのモード？
	case MODE_TITLE:	// タイトル
		DrawTitle();
		break;

	case MODE_GAME:		// ゲーム
		DrawGame();
		break;

	case MODE_NONE:
		/* 処理なし */
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetMode(void)
{
	if (s_modeNext == MODE_NONE)
	{// 次のモードが決まってない
		return;
	}

	if (GetFade() == FADE_NONE)
	{// 何もしていない状態なら
		StartFadeOut();
	}

	if (GetFade() != FADE_IN)
	{// フェードイン状態じゃない
		return;
	}

	switch (s_mode)
	{// 現在のモードの終了
	case MODE_TITLE:	// タイトル
		UninitTitle();
		break;

	case MODE_GAME:		// ゲーム
		UninitGame();
		break;

	case MODE_NONE:
		/* 処理なし */
		break;

	default:
		assert(false);
		break;
	}

	// 矩形の終了
	UninitRectangle();

	// 矩形の初期化
	InitRectangle();

	s_mode = s_modeNext;	// 現在の画面(モード)を切り替える
	
	switch (s_modeNext)
	{// 次のモードの初期化
	case MODE_TITLE:	// タイトル
		InitTitle();
		break;

	case MODE_GAME:		// ゲーム
		InitGame();
		break;
	
	case MODE_NONE:
	default:
		assert(false);
		break;
	}

	s_modeNext = MODE_NONE;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
EMode GetMode(void)
{
	return s_mode;
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void ChangeMode(EMode inModeNext)
{
	assert(inModeNext >= 0 && inModeNext < MODE_MAX);

	s_modeNext = inModeNext;
}
