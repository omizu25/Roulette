//**************************************************
//
// FPD制作 ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "rectangle.h"
#include "color.h"
#include "time.h"
#include "utility.h"
#include "bg.h"
#include "roulette.h"
#include "mode.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_TIME = 1500;	// タイムの最大値
const int	CHANGE_TIME = 15;	// タイムの変更値
}// namesapceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
EGameState	s_gameState = GAMESTATE_NONE;	// ゲームの状態
int			s_counterState;					// 状態管理カウンター
bool		s_pause = false;				// ポーズ中かどうか [してる  : true してない  : false]
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	// 背景の初期化
	InitBG();

	// ルーレットの初期化
	InitRoulette();

	s_pause = false;	// ポーズ解除
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// 背景の終了
	UninitBG();

	// ルーレットの終了
	UninitRoulette();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	// ルーレットの更新
	UpdateRoulette();

	if (s_gameState == GAMESTATE_RESULT)
	{
		s_counterState++;

		if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
		{//決定キー(ENTERキー)が押されたかどうか
			if (s_counterState >= CHANGE_TIME)
			{// 一定時間経過
				// モードの変更
				ChangeMode(MODE_TITLE);
			}
		}

		if (s_counterState >= MAX_TIME)
		{// 一定時間経過
			// モードの変更
			ChangeMode(MODE_TITLE);
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawGame(void)
{
	// 矩形の描画
	DrawRectangle();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetGameState(EGameState inState)
{
	assert(inState >= 0 && inState < GAMESTATE_MAX);

	s_gameState = inState;
	s_counterState = 0;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
EGameState GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// ポーズの有効無効設定
//--------------------------------------------------
void SetEnablePause(bool inPause)
{
	s_pause = inPause;
}

//--------------------------------------------------
// ポーズの有効無効取得
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_pause;
}
