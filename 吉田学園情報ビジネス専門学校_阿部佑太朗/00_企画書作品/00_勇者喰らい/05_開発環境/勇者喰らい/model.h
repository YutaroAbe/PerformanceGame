//=============================================================================
//
// ���f������ [model.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// * �}�N���錾 *
//*****************************************************************************
#define	MAX_MODEL_MOTION	(40)	//���[�V�����̐�

#define MAX_KEY	(12)	//�ő�L�[�t���[����
#define MAX_PARTS	(28)	//�ő�L�[�t���[����
#define MAX_ENEMY	(96)	//��x�ɏo����ő�̓G�̐�

#define ENEMY_ATIME	(100)	//�G���G���U�����郉���hTIME
#define SKILL_TIME	(1800)	//�o�t�̎�������

#define	INIT_ATK			(115.0f)	//�����U����
#define	INIT_INT			(115.0f)	//�����U����
#define	INIT_DFF			(70.0f)		//�����h���
#define	INIT_RES			(70.0f)	//�����U����
#define	INIT_SPD			(70.0f)		//��������
#define	INIT_LUK			(25.0f)		//�����^
#define	INIT_HP				(1000.0f)		//�������C�t
#define	INIT_SP				(60.0f)		//�����X�L���|�C���g
//*****************************************************************************
// * �\���̐錾 *
//*****************************************************************************
typedef enum
{
	MODEL_USE_PLAYER = 0,	//�v���C���[
	MODEL_USE_TUTORIAL,		//�`���[�g���A����p
	MODEL_USE_OBJECT,		//�I�u�W�F�N�g
	MODEL_USE_Title,		//�^�C�g���}��
	MODEL_USE_Pause,		//�|�[�Y�}��
	MODEL_USE_ENEMY_Z,		//�G���I
	MODEL_USE_ENEMY_ZE,		//�G���I
	MODEL_USE_ENEMY_S,		//���{�X
	MODEL_USE_ENEMY_T,		//���{�X
	MODEL_USE_ENEMY_B,		//BOSS

}MODEL_USE;
typedef enum
{//���f���̎��
	MODEL_TYPE_RUN_bodyD,		//�����j���O�}����
	MODEL_TYPE_RUN_bodyU,		//�����j���O�}����
	MODEL_TYPE_RUN_head,		//�����j���O�}����
	MODEL_TYPE_RUN_armUR,		//�����j���O�}���E��r
	MODEL_TYPE_RUN_armDR,		//�����j���O�}���E�O�r
	MODEL_TYPE_RUN_handR,		//�����j���O�}���E��
	MODEL_TYPE_RUN_armUL,		//�����j���O�}������r
	MODEL_TYPE_RUN_armDL,		//�����j���O�}�����O�r
	MODEL_TYPE_RUN_handL,		//�����j���O�}������
	MODEL_TYPE_RUN_legUR,		//�����j���O�}���E�G
	MODEL_TYPE_RUN_legDR,		//�����j���O�}���E��
	MODEL_TYPE_RUN_footR,		//�����j���O�}���E��
	MODEL_TYPE_RUN_legUL,		//�����j���O�}�����G
	MODEL_TYPE_RUN_legDL,		//�����j���O�}������
	MODEL_TYPE_RUN_footL,		//�����j���O�}������
	MODEL_TYPE_RUN_Sword0,		//�����j���O�}����0
	MODEL_TYPE_RUN_Sword1,		//�����j���O�}����1
	MODEL_TYPE_RUN_Sword2,		//�����j���O�}����2

	MODEL_TYPE_PNOR_hip,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_chest,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_neck,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_head,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_chin,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Rhand,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Lhand,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Rleg,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Rknee,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Rfoot,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Lleg,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Lknee,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_Lfoot,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_tail1,		//�v���C���[�m�[�}���^
	MODEL_TYPE_PNOR_tail2,		//�v���C���[�m�[�}���^

	MODEL_TYPE_PATK_hip,		//�v���C���[�U���^
	MODEL_TYPE_PATK_body,		//�v���C���[�U���^
	MODEL_TYPE_PATK_chest,		//�v���C���[�U���^
	MODEL_TYPE_PATK_neck,		//�v���C���[�U���^
	MODEL_TYPE_PATK_head,		//�v���C���[�U���^
	MODEL_TYPE_PATK_chin,		//�v���C���[�U���^
	MODEL_TYPE_PATK_legR,		//�v���C���[�U���^
	MODEL_TYPE_PATK_kneeR,		//�v���C���[�U���^
	MODEL_TYPE_PATK_footR,		//�v���C���[�U���^
	MODEL_TYPE_PATK_legL,		//�v���C���[�U���^
	MODEL_TYPE_PATK_kneeL,		//�v���C���[�U���^
	MODEL_TYPE_PATK_footL,		//�v���C���[�U���^
	MODEL_TYPE_PATK_shoulderR,	//�v���C���[�U���^
	MODEL_TYPE_PATK_armR,		//�v���C���[�U���^
	MODEL_TYPE_PATK_handR,		//�v���C���[�U���^
	MODEL_TYPE_PATK_shoulderL,	//�v���C���[�U���^
	MODEL_TYPE_PATK_armL,		//�v���C���[�U���^
	MODEL_TYPE_PATK_handL,		//�v���C���[�U���^
	MODEL_TYPE_PATK_tail1,		//�v���C���[�U���^
	MODEL_TYPE_PATK_tail2,		//�v���C���[�U���^

	MODEL_TYPE_PINT_body3,		//�v���C���[���@�^
	MODEL_TYPE_PINT_body2,		//�v���C���[���@�^
	MODEL_TYPE_PINT_body1,		//�v���C���[���@�^
	MODEL_TYPE_PINT_body0,		//�v���C���[���@�^
	MODEL_TYPE_PINT_neck,		//�v���C���[���@�^
	MODEL_TYPE_PINT_head,		//�v���C���[���@�^
	MODEL_TYPE_PINT_chin,		//�v���C���[���@�^
	MODEL_TYPE_PINT_tail0,		//�v���C���[���@�^
	MODEL_TYPE_PINT_tail1,		//�v���C���[���@�^
	MODEL_TYPE_PINT_wingS,		//�v���C���[���@�^
	MODEL_TYPE_PINT_wingL,		//�v���C���[���@�^
	MODEL_TYPE_PINT_wingR,		//�v���C���[���@�^
	MODEL_TYPE_PINT_armLU,		//�v���C���[���@�^
	MODEL_TYPE_PINT_armLD,		//�v���C���[���@�^
	MODEL_TYPE_PINT_handL,		//�v���C���[���@�^
	MODEL_TYPE_PINT_armRU,		//�v���C���[���@�^
	MODEL_TYPE_PINT_armRD,		//�v���C���[���@�^
	MODEL_TYPE_PINT_handR,		//�v���C���[���@�^
	MODEL_TYPE_PINT_legLU,		//�v���C���[���@�^
	MODEL_TYPE_PINT_legLD,		//�v���C���[���@�^
	MODEL_TYPE_PINT_footL,		//�v���C���[���@�^
	MODEL_TYPE_PINT_legRU,		//�v���C���[���@�^
	MODEL_TYPE_PINT_legRD,		//�v���C���[���@�^
	MODEL_TYPE_PINT_footR,		//�v���C���[���@�^

	MODEL_TYPE_PSPD_hip,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_third_body,	//�v���C���[���x�^
	MODEL_TYPE_PSPD_second_body,//�v���C���[���x�^
	MODEL_TYPE_PSPD_chest,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_head,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_chin,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rleg,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rknee,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rfoot,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Lleg,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Lknee,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Lfoot,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rshoulder,	//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rarm,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Rhand,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Lshoulder,	//�v���C���[���x�^
	MODEL_TYPE_PSPD_Larm,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_Lhand,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_tail1,		//�v���C���[���x�^
	MODEL_TYPE_PSPD_tail2,		//�v���C���[���x�^

	MODEL_TYPE_EKING_bodyD,		//�G�@����
	MODEL_TYPE_EKING_bodyU,		//�G�@����
	MODEL_TYPE_EKING_head,		//�G�@����
	MODEL_TYPE_EKING_armUR,		//�G�@����
	MODEL_TYPE_EKING_armDR,		//�G�@����
	MODEL_TYPE_EKING_handR,		//�G�@����
	MODEL_TYPE_EKING_armUL,		//�G�@����
	MODEL_TYPE_EKING_armDL,		//�G�@����
	MODEL_TYPE_EKING_handL,		//�G�@����
	MODEL_TYPE_EKING_legUR,		//�G�@����
	MODEL_TYPE_EKING_legDR,		//�G�@����
	MODEL_TYPE_EKING_footR,		//�G�@����
	MODEL_TYPE_EKING_legUL,		//�G�@����
	MODEL_TYPE_EKING_legDL,		//�G�@����
	MODEL_TYPE_EKING_footL,		//�G�@����
	MODEL_TYPE_EKING_Sword,		//�G�@����

	MODEL_TYPE_EWarrior_bodyD,	//�G�@��m
	MODEL_TYPE_EWarrior_bodyU,	//�G�@��m
	MODEL_TYPE_EWarrior_head,	//�G�@��m
	MODEL_TYPE_EWarrior_armUR,	//�G�@��m
	MODEL_TYPE_EWarrior_armDR,	//�G�@��m
	MODEL_TYPE_EWarrior_handR,	//�G�@��m
	MODEL_TYPE_EWarrior_armUL,	//�G�@��m
	MODEL_TYPE_EWarrior_armDL,	//�G�@��m
	MODEL_TYPE_EWarrior_handL,	//�G�@��m
	MODEL_TYPE_EWarrior_legUR,	//�G�@��m
	MODEL_TYPE_EWarrior_legDR,	//�G�@��m
	MODEL_TYPE_EWarrior_footR,	//�G�@��m
	MODEL_TYPE_EWarrior_legUL,	//�G�@��m
	MODEL_TYPE_EWarrior_legDL,	//�G�@��m
	MODEL_TYPE_EWarrior_footL,	//�G�@��m
	MODEL_TYPE_EWarrior_Sword,	//�G�@��m

	MODEL_TYPE_ENinja_bodyD,	//�G�@�E��
	MODEL_TYPE_ENinja_bodyU,	//�G�@�E��
	MODEL_TYPE_ENinja_head,		//�G�@�E��
	MODEL_TYPE_ENinja_armUR,	//�G�@�E��
	MODEL_TYPE_ENinja_armDR,	//�G�@�E��
	MODEL_TYPE_ENinja_handR,	//�G�@�E��
	MODEL_TYPE_ENinja_armUL,	//�G�@�E��
	MODEL_TYPE_ENinja_armDL,	//�G�@�E��
	MODEL_TYPE_ENinja_handL,	//�G�@�E��
	MODEL_TYPE_ENinja_legUR,	//�G�@�E��
	MODEL_TYPE_ENinja_legDR,	//�G�@�E��
	MODEL_TYPE_ENinja_footR,	//�G�@�E��
	MODEL_TYPE_ENinja_legUL,	//�G�@�E��
	MODEL_TYPE_ENinja_legDL,	//�G�@�E��
	MODEL_TYPE_ENinja_footL,	//�G�@�E��
	MODEL_TYPE_ENinja_Sword1,	//�G�@�E��
	MODEL_TYPE_ENinja_Sword2,	//�G�@�E��

	MODEL_TYPE_EWizard_bodyD,	//�G�@���@�g��
	MODEL_TYPE_EWizard_bodyU,	//�G�@���@�g��
	MODEL_TYPE_EWizard_head,	//�G�@���@�g��
	MODEL_TYPE_EWizard_armUR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_armDR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_handR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_armUL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_armDL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_handL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_legUR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_legDR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_footR,	//�G�@���@�g��
	MODEL_TYPE_EWizard_legUL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_legDL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_footL,	//�G�@���@�g��
	MODEL_TYPE_EWizard_Sword,	//�G�@���@�g��

	MODEL_TYPE_ESoldiers_bodyD,	//�G�@���m
	MODEL_TYPE_ESoldiers_bodyU,	//�G�@���m
	MODEL_TYPE_ESoldiers_head,	//�G�@���m
	MODEL_TYPE_ESoldiers_armUR,	//�G�@���m
	MODEL_TYPE_ESoldiers_armDR,	//�G�@���m
	MODEL_TYPE_ESoldiers_handR,	//�G�@���m
	MODEL_TYPE_ESoldiers_armUL,	//�G�@���m
	MODEL_TYPE_ESoldiers_armDL,	//�G�@���m
	MODEL_TYPE_ESoldiers_handL,	//�G�@���m
	MODEL_TYPE_ESoldiers_legUR,	//�G�@���m
	MODEL_TYPE_ESoldiers_legDR,	//�G�@���m
	MODEL_TYPE_ESoldiers_footR,	//�G�@���m
	MODEL_TYPE_ESoldiers_legUL,	//�G�@���m
	MODEL_TYPE_ESoldiers_legDL,	//�G�@���m
	MODEL_TYPE_ESoldiers_footL,	//�G�@���m
	MODEL_TYPE_ESoldiers_Sword,	//�G�@���m

	MODEL_TYPE_EMPTY			//�����

}MODEL_TYPE;

