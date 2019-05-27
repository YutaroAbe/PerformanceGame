//=============================================================================
//
// ���C������ [main.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"
#include "xaudio2.h"				//�T�E���h�����ŕK�v
#include "Xinput.h"
//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "Xinput.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���_�J���[  )
#define	FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
#define		VERTICAL_BLOCK		(40)		//�c�̃u���b�N��
#define		CROSS_BLOCK			(40)		//���̃u���b�N��
#define		VERTICAL_LENGTH		(80.0f)		//�c�̒���
#define		CROSS_LENGTH		(80.0f)		//���̒���
#define		VERTEX_NUMBER		((VERTICAL_BLOCK + 1) * (CROSS_BLOCK + 1))		//���_��
#define		INDEX_NUMBER		(VERTICAL_BLOCK * (CROSS_BLOCK + 1) * 2 + (VERTICAL_BLOCK - 1) * 2 + 1)		//���_��

#define		GAP_CROSS			(0)
#define		GAP_CENTERX			(0)
#define		GAP_CENTERZ			(0)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

typedef enum
{//�A�j���[�V�����̎g�p���
	ANIMATION_NORMAL = 0,
	ANIMATION_FADE,
	ANIMATION_LOOP,
	ANIMATION_UP,
	ANIMATION_MAX,

}ANIMATION;

typedef struct
{
	int nCross;
	int nVertical;

}WallInfo;

typedef enum
{//���[�h�̏��

	MODE_TITLE = 0,		//  �^�C�g��
	MODE_RANKING,		//  �����L���O
	MODE_SELCT,			//�@�Z���N�g
	MODE_GAME,			//  �Q�[�����C��
	MODE_START,			//  �L�������C�N
	MODE_STORY,			//�@�X�g�[���[
	MODE_CREDIT,		//�@�N���W�b�g
	MODE_ENDSTORY,		//	�G���h�X�g�[���[
	MODE_ENDROLL,		//�@�G���h���[��
	MODE_GAMEOVER,		//�@�Q�[���I�[�o�[
	MODE_RESULT,		//  ���U���g
	MODE_MAX

}MODE;

typedef enum
{//window�̕\�����
	WINDOWSTATE_NORMAL = 0,			//�����X�V���Ȃ�
	WINDOWSTATE_Delete0,			//��������
	WINDOWSTATE_VIBRATION,			//�U��
	WINDOWSTATE_LEVELUP,			//���x���A�b�v
	WINDOWSTATE_STEALTH,			//���񂾂�s������->�ʏ�ɂȂ�
	WINDOWSTATE_FADEIN,				//
	WINDOWSTATE_FADEOUT,			//
	WINDOWSTATE_FADEOUT_B,			//
	WINDOWSTATE_FADE_Z,				//�Y�[�����Ȃ��������
	WINDOWSTATE_FADE_ALL,			//�o�Ă��ď���ɏ�����
	WINDOWSTATE_FLASH,				//�_��
	WINDOWSTATE_FLASH2,				//���_��
	WINDOWSTATE_SCROLL0,			//�c�X�N���[��
	WINDOWSTATE_SCROLL1,			//�΃X�N���[�� ������
	WINDOWSTATE_SCROLL2,			//��SCROLL
	WINDOWSTATE_SELECTON,			//�I������Ă�����
	WINDOWSTATE_SELECTOFF,			//�I������Ă��Ȃ����
	WINDOWSTATE_WALL,				//��
	WINDOWSTATE_BG,					//�X�N���[���ɂ����W�ύX
	WINDOWSTATE_FIELD,				//�n��
	WINDOWSTATE_STAMINAGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_MAXSTAMINAGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_LIFEGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_AUTOLIFEGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_MAXLIFEGAGE,		//�Q�[�W�g
	WINDOWSTATE_MPGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_AUTOMPGAGE,		//�����ő�������Q�[�W
	WINDOWSTATE_MAXMPGAGE,		//�Q�[�W�g
	WINDOWSTATE_EXPGAGE,			//GAGE
	WINDOWSTATE_MAXEXPGAGE,			//�ォ�瑝�����Ă���GAGE
	WINDOWSTATE_PLAYER,				//���@�̃p�^�[���ɂ��ύX
	WINDOWSTATE_FLOW,				//�����
	WINDOWSTATE_FLOW0,				//�΂߉E�����痬���
	WINDOWSTATE_FLOW1,				//�΂ߍ������痬���
	WINDOWSTATE_SHOT,				//10�{a0.0f����1�{a1.0f�܂�
	WINDOWSTATE_MAX,

}WINDOWSTATE; typedef enum
{//window�̕\�����
	WINDOWTYPE_CENTER = 0,			//���S
	WINDOWTYPE_LEFT_DOWN,			//����
	WINDOWTYPE_MAX,

}WINDOWTYPE;
typedef enum
{//window�̕\�����
	WINDOW_UPDATE_GAME = 0,			//�Q�[�����̂ݍX�V
	WINDOW_UPDATE_SELECT,			//���ł��X�V
	WINDOW_UPDATE_MAX,

}WINDOW_UPDATE;
typedef enum
{//window�̕\�����
	WINDOW_DRAW_0 = 0,		//�\������
	WINDOW_DRAW_1,
	WINDOW_DRAW_2,
	WINDOW_DRAW_3,
	WINDOW_DRAW_PAUSE,
	WINDOW_DRAW_MAP,
	WINDOW_DRAW_MINIMAP,
	WINDOW_DRAW_MINIMAP0,
	WINDOW_DRAW_FRONT,
	WINDOW_DRAW_TIME,
	WINDOW_DRAW_BACK,
	WINDOW_DRAW_MAX,

}WINDOW_DRAW;

