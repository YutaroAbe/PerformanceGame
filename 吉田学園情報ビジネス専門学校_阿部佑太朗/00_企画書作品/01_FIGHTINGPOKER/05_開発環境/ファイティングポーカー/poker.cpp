//=============================================================================
//
// ポーカー処理 [poker.cpp]
// Author : 蝦名陸
//
//=============================================================================
#include "main.h"
#include "poker.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "cardModel.h"
#include "timer.h"
#include "ui.h"
#include "3DUi.h"
#include "fade.h"
#include "meshField.h"
//=============================================================================
//ゲームの初期化処理
//=============================================================================
void InitPoker(void)
{
	// カメラの初期化
	InitCamera();

	// モデルの初期化処理
	InitCardModel();

	// フィールドの初期化
	InitField();

	// タイマーの初期化処理
	InitTimer();

	// UIの初期化処理
	InitUI();

	// 3DUIの初期化処理
	Init3DUI();
}
//=============================================================================
//ゲームの終了処理
//=============================================================================
void UninitPoker(void)
{
	// ライトの終了処理
	UninitLight();

	// フィールドの終了処理
	UninitField();

	// タイマーの終了処理
	UninitTimer();

	// UIの終了処理
	UninitUI();

	// 3DUIの終了処理
	Uninit3DUI();

	// カードモデルの終了処理
	UninitCardModel();
}
//=============================================================================
//ゲームの更新
//=============================================================================
void UpdatePoker(void)
{
	// ライトの更新処理
	UpdateLight();

	// フィールドの更新処理
	UpdateField();

	// モデルの更新処理
	UpdateCardModel();

	// タイマーの更新処理
	UpdateTimer();

	// UIの更新所処理
	UpdateUI();

	// 3DUIの更新処理
	Update3DUI();
}
//=============================================================================
//ゲームの描画処理
//=============================================================================
void DrawPoker(void)
{
	// カメラの設定
	SetCamera(0);

	// モデルの描画処理
	DrawCardModel();

	// フィールドの描画処理
	DrawField();

	// UIの描画処理
	DrawUI();

	// タイマーの描画処理
	DrawTimer();

	// 3DUIの描画処理
	Draw3DUI();
}