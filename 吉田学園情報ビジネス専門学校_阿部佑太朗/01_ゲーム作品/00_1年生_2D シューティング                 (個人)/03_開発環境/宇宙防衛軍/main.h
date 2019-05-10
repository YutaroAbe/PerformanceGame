//=============================================================================
//
// ���C������ [main.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"								//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)			//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"								//���͎��ɕK�v
#include "xaudio2.h"							//�T�E���h�����ɕK�v

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")					//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")				//[d3d9]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")				//directtx�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")				//�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")				//���͎��ɕK�v
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)					// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)					// �E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_���W�@�b�@���_�J���[ | �e�N�X�`�����W

//*****************************************************************************
//�\���̒�`
//*****************************************************************************
typedef enum
{
	MODE_TITLE = 0,
	MODE_SELECTMODE,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RANKING,
	MODE_RESULT,
	MODE_CLEAR,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;							//���_���W
	float rhw;									//1.0���ŌŒ�
	D3DCOLOR col;								//���_�J���[
	D3DXVECTOR2 tex;							//�e�N�X�`�����W

}VERTEX_2D;
//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void SetMode(MODE mode);
MODE GetMode(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif