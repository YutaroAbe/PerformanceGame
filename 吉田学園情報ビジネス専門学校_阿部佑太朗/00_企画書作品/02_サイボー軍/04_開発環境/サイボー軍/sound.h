//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
//	�T�E���h�N���X
//=============================================================================
class CSound
{
public:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	typedef enum
	{// �T�E���h�t�@�C��
		SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��
		SOUND_LABEL_BGM_SELECT,			// �Z���N�g
		SOUND_LABEL_BGM_STAGESELECT,	// �X�e�[�W�Z���N�g
		SOUND_LABEL_BGM_CREDIT,			//�N���W�b�g
		SOUND_LABEL_BGM_TUTORIAL,		// �`���[�g���A��
		SOUND_LABEL_BGM_STAGE1,			// �X�e�[�W1
		SOUND_LABEL_BGM_STAGE2,			// �X�e�[�W2
		SOUND_LABEL_BGM_CLEAR,			// �Q�[���N���A
		SOUND_LABEL_BGM_OVER,			// �Q�[���I�[�o�[
		SOUND_LABEL_SE_BULLET,			// �e���ˉ�
		SOUND_LABEL_SE_DAMAGE,			// �_���[�W��
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_PRESS,			// ���艹
		SOUND_LABEL_SE_TUTO,			// ���艹
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	CSound();						//	�R���X�g���N�^
	~CSound();						//	�f�X�g���N�^
	static HRESULT InitSound(HWND hWnd);
	static void UninitSound(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	void StopSound(void);
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:

	static IXAudio2 *m_pXAudio2;										// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	static IXAudio2MasteringVoice *m_pMasteringVoice;					// �}�X�^�[�{�C�X�ւ̃|�C���^
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];		// �\�[�X�{�C�X�ւ̃|�C���^
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX] ;						// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX] ;						// �I�[�f�B�I�f�[�^�T�C�Y
																// �e���f�ނ̃p�����[�^


};

#endif
