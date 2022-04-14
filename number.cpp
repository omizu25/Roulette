//**************************************************
// 
// Hackathon ( number.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "number.h"
#include "rectangle.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_NUMBER = 256;	// ���̍ő吔
const int	MAX_DIGIT = 8;		// �����̍ő吔
const int	TEX_DIVIDE = 10;	// �e�N�X�`���̕�����

typedef struct
{
	D3DXVECTOR3	pos;				// �ʒu
	D3DXVECTOR3	size;				// �T�C�Y
	D3DXCOLOR	col;				// �F
	int			number[MAX_DIGIT];	// ��
	int			digit;				// ����
	int			idx[MAX_DIGIT];		// ��`�̃C���f�b�N�X
	bool		zero;				// 0��\�����邩�ǂ���
	bool		use;				// �g�p���Ă��邩�ǂ���
}Number;
}// namesapce�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Number	s_number[MAX_NUMBER];	// ���̏��
int		s_digit;				// �����v�Z�p
}// namesapce�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void OneDivideNumber(Number *pNumber, int inNumber);
void SetOneDigitNumber(Number *pNumber, int inDigit);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitNumber(void)
{
	// �������̃N���A
	memset(&s_number, NULL, sizeof(s_number));

	s_digit = 0;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitNumber(void)
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		Number *pNumber = &s_number[i];

		if (!pNumber->use)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		for (int j = 0; j < pNumber->digit; j++)
		{
			// �g���̂��~�߂�
			StopUseRectangle(pNumber->idx[j]);
		}
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateNumber(void)
{
	
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawNumber(void)
{
	
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetNumber(const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize, const D3DXCOLOR &inCol, int inNumber, int inDigit, bool inZero)
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		Number *pNumber = &s_number[i];

		if (pNumber->use)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pNumber->pos = inPos;
		pNumber->size = inSize;
		pNumber->col = inCol;

		if (inZero)
		{// 0��\������
			pNumber->digit = inDigit;
		}
		else
		{// 0��\�����Ȃ�
			pNumber->digit = DigitNumber(inNumber);
		}

		// �ꌅ���ɕ�����
		OneDivideNumber(pNumber, inNumber);

		for (int j = 0; j < pNumber->digit; j++)
		{
			// ��`�̐ݒ�
			pNumber->idx[j] = SetRectangle(TEXTURE_Number_000);

			// �ꌅ���̐ݒ�
			SetOneDigitNumber(pNumber, j);
		}

		pNumber->zero = inZero;
		pNumber->use = true;

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void SetPosNumber(int inIdx, const D3DXVECTOR3 &inPos, const D3DXVECTOR3 &inSize)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pNumber->pos = inPos;
	pNumber->size = inSize;

	for (int i = 0; i < pNumber->digit; i++)
	{
		// �ꌅ���̐ݒ�
		SetOneDigitNumber(pNumber, i);
	}
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
int ChangeNumber(int inIdx, int inNumber)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// �g�p���Ă��Ȃ�
		return inIdx;
	}

	/*�� �g�p���Ă��� ��*/

	if (!pNumber->zero)
	{// 0��\�����Ȃ�
		if (pNumber->digit != DigitNumber(inNumber))
		{// �������Ⴄ
			// �g���̂��~�߂�
			StopUseNumber(inIdx);

			// �ݒ�
			return SetNumber(pNumber->pos, pNumber->size, pNumber->col, inNumber, DigitNumber(inNumber), false);
		}
		else
		{// ����������
			// �ꌅ���ɕ�����
			OneDivideNumber(pNumber, inNumber);
		}
	}
	else
	{// 0��\������
		if (pNumber->digit < DigitNumber(inNumber))
		{// �������Ⴄ
			// �g���̂��~�߂�
			StopUseNumber(inIdx);

			// �ݒ�
			return SetNumber(pNumber->pos, pNumber->size, pNumber->col, inNumber, DigitNumber(inNumber), true);
		}
		else
		{// ����������
			// �ꌅ���ɕ�����
			OneDivideNumber(pNumber, inNumber);
		}
	}

	float divide = 1.0f / TEX_DIVIDE;

	for (int i = 0; i < pNumber->digit; i++)
	{
		float tex = divide * pNumber->number[i];

		// ��`�̃e�N�X�`�����W�̐ݒ�
		SetTexRectangle(pNumber->idx[i], D3DXVECTOR2(tex, tex + divide), D3DXVECTOR2(0.0f, 1.0f));
	}

	return inIdx;
}

//--------------------------------------------------
// �g���̂��~�߂�
//--------------------------------------------------
void StopUseNumber(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	pNumber->use = false;

	for (int i = 0; i < pNumber->digit; i++)
	{
		// �g���̂��~�߂�
		StopUseRectangle(pNumber->idx[i]);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
int DigitNumber(int inNumber)
{
	s_digit = 0;
	int number = inNumber;

	while (1)
	{// �������[�v
		if (number >= 10)
		{// 2���ȏ�
			number /= 10;
			s_digit++;
		}
		else
		{// 1��
			s_digit++;

			if (s_digit > MAX_DIGIT)
			{// �w��̒l���傫��
				s_digit = MAX_DIGIT;
			}
			break;
		}
	}

	return s_digit;
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawNumber(int inIdx, bool inDraw)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	for (int i = 0; i < pNumber->digit; i++)
	{
		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pNumber->idx[i], inDraw);
	}
}

//--------------------------------------------------
// �e�N�X�`���̕ύX
//--------------------------------------------------
void ChangeTextureNumber(int inIdx, TEXTURE inTexture)
{
	assert(inIdx >= 0 && inIdx < MAX_NUMBER);

	Number *pNumber = &s_number[inIdx];

	if (!pNumber->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	for (int i = 0; i < pNumber->digit; i++)
	{
		// ��`�̕`�悷�邩�ǂ���
		ChangeTextureRectangle(pNumber->idx[i], inTexture);
	}
}

namespace
{
//--------------------------------------------------
// �ꌅ���ɕ�����
//--------------------------------------------------
void OneDivideNumber(Number *pNumber, int inNumber)
{
	int number = inNumber;

	for (int i = 0; i < pNumber->digit; i++)
	{// �ꌅ���ɕ�����
		pNumber->number[i] = number % 10;
		number /= 10;
	}
}

//--------------------------------------------------
// �ꌅ���̐ݒ�
//--------------------------------------------------
void SetOneDigitNumber(Number *pNumber, int inDigit)
{
	float interval = (pNumber->size.x * inDigit) + (pNumber->size.x * 0.5f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(pNumber->idx[inDigit], pNumber->pos + D3DXVECTOR3(-interval, 0.0f, 0.0f), pNumber->size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(pNumber->idx[inDigit], pNumber->col);

	float divide = 1.0f / TEX_DIVIDE;
	float tex = divide * pNumber->number[inDigit];

	// ��`�̃e�N�X�`�����W�̐ݒ�
	SetTexRectangle(pNumber->idx[inDigit], D3DXVECTOR2(tex, tex + divide), D3DXVECTOR2(0.0f, 1.0f));
}
}// namespace�͂����܂