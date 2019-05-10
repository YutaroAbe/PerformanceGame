//=============================================================================
//
// ���C������ [main.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <time.h>
#include "d3dx9.h"								//�`�揈���ɕK�v

#define DIRECTINPUT_VERSION (0x0800)			// �x���Ώ��p
#include "dinput.h"								//���͎��ɕK�v
#include "xaudio2.h"							//�T�E���h�����ɕK�v
#include "stdio.h"

//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")				//�`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")				//[d3d9]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")				//directtx�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")				//�V�X�e�������擾�ɕK�v
#pragma comment (lib, "dinput8.lib")			//���͎��ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] /	�@���x�N�g�� / ���_�J���[// �e�N�X�`�����W  )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)

//*****************************************************************************
//�\���̒�`
//*****************************************************************************
//���[�h�ؑ�
typedef enum
{
	MODE_TITLE = 0,		//�@�^�C�g��
	MODE_SELCT,			//�@�Z���N�g
	MODO_TUTORIAL,		//�@TUTORIAL
	MODE_GAME,			//�@�Q�[��
	MODE_CLEAR,			//�@�Q�[���N���A
	MODE_GAMEOVER,		//�@�Q�[���I�[�o�[
	MODE_RANKING,
	MODE_MAX
}MODE;



// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//3D���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`�����W

}VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetMode(MODE mode);
MODE GetMode(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif