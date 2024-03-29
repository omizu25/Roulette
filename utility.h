//**************************************************
//
// Hackathon ( utility.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// このマクロ定義がされてなかったら
#define _UTILITY_H_	// ２重インクルード防止のマクロ定義

//==================================================
// デバッグ用
//==================================================
#include <crtdbg.h>

//--------------------------------------------------
// 出力にテキストを出力する。
// 引数  : pAngle / 角度
//--------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 角度の正規化
// 引数  : float* pAngle / 角度
//--------------------------------------------------
void NormalizeAngle(float* pAngle);

//--------------------------------------------------
// ホーミング
// 引数1  : D3DXVECTOR3* pPosOut / 位置
// 引数2  : D3DXVECTOR3& inPosNow / 現在の位置
// 引数3  : D3DXVECTOR3& inPosDest / 目的の位置
// 引数4  : float inSpeed / 速さ
// 返値  : bool / 目的の位置に着いたかどうか
//--------------------------------------------------
bool Homing(D3DXVECTOR3* pPosOut, const D3DXVECTOR3& inPosNow, const D3DXVECTOR3& inPosDest, float inSpeed);

//--------------------------------------------------
// 小数点のランダム
// 引数1  : float inMax / 最大値
// 引数2  : float inMin / 最小値
// 返値  : float / ランダム値
//--------------------------------------------------
float FloatRandam(float inMax, float inMin);

//--------------------------------------------------
// 整数のランダム
// 引数1  : int inMax / 最大値
// 引数2  : int inMin / 最小値
// 返値  : int / ランダム値
//--------------------------------------------------
int IntRandam(int inMax, int inMin);

//--------------------------------------------------
// sinカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int inTime / タイム
// 引数2  : float inCycle / 周期
// 返値  : float / 1.0f〜0.0fのsinカーブ
//--------------------------------------------------
float SinCurve(int inTime, float inCycle);

//--------------------------------------------------
// cosカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int inTime / タイム
// 引数2  : float inCycle / 周期
// 返値  : float / 1.0f〜0.0fのcosカーブ
//--------------------------------------------------
float CosCurve(int inTime, float inCycle);

//--------------------------------------------------
// カーブの値が帰ってくる
// 引数1  : float inCurve / カーブ
// 引数2  : float inMax / 最大値
// 引数3  : float inMin / 最小値
// 返値  : float / カーブ
//--------------------------------------------------
float Curve(float inCurve, float inMax, float inMin);

#endif // !_UTILITY_H_
