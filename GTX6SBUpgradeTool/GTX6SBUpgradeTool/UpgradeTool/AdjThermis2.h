#if !defined(AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_)
#define AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis2 �_�C�A���O

class CAdjThermis2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis2)

// �R���X�g���N�V����
public:
	CAdjThermis2();
	~CAdjThermis2();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAdjThermis2)
	enum { IDD = IDD_SERV_ADJ_THERMIS02 };
	double	m_fCTemp;
	double	m_fFTemp;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAdjThermis2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int m_nPrevIDD;
	void OnChangeTemperature();
	int  ChangeTempUnit( double fTemp, bool bF );
	bool m_bFahrenheit;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAdjThermis2)
	afx_msg void OnRadioFahrenheight();
	afx_msg void OnRadioCelsius();
	afx_msg void OnChangeEditCtemp();
	afx_msg void OnChangeEditFtemp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_)
