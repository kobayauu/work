#pragma once

//�ȒP��CWnd�I�u�W�F�N�g�̃t�H���g�T�C�Y��ύX����
//CFontSize�I�u�W�F�N�g�́A�I�[�g�ϐ��ō쐬���Ȃ��ł��������B

class CFontSize
{
public:

	CFontSize(void);
	virtual ~CFontSize(void);

	BOOL ChangeFontSize( CWnd* pWnd , int iSize , int iWeight = FW_NORMAL );

protected:

	CFont** m_ppFont;
	int     m_iNum;		 //1�u���b�N���̕ύX�����t�H���g�̐��@0�`iBLOCK_SIZE�̃J�E���^
	int     m_iBlockNum; //�u���b�N�������g���Ă��邩

	BOOL ArrocOneBlock();
};
