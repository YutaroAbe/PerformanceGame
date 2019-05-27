//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include  "input.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "effect.h"
#include "explosion.h"
#include "block.h"
#include "item.h"
#include "fade.h"
#define PLAYERTEX_X (6.0f)
#define PLAYERTEX_Y (6.0f)

//==============================================================================
//	静的メンバ変数の初期化
//==============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_Texture = NULL;
bool CPlayer::bDisp = true;
int CPlayer::m_nLife = NULL;
D3DXVECTOR3 CPlayer::m_GetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_GetMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CPlayer::m_nTexChange = NULL;										//	テクスチャの変化用の初期化
D3DXVECTOR3  CPlayer::m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3  CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CPlayer::m_nBulletType = NULL;										//　弾の種類の初期化n
float CPlayer::m_fWindth = NULL;
float CPlayer::m_fHeight = NULL;
bool CPlayer::m_bLandDropBlock = false;
CPlayer::PLAYERSTATE CPlayer::m_PlayerState = PLAYERSTATE_NOMAL;
int CPlayer::m_nCounterState = NULL;

//==============================================================================
//	コンストラクタ
//==============================================================================
CPlayer::CPlayer() :CScene2D(3)
{
	m_nCounterAnim = NULL;												//	テクスチャアニメーションの初期化
	m_nPatternAnim = NULL;												//	アニメーションパターンの初期化
	m_nBulletRot = NULL;
	m_nMotionState = NULL;
	m_nMotionStateID = NULL;											//	現在のモーションの保存用変数
	m_bBullet = false;
	m_bLandBlock = NULL;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CPlayer::~CPlayer()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init();

	//	オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_PLAYER);
	m_PlayerState = PLAYERSTATE_NOMAL;
	m_nBulletType = 0;
	m_nTexChange = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nBulletRot = 0;
	m_fWindth = 0;									//	幅
	m_fHeight = 0;									//	高さ
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 15;
	m_nMotionStateID = 0;
	bDisp = true;
	m_bLandDropBlock = false;
	m_nMotionState = 0;
	m_bBullet = false;
	m_bLandBlock = 0;

	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-m_fWindth, -m_fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(m_fWindth,-m_fHeight, 0.0f) ;
	pPos[2] = D3DXVECTOR3(-m_fWindth, 0.0f, 0.0f) ;
	pPos[3] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f) ;
	CScene2D::SetVtxPosition(&pPos[0], pos);

	//テクスチャの設定
	D3DXVECTOR2 tex[4];
	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f/ PLAYERTEX_X), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
	tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
	CScene2D::SetTexture(&tex[0]);

	//	テキストの読み込み
	LoadPlayer();

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	更新処理
//==============================================================================
void CPlayer::Update(void)
{
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();
	D3DXVECTOR2 tex[4];

	switch (m_PlayerState)
	{
	case PLAYERSTATE_NOMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		m_bBullet = false;
		CScene2D::ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			m_PlayerState = PLAYERSTATE_NOMAL;
			CScene2D::ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	case PLAYERSTATE_DEATH:
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			if (pFade->m_fade == pFade->FADE_NONE)
			{//	フェイドが終わったら
				pFade->SetFade(CManager::MODE_RESULT);
				Uninit();
			}

		}
		break;
	}
	if (bDisp == true)
	{
		m_nMotionState = 0;
		D3DXVECTOR3 pos;
		pos = CScene2D::GetPosition();
		m_bLandDropBlock = false;
		m_bLandBlock = false;

		if (pos.x = 600)
		{
			pos.x = 600;
		}
		m_posold = pos;

		if (m_bBullet == false)
		{//	攻撃モーション中じゃない
				//任意のキー(Aキー)が押されたかどうか : 左移動
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetPovTpress(CROSSKEY_LEFT) == true)
			{
				m_move.x += sinf(-D3DX_PI * 0.5) * 2.25f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetPovTpress(CROSSKEY_RIGHT) == true)
			{//任意のキー(Dキー)が押されたかどうか　：右移動
				m_move.x += sinf(D3DX_PI * 0.5) * 2.25f;
			}
		}

		m_move.y += 0.95f;		//重力設定

		if (m_move.y >= 5)
		{
			m_move.y = 5;
		}
		pos.x += m_move.x;
		pos.y += m_move.y;
		m_move.x += (0.0f - m_move.x)*0.425f;
		m_GetMove = m_move;
		m_GetPos = pos;

		for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
		{
			//ブロックの当たり判定
			for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
			{//	オブジェクトの総数分
				CScene2D *pScene;
				pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);
				if (pScene != NULL)
				{
					CScene::OBJTYPE objtype = pScene->GetObjType();
					//-----------------------------------------------------------------------------------------
					//エネミーの当たり判定
					//-----------------------------------------------------------------------------------------
					if (objtype == CScene::OBJECT_ENEMY)
					{
						D3DXVECTOR3 enemy_pos = pScene->GetPosition();		//	敵の位置
						float enemy_fWindth = pScene->GetfWindth();			//	敵の幅
						float  enemy_fHeight = pScene->GetfHeight();			//	敵の高さ
						int nEnemy_Type = pScene->GetType();

						if (pos.x + (m_fWindth / 2) >= enemy_pos.x - (enemy_fWindth / 2) &&
							pos.x - (m_fWindth / 2) <= enemy_pos.x + (enemy_fWindth / 2) &&
							pos.y >= enemy_pos.y - enemy_fHeight &&
							pos.y - m_fHeight <= enemy_pos.y)
						{//	YXが範囲内
							if (m_posold.y <= enemy_pos.y - enemy_fHeight && pos.y >= enemy_pos.y - enemy_fHeight)
							{//	敵の上判定
								pos.y = enemy_pos.y - enemy_fHeight;
								m_move.y -= 15.0f;

								if (nEnemy_Type == 0)
								{//	種類[0]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	種類[1]に当たった時
									HitDamage(2);
								}
								else if (nEnemy_Type == 2)
								{//	種類[2]に当たった時
									HitDamage(1);
								}
							}
							else if (m_posold.y - m_fHeight >= enemy_pos.y  &&
								pos.y - m_fHeight <= enemy_pos.y)
							{//	敵の下判定
								pos.y = enemy_pos.y;
								m_move.y = 0.0f;
								if (nEnemy_Type == 0)
								{//	種類[0]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	種類[1]に当たった時
									HitDamage(2);
								}
								else if (nEnemy_Type == 2)
								{//	種類[2]に当たった時
									HitDamage(1);
								}
							}
							else if (m_posold.x + (m_fWindth / 2) >= enemy_pos.x + (enemy_fWindth / 2) &&
								pos.x - (m_fWindth / 2) <= enemy_pos.x + (enemy_fWindth / 2))
							{//敵の右判定
								pos.x = m_posold.x;
								m_move.x = 10.0f;
								m_move.y = -12.0f;
								if (nEnemy_Type == 0)
								{//	種類[0]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	種類[1]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 2)
								{//	種類[2]に当たった時
									HitDamage(1);
								}
							}
							else if (m_posold.x - (m_fWindth / 2) <= enemy_pos.x - (enemy_fWindth / 2) &&
								pos.x + (m_fWindth / 2) >= enemy_pos.x - (enemy_fWindth / 2))
							{//敵の左判定
								pos.x = m_posold.x;
								m_move.x = -10.0f;
								m_move.y = -12.0f;
								if (nEnemy_Type == 0)
								{//	種類[0]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	種類[1]に当たった時
									HitDamage(1);
								}
								else if (nEnemy_Type == 2)
								{//	種類[2]に当たった時
									HitDamage(1);
								}

							}
						}
					}
					//-----------------------------------------------------------------------------------------
					//ブロックの当たり判定
					//-----------------------------------------------------------------------------------------
					if (objtype == CScene::OBJECT_BLOCK)
					{
						D3DXVECTOR3 block_pos = pScene->GetPosition();		//	ブロックの位置
						D3DXVECTOR3 block_move = pScene->GetMoveing();		//	ブロックの位置
						float block_fWindth = pScene->GetfWindth();			//	ブロックの幅
						float block_fHeight = pScene->GetfHeight();			//	ブロックの高さ
						int nBlock_Type = pScene->GetType();
						if (pos.x + (m_fWindth / 2) >= block_pos.x  &&
										//	プレイヤーが右からめり込んでるとき
							pos.x - (m_fWindth / 2) <= block_pos.x + block_fWindth &&														//	プレイヤーが左からめり込んでるとき
							pos.y >= block_pos.y &&																							//	プレイヤーが上から下にめり込んでるとき
							pos.y - m_fHeight <= block_pos.y + block_fHeight)																//	プレイヤーが下から上にめり込んでるとき
						{//	YXが範囲内
							if (m_posold.y <= block_pos.y && pos.y >= block_pos.y)															//	昔の位置が上に居て現在の位置がプロックにめり込んでるとき
							{//	ブロック上判定
								m_bLandBlock = true;
								pos.y = block_pos.y;
								if (nBlock_Type == CBlock::TYPE_BREAKBLOCK)
								{//	壊れるブロック
									pScene->Uninit();
									CExplosion::Create(D3DXVECTOR3(block_pos.x + block_fWindth / 2, block_pos.y, block_pos.z));
								}
								else if (nBlock_Type == CBlock::TYPE_FALL)
								{//	落ちるブロック
									m_bLandDropBlock = true;
								}
								else if (nBlock_Type == CBlock::TYPE_DAMAGE)
								{//	ダメージ受けるブロック
									HitDamage(1);
									m_move.y -= 17.0f;
								}
							}
							else if (m_posold.y - m_fHeight >= block_pos.y + block_fHeight  &&											//	プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
								pos.y - m_fHeight <= block_pos.y + block_fHeight)														//	現在の位置がめり込んでるとき
							{//	ブロック下判定
								pos.y = block_pos.y + block_fHeight + m_fHeight;														//	プレイヤーをブロック中心+ブロックの高さ+プレイヤーの高さの位置に出現させる
								m_move.y = 0.0f;
								if (nBlock_Type == CBlock::TYPE_ITEMBLOCK)
								{//	アイテム出現用ブロック
									CItem::Create(D3DXVECTOR3(block_pos.x + block_fWindth / 2, block_pos.y, block_pos.z), 1);
									pScene->Uninit();
								}
							}
							else if (m_posold.x + m_fWindth >= block_pos.x + block_fWindth &&											//	昔の位置がブロックより右にあって現在の位置がめり込んでる場合
								pos.x - m_fWindth <= block_pos.x + block_fWindth)
							{//ブロック右判定
								if (nBlock_Type == CBlock::TYPE_STAGE)
								{//	階段用ブロック
									pos.x = block_pos.x += block_fWindth;
									pos.y = block_pos.y;
								}
								else
								{
									pos.x = m_posold.x;
									m_move.x = 4.0f;
								}
							}
							else if (m_posold.x - m_fWindth <= block_pos.x &&																//	昔の位置がブロックより左にあって現在の位置がめり込んでる場合
								pos.x + m_fWindth >= block_pos.x)
							{//ブロック左判定
								if (nBlock_Type == CBlock::TYPE_STAGE)
								{//	階段用ブロック
									pos = block_pos;
								}
								else
								{
									pos.x = m_posold.x;																							//	昔の位置に出現させる
									m_move.x = -4.0f;
								}
							}
						}
					}
				}
			}
		}

		//	頂点情報の設定
		D3DXVECTOR3 pPos[4];
		pPos[0] = D3DXVECTOR3(-m_fWindth, -m_fHeight, 0.0f);
		pPos[1] = D3DXVECTOR3(m_fWindth, -m_fHeight, 0.0f);
		pPos[2] = D3DXVECTOR3(-m_fWindth, 0.0f, 0.0f);
		pPos[3] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f);
		CScene2D::SetVtxPosition(&pPos[0], pos);

		if (m_move.x <= -2.0f)
		{// プレイヤーが左方向に進んだら
			m_nMotionState = 2;
			m_nMotionStateID = m_nMotionState;
		}
		else if (m_move.x >= 2.0f)
		{// プレイヤーが右方向に進んだら
			m_nMotionState = 1;
			m_nMotionStateID = m_nMotionState;
		}

		//if (m_bBullet == false)
		{//	攻撃モーション中じゃない
			if ((pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_B) == true) && m_nMotionStateID == 2)
			{//	攻撃モーション
				m_bBullet = true;
				m_nPatternAnim = 0;
				m_nCounterAnim = 0;
				m_nMotionState = 4;
			}
			else if ((pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_B) == true) && m_nMotionStateID == 1)
			{//	攻撃モーション
				m_bBullet = true;
				m_nPatternAnim = 0;
				m_nCounterAnim = 0;
				m_nMotionState = 3;
			}
		}
		switch (m_nMotionState)
		{//	モーション仕様ナンバー
		case 0://	何もない
			break;
		case 1://	歩行[左方向]
			m_nPatternAnim++;
			m_nTexChange = 0;
			break;
		case 2://	歩行[右方向]
			m_nPatternAnim++;
			m_nTexChange = 1;
			break;
		case 3://	弾投げる[左方向]
			m_nTexChange = 2;
			break;
		case 4://	弾投げる[右方向]
			m_nTexChange = 3;
			break;
		}

		if (m_bLandBlock == true)
		{//ブロックに乗ってたら
			switch (m_nTexChange)
			{
			case 0:	//左方向に歩いている
				m_nCounterAnim++;
				if ((m_nCounterAnim % 7) == 0)
				{
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), 0.0f);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), 0.0f);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					CScene2D::SetTexture(&tex[0]);
				}
				break;
			case 1:	//右方向に歩いている
				m_nCounterAnim++;
				if ((m_nCounterAnim % 7) == 0)
				{
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					CScene2D::SetTexture(&tex[0]);
				}
				break;
			case 2://弾投げる[左方向]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 3)
				{
					m_nBulletRot = 0;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 4 * 3.5f)
				{
					m_nTexChange = 0;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 4) == 0)
				{
					m_nPatternAnim++;
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			case 3://弾投げる[右方向]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 3)
				{
					m_nBulletRot = 1;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 4 * 3.5f)
				{
					m_nTexChange = 1;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 4) == 0)
				{
					m_nPatternAnim++;

					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			}
		}
		if (m_bLandBlock == false)
		{//ブロックに乗ってなかったら
			switch (m_nTexChange)
			{
			case 0:	//左方向に歩いている
				tex[0] = D3DXVECTOR2(0.0f, 0.0f);
				tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X), 0.0f);
				tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
				tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
				CScene2D::SetTexture(&tex[0]);
				break;
			case 1:	//右方向に歩いている
				tex[0] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
				tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
				tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y) * 2);
				tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
				CScene2D::SetTexture(&tex[0]);
				break;
			case 2://空中で弾投げる[左方向]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 2.5)
				{
					m_nBulletRot = 0;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(-6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 6 * 3.0f)
				{
					m_nTexChange = 0;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 6) == 0)
				{
					m_nPatternAnim++;
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			case 3://空中で弾投げる[右方向]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 2.5)
				{
					m_nBulletRot = 1;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(-6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 6 * 3.0f)
				{
					m_nTexChange = 1;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 6) == 0)
				{
					m_nPatternAnim++;

					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 6);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 6);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			}
		}
		if (pos.y >= 760.0f)
		{
			HitDamage(15);

		}
		if (m_bLandBlock == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true || pInputGamepad->GetPovTpress(CROSSKEY_UP) == true)
			{
				m_move.y += cosf(D3DX_PI) * 20.0f;
			}
		}
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CPlayer::Draw(void)
{
	if (bDisp == true)
	{
		CScene2D::Draw();
	}
}

