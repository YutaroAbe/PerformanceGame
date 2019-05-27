//=============================================================================
//
// 2D�|���S������ [scene2D.h]
// Author :
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "main.h"
#include "scene.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_POLIGON (2)

//=============================================================================
//	2D�|���S���N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CScene2D : public CScene
{
public:
	CScene2D();																			//	�R���X�g���N�^
	CScene2D(int nPriarity);															//	�R���X�g���N�^
	~CScene2D();																		//	�f�X�g���N�^
	HRESULT Init(void);																	//	2D�|���S���̏���������
	void Uninit(void);																	//	2D�|���S���̏I������
	void Update(void);																	//	2D�|���S���̍X�V����
	void Draw(void);																	//	2D�|���S���̕`�揈��
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);									//	���ʃe�N�X�`�������蓖�Ă�

	void ColorChange(D3DXCOLOR m_Col);													//	�J���[�̕ύX
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);												//	�o�b�t�@�̎擾
	void BGMove(D3DXVECTOR3 move);														//	�w�i������

	int GetType(void);
	int GetLife(void);																	//	���C�t�|�C���g�̎擾
	D3DXVECTOR3 GetPosition(void);														//	2D�|���S���̍��W�擾
	D3DXVECTOR3 GetMoveing(void);
	 void SetPosition(D3DXVECTOR3 pos, float PolygonSizeX, float PolygonSizeY);
	float GetfWindth(void);
	 float GetfHeight(void);
	 void SetLife(int nLife);															//	���C�t�|�C���g�̐ݒ�
	 void SetType(int nType);
	 void SetWindthHeigth(float fWindth, float m_fHeight);								//	���ƍ����̐ݒ�
	void SetTexture(D3DXVECTOR2 *pTex);
	void SetVtxPosition(D3DXVECTOR3 *pPos,D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR *color);
	 void HitDamage(int nDamage);														//	�v���C���[�̃_���[�W�ݒ�
private:
	LPDIRECT3DTEXTURE9		m_pTexture;													// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;														// �|���S���̈ʒu
	D3DXVECTOR3				m_move;														// �|���S���̓���
	int m_nLife;																		//	���C�t�|�C���g
	int m_nType;
	 float m_fWindth;																	//	��
	 float m_fHeight;																	//	����
protected:
	void SetAnimation(int PatternAnim, float Split, int SplitAnim);						//	�A�j���[�V�����̐ݒ�
	void InitAnimationTex(float Split);													//	�A�j���[�V�����̃e�N�X�`���̏������ݒ�

};
#endif