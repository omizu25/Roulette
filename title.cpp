//**************************************************
//
// Hackathon ( title.cpp )
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
#include "title.h"
#include "color.h"
#include "texture.h"
#include "utility.h"
#include "menu.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// タイトルロゴの幅
const float	TITLE_HEIGHT = 200.0f;	// タイトルロゴの高さ
const float	MENU_WIDTH = 300.0f;	// メニューの幅
const float	MENU_HEIGHT = 80.0f;	// メニューの高さ

enum EMenu
{
	MENU_GAME = 0,	// ゲーム
	MENU_MAX
};
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_idxBG;		// 背景の矩形のインデックス
int	s_idxTitleLogo;	// タイトルロゴの矩形のインデックス
int	s_selectMenu;	// 選ばれているメニュー
int	s_idxMenu;		// メニューの配列のインデックス
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
void InitTitle(void)
{
	s_selectMenu = 0;

	{// 背景
		// 矩形の設定
		s_idxBG = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_idxBG, pos, size);
	}

	{// タイトルロゴ
		// 矩形の設定
		s_idxTitleLogo = SetRectangle(TEXTURE_Roulette);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_idxTitleLogo, pos, size);

		// 矩形の色の設定
		SetColorRectangle(s_idxTitleLogo, GetColor(COLOR_RED));
	}
	
	{// メニュー
		// メニューの初期化
		InitMenu();

		SInMenu menu;
		menu.numUse = MENU_MAX;
		menu.left = SCREEN_WIDTH * 0.55f;
		menu.right = SCREEN_WIDTH * 0.95f;
		menu.top = 0.0f;
		menu.bottom = SCREEN_HEIGHT;
		menu.width = MENU_WIDTH;
		menu.height = MENU_HEIGHT;
		menu.sort = true;

		menu.texture[MENU_GAME] = TEXTURE_GameStart_008;

		SInFrame frame;
		frame.use = true;
		frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		frame.texture = TEXTURE_NONE;

		// メニューの設定
		s_idxMenu = SetMenu(menu, frame);

		// 選択肢の色の設定
		SetColorOption(s_idxMenu, GetColor(COLOR_WHITE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 選ばれていない選択肢の色の設定
		SetColorDefaultOption(s_idxMenu, GetColor(COLOR_WHITE));
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTitle(void)
{
	// メニューの終了
	UninitMenu();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTitle(void)
{
	// 入力
	Input();

	// メニューの更新
	UpdateMenu();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTitle(void)
{
	// 矩形の描画
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// 入力
//--------------------------------------------------
void Input(void)
{
	if (GetFade() != FADE_NONE)
	{// フェードしている
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		switch (s_selectMenu)
		{
		case MENU_GAME:	// ゲーム
			ChangeMode(MODE_GAME);
			break;

		default:
			assert(false);
			break;
		}

		// 選択肢の決定
		DecisionOption();
	}
}
}// namespaceはここまで
