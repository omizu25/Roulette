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

#include <stdio.h>
#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	STOP_TIME = 15;							// 止めれるまでの時間
const int	MAX_NUMBER = 17;						// 数の最大値
const int	MIN_NUMBER = 1;							// 数の最小値
const int	RANDOM = (MAX_NUMBER - MIN_NUMBER + 1);	// ランダムの範囲の個数
const int	MAX_TEXT = 1024;						// テキストの最大文字数
const float	NUMBER_WIDTH = 300.0f;					// 数字の幅
const float	NUMBER_HEIGHT = 400.0f;					// 数字の高さ
const char	*TEXT_NAME = "data/TEXT/Roulette.txt";	// テキスト名
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_time;					// 時間
int	s_randomNumber;			// ランダムな数字
int	s_idxNumber;			// 数字の配列のインデックス
int	s_usedNumber[RANDOM];	// 使用された数字
int	s_useNumber[RANDOM];	// 使用する数字
int	s_counterUsed;			// 使用された数字の数
int	s_counterUse;			// 使用する数字の数
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Load(void);
void Number(void);
void Random(void);
void Input(void);
void Save(void);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitRoulette(void)
{
	s_time = 0;

	// 読み込み
	Load();

	if (s_counterUsed >= RANDOM)
	{// 全部使用された
		// ゲーム状態の設定
		SetGameState(GAMESTATE_NONE);

		// モードの変更
		ChangeMode(MODE_TITLE);

		return;
	}
	else
	{// まだ残ってる
		// ゲーム状態の設定
		SetGameState(GAMESTATE_NORMAL);
	}

	// 数
	Number();

	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 数の設定
	s_idxNumber = SetNumber(pos, size, GetColor(COLOR_WHITE), 0, 0, false);

	// ランダム
	Random();
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
	if (s_counterUsed >= RANDOM)
	{// 全部使用された
		// モードの変更
		ChangeMode(MODE_TITLE);

		return;
	}

	if (GetGameState() != GAMESTATE_NORMAL)
	{// 通常状態じゃない
		return;
	}

	// ランダム
	Random();

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
// 読み込み
//--------------------------------------------------
void Load(void)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(TEXT_NAME, "r");

	s_counterUsed = 0;

	if (pFile != NULL)
	{// ファイルが開いた場合
		char string[MAX_TEXT];

		while (fscanf(pFile, "%s", &string[0]) != EOF)
		{// ファイルの最後が来るまで繰り返す
			if (strncmp(&string[0], "#", 1) == 0)
			{
				fscanf(pFile, "%d", &s_usedNumber[s_counterUsed]);
				s_counterUsed++;
				assert(s_counterUsed >= 0 && s_counterUsed <= RANDOM);
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
		s_counterUsed = -1;
	}
}

//--------------------------------------------------
// セーブ
//--------------------------------------------------
void Save(void)
{
	FILE *pFile = NULL;	// ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(TEXT_NAME, "w");

	if (pFile != NULL)
	{// ファイルが開いた場合
		int counter = 0;

		while (counter <= s_counterUsed)
		{// カウンターが越すまで
			fprintf(pFile, "# %d\n\n", s_usedNumber[counter]);
			counter++;
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
		s_counterUsed = -1;
	}
}

//--------------------------------------------------
// 数
//--------------------------------------------------
void Number(void)
{
	s_counterUse = 0;

	for (int number = MIN_NUMBER; number <= MAX_NUMBER; number++)
	{
		bool used = false;

		for (int i = 0; i < s_counterUsed; i++)
		{
			if (number == s_usedNumber[i])
			{// 使用された数字
				used = true;
				break;
			}
		}

		if (used)
		{// 使用されていた
			continue;
		}

		/* 使用されていない数字 */

		s_useNumber[s_counterUse] = number;

		s_counterUse++;
	}
}

//--------------------------------------------------
// ランダム
//--------------------------------------------------
void Random(void)
{
	// ランダム
	int rand = IntRandam(s_counterUse - 1, 0);
	assert(rand >= 0 && rand < s_counterUse);
	s_randomNumber = s_useNumber[rand];
	assert(s_randomNumber >= MIN_NUMBER && s_randomNumber <= MAX_NUMBER);

	// 桁数
	int digit = DigitNumber(s_randomNumber);
	D3DXVECTOR3 size = D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + ((NUMBER_WIDTH * 0.5f) * digit), SCREEN_HEIGHT * 0.5f, 0.0f);

	// 数の変更
	s_idxNumber = ChangeNumber(s_idxNumber, s_randomNumber);

	// 数の位置の設定
	SetPosNumber(s_idxNumber, pos, size);
}

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

		s_usedNumber[s_counterUsed] = s_randomNumber;

		// セーブ
		Save();
	}
}
}// namespaceはここまで
