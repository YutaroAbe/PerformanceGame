//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �Q�[���̏��� [battle.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _BATTLE_H_
#define _BATTLE_H_

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define BATTLE_TIMEOVER_FADETIME			(240)	// �^�C���I�[�o�[���̃t�F�[�h����
#define BATTLE_KO_FADETIME					(240)	// KO���̃t�F�[�h����
#define BATTLE_STARTTIME					(240)	// �o�g���X�^�[�g�܂ł̎���
#define BATTLE_SKILLTIME					(30)	// �X�L���g�p���̈Ó]����
#define MAX_LOAD_LINE						(256)	// �ǂݍ��݃e�L�X�g��1�s�̍ő啶����
#define BATTLE_TIME							(30)	// 1ROUND�̎���
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	BATTLESTATE_NONE = 0,		// �������Ă��Ȃ����
	BATTLESTATE_START,			// �J�n���
	BATTLESTATE_NORMAL,			// �ʏ���
	BATTLESTATE_SKILL,			// �X�L���g�p���
	BATTLESTATE_CLEAR,			// �N���A���
	BATTLESTATE_END,			// �I�����
	BATTLESTATE_TIMEOVER,		// ���Ԓ��ߏ��
	BATTLESTATE_MAX				// ����
}BATTLESTATE;

typedef enum
{
	BATTLELEVEL_EASY = 0,		// �C�[�W�[
	BATTLELEVEL_HARD,			// �n�[�h
	BATTLELEVEL_MAX			// ����
}BATTLELEVEL;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitBattle(void);
void UninitBattle(void);
void UpdateBattle(void);
void DrawBattle(void);
void SetBattleState(BATTLESTATE state);
void SetBattleLevel(BATTLELEVEL level);
BATTLESTATE GetBattleState(void);
BATTLESTATE GetBattleStateOld(void);
BATTLELEVEL GetBattleLevel(void);
void SetPauseState(bool bPause);
void SetRulePauseState(bool bRulePause);

#endif