typedef enum
{
	MODEL_STATE_NONE = 0,	//�����Ȃ�(�L�E�ցE`)
	MODEL_STATE_ATK,		//�U����
	MODEL_STATE_ATKHIT,		//�U������������
	MODEL_STATE_POISED,		//�K�[�h�̍\��
	MODEL_STATE_GUARD,		//�K�[�h����
	MODEL_STATE_DAMAGE,		//��_�����@�X�L���L�����Z���ł��Ȃ�
	MODEL_STATE_DIE,		//���S�@�X�L���L�����Z���ł��Ȃ�
	MODEL_STATE_MAP,		//�}�b�v�؂�ւ��� �����Ȃ�

}MODEL_STATE;
typedef struct
{//�L�����N�^�[�̃X�e�[�^�X
	float	fLifePoint;		//HP
	float	fSkillPoint;	//SP
	float	fAttack;		//�U����
	float	fDefense;		//�h���
	float	fSpeed;			//����, �X�^�~�i
	float	fLucky;			//�^, ��S��, ��S���

	float	fInt;			//���U	SP���f
	float	fRes;			//���h	�񕜗ʔ��f

}CHAR_STATUS;
typedef struct
{//�L�����N�^�[�̃X�e�[�^�X
	char	aName[25];		//���O
	int		nLevel;			//���x��
	int		nCareer;		//�E��
	int		nStrength;		//�퓬�� �o���l
	int		nExperience;	//���݂̌o���l
	int		nNextLevel;		//���̃��x���܂ł̌o���l
	int		nLifePoint;		//���݂�HP
	int		nSkillPoint;	//���݂�SP
	int		nStamina;		//�X�^�~�i�Q�[�W
	int		nMaxStamina;	//�ő�X�^�~�i�Q�[�W
	int		nTimeStamina;	//�X�^�~�i�̉񕜑҂�����
	int		nSkill[2][5];	//�����Ă���X�L��2�Ɓ@0:�X�L���ԍ� 1: 2: 3:�ǉ� 4:�X�L����������
	CHAR_STATUS status;		//�v�Z���ꂽ�X�e�[�^�X
	CHAR_STATUS gifted;		//�˔\(���O����̑��蕨) ���j���˔\+
	CHAR_STATUS plus[2];	//�㏸�X�e�[�^�X�ƃJ�E���g�p

}CHAR_DATA;

