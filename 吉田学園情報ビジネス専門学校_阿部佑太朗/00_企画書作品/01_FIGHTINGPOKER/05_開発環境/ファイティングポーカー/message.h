//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�Z�[�W���� [message.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // �e�N�X�`���̎�ނ̗񋓑�
	MESSAGE_TEX_ROUND1 = 0,	// ROUND1
	MESSAGE_TEX_ROUND2,		// ROUND2
	MESSAGE_TEX_ROUND3,		// ROUND3
	MESSAGE_TEX_ROUND4,		// ROUND4
	MESSAGE_TEX_ROUND5,		// ROUND5
	MESSAGE_TEX_FIGHT,		// FIGHT
	MESSAGE_TEX_KO,			// KO
	MESSAGE_TEX_TIMEOVER,	// TIMEOVER
	MESSAGE_TEX_MAX,		// ����
}MESSAGE_TEX_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESSAGE_APPEAR_FRAME		(30)				// �o���t���[����
#define MESSAGE_WAIT_FRAME			(30)				// �ҋ@�t���[����
#define MESSAGE_DELETE_FRAME		(10)				// �폜�t���[����
#define MESSAGE_INFO_NUM			(2)					// �C���t�H�̐�
#define MESSAGE_ROUND_FRAME			(10)				// ���E���h�����t���[��
#define MESSAGE_FIGHT_FRAME			(150)				// �t�@�C�g�����t���[��

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitMessage(void);
void UninitMessage(void);
void UpdateMessage(void);
void DrawMessage(void);
void SetMessage(D3DXVECTOR3 pos, float fDestWidth, float fDestHeight, MESSAGE_TEX_TYPE texType);

#endif
