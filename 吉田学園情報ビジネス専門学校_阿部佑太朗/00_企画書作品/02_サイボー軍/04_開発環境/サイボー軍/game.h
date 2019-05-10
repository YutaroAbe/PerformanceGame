//=============================================================================
//
// �Q�[���̏��� [manager.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"
#include "player.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define EMEMY_NUM_MAX (128)
#define ITEM_NUM_MAX (128)
#define	BLOCK_NUM_MAX (128)
//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CGame
{
public:

	typedef enum
	{
		GAMESTATE_NONE = 0,				//�������Ă��Ȃ�
		GAMESTATE0_NORMAL,				//�ʏ���
		GAMESTATE_END,					//�I�[�o�[���
		GAMESTATE_CLEAR,				//�N���A���
		GAMESTATE_MAX
	}GAMESTATE;

	typedef enum
	{//	�X�e�[�W�̃��[�h�ݒ�
		SETSTEGEMODE_000 = 0,	//	�`���[�g���A���X�e�[�W
		SETSTEGEMODE_001,		//	�X�e�[�W1
		SETSTEGEMODE_002,		//	�X�e�[�W2
		SETSTEGEMODE_MAX
	}SETSTEGEMODE;
	CGame();																// �R���X�g���N�^
	~CGame();																// �f�X�g���N�^
	 HRESULT Init(void);													// ����������
	 void Uninit(void);														// �I������
	 void Update(void);														// �X�V����
	 void Draw(void);														// �`�揈��
	static CPlayer *m_pPlayer;												//	�v���C���[�̃|�C���^�^
	static bool GetPause(void);												//	�|�[�Y�̏�Ԃ̎擾
	static void SetPause(bool bPause);										//	�|�[�Y�̏�Ԃ̐ݒ�
	static void LoadSetTutorial(void);										//	�`���[�g���A���̃I�u�W�F�N�g�̐ݒu
	static void LoadSetGame(void);											//	�Q�[���̃I�u�W�F�N�g�̐ݒu
	static void LoadSetGameStage2(void);									//	�Q�[���̃I�u�W�F�N�g�̐ݒu[�Q�X�e�[�W��]
	static void SetStage(SETSTEGEMODE SetStageMode);						//	�X�e�[�W�̑I��
	static GAMESTATE GetGameState(void);
	static SETSTEGEMODE GetStageState(void);
private:
	static GAMESTATE m_GameState;
	int m_nCounterState;
	static SETSTEGEMODE m_SetStageMode;										//	�X�e�[�W�̃��[�h�ݒ�
	static bool m_bPause;
	static int m_nEnemyCount;												//	�G�l�~�[�̐�
	static D3DXVECTOR3 m_EnemyPos[EMEMY_NUM_MAX];							//	�G�l�~�[�̃|�W�V����
	static int m_nEnemyLife[EMEMY_NUM_MAX];									//	�G�l�~�[�̎��
	static int m_nEnemyType[EMEMY_NUM_MAX];									//	�G�l�~�[�̎��

	static int m_nItemCount;												//	�A�C�e���̐�
	static D3DXVECTOR3 m_ItemPos[ITEM_NUM_MAX];								//	�A�C�e���̃|�W�V����
	static int m_nItemType[ITEM_NUM_MAX];									//	�A�C�e���̎��

	static int m_nBlockCount;												//	�u���b�N�̐�
	static D3DXVECTOR3 m_BlockPos[BLOCK_NUM_MAX];							//	�u���b�N�̃|�W�V����
	static int m_nBlockType[BLOCK_NUM_MAX];									//	�u���b�N�̎��
	static float m_fBlockfWindth[BLOCK_NUM_MAX];							//	�u���b�N�̕�
	static float m_fBlockfHeight[BLOCK_NUM_MAX];							//	�u���b�N�̍���
	static float m_fBlockTexSplitX[BLOCK_NUM_MAX];							//	�u���b�N�̃e�N�X�`���̕�����X��
	static float m_fBlockTexSplitY[BLOCK_NUM_MAX];							//	�u���b�N�̃e�N�X�`���̕�����Y��
};

#endif // _MANAGER_H_