//*****************************************************************************
// �}�b�v�؂�ւ��̍\����
//*****************************************************************************
typedef enum
{//���f���̎��
	MAP_TYPE_EMPTY = 0,		//�؂�ւ�����
	MAP_TYPE_000_CHAR_MAKE,		//�X
	MAP_TYPE_100_YEUNG,		//�X
	MAP_TYPE_200_CITY,	//�鉺��
	MAP_TYPE_300_CASTLE,		//��1F
	MAP_TYPE_301_CASTLE,		//��2F
	MAP_TYPE_400_THRONE,	//�ʍ�

}MAP_TYPE;
typedef struct
{
	MAP_TYPE	MapNumber;		//�}�b�v�̔ԍ�
	D3DXVECTOR3 Entrance;		//����
	D3DXVECTOR3 Export;			//�o��
	int			nLengthX;		//�͈�X
	int			nLengthZ;		//�͈�Z
	bool		bUse;			//�g�p���Ă邩�ǂ���

}MAP_CHANGE;
typedef struct
{
	D3DXVECTOR3 Export;			//�o��
	MAP_TYPE	nMapNumber;		//�}�b�v�̔ԍ�

}LOAD_MAP;

typedef enum
{
	BUTTON_W = 0,	//W
	BUTTON_A,	//A
	BUTTON_S,	//S
	BUTTON_D,	//D
	BUTTON_WS,	//W
	BUTTON_AS,	//A
	BUTTON_SS,	//S
	BUTTON_DS,	//D
	BUTTON_UP,	//W
	BUTTON_LEFT,	//A
	BUTTON_DOWN,	//S
	BUTTON_RIGHT,	//D
	BUTTON_E,	//E
	BUTTON_Q,	//Q
	BUTTON_X,	//X
	BUTTON_C,	//C
	BUTTON_Z,	//Z
	BUTTON_LSHIFT,	//LSHIFT
	BUTTON_LCTRL,	//ENTER
	BUTTON_SPACE,	//SPACE
	BUTTON_ENTER,	//ENTER
	BUTTON_JENTER,	//ENTER
	BUTTON_BACKSPACE,	//SPACE
	BUTTON_U,	//U
	BUTTON_O,	//O
	BUTTON_Y,	//Y
	BUTTON_H,	//H
	BUTTON_US,	//U
	BUTTON_OS,	//O
	BUTTON_YS,	//Y
	BUTTON_HS,	//H
	BUTTON_J,	//J
	BUTTON_K,	//K
	BUTTON_I,	//I
	BUTTON_L,	//L
	BUTTON_P,	//P
	BUTTON_MAX,	//�ő�button��

}BUTTON;
typedef enum
{
	JAYPAD_STATE_SELECT = 0,	//SELECT��ʂ̎�
	JAYPAD_STATE_GAME,			//�Q�[���̎�

}JAYPAD_STATE;
typedef enum
{
	SDROP_STATE_NONE = 0,	//�����Ȃ�
	SDROP_STATE_SELECT,		//�Q�[���̎�
	SDROP_STATE_END,		//�I����
				
}SDROP_STATE;
typedef struct
{//�L�����N�^�[�̃X�e�[�^�X
	JAYPAD_STATE	state;			//�{�^���̓��͏����p
	int		nCntHPGage[3];			//HP�̃Q�[�W�ԍ�
	int		nCntMPGage[3];			//MP�̃Q�[�W�ԍ�
	int		nCntEXPGage[2];			//EXP�̃Q�[�W�ԍ�
	int		nCntSkillWindow[2];		//��X�L���Ƌ��X�L���̔ԍ�
	int		nCntStamina[2];			//�X�^�~�i�Q�[�W�ԍ�
	int		nCntGageWindow;			//HP�Q�[�W�̑���
	int		nTime[2];				//���ԃJ�E���g
	int		nCntIcon[8];			//�U���㏸���̃A�C�R��
	int		nCntModel_P;			//�|�[�Y���̃��f��
	int		nCntModel_M;			//MAP�p���f��
	
	SDROP_STATE SDstate;			//��ԊǗ��Ǘ��@�X�L���h���b�v
	int		nCntSDstate;				//�J�E���g�p
	int		nDSkill[3];				//�h���b�v�����X�L���ۑ�
	int		nCntDWindow[3];			//�E, ��, ���̑I�����̔ԍ��ۑ�

	MAP_TYPE	maptype;			//���݂���}�b�v
	D3DXVECTOR3	target;				//�ڎw���ꏊ
	int			nCntTarget;			//�|���S���ԍ�
	bool		bTarget;			//�ڎw���ꏊ�̗L��

	int			nScnSpeech;			//�ǂ̃V�[����
	int			nNumSpeech;			//�ǂ��܂Řb������
	int			nCntSpeech;			//�E�B���h�E�ԍ�
	int			nCntSTime;			//��b�̑҂����ԃJ�E���g
	int			nCntSStop;			//��b�̑҂����ԍ��v

	bool	bButton[BUTTON_MAX];
	bool	bJoyUse;				//�W���C�p�b�h�̎g�p���g�p
	bool	bGame;
}PLAYER;
typedef struct
{//�L�����N�^�[�̃X�e�[�^�X
	int		nCntHPGage[3];		//HP�̃Q�[�W�ԍ�
	int		nDistance;
	int		nAction[3];
	int		nCntTime;
	int		nMaxTime;
	int		nDying;				//0:���S, 1:�m��, 2:�ʏ�, 3:�m������
	int		nDSkill[2];			//���Ƃ��X�L��2��
	int		nItem;				//���Ƃ��A�C�e��
	int		nDropS;				//�X�L���𗎂Ƃ��m��(�{��)
	int		nDropI;				//�A�C�e���𗎂Ƃ��m��(�{��)
	bool	bUse;				//�g�por���g�p

}ENEMY;

