//**************************************************
// 
// Hackathon ( menu.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "input.h"
#include "menu.h"
#include "fade.h"
#include "color.h"
#include "rectangle.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_MENU = 16;					// ���j���[�̍ő吔
const float	NORMAL_CHANGE_SPEED = 0.01f;	// �ʏ펞�̕ύX���x
const float	DECISION_CHANGE_SPEED = 0.1f;	// ���莞�̕ύX���x
const float	MIN_ALPHA = 0.5f;				// ���l�̍ŏ��l

/*�� �I���� ��*/
struct SOption
{
	D3DXVECTOR3	pos;	// �ʒu
	D3DXCOLOR	col;	// �F
	int			idx;	// ��`�̃C���f�b�N�X
	float		width;	// ��
	float		height;	// ����
};

/*�� ���j���[ ��*/
struct SMenu
{
	D3DXVECTOR3	pos;				// �ʒu
	D3DXCOLOR	colStart;			// �n�܂�̐F
	D3DXCOLOR	colEnd;				// �I���̐F
	D3DXCOLOR	colDefault;			// �I�΂�ĂȂ��I�����̐F
	SOption		option[MAX_OPTION];	// �I�����̏��
	int			numUse;				// �g�p��
	int			idx;				// ��`�̃C���f�b�N�X
	float		width;				// ��
	float		height;				// ����
	float		interval;			// �I�����̊Ԋu
	float		changeSpeed;		// �ύX���x
	bool		frame;				// �g�����邩�ǂ��� [ true : ���� false : ����Ȃ� ]
	bool		draw;				// �`�悷�邩�ǂ���
	bool		use;				// �g�p���Ă��邩�ǂ���
};
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
SMenu	s_menu[MAX_MENU];	// ���j���[�̏��
int		s_idxMenu;			// �I�΂�Ă��郁�j���[�̔ԍ�
int		s_idxOption;		// �I�΂�Ă���I�����̔ԍ�
int		s_time;				// ���l�ύX�p�̎���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void ChangeColor(SMenu *pMenu);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitMenu(void)
{
	s_idxMenu = 0;
	s_idxOption = 0;
	s_time = 0;

	// �������̃N���A
	memset(s_menu, 0, sizeof(s_menu));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitMenu(void)
{
	for (int i = 0; i < MAX_MENU; i++)
	{
		SMenu *pMenu = &s_menu[i];

		if (!pMenu->use)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		if (pMenu->frame)
		{// �g���g���Ă���
			// �g���̂��~�߂�
			StopUseRectangle(pMenu->idx);
		}

		for (int j = 0; j < pMenu->numUse; j++)
		{
			SOption *pOption = &pMenu->option[j];

			// �g���̂��~�߂�
			StopUseRectangle(pOption->idx);
		}
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateMenu(void)
{
	SMenu *pMenu = &s_menu[s_idxMenu];

	if (!pMenu->use)
	{// �g�p���Ă��Ȃ�
		return;
	}
	
	// �F�̕ύX
	ChangeColor(pMenu);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawMenu(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetMenu(const SInMenu &inMenu, const SInFrame &inFrame)
{
	assert(inMenu.numUse >= 0 && inMenu.numUse < MAX_OPTION);
	
	for (int i = 0; i < MAX_MENU; i++)
	{
		SMenu *pMenu = &s_menu[i];

		if (pMenu->use)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		float posX = inMenu.left + ((inMenu.right - inMenu.left) * 0.5f);
		float posY = inMenu.top + ((inMenu.bottom - inMenu.top) * 0.5f);

		pMenu->pos = D3DXVECTOR3(posX, posY, 0.0f);
		pMenu->colStart = GetColor(COLOR_WHITE);
		pMenu->colEnd = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pMenu->colDefault = GetColor(COLOR_WHITE);
		pMenu->numUse = inMenu.numUse;
		pMenu->width = inMenu.right - inMenu.left;
		pMenu->height = inMenu.bottom - inMenu.top;
		pMenu->changeSpeed = NORMAL_CHANGE_SPEED;
		pMenu->frame = inFrame.use;
		pMenu->draw = true;
		pMenu->use = true;

		if (inMenu.sort)
		{// �c
			pMenu->interval = pMenu->height / (inMenu.numUse + 1);
		}
		else
		{// ��
			pMenu->interval = pMenu->width / (inMenu.numUse + 1);
		}

		s_idxMenu = i;
		s_idxOption = 0;

		if (inFrame.use)
		{// �g������
			// ��`�̐ݒ�
			pMenu->idx = SetRectangle(inFrame.texture);

			posX = inMenu.left + (pMenu->width * 0.5f);
			posY = inMenu.top + (pMenu->height * 0.5f);
			D3DXVECTOR3 pos = D3DXVECTOR3(posX, posY, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pMenu->width, pMenu->height, 0.0f);

			// ��`�̈ʒu�̐ݒ�
			SetPosRectangle(pMenu->idx, pos, size);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(pMenu->idx, inFrame.col);
		}

		for (int j = 0; j < pMenu->numUse; j++)
		{
			SOption *pOption = &pMenu->option[j];

			if (inMenu.sort)
			{// �c
				pOption->pos = D3DXVECTOR3(pMenu->pos.x, inMenu.top + (pMenu->interval * (j + 1)), 0.0f);
			}
			else
			{// ��
				pOption->pos = D3DXVECTOR3(inMenu.left + (pMenu->interval * (j + 1)), pMenu->pos.y, 0.0f);
			}

			pOption->col = GetColor(COLOR_WHITE);
			pOption->width = inMenu.width;
			pOption->height = inMenu.height;

			// ��`�̐ݒ�
			pOption->idx = SetRectangle(inMenu.texture[j]);

			D3DXVECTOR3 size = D3DXVECTOR3(inMenu.width, inMenu.height, 0.0f);

			// ��`�̈ʒu�̐ݒ�
			SetPosRectangle(pOption->idx, pOption->pos, size);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(pOption->idx, pOption->col);
		}

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �I�����̐F�̐ݒ�
//--------------------------------------------------
void SetColorOption(int inIdx, const D3DXCOLOR &inColStart, const D3DXCOLOR &inColEnd)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pMenu->colStart = inColStart;
	pMenu->colEnd = inColEnd;
}

//--------------------------------------------------
// �I�΂�Ă��Ȃ��I�����̐F�̐ݒ�
//--------------------------------------------------
void SetColorDefaultOption(int inIdx, const D3DXCOLOR &inColDefault)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pMenu->colDefault = inColDefault;

	// �I�����̐F�̏�����
	InitColorOption();
}

//--------------------------------------------------
// �I�����̐F�̏�����
//--------------------------------------------------
void InitColorOption(void)
{
	SMenu *pMenu = &s_menu[s_idxMenu];

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		pOption->col = pMenu->colDefault;

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pOption->idx, pOption->col);
	}
}

//--------------------------------------------------
// �I�����̕ύX
//--------------------------------------------------
void ChangeOption(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_OPTION);

	s_idxOption = inIdx;
	s_time = 0;
}

//--------------------------------------------------
// �I�����̌���
//--------------------------------------------------
void DecisionOption(void)
{
	s_menu[s_idxMenu].changeSpeed = DECISION_CHANGE_SPEED;
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void ResetMenu(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	s_idxMenu = 0;
	s_idxOption = 0;
	s_time = 0;
	
	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	if (pMenu->frame)
	{// �g���g���Ă���
		// �g���̂��~�߂�
		StopUseRectangle(pMenu->idx);
	}

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		// �g���̂��~�߂�
		StopUseRectangle(pOption->idx);
	}

	pMenu->use = false;
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawMenu(int inIdx, bool inDraw)
{
	assert(inIdx >= 0 && inIdx < MAX_MENU);

	SMenu *pMenu = &s_menu[inIdx];

	if (!pMenu->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	if (pMenu->frame)
	{// �g���g���Ă���
		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pMenu->idx, inDraw);
	}

	for (int i = 0; i < pMenu->numUse; i++)
	{
		SOption *pOption = &pMenu->option[i];

		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pOption->idx, inDraw);

		pOption->col = GetColor(COLOR_WHITE);
	}

	pMenu->draw = inDraw;

	pMenu->changeSpeed = NORMAL_CHANGE_SPEED;
	s_idxOption = 0;
	s_time = 0;
}

namespace
{
//--------------------------------------------------
// �F�̕ύX
//--------------------------------------------------
void ChangeColor(SMenu *pMenu)
{
	s_time++;

	SOption *pOption = &pMenu->option[s_idxOption];

	float curve = CosCurve(s_time, pMenu->changeSpeed);
	pOption->col.r = Curve(curve, pMenu->colStart.r, pMenu->colEnd.r);
	pOption->col.g = Curve(curve, pMenu->colStart.g, pMenu->colEnd.g);
	pOption->col.b = Curve(curve, pMenu->colStart.b, pMenu->colEnd.b);
	pOption->col.a = Curve(curve, pMenu->colStart.a, pMenu->colEnd.a);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(pOption->idx, pOption->col);
}
}// namespace�͂����܂