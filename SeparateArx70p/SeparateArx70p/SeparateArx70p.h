// SeparateArx70p.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CSeparateArx70pApp:
// ���̃N���X�̎����ɂ���SeparateArx6eC.cpp ���Q�Ƃ��Ă��������B
//

class CSeparateArx70pApp : public CWinApp
{
public:
	CSeparateArx70pApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CSeparateArx70pApp theApp;