//*****************************************************************************
// * �\���̐錾 ���f���̐e�q�֌W�ɂ��� *
//*****************************************************************************
typedef struct
{//�e�q�֌W
	MODEL_TYPE		type;					//���f���̎�� ����
	int				nParent;				//�e�̔ԍ�
	D3DXMATRIX		mtxWorldModel;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		addrot;					//���Z�̌��� ���[�V����
	D3DXVECTOR3		addRotmove;				//���[�V�����̈ړ�

}MODEL_PARENT;
typedef struct
{//�e�q�֌W�̃Z�b�g
	int				nMaxModel;				//���ɓ����Ă��郂�f����
	MODEL_PARENT	parent[MAX_PARTS];		//���f���̎�� ����
	MODEL_STATE		state;					//�L�����X�e�[�g
	int				nCntState;				//��ԊǗ��p	���݂ɂ����g��Ȃ�...
	D3DXVECTOR3		Initpos;				//�����ʒu...�G���[�Ώ��p...
	D3DXVECTOR3		pos;					//�v���C���[�̌��_
	D3DXVECTOR3		rot;					//�v���C���[�̌���
	D3DXVECTOR3		move;					//���f���̈ʒu
	D3DXVECTOR3		addpos;					//���Z�̈ʒu ���[�V����
	D3DXVECTOR3		addPosmove;				//���[�V�����̈ړ�
	D3DXVECTOR3		angle;					//�ړ�����
	D3DXVECTOR3		posold;					//�O��̃��f���̈ʒu
	int				nSkillTime[2];			//�X�L���̑ҋ@����
	int				nCntHeel;				//�񕜎��ԃJ�E���g
	int				nAirTime;				//���G����
	int				nPlayTime;				//P:�w���̗L������ E:�w���̑҂�����
	int				nNumMotion[6];			//0:���[�V�����f�[�^ 1:���݂̃��[�V���� 2:���̃��[�V���� 3:�L�[�ԍ� 4:�L�[�̃t���[���� 5:�O�̃��[�V����
	int				nMotionFrame;			//MOTION�S�̂̃t���[�������J�E���g
	int				nLeg;					//�E�����o���Ă��邩�������o���Ă��邩
	int				nLockChar;				//lock���Ă���L����
	int				nCntChar;				//�����̃L�����ԍ�
	float			fSpeed;					//�ړ����x
	float			fPos;					//Y���Ԃ����̕⏕
	float			fSlength;				//�e�̒��� �����蔻��
	float			fHeight;				//�����蔻��
	bool			bStep;					//�X�e�b�v�������ǂ���
	bool			bJump;					//�n��ɂ��邩�ǂ���
	bool			bRun;					//�����Ă��邩�ǂ���

}MODEL_SETTING;

