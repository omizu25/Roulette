//**************************************************
// 
// Hackathon ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// �萔
//==================================================
namespace
{
const char *s_FileName[] =
{// �e�N�X�`���̃p�X	
	"data/TEXTURE/Number_000.png",		// ����000
	"data/TEXTURE/Number_001.png",		// ����001
	"data/TEXTURE/Number_002.png",		// ����002
	"data/TEXTURE/Number_003.png",		// ����003
	"data/TEXTURE/Number_004.png",		// ����004
	"data/TEXTURE/Number_005.png",		// ����005
	"data/TEXTURE/Number_006.png",		// ����006
	"data/TEXTURE/Number_007.png",		// ����007
	"data/TEXTURE/Number_008.png",		// ����008
	"data/TEXTURE/Number_009.png",		// ����009
	"data/TEXTURE/Number_010.png",		// ����010
	"data/TEXTURE/Roulette.png",		// �^�C�g�����S
	"data/TEXTURE/BG.jpg",				// �w�i
	"data/TEXTURE/GameStart_008.png",	// �X�^�[�g
};
}// namespace�͂����܂�

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespace�͂����܂�

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	return s_pTexture[inTexture];
}