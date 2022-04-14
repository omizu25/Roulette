//**************************************************
// 
// Hackathon ( menu.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "input.h"
#include "menu.h"
#include "fade.h"
#include "color.h"
#include "rectangle.h"
#include "utility.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_MENU = 16;					// メニューの最大数
const float	NORMAL_CHANGE_SPEED = 0.01f;	// 通常時の変更速度
const float	DECISION_CHANGE_SPEED = 0.1f;	// 決定時の変更速度
const float	MIN_ALPHA = 0.5f;				// α値の最小値

/*↓ 選択肢 ↓*/
struct SOption
{
	D3DXVECTOR3	pos;	// 位置
	D3DXCOLOR	col;	// 色
	int			idx;	// 矩形のインデックス
	float		width;	// 幅
	float		height;	// 高さ
};

/*↓ メニュー ↓*/
struct SMenu
{
	D3DXVECTOR3	pos;				// 位置
	D3DXCOLOR	colStart;			// 始まりの色
	D3DXCOLOR	colEnd;				// 終わりの色
	D3DXCOLOR	colDefault;			// 選ばれてない選択肢の色
	SOption		option[MAX_OPTION];	// 選択肢の情報
	int			numUse;				// 使用数
	int			idx;				// 矩形のインデックス
	float		width;				// 幅
	float		height;				// 高さ
	float		interval;			// 選択肢の間隔
	float		changeSpeed;		// 変更速度
	bool		frame;				// 枠がいるかどうか [ true : いる false : いらない ]
	bool		draw;				// 描画するかどうか
	bool		use;				// 使用しているかどうか
};
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
SMenu	s_menu[MAX_MENU];	// メニューの情報
int		s_idxMenu;			// 選ばれているメニューの番号
int		s_idxOption;		// 選ばれている選択肢の番号
int		s_time;				// α値変更用の時間
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void ChangeColor(SMenu *pMenu);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitMenu(void)
{
	s_idxMenu = 0;
	s_idxOption = 0;
	s_time = 0;

	// メモリのクリア
	memset(s_menu, 0, sizeof(s_menu));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitMenu(void)
{
	for (int i = 0; i < MAX_MENU; i++)
	{
		SMenu *pMenu = &s_menu[i];

		if (!pMenu->use)
		{// 使用していない
			continue;
		}

		/*↓ 使用している ↓*/

		if (pMenu->frame)
		{// 枠を使っている
			// 使うのを止める
			StopUseRectangle(pMenu->idx);
		}

		for (int j = 0; j < pMenu->numUse; j++)
		{
			SOption *pOption = &pMenu->option[j];

			// 使うのを止める
			StopUseRectangle(pOption->idx);
		}
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateMenu(void)
{
	SMenu *pMenu = &s_menu[s_idxMenu];

	if (!pMenu->use)
	{// 使用していない
		return;
	}
	
	// 色の変更
	ChangeColor(pMenu);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawMenu(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
int SetMenu(const SInMenu &inMenu, const SInFrame &inFrame)
{
	assert(inMenu.numUse >= 0 && inMenu.numUse < MAX_OPTION);
	
	for (int i = 0; i < MAX_MENU; i++)
	{
		SMenu *pMenu = &s_menu[i];

		if (pMenu->use)
		{// 使用している
			continue;
		}

		/*↓ 使用していない ↓*/

		float posX = inMenu.left + ((inMenu.right - inMenu.left) * 0.5f);
		float posY = inMenu.top + ((inMenu.bottom - inMenu.top) * 0.5f);

		pMenu->pos = D3DXVECTOR3(posX, posY, 0.0f);
		pMenu->colStart = GetColor(COLOR_WHITE);
		pMenu->colEnd = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pMenu->colDefault = GetColor(COLOR_WHITE);
		pMenu->numUse = inMenu.numUse;
		pMenu->width = inMenu.right - inMenu.left;
		pMenu->height = inMenu.bottom - inMenu.top;
		pMenu->changeSpeed = NORMAL_CHANGE_SPEED;
		pMenu->frame = inFrame.use;
		pMenu->draw = true;
		pMenu->use = true;

		if (inMenu.sort)
		{// 縦
			pMenu->interval = pMenu->height / (inMenu.numUse + 1);
		}
		else
		{// 横
			pMenu->interval = pMenu->width / (inMenu.numUse + 1);
		}

		s_idxMenu = i;
		s_idxOption = 0;

		if (inFrame.use)
		{// 枠がいる
			// 矩形の設定
			pMenu->idx = SetRectangle(inFrame.texture);

			posX = inMenu.left + (pMenu->width * 0.5f);
			posY = inMenu.top + (pMenu->height * 0.5f);
			D3DXVECTOR3 pos = D3DXVECTOR3(posX, posY, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pMenu->width, pMenu->height, 0.0f);

			// 矩形の位置の設定
			SetPosRectangle(pMenu->idx, pos, size);

			// 矩形の色の設定
			SetColorRectangle(pMenu->idx, inFrame.col);
		}

		for (int j = 0; j < pMenu->numUse; j++)
		{
			SOption *pOption = &pMenu->option[j];

			if (inMenu.sort)
			{// 縦
				pOption->pos = D3DXVECTOR3(pMenu->pos.x, inMenu.top + (pMenu->interval * (j + 1)), 0.0f);
			}
			else
			{// 横
				pOption->pos = D3DXVECTOR3(inMenu.left + (pMenu->interval * (j + 1)), pMenu->pos.y, 0.0f);
			}

			pOption->col = GetColor(COLOR_WHITE);
			pOption->width = inMenu.width;
			pOption->height = inMenu.height;

			// 矩形の設定
			pOption->idx = SetRectangle(inMenu.texture[j]);

			D3DXVECTOR3 size = D3DXVECTOR3(inMenu.width, inMenu.height, 0.0f);

			// 矩形の位置の設定
			SetPosRectangle(pOption->idx, pOption->pos, size);

			// 矩形の色の設定
			SetColorRectangle(pOption->idx, pOption->col);
		}

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// 選択肢の色の設定
//--------------------------------------------------
void SetColorOption(int inIdx, const D3DXCOLOR &inColStart, const D3DXCOLOR &inColEnd)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pMenu->colStart = inColStart;
	pMenu->colEnd = inColEnd;
}

//--------------------------------------------------
// 選ばれていない選択肢の色の設定
//--------------------------------------------------
void SetColorDefaultOption(int inIdx, const D3DXCOLOR &inColDefault)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	pMenu->colDefault = inColDefault;

	// 選択肢の色の初期化
	InitColorOption();
}

//--------------------------------------------------
// 選択肢の色の初期化
//--------------------------------------------------
void InitColorOption(void)
{
	SMenu *pMenu = &s_menu[s_idxMenu];

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		pOption->col = pMenu->colDefault;

		// 矩形の色の設定
		SetColorRectangle(pOption->idx, pOption->col);
	}
}

//--------------------------------------------------
// 選択肢の変更
//--------------------------------------------------
void ChangeOption(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_OPTION);

	s_idxOption = inIdx;
	s_time = 0;
}

//--------------------------------------------------
// 選択肢の決定
//--------------------------------------------------
void DecisionOption(void)
{
	s_menu[s_idxMenu].changeSpeed = DECISION_CHANGE_SPEED;
}

//--------------------------------------------------
// リセット
//--------------------------------------------------
void ResetMenu(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	s_idxMenu = 0;
	s_idxOption = 0;
	s_time = 0;
	
	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	if (pMenu->frame)
	{// 枠を使っている
		// 使うのを止める
		StopUseRectangle(pMenu->idx);
	}

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		// 使うのを止める
		StopUseRectangle(pOption->idx);
	}

	pMenu->use = false;
}

//--------------------------------------------------
// 描画するかどうか
//--------------------------------------------------
void SetDrawMenu(int inIdx, bool inDraw)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	if (pMenu->frame)
	{// 枠を使っている
		// 矩形の描画するかどうか
		SetDrawRectangle(pMenu->idx, inDraw);
	}

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		// 矩形の描画するかどうか
		SetDrawRectangle(pOption->idx, inDraw);

		pOption->col = GetColor(COLOR_WHITE);
	}

	pMenu->draw = inDraw;

	pMenu->changeSpeed = NORMAL_CHANGE_SPEED;
	s_idxOption = 0;
	s_time = 0;
}

namespace
{
//--------------------------------------------------
// 色の変更
//--------------------------------------------------
void ChangeColor(SMenu *pMenu)
{
	s_time++;

	SOption *pOption = &pMenu->option[s_idxOption];

	float curve = CosCurve(s_time, pMenu->changeSpeed);
	pOption->col.r = Curve(curve, pMenu->colStart.r, pMenu->colEnd.r);
	pOption->col.g = Curve(curve, pMenu->colStart.g, pMenu->colEnd.g);
	pOption->col.b = Curve(curve, pMenu->colStart.b, pMenu->colEnd.b);
	pOption->col.a = Curve(curve, pMenu->colStart.a, pMenu->colEnd.a);

	// 矩形の色の設定
	SetColorRectangle(pOption->idx, pOption->col);
}
}// namespaceはここまで