//==============================================================================
//プレイヤーの生成処理
//==============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = {};

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//	ポリゴンの初期化処理
			pPlayer->Init(pos);
			//	弾のテクスチャの割り当て
			pPlayer->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pPlayer;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CPlayer::Laod(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//	テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_PLAYER, &m_Texture);

	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CPlayer::UnLoad(void)
{
	//	テクスチャの破棄
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

//==============================================================================
//	プレイヤーのダメージ設定
//==============================================================================
void  CPlayer::HitDamage(int nDamage)
{
	m_nLife -= nDamage;
	CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);
	if (m_nLife <= 0)
	{//体力が0になったら
		bDisp = false;
		m_PlayerState = PLAYERSTATE_DEATH;
		m_nCounterState = 20;
	}
	else
	{
		m_PlayerState = PLAYERSTATE_DAMAGE;
		m_nCounterState = 15;
	}
}

//==============================================================================
//	プレイヤーの体力回復
//==============================================================================
void CPlayer::UpLife(int nLife)
{
	m_nLife += nLife;

	if (m_nLife >= 15)
	{//	プレイヤーのライフが上限を越した場合固定値にする
		m_nLife = 15;
	}
}
//==============================================================================
//プレイヤーの弾の変化
//==============================================================================
void CPlayer::BulletChange(int nBulletType)
{
	m_nBulletType = nBulletType;
}
//=============================================================================
//	プレイヤーの体力の取得
//==============================================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}
//==============================================================================
//	プレイヤーのポジションの取得
//==============================================================================
D3DXVECTOR3 CPlayer::GetPosition(void)
{
	return m_GetPos;
}
//==============================================================================
//	プレイヤーの動きの取得
//==============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_GetMove;
}
//==============================================================================
//	プレイヤーのテクスチャパターンの取得
//==============================================================================
int CPlayer::GetTexNumber(void)
{
	return m_nTexChange;
}
//==============================================================================
//
//==============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLandDropBlock;
}

//==============================================================================
//	プレイヤーのテキスト読み込み
//==============================================================================
void CPlayer::LoadPlayer(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/player.txt", "r");

	if (pFile != NULL)
	{//	ファイルが開けた場合

		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "PLAYER_SET") == 0)
		{
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "PLAYER_LIFE") == 0)
				{//	プレイヤーのHPの設定
					fscanf(pFile, "%s%d\n", &read[0], &m_nLife);
				}
				else if (strcmp(&read[0], "PLAYER_WINDTH") == 0)
				{//	プレイヤーの幅の設定
					fscanf(pFile, "%s%f\n", &read[0], &m_fWindth);
				}
				else if (strcmp(&read[0], "PLAYER_HEIGTH") == 0)
				{//	プレイヤーの高さの設定
					fscanf(pFile, "%s%f\n", &read[0], &m_fHeight);
				}
			} while (strcmp(&read[0], "PLAYER_END") != 0);

		}
		fclose(pFile);												//*クローズ*
	}
	else
	{
		MessageBox(0, "プレイヤーのテキストに問題があります", "警告", MB_OK);
	}

}