typedef enum
{//window�̎g�p���
	WINDOWUSE_NORMAL = 0,
	WINDOWUSE_GAME,	//�c�@
	WINDOWUSE_SELECT,			//�I��
	WINDOWUSE_GUARD,			//GUARD
	WINDOWUSE_LOAD,				//�ǂݍ��݉�ʂ�
	WINDOWUSE_FONT,				//�������͎� ����
	WINDOWUSE_RANKING,			//RANKING�̎��Ɏg�p�@��Փx�̃��S
	WINDOWUSE_RANKNUMBER,		//RANKING�̎��Ɏg�p�@����
	WINDOWUSE_PLAYER,			//�v���C���[�̏ꍇ
	WINDOWUSE_ENEMY,			//BOSS�G�l�~�[�̏ꍇ
	WINDOWUSE_MAX,

}WINDOWUSE;

typedef enum
{//�����̏��
	FONTSTATE_NONE = 0,
	FONTSTATE_NORMAL,
	FONTSTATE_DELETE,
	FONTSTATE_RANKDOWN,
	FONTSTATE_RANKSET,		//�����L���O���̃Z�b�g
	FONTSTATE_RANKDELETE,	//�����L���O���̃f���[�g
	FONTSTATE_FLASH,		//�_��
	FONTSTATE_FLASH0,		//�_�ō�
	FONTSTATE_FLOW,		//�����

}FONTSTATE;
typedef struct
{
	FONTSTATE	state;		//�����̏��
	D3DXCOLOR	col;		//�J���[
	RECT		rect;		//�����̕\���͈�
	int			nType;		//�t�H���g�̃^�C�v
	int			nFormat;	//�\���ꏊ
	int			nCntState;	//��ԊǗ��p
	int			nMaxFont;	//�\������ő吔
	int			nCntTime;	//�\���̂��߂̃J�E���g
	char		aStr[84];	//�����̗�
	bool		bDisplay;	//�\����\��
	bool		bUse;		//�g�por���g�p
	WINDOW_DRAW draw;
	bool		bshadow;	//�e�̗L��

}Font;

typedef enum
{//�A�j���[�V�����̎g�p���
	EXPLOSIONSTATE_PHIT,		//�v���C���[�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_PHITMINUS,	//�v���C���[�ɂ����蔻��̂��锚�� ����̏�����
	EXPLOSIONSTATE_EHIT,		//�G�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_EFFECT,		//�����蔻�薳��
	EXPLOSIONSTATE_DELETE,		//�����Ă���
	EXPLOSIONSTATE_FADE,
	EXPLOSIONSTATE_GAGE,		//EXP�Q�[�W
	EXPLOSIONSTATE_LOAD,		//LOAD��p
	EXPLOSIONSTATE_DFADE,		//�o�Ă��ď�����

}EXPLOSIONSTATE;

typedef struct
{//���U���g�Ŏg��
	int nCntScore;		//for�ŉ񂳂Ȃ����߃��[�J�����Ə������ɍ���
	int nCntResult;		//���ԃJ�E���g
	int nRankin;		//�n�C�X�R�A���̏��ʕۑ� ���O���͎��g�p
	int nWideFont;		//50���\�̉��I�𕔕�
	int nHightFont;		//50���\�̏c�I�𕔕�
	char aStr[25];		//���O���͂̂���

}Result;

//*********************************************************************************************************//
// �\���̒�`
//*********************************************************************************************************//
typedef enum
{//�X�R�A�̏��
	DIGITALSTATE_NONE = 0,
	DIGITALSTATE_WAVE,
	DIGITALSTATE_DAMAGE,		//�΂߉E���ɃX���C�h
	DIGITALSTATE_HEEL,			//�΂ߍ���ɃX���C�h
	DIGITALSTATE_WAVE0,

}DIGITALSTATE;
typedef struct
{//�X�R�A�̍\����
	D3DXVECTOR3 pos;			//�ꏊ
	D3DXVECTOR3 move;			//�����l
	D3DXCOLOR	col;			//�J���[
	int			nDigital;		// ����
	int			nLengthX;
	int			nLengthY;
	float		fHeight;
	DIGITALSTATE	state;		//���
	int		nCntstate;			//��ԊǗ��p
	bool		bUse;			//�g���Ă邩�g���ĂȂ���

}DIGITAL;