//*****************************************************************************
// * �\���̐錾 ���[�V�����ɂ��� *
//*****************************************************************************
typedef struct
{//�e�q�֌W
	int				nMuse;				//move�̉��Z  0:�P��, 1:�i��
	int				nAtkFrame[2];		//�n�܂肩��I���܂ł̍U���L���t���[��
	int				nParts;				//�U�����镔�� �n2������ ���2���Ȃ���͈�
	int				nInvincible;		//�q�b�g���̖��G�ɂȂ鎞��
	int				nFloating;			//���V����or����
	int				nAtkEffect;			//�U���ɂ����ʁ@�e����񂾂�
	int				nShowEffect;		//�G�t�F�N�g�^�C�v
	float			fFrame;				//������t���[����
	float			fRange;				//�U���͈�
	float			fAtkplus;			//�U���̔{�� ���ݎ��Ԍv�Z�����p
	float			fSlip;				//����{��
	D3DXVECTOR3		blown;				//������ԋ���
	D3DXVECTOR3		move;				//�ړ��l
	D3DXVECTOR3		pos;			//���[�V�����̈ʒu
	D3DXVECTOR3		rot[MAX_PARTS];			//���[�V�����̌���

}MODEL_KEY;
typedef struct
{//�e�q�֌W
	int				nKey;					//�L�[��
	int				nCancel[2];				//�n�܂肩��I���܂ł̃L�����Z���L���t���[��
	int				nBranch[4];				//�h���ۑ�  0:�ʏ펞  1:��U��  2:���U�� 3:���n����
	float			fFastFrame;				//�����l�܂ł̉��Z�t���[����	�펞���@���[�v�L����l����
	float			fEndFreame;			//���̂܂܎��̃��[�V�����ɂȂ�܂ł̍d������+
	float			fCancelFreame;			//�L�����Z�������̃��[�V�����ɂȂ�܂ł̍d������+
	MODEL_KEY		key[MAX_KEY];

}MODEL_MOTION;

