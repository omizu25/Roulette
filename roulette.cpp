//**************************************************
//
// Hackathon ( roulette.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "mode.h"
#include "rectangle.h"
#include "color.h"
#include "texture.h"
#include "utility.h"
#include "roulette.h"
#include "number.h"
#include "game.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	STOP_TIME = 15;			// 止めれるまでの時間
const int	MAX_RANDOM = 30;		// ランダムの最大値
const int	MIN_RANDOM = 1;			// ランダムの最小値
const float	NUMBER_WIDTH = 300.0f;	// 数字の幅
const float	NUMBER_HEIGHT = 400.0f;	// 数字の高さ
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_time;			// 時間
int	s_randomNumber;	// ランダムな数字
int	s_idxNumber;	// 数字の配列のインデックス
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Input(void);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitRoulette(void)
{
	s_time = 0;

	// ランダム
	s_randomNumber = IntRandam(MAX_RANDOM, MIN_RANDOM);

	// 桁数
	int digit = DigitNumber(s_randomNumber);
	
	D3DXVECTOR3 size = D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + ((NUMBER_WIDTH * 0.5f) * digit), SCREEN_HEIGHT * 0.5f, 0.0f);

	// 数の設定
	s_idxNumber = SetNumber(pos, size, GetColor(COLOR_WHITE), s_randomNumber, 0, false);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitRoulette(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateRoulette(void)
{
	if (GetGameState() != GAMESTATE_NORMAL)
	{// 通常状態じゃない
		return;
	}

	// ランダム
	s_randomNumber = IntRandam(MAX_RANDOM, MIN_RANDOM);
	assert(s_randomNumber >= MIN_RANDOM && s_randomNumber <= MAX_RANDOM);

	// 桁数
	int digit = DigitNumber(s_randomNumber);
	D3DXVECTOR3 size = D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + ((NUMBER_WIDTH * 0.5f) * digit), SCREEN_HEIGHT * 0.5f, 0.0f);

	// 数の変更
	s_idxNumber = ChangeNumber(s_idxNumber, s_randomNumber);

	// 数の位置の設定
	SetPosNumber(s_idxNumber, pos, size);

	// 入力
	Input();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawRoulette(void)
{
}

namespace
{
//--------------------------------------------------
// 入力
//--------------------------------------------------
void Input(void)
{
	s_time++;

	if (s_time < STOP_TIME)
	{// 一定時間経っていない
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		// ゲーム状態の設定
		SetGameState(GAMESTATE_RESULT);
	}
}
}// namespaceはここまで
