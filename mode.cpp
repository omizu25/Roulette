//**************************************************
//
// Hackathon ( mode.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "fade.h"
#include "game.h"
#include "mode.h"
#include "rectangle.h"
#include "texture.h"
#include "title.h"

#include <assert.h>
#include <time.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
EMode	s_mode = MODE_NONE;		// ���݂̃��[�h
EMode	s_modeNext = MODE_NONE;	// ���̃��[�h
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitMode(void)
{
	// rand�̏�����
	srand((unsigned int)time(NULL));

	// �e�N�X�`���̓ǂݍ���
	LoadTexture();

	// ��`�̏�����
	InitRectangle();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitMode(void)
{
	// �Q�[���̏I��
	UninitGame();

	// �^�C�g���̏I��
	UninitTitle();

	// ��`�̏I��
	UninitRectangle();

	// �e�N�X�`���̏I��
	UninitTexture();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateMode(void)
{
	switch (s_mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		UpdateTitle();
		break;

	case MODE_GAME:		// �Q�[��
		UpdateGame();
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawMode(void)
{
	switch (s_mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		DrawTitle();
		break;

	case MODE_GAME:		// �Q�[��
		DrawGame();
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetMode(void)
{
	if (s_modeNext == MODE_NONE)
	{// ���̃��[�h�����܂��ĂȂ�
		return;
	}

	if (GetFade() == FADE_NONE)
	{// �������Ă��Ȃ���ԂȂ�
		StartFadeOut();
	}

	if (GetFade() != FADE_IN)
	{// �t�F�[�h�C����Ԃ���Ȃ�
		return;
	}

	switch (s_mode)
	{// ���݂̃��[�h�̏I��
	case MODE_TITLE:	// �^�C�g��
		UninitTitle();
		break;

	case MODE_GAME:		// �Q�[��
		UninitGame();
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		assert(false);
		break;
	}

	// ��`�̏I��
	UninitRectangle();

	// ��`�̏�����
	InitRectangle();

	s_mode = s_modeNext;	// ���݂̉��(���[�h)��؂�ւ���
	
	switch (s_modeNext)
	{// ���̃��[�h�̏�����
	case MODE_TITLE:	// �^�C�g��
		InitTitle();
		break;

	case MODE_GAME:		// �Q�[��
		InitGame();
		break;
	
	case MODE_NONE:
	default:
		assert(false);
		break;
	}

	s_modeNext = MODE_NONE;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
EMode GetMode(void)
{
	return s_mode;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void ChangeMode(EMode inModeNext)
{
	assert(inModeNext >= 0 && inModeNext < MODE_MAX);

	s_modeNext = inModeNext;
}