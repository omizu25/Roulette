//**************************************************
// 
// Hackathon ( number.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "number.h"
#include "rectangle.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_NUMBER = 256;	// 数の最大数
const int	MAX_DIGIT = 8;		// 桁数の最大数
const int	TEX_DIVIDE = 10;	// テクスチャの分割数

typedef struct
{
	D3DXVECTOR3	pos;				// 位置
	D3DXVECTOR3	size;				// サイズ
	D3DXCOLOR	col;				// 色
	int			number[MAX_DIGIT];	// 数
	int			digit;				// 桁数
	int			idx[MAX_DIGIT];		// 矩形のインデックス
	bool		zero;				// 0を表示するかどうか
	bool		use;				// 使用しているかどうか
}Number;
}// namesapceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
Number	s_number[MAX_NUMBER];	// 数の情報
int		s_digit;				// 桁数計算用
}// namesapceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void OneDivideNumber(Number *pNumber, int inNumber);
void SetOneDigitNumber(Number *pNumber, int inDigit);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitNumber(void)
{
	// メモリのクリア
	memset(&s_number, NULL, sizeof(s_number));

	s_digit = 0;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitNumber(void)
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		Number *pNumber = &s_number[i];

		if (!pNumber->use)
		{// 使用していない
			continue;
		}

		/*↓ 使用している ↓*/

		for (int j = 0; j < pNumber->digit; j++)
		{
			// 使うのを止める
			StopUseRectangle(pNumber->idx[j]);
		}
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateNumber(void)
{
	
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawNumber(void)
{
	
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
int SetNumber(const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize, const D3DXCOLOR &inCol, int inNumber, int inDigit, bool inZero)
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		Number *pNumber = &s_number[i];

		if (pNumber->use)
		{// 使用している
			continue;
		}

		/*↓ 使用していない ↓*/

		pNumber->pos = inPos;
		pNumber->size = inSize;
		pNumber->col = inCol;

		if (inZero)
		{// 0を表示する
			pNumber->digit = inDigit;
		}
		else
		{// 0を表示しない
			pNumber->digit = DigitNumber(inNumber);
		}

		// 一桁ずつに分ける
		OneDivideNumber(pNumber, inNumber);

		for (int j = 0; j < pNumber->digit; j++)
		{
			// 矩形の設定
			pNumber->idx[j] = SetRectangle(TEXTURE_Number_000);

			// 一桁ずつの設定
			SetOneDigitNumber(pNumber, j);
		}

		pNumber->zero = inZero;
		pNumber->use = true;

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void SetPosNumber(int inIdx, const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pNumber->pos = inPos;
	pNumber->size = inSize;

	for (int i = 0; i < pNumber->digit; i++)
	{
		// 一桁ずつの設定
		SetOneDigitNumber(pNumber, i);
	}
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
int ChangeNumber(int inIdx, int inNumber)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// 使用していない
		return inIdx;
	}

	/*↓ 使用している ↓*/

	if (!pNumber->zero)
	{// 0を表示しない
		if (pNumber->digit != DigitNumber(inNumber))
		{// 桁数が違う
			// 使うのを止める
			StopUseNumber(inIdx);

			// 設定
			return SetNumber(pNumber->pos, pNumber->size, pNumber->col, inNumber, DigitNumber(inNumber), false);
		}
		else
		{// 桁数が同じ
			// 一桁ずつに分ける
			OneDivideNumber(pNumber, inNumber);
		}
	}
	else
	{// 0を表示する
		if (pNumber->digit < DigitNumber(inNumber))
		{// 桁数が違う
			// 使うのを止める
			StopUseNumber(inIdx);

			// 設定
			return SetNumber(pNumber->pos, pNumber->size, pNumber->col, inNumber, DigitNumber(inNumber), true);
		}
		else
		{// 桁数が同じ
			// 一桁ずつに分ける
			OneDivideNumber(pNumber, inNumber);
		}
	}

	float divide = 1.0f / TEX_DIVIDE;

	for (int i = 0; i < pNumber->digit; i++)
	{
		float tex = divide * pNumber->number[i];

		// 矩形のテクスチャ座標の設定
		SetTexRectangle(pNumber->idx[i], D3DXVECTOR2(tex, tex + divide), D3DXVECTOR2(0.0f, 1.0f));
	}

	return inIdx;
}

//--------------------------------------------------
// 使うのを止める
//--------------------------------------------------
void StopUseNumber(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	pNumber->use = false;

	for (int i = 0; i < pNumber->digit; i++)
	{
		// 使うのを止める
		StopUseRectangle(pNumber->idx[i]);
	}
}

//--------------------------------------------------
// 桁数
//--------------------------------------------------
int DigitNumber(int inNumber)
{
	s_digit = 0;
	int number = inNumber;

	while (1)
	{// 無限ループ
		if (number >= 10)
		{// 2桁以上
			number /= 10;
			s_digit++;
		}
		else
		{// 1桁
			s_digit++;

			if (s_digit > MAX_DIGIT)
			{// 指定の値より大きい
				s_digit = MAX_DIGIT;
			}
			break;
		}
	}

	return s_digit;
}

//--------------------------------------------------
// 描画するかどうか
//--------------------------------------------------
void SetDrawNumber(int inIdx, bool inDraw)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	for (int i = 0; i < pNumber->digit; i++)
	{
		// 矩形の描画するかどうか
		SetDrawRectangle(pNumber->idx[i], inDraw);
	}
}

//--------------------------------------------------
// テクスチャの変更
//--------------------------------------------------
void ChangeTextureNumber(int inIdx, TEXTURE inTexture)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	for (int i = 0; i < pNumber->digit; i++)
	{
		// 矩形の描画するかどうか
		ChangeTextureRectangle(pNumber->idx[i], inTexture);
	}
}

namespace
{
//--------------------------------------------------
// 一桁ずつに分ける
//--------------------------------------------------
void OneDivideNumber(Number *pNumber, int inNumber)
{
	int number = inNumber;

	for (int i = 0; i < pNumber->digit; i++)
	{// 一桁ずつに分ける
		pNumber->number[i] = number % 10;
		number /= 10;
	}
}

//--------------------------------------------------
// 一桁ずつの設定
//--------------------------------------------------
void SetOneDigitNumber(Number *pNumber, int inDigit)
{
	float interval = (pNumber->size.x * inDigit) + (pNumber->size.x * 0.5f);

	// 矩形の位置の設定
	SetPosRectangle(pNumber->idx[inDigit], pNumber->pos + D3DXVECTOR3(-interval, 0.0f, 0.0f), pNumber->size);

	// 矩形の色の設定
	SetColorRectangle(pNumber->idx[inDigit], pNumber->col);

	float divide = 1.0f / TEX_DIVIDE;
	float tex = divide * pNumber->number[inDigit];

	// 矩形のテクスチャ座標の設定
	SetTexRectangle(pNumber->idx[inDigit], D3DXVECTOR2(tex, tex + divide), D3DXVECTOR2(0.0f, 1.0f));
}
}// namespaceはここまで
