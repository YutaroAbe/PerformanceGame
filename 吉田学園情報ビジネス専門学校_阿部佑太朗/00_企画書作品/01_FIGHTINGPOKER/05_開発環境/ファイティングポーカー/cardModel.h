//=============================================================================
//
// ���f������ [model.h]
// Author : �ړc ��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL_TEX	(60)
#define MAX_PLAYER		(2)							// �v���C���[�̍ő吔
#define LOAD_TEXT_1P	"data/TEXT/1PInfo.txt"		// 1P�̏��i�[�e�L�X�g
#define LOAD_TEXT_2P	"data/TEXT/2PInfo.txt"		// 2P�̏��i�[�e�L�X�g
//=============================================================================
// �񋓌^��`(�J�[�h�̎��)
//=============================================================================
typedef enum
{
	TYPE_BRAVE = 0,
	TYPE_KING,
	TYPE_DEVIL,
	TYPE_JOKER,
	TYPE_COMMONER,
	TYPE_GOD,
	TYPE_MAX
}CARDTYPE;

//=============================================================================
//�\���̒�`
//=============================================================================
typedef enum
{
	STATUS_ATTACK = 0,
	STATUS_DEFENSE,
	STATUS_MAX
}PARAM;

typedef enum
{
	CARD_SET = 0,
	CARD_DECK,
	CARD_ENUM_MAX
}POSENUM;
typedef enum
{
	CARD_POS_LEFT = 0,			// ��
	CARD_POS_CENTERLEFT,		// �Z���^�[��
	CARD_POS_CENTER,			// �Z���^�[
	CARD_POS_CENTERRIGHT,		// �E
	CARD_POS_RIGHT,				// �Z���^�[�E
	CARD_POS_MAX
}CARDPOS;

typedef enum
{
	CARD_SIDE_1P,			// 1P
	CARD_SIDE_2P,			// 2P
	CARD_SIDE_ALL,			// 1P��2P�I����
	CARD_SIDE_MAX,
}CARDSIDE;

typedef struct
{
	D3DXVECTOR3 pos;		// ��
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 move;		// �ړ���
	int			ModelType;	// ���f���^�C�v
	D3DXMATRIX  mtxWorld;	// �}�g���b�N�X���[���h
	bool		bUse;       // �g�p���Ă��邩�ǂ���
	CARDPOS		PosType;	// �J�[�h�̃|�W�V����
	D3DXVECTOR3 DestPos;	// �ړI�̈ʒu
	D3DXVECTOR3 distance;	// ����
	bool		bMove;		// �����Ă邩
	bool		bSelect;	// �I�΂�Ă邩
	bool		bChange;	// �`�F���W���Ă��邩
	bool		bSet;		// �Z�b�g���ꂽ���ǂ���
	CARDTYPE type;			// �J�[�h�̎��
	CARDSIDE side;			// �Q�[���̏��
} CardModel;

typedef struct
{
	D3DXVECTOR3			vtxMin;
	D3DXVECTOR3			vtxMax;
	LPD3DXMESH			pMesh;
	LPD3DXBUFFER		pBuffMat;
	DWORD				nNumMat;
	LPDIRECT3DTEXTURE9  pTextureModel[MAX_MODEL_TEX];	// ���f����̂ɑ΂���e�N�X�`��
}CardData;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCardModel(void);
void UninitCardModel(void);
void UpdateCardModel(void);
void DrawCardModel(void);
void PlayerShowSetCard1P(void);
void PlayerShowSetCard2P(void);
void SetSide(CARDSIDE side);
void SetCard(void);														// 1P�E2P�E�R�D�S�ẴJ�[�h��z�u����
void SetCardModel1P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side);	// 1P�̃J�[�h�ݒ�
void SelectCard1P(CARDPOS CardPos);										// �J�[�h��I�ԏ���
void ChangeCard1P(void);												// �I�񂾃J�[�h���R�D�ɓ���������
void CheckHand1P(void);													// ���m�F
void CheckType1P(void);													// �^�C�v�m�F
void WriteText1P(void);													// ��D���L������
void ExchangeCard1P(void);												// �J�[�h�̌���
void LoadText1P(void);
void LoadText2P(void);
D3DXVECTOR3 GetCardPos1P(int nSelectNum);								// 1P�̈ʒu���擾�p
CARDTYPE Get1PHand(int nIndex);											// 1P�̎�D�m�F�p
void SetCardModel2P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side, D3DXVECTOR3 rot);	// 2P�̃J�[�h�ݒ�
void SelectCard2P(CARDPOS CardPos);										// �J�[�h��I�ԏ���
void ChangeCard2P(void);												// �I�񂾃J�[�h���R�D�ɓ���������
void CheckHand2P(void);													// ���m�F
void CheckType2P(void);													// �^�C�v�m�F
void WriteText2P(void);													// ��D���L������
void ExchangeCard2P(void);												// �J�[�h�̌���
void LoadText2P(void);
D3DXVECTOR3 GetCardPos2P(int nSelectNum);								// 2P�̈ʒu���擾�p
CARDTYPE Get2PHand(int nIndex);											// 2P�̎�D�m�F�p
void SetDeckCard(D3DXVECTOR3 pos);										// �R�D�̐ݒ�
void MoveCursor(void);													// �J�[�\���ړ�
void LoadModel(LPDIRECT3DDEVICE9 pDevice);								// ���f���ƃe�N�X�`���̓ǂݍ���
int GetNum(void);
int GetHandNum(int nNowPlayer);
CARDTYPE GetType(int nNowPlayer);
CARDSIDE GetPokerState(void);
D3DXVECTOR3 GetLockPos1P(int nNumber);
D3DXVECTOR3 GetLockPos2P(int nNumber);
int GetNowPlayer(void);
bool GetSet(void);
#endif

