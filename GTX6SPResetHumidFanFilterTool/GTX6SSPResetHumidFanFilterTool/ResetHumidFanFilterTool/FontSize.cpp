#include "StdAfx.h"
#include ".\fontsize.h"

//���߂Ƀu���b�N���P�쐬����B
//�u���b�N�P�ɕt���A�t�H���g��iBLOCK_SIZE��
//�ۑ��ł���B�u���b�N����t�ɂȂ�����A
//ArrocOneBlock���Ă�Ńu���b�N��ǉ�����

static const int iBLOCK_SIZE = 10;	//�P�̃u���b�N�ɂ����t�H���g��ۑ����邩

CFontSize::CFontSize(void)
{
	m_iNum		= 0;
	m_iBlockNum = 0;
	m_ppFont	= NULL;
	//���߂Ƀu���b�N���P�쐬����B
	ArrocOneBlock();
}


CFontSize::~CFontSize(void)
{
	//m_ppFont�̊J��
	for( int i=0 ; i < m_iBlockNum ; i++ )
	{
		delete [] m_ppFont[i];//DeleteObject()�͕K�v�Ȃ�
	}
	if( m_ppFont ) delete [] m_ppFont;
}

//�u���b�N(CFont�̃|�C���^)��m_ppFont�ɒǉ�����
BOOL CFontSize::ArrocOneBlock()
{
	BOOL bRet = FALSE;

	//CFont�|�C���^�̔z����쐬�@m_ppFont���P�����u���b�N���쐬����
	CFont** ppFont = (CFont**) new CFont*[ ( m_iBlockNum + 1 ) ];

	if( ppFont )
	{
		for( int i=0 ; i < m_iBlockNum ; i++ )
		{//�����u���b�N���R�s�[
			ppFont[i] = m_ppFont[i];
		}
		//m_ppFont���폜���AppFont��m_ppFont�Ƃ���
		if( m_ppFont ) delete [] m_ppFont;
		m_ppFont = ppFont;

		//�V���ɍ�����u���b�N��iBLOCK_SIZE�̗̈���m�ۂ���
		m_ppFont[ m_iBlockNum ] = (CFont*) new CFont[ iBLOCK_SIZE ];
		if( m_ppFont[ m_iBlockNum ] )
		{
			m_iBlockNum++;
			bRet = TRUE;
		}
	}
	return bRet;
}

//�t�H���g�T�C�Y��ύX����
BOOL CFontSize::ChangeFontSize( CWnd* pWnd , int iSize , int iWeight /* = FW_NORMAL */ )
{
	BOOL bRet = TRUE;

	if(  m_iBlockNum == 0 || m_iNum == iBLOCK_SIZE )
	{//�u���b�N���������A��t�̎�
		//�u���b�N��ǉ�����
		bRet = ArrocOneBlock();
		m_iNum = 0;
	}

	if( bRet )
	{
		CFont *pOldfont;
		LOGFONT Logfont;

		pOldfont = pWnd->GetFont();//���݂̃t�H���g���擾�@�i�e���|�����|�C���^�j
		pOldfont->GetLogFont( &Logfont );//�t�H���g���̎擾

		//�t�H���g���̕ύX
		Logfont.lfHeight = iSize;
		Logfont.lfWeight = iWeight;
		
		//�ύX�����t�H���g��񂩂�t�H���g�̍쐬�@
		//m_ppFont[ m_iBlockNum - 1 ][ m_iNum ]���J������ƃt�H���g���J�������̂�
		//���Ƃ�DeleteOblect()�͕K�v�Ȃ�
		m_ppFont[ m_iBlockNum - 1 ][ m_iNum ].CreateFontIndirect( &Logfont );
		//�t�H���g���Z�b�g����
		pWnd->SetFont( &m_ppFont[ m_iBlockNum - 1 ][ m_iNum ] );
		m_iNum++;
	}

	return bRet;
}