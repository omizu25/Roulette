//**************************************************
//
// Hackathon ( menu.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _MENU_H_	//このマクロ定義がされてなかったら
#define _MENU_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "texture.h"

//==================================================
// 定義
//==================================================
const int	MAX_OPTION = 56;	// 選択肢の最大数

//==================================================
// 構造体
//==================================================

/*↓ メニューの引数 ↓*/
struct SInMenu
{
	TEXTURE	texture[MAX_OPTION];	// テクスチャ
	int		numUse;					// 使用数
	float	left;					// 左端
	float	right;					// 右端
	float	top;					// 上端
	float	bottom;					// 下端
	float	width;					// 選択肢の幅
	float	height;					// 選択肢の高さ
	bool	sort;					// 並べ方 [ true : 縦 false : 横 ]
};

/*↓ 枠の引数 ↓*/
struct SInFrame
{
	TEXTURE		texture;	// テクスチャ
	D3DXCOLOR	col;		// 色
	bool		use;		// 枠がいるかどうか [ true : いる false : いらない ]
};

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitMenu(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitMenu(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateMenu(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawMenu(void);

//--------------------------------------------------
// 設定
// 引数1  : SInMenu &inMenu / 構造体 メニュー情報
// 引数2  : SInFrame &inFrame / 構造体 枠の情報
// 返値   ; int / 何番目かのインデックス
//--------------------------------------------------
int SetMenu(const SInMenu &inMenu, const SInFrame &inFrame);

//--------------------------------------------------
// 選択肢の色の設定
// 引数1  : int inIdx / メニューのインデックス
// 引数2  : D3DXCOLOR &inColStart / 始まりの色
// 引数3  : D3DXCOLOR &inColEnd / 終わりの色
//--------------------------------------------------
void SetColorOption(int inIdx, const D3DXCOLOR &inColStart, const D3DXCOLOR &inColEnd);

//--------------------------------------------------
// 選ばれていない選択肢の色の設定
// 引数1  : int inIdx / メニューのインデックス
// 引数2  : D3DXCOLOR &inColDefault / 選ばれてない選択肢の色
//--------------------------------------------------
void SetColorDefaultOption(int inIdx, const D3DXCOLOR &inColDefault);

//--------------------------------------------------
// 選択肢の色の初期化
//--------------------------------------------------
void InitColorOption(void);

//--------------------------------------------------
// 選択肢の変更
// 引数  : int inIdx / 選択肢のインデックス
//--------------------------------------------------
void ChangeOption(int inIdx);

//--------------------------------------------------
// 選択肢の決定
//--------------------------------------------------
void DecisionOption(void);

//--------------------------------------------------
// メニューのリセット
// 引数  : int inIdx / メニューのインデックス
//--------------------------------------------------
void ResetMenu(int inIdx);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int inIdx / メニューのインデックス
// 引数2  : bool inDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawMenu(int inIdx, bool inbDraw);

#endif // !_MENU_H_