//*****************************************************************************
// * �\���̐錾 ���f���̕\���ɂ��� *
//*****************************************************************************
typedef struct
{//��ނ��Ƃ̃��f�����ۑ�
	LPD3DXMESH		MeshModel = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
	DWORD			nNumMatModel = NULL;	//�}�e���A���̏��
	D3DXVECTOR3		addpos;					//���f���̈ʒu
	D3DXVECTOR3		addrot;					//���f���̌���
	int				nTexture;				//�e�N�X�`��
	char			aText[48];				//�e�L�X�g�̖��O

}MODEL_DRAW;
typedef struct
{//���f���̏��
	CHAR_DATA		data;					//�L�����f�[�^
	MODEL_SETTING	set;					//���f���̎�� ����
	MODEL_USE		use;					//���f���̎g����
	int				nCntShadow;				//�����̉e�̔ԍ�
	int				nCntObject;				//�����̉e�̔ԍ�
	bool			bUse;					//�g�p or ���g�p

}MODEL_INFO;

//*****************************************************************************
// * �v���g�^�C�v�錾 *
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void LoadModel(int type);

void UpdateModel(void);
void UpdatePlayer(int nCount);
void UpdateModel_P(void);

void UpdateSpeech(void);
void Speech_Tutorial(void);

void UpdateEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);
void UpdateSubEnemy(MODEL_SETTING *set, CHAR_DATA *data, float fRot, bool bMove);
void UpdateBEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);
void UpdateTEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);
void UpdateSEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);
void UpdateZEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);
void UpdateZEnemyE(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode);

