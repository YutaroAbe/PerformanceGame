//=============================================================================
//
// ���f������ [object.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "game.h"

//*****************************************************************************
// * �}�N���錾 *
//*****************************************************************************
#define	MAX_ENEMY_APPEAR	(16)		//�ő�G�o���n�̐�

//*****************************************************************************
// * �\���̐錾 *
//*****************************************************************************
typedef enum
{//���f���̎��
	//�L�����쐬
	OBJECT_TYPE_000_FLOOR = 0,		//��

	//+ �X�X�e�[�W
	OBJECT_TYPE_100_FLOOR,			//��
	OBJECT_TYPE_100_GATE,			//��
	OBJECT_TYPE_100_FENCE,			//��
	OBJECT_TYPE_100_BACK,			//�o�b�N
	OBJECT_TYPE_100_CROSS,			//��
	OBJECT_TYPE_100_FLOOR_L,		//���g��
	OBJECT_TYPE_100_WOOD,			//��

	//+ �鉺��
	OBJECT_TYPE_200_FLOOR,			//��
	OBJECT_TYPE_200_SIDE_FLOOR,			//��
	OBJECT_TYPE_200_SIDE_FLOOR2,			//��
	OBJECT_TYPE_200_BRIDGE,//��
	OBJECT_TYPE_200_CHAIN,//��
	OBJECT_TYPE_200_HUNSUI,			//����
	OBJECT_TYPE_200_HOME1,			//��1
	OBJECT_TYPE_200_HOME2,			//��2
	OBJECT_TYPE_200_IDO,			//���
	OBJECT_TYPE_200_CHURCH,			//����
	OBJECT_TYPE_200_BABYLON,			//��
	OBJECT_TYPE_200_GAKE,			//�R
	OBJECT_TYPE_200_DOUZOU,			//����
	OBJECT_TYPE_200_GATE,			//����

	//+ ���1�K
	OBJECT_TYPE_300_STAGE,//��
	OBJECT_TYPE_300_WALL,//��
	OBJECT_TYPE_300_WALL02,//����
	OBJECT_TYPE_300_WALL03,//������
	OBJECT_TYPE_300_WALL04,//��&��
	OBJECT_TYPE_300_WALL05,//��
	OBJECT_TYPE_300_WALL06,//��
	OBJECT_TYPE_300_TENJOU,//�V��
	OBJECT_TYPE_300_KAIDAN,//�K�i
	OBJECT_TYPE_300_HASIRA,//��
	OBJECT_TYPE_300_TABLE,//��
	OBJECT_TYPE_300_CHAIR,//�֎q
	OBJECT_TYPE_300_BOOK,//�֎q

	//+ ���2�K
	OBJECT_TYPE_301_FLOOR,//��
	OBJECT_TYPE_301_WALL,//��
	OBJECT_TYPE_301_WALL02,//��
	OBJECT_TYPE_301_WALL03,//��&��
	OBJECT_TYPE_301_WALL_K,//��
	OBJECT_TYPE_301_WALL_K02,//��
	OBJECT_TYPE_301_KAIDAN,//�K�i
	OBJECT_TYPE_301_DOOR,//�h�A
	OBJECT_TYPE_301_KAIGA,//�G��
	OBJECT_TYPE_301_KAIGA02,//�G��
	OBJECT_TYPE_301_KAIGA_KENOU,//�G��
	OBJECT_TYPE_301_YOROI,//�b�h
	//+ ����
	MAP_TYPE_400_FLOOR,//��
	MAP_TYPE_400_DAIZA,//���
	MAP_TYPE_400_GYOKUZA,//�ʍ�
	MAP_TYPE_400_HASIRA02,//�ʍ�

	OBJECT_TYPE_999_Sword0,	//��
	OBJECT_TYPE_999_Sword1,	//��
	OBJECT_TYPE_999_Sword2,	//��

	OBJECT_TYPE_999_PARROW,		//�傫�����
	OBJECT_TYPE_999_PARROWS,	//���@�v���C���[
	OBJECT_TYPE_999_EARROWS,	//���@�G�l�~�[

	
	OBJECT_TYPE_MAX	//�ő�

}OBJECT_TYPE;
typedef enum
{//���f���̎��
	OBJECT_USE_BLOCK = 0,		//�����̕���
	OBJECT_USE_BACK,			//����̂Ȃ�����
	OBJECT_USE_BACK0,			//�w�i ���
	OBJECT_USE_NO,				//�����Ȃ�
	OBJECT_USE_MAP,				//�}�b�v�p

	OBJECT_USE_ITEM,			//�A�C�e���X�^�[�g
	OBJECT_USE_ITEM_HEEL0,		//�񕜃A�C�e��0
	OBJECT_USE_ITEM_HEEL1,		//�񕜃A�C�e��0
	OBJECT_USE_ITEM_HEEL2,		//�񕜃A�C�e��0
	OBJECT_USE_ITEM_GIFT0,		//�X�e�㏸�A�C�e��0
	OBJECT_USE_ITEM_GIFT1,		//�X�e�㏸�A�C�e��0
	OBJECT_USE_ITEM_GIFT2,		//�X�e�㏸�A�C�e��0

}OBJECT_USE;
typedef enum
{//���f���̎��
	OBJECT_STATE_NONE = 0,		//�����Ȃ�
	OBJECT_STATE_SWAYING,		//�h���
	OBJECT_STATE_SPIN,			//���

}OBJECT_STATE;