typedef struct
{
	int			nResults;		//�Q�[���I�����
	int			nCntPoint;
	bool		bUse;			//�g�p���Ă邩�ǂ���

}GAME_PLAY;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode, int nFade);
int *GetTime(void);
MODE *GetMode(void);
HWND *GethWnd(void);
GAME_PLAY *GetGame_Play(void);
int *GetStoryTXT(void);
int *GetENDStoryTXT(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾
//*********************************************************************************************************//
void InitFont(void);
void UninitFont(void);
void UpdateFont(void);
void DrawFont(WINDOW_DRAW draw);
void SetFont(RECT rect, D3DXCOLOR col, char *aStr, int nNumber, int nType, int nFormat, int nMaxFont, bool bShadow, FONTSTATE state, WINDOW_DRAW draw);
void ChangeFont(bool bUse, char *aStr, int nNumber, int nStrType, int nMaxFont, int nCntTime, FONTSTATE state, D3DCOLOR col);
void BreakFont(void);
int *GetSetFont(void);
void SetFontDamage(RECT rect, D3DCOLOR col, char *aStr, int nWide, int nHeight, FONTSTATE state);
void FontScroll(D3DXVECTOR3 move);

//*****************************************************************************
// �v���g�^�C�v�錾�@���� �Ă�Animation�S��
//*****************************************************************************
void InitAnimation(void);
void UninitAnimation(void);
void UpdateAnimation(void);
void DrawAnimation(void);
void SetAnimation(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nView, ANIMATION anim);
void BreakAnimation(void);

//*****************************************************************************
// �v���g�^�C�v�錾�@�r���{�[�h
//*****************************************************************************
void InitZWindow(void);
void UninitZWindow(void);
void UpdateZWindow(void);
void DrawZWindow(void);
int SetZWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float nLengthX, float nLengthY, int nType, int nView, WINDOWSTATE state, float fCntState);
void BreakZWindow(void);
void ChangeZWindow(int nCount, float fMax, float fMin, D3DXVECTOR3 pos, bool bUse);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�w�i
//*********************************************************************************************************//
void InitWindow(void);
void UninitWindow(void);
void UpdateWindow(WINDOW_UPDATE update);
void DrawWindow(WINDOW_DRAW draw);
int SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nPtnUV, int nPtnWide, int nPtnHeight
	, int nCntUse, WINDOW_UPDATE nUpdateType, WINDOWSTATE state, WINDOWUSE use, WINDOWTYPE type, WINDOW_DRAW draw);
void BreakWindow(void);
void ChangeWindow(int nCntWindow, D3DXCOLOR col, WINDOWSTATE state);
void CheckGage(float fGage, float fMaxGage, int nCntWindow);
void SelectWindow(int nNumber);
void BackWindow(int nNumber);
void FontWindowMove(int nWide, int nHeight);
void ColPlayerWindow(float fCola);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�t�F�[�h�̃|���S���\������
//*********************************************************************************************************//
void InitFadeWindow(void);
void UninitFadeWindow(void);
void UpdateFadeWindow(void);
void DrawFadeWindow(void);
void SetFadeWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntUse, WINDOWSTATE state, WINDOWUSE use);
void LoadBreakWindow(void);
void BreakFadeWindow(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�w�i
//*********************************************************************************************************//
void InitBGWindow(void);
void UninitBGWindow(void);
void UpdateBGWindow(void);
void DrawBGWindow(void);
void SetBGWindow(D3DXVECTOR3 pos, D3DXCOLOR col, float fSpeed, float fPos, int nLengthX, int nLengthY, int nType, WINDOWSTATE state);
void BreakBGWindow(void);
void BGScroll(D3DXVECTOR3 move);

//*********************************************************************************************************//
// �v���g�^�C�v�錾 ���U���g
//*********************************************************************************************************//
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
int nCntPoint(int nCntFont, int nShadowFont, int *nPoint, int nMaxPoint, bool bCnt);

//*********************************************************************************************************//
// �v���g�^�C�v�錾 �����L���O
//*********************************************************************************************************//
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾 �L�������C�N
//*********************************************************************************************************//
void InitStart(void);
void UninitStart(void);
void UpdateStart(void);
void DrawStart(void);
Result *GetResult(void);
void InputName(int nMode);
void InputName1(void);
void InputName2(void);
void InputName3(void);

//*****************************************************************************
// �v���g�^�C�v�錾�@Animation�S��
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
int SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, ANIMATION anim, EXPLOSIONSTATE state, float steep, int nView);
void ExplosionScroll(D3DXVECTOR3 move);
void BreakExplosion(void);
void CheckEXP(float fEXP, float fMaxEXP, int nCntExplosion);
void ChangeExplosion(int nCntExplosion, EXPLOSIONSTATE state);

//*****************************************************************************
// �v���g�^�C�v�錾  digital
//*****************************************************************************
DIGITAL *GetDigital(void);
void BreakDigital(void);
void DigitalScroll(D3DXVECTOR3 move);
void SetDigital(D3DXVECTOR3 pos, D3DXCOLOR col, DIGITALSTATE state, int nLengthX, int nLengthY, int nDigital);
void DrawDigital(void);
void UpdateDigital(void);
void UninitDigital(void);
void InitDigital(void);
#endif