void PointEnemy(MODEL_SETTING *set, int nRand);
void MotionEffect_A(int nCount, int nEnemy, float fAtk, float *fHeel, float *fPredator);
void SadnessError(int nCount);	//���タ���Ə�����...
void LockOn_MODEL(int nCount);
float ReturnAngle(MODEL_SETTING *set);
void CollisionModel(int nCount);
void UpdateMotion(int nCount);
void ResetMotion(MODEL_SETTING *set);
int MotionSkill(int nCntMotion);
void MotionEffect_S(int nMode, int nCount);
void Attackjudge(void);
void Hitjudge(int nCntModel, int nCntBullet, int nCntAtk, int nInvincible, float fRange, float fAtk, float fAtkplus, D3DXVECTOR3 blown, D3DXMATRIX	mtxParts, int nMode);

void DropSkill(int nSkill);
void SwapSkill(int nNumber, int nCount);
void PlusSkill(int *nSkill, int nCount);
void SkillEffect_S(int *nSkill, int nCount);
void SkillEffect_A(int *nSkill, int nCount, int nEnemy, float *fAtk, float *fHeel, float *fPredator);
void ReturnSkillName_P(char *aName, int *nSkill);
void ReturnSkillName(char *aName, int nSkill);

void DrawModel(void);
void DrawModel_P(void);
int SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_USE use, MODEL_SETTING *pSet, CHAR_DATA *data, float fSlength, float fHeight);
int SetEnemy(CHAR_DATA *data, D3DXVECTOR3 pos, MODEL_TYPE type);