typedef struct
{//��ނ��Ƃ̃��f�����ۑ�
	LPD3DXMESH		MeshObject = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatObject = NULL;	//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9		pTextureObject = NULL;
	DWORD			nNumMatObject = NULL;	//�}�e���A���̏��
	float			SlengthX;				//�e�̒���
	float			SlengthZ;				//�e�̒���
	char			aText[48];				//�e�L�X�g�̖��O

}OBJECT_DRAW;
typedef struct
{//���f���̏��
	D3DXMATRIX		mtxWorldObject;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		InitPos;				//�n�߂̏ꏊ
	D3DXVECTOR3		pos;					//�ꏊ
	D3DXVECTOR3		rot;					//�p�x
	OBJECT_TYPE		type;					//���f���̎�� ����
	OBJECT_STATE	state;					//���
	OBJECT_USE		use;					//�g����
	D3DXVECTOR3		length;					//����̒���
	int				nCntState;				//�Ǘ��p
	int				nCntShadow;				//�����̉e�̔ԍ�
	bool			bUse;					//�g�p or ���g�p

}OBJECT_INFO;

//*****************************************************************************
// * �v���g�^�C�v�錾 *
//*****************************************************************************
void InitObject(void);
void UninitObject(void);
void LoadObject(int type);
void UpdateObject(void);
void DrawObject(void);
void DrawObject_MAP(int nMode);
int CollisionObject(int nCntModel);
int CollisionObject_Plus(MODEL_SETTING *set);
void CollisionObjectS(D3DXVECTOR3 *pos);
void HitItem(int nCntModel, int nCntObject);
int SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type, OBJECT_USE use, D3DXVECTOR3 length, int nShadow);
void SettingObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumber);
void BreakObject(int nMode);
void SetMap_Change(D3DXVECTOR3 Entrance, D3DXVECTOR3 Export, int nLengthX, int nLengthZ, MAP_TYPE MapNumber);
void BreakMap_Change(void);
void UpdateMap_Change(int nCntModel, int nMode);
void SetLoad_Map(D3DXVECTOR3 Export, MAP_TYPE nMapNumber);
MAP_CHANGE *GetMap_Change(void);
LOAD_MAP *GetLoad_Map(void);
void Enemy_Appear(D3DXVECTOR3 Entrance, int nNumber);
void BreakAppear(void);
ENEMY_APPEAR *GetEnemy_Appear(void);
OBJECT_INFO *GetObject(void);
#endif
