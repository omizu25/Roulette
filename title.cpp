//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "mode.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "texture.h"
#include "utility.h"
#include "menu.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// �^�C�g�����S�̕�
const float	TITLE_HEIGHT = 200.0f;	// �^�C�g�����S�̍���
const float	MENU_WIDTH = 300.0f;	// ���j���[�̕�
const float	MENU_HEIGHT = 80.0f;	// ���j���[�̍���

enum EMenu
{
	MENU_GAME = 0,	// �Q�[��
	MENU_MAX
};
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_idxBG;		// �w�i�̋�`�̃C���f�b�N�X
int	s_idxTitleLogo;	// �^�C�g�����S�̋�`�̃C���f�b�N�X
int	s_selectMenu;	// �I�΂�Ă��郁�j���[
int	s_idxMenu;		// ���j���[�̔z��̃C���f�b�N�X
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Input(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTitle(void)
{
	s_selectMenu = 0;

	{// �w�i
		// ��`�̐ݒ�
		s_idxBG = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_idxBG, pos, size);
	}

	{// �^�C�g�����S
		// ��`�̐ݒ�
		s_idxTitleLogo = SetRectangle(TEXTURE_Roulette);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_idxTitleLogo, pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_idxTitleLogo, GetColor(COLOR_RED));
	}
	
	{// ���j���[
		// ���j���[�̏�����
		InitMenu();

		SInMenu menu;
		menu.numUse = MENU_MAX;
		menu.left = SCREEN_WIDTH * 0.55f;
		menu.right = SCREEN_WIDTH * 0.95f;
		menu.top = 0.0f;
		menu.bottom = SCREEN_HEIGHT;
		menu.width = MENU_WIDTH;
		menu.height = MENU_HEIGHT;
		menu.sort = true;

		menu.texture[MENU_GAME] = TEXTURE_GameStart_008;

		SInFrame frame;
		frame.use = true;
		frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		frame.texture = TEXTURE_NONE;

		// ���j���[�̐ݒ�
		s_idxMenu = SetMenu(menu, frame);

		// �I�����̐F�̐ݒ�
		SetColorOption(s_idxMenu, GetColor(COLOR_WHITE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// �I�΂�Ă��Ȃ��I�����̐F�̐ݒ�
		SetColorDefaultOption(s_idxMenu, GetColor(COLOR_WHITE));
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTitle(void)
{
	// ���j���[�̏I��
	UninitMenu();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTitle(void)
{
	// ����
	Input();

	// ���j���[�̍X�V
	UpdateMenu();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTitle(void)
{
	// ��`�̕`��
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// ����
//--------------------------------------------------
void Input(void)
{
	if (GetFade() != FADE_NONE)
	{// �t�F�[�h���Ă���
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		switch (s_selectMenu)
		{
		case MENU_GAME:	// �Q�[��
			ChangeMode(MODE_GAME);
			break;

		default:
			assert(false);
			break;
		}

		// �I�����̌���
		DecisionOption();
	}
}
}// namespace�͂����܂