void SetEnemySkill(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy);
void SetEnemySkill_100(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy);
void SetEnemySkill_200(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy);
void SetEnemySkill_300(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy);
void SetEnemySkill_301(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy);

void BreakEnemy(void);
void BreakModel(int nUse);
void GetStatus(CHAR_DATA *data, bool bInit);
CHAR_DATA GetGifted(char *Name);
void ShowStatus0(CHAR_DATA data, char *aStr);
void ShowStatus(CHAR_DATA data, CHAR_DATA data0);
CHAR_STATUS GetCareer(int nCareer, char *aCareer);

void SetRunningman(MODEL_SETTING *set, MODEL_TYPE type);
void Set_P_NOR(MODEL_SETTING *set);
void Set_P_ATK(MODEL_SETTING *set);
void Set_P_INT(MODEL_SETTING *set);
void Set_P_SPD(MODEL_SETTING *set);
void Set_E_KING(MODEL_SETTING *set);
void Set_E_WARRIOR(MODEL_SETTING *set);
void Set_E_NINJA(MODEL_SETTING *set);
void Set_E_WIZARD(MODEL_SETTING *set);
void Set_E_SOLDIERS(MODEL_SETTING *set);

MODEL_INFO *GetModel_Info(void);
MODEL_MOTION *GetModel_Motion(void);
PLAYER *GetPlayer(void);
ENEMY *GetEnemy(void);
CHAR_DATA *GetChar_Data(void);
void InitChar_Data(int nLevel);
void LoadChar_Data(CHAR_DATA *data);
void SaveChar_Data(CHAR_DATA Pdata);
void CorrectionChar_Data(void);
#endif