//**************************************************
//
// Hackathon ( number.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _NUMBER_H_	//このマクロ定義がされてなかったら
#define _NUMBER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "texture.h"

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitNumber(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitNumber(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateNumber(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawNumber(void);

//--------------------------------------------------
// 設定
// 引数1  : D3DXVECTOR3 &inPos / 中心の位置
// 引数2  : D3DXVECTOR3 &inSize / サイズ
// 引数3  : D3DXCOLOR &inCol / 色
// 引数4  : int inNumber / 数
// 引数5  : int inDigit / 桁数
// 引数6  : bool inZero / 0を表示するかどうか
// 返値  : int / 配列のインデックス
//--------------------------------------------------
int SetNumber(const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize, const D3DXCOLOR &inCol, int inNumber, int inDigit, bool inZero);

//--------------------------------------------------
// 位置の設定
// 引数1  : int inIdx / 配列のインデックス
// 引数2  : D3DXVECTOR3 &inPos / 中心の位置
// 引数3  : D3DXVECTOR3 &inSize / サイズ
//--------------------------------------------------
void SetPosNumber(int inIdx, const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize);

//--------------------------------------------------
// 変更
// 引数1  : int inIdx / 配列のインデックス
// 引数2  : int inNumber / 数
// 返値  : int / 新しい配列のインデックス
//--------------------------------------------------
int ChangeNumber(int inIdx, int inNumber);

//--------------------------------------------------
// 使うのを止める
// 引数  : int inIdx / インデックス
//--------------------------------------------------
void StopUseNumber(int inIdx);

//--------------------------------------------------
// 桁数
// 引数  : int inNumber / 数
// 返値  : int / 桁数
//--------------------------------------------------
int DigitNumber(int inNumber);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int inIdx / インデックス
// 引数2  : bool inDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawNumber(int inIdx, bool inDraw);

//--------------------------------------------------
// テクスチャの変更
// 引数1  : int inIdx / インデックス
// 引数2  : TEXTURE inTexture / 列挙型 種類
//--------------------------------------------------
void ChangeTextureNumber(int inIdx, TEXTURE inTexture);

#endif // !_NUMBER_H_
