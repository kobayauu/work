/**
 * LogRecord.cpp
 */

#include "stdafx.h"
#include "LogRecord.h"
#include "LogString.h"
#include "LogCode.h"

/*********************************************************
 * CLogRecord.
 *********************************************************/

#define toLong(c)	((c[0]<<24)|(c[1]<<16)|(c[2]<<8)|c[3])
/**
 * CLogRecord.
 */
CLogRecord::CLogRecord()
{
	m_selected = true;
}

/**
 * ~CLogRecord.
 */
CLogRecord::~CLogRecord()
{

}

/**
 * 選択されている？.
 * @return true:yes , false:no
 */
bool CLogRecord::isSelected() const
{
	return m_selected;
}

/**
 * ログコードとログクラスが一致する？.
 * @param code ログコード
 * @param logclass ログクラス
 * @return true:Yes , false:No 
 */
bool CLogRecord::isMatched(unsigned long code) const
{
	return (m_code == code) ?
		true : false;
}
bool CLogRecord::isMatched(unsigned long code, unsigned long logclass) const
{
	return ((m_code & 0x0000ffff) == code && m_logclass == logclass) ?
		true : false;
}


/**
 * 同じログ？.
 * @param record 比較するログ
 * @return true:Yes , false:No 
 */
bool CLogRecord::isSameRecord(const CLogRecord& record) const
{
	if(m_code == record.m_code &&
	   m_logclass == record.m_logclass &&
	   m_date == record.m_date)
		return true;
	else
		return false;
}

/**
 * 選択する.
 */
void CLogRecord::select()
{
	m_selected = true;
}

/**
 * 選択を解除する.
 */
void CLogRecord::deselect()
{
	m_selected = false;
}

/**
 * ログ情報を文字列に変換する.
 * @return 文字列
 */
CString CLogRecord::toString() const
{
	CString string;
	string.Format(_T("%06d: 0x%08X %s - %s - %d "),
		m_id, m_code, m_date.toString(), CLogString::logclassToString(m_logclass), m_level);
	return string;
}

CString CLogRecord::GetFileName() const
{
	return m_strFileName;
}

/**
 * 付加情報の行数を得る.
 * @return 付加情報の行数
 */
int CLogRecord::getCountAddition() const
{
	return 1;
}

/**
 * 付加情報を得る.
 * @param index 配列番号
 * @return 付加情報
 */
CString CLogRecord::getAddition(int index) const
{
	if (index) return "";

	return m_addition;
}

/**
 * 付加情報をセットする.
 * @param addition 付加情報
 */
void CLogRecord::setAddition(const CString& addition)
{
	m_addition = addition;
}

/**
 * ログ情報を得る
 * @param id 
 * @param code 
 * @param date 
 * @param kind 
 * @param level 
 */
void CLogRecord::getRecord(unsigned long& id, unsigned long& code, CLogDate& date,
	unsigned long& logclass, unsigned long& level) const
{
	id = m_id;
	code = m_code;
	date = m_date;
	logclass = m_logclass;
	level = m_level;
}

/**
 * IDを得る.
 * @return ID
 */
unsigned long CLogRecord::getID() const
{
	return m_id;
}

/**
 * IDを設定する.
 * @param id ID
 */
void CLogRecord::setID(unsigned long id)
{
	m_id = id;
}

/**
 * コードを得る.
 * @return コード
 */
unsigned long CLogRecord::getCode() const
{
	return m_code;
}

/**
 * ログ種別を得る.
 * @return ログ種別
 */
unsigned long CLogRecord::getLogclass() const
{
	return m_logclass;
}

/**
 * レベルを得る.
 * @return レベル
 */
unsigned long CLogRecord::getLevel() const
{
	return m_level;
}

/**
 * 日付を得る.
 * @return 日付
 */
const CLogDate& CLogRecord::getDate() const
{
	return m_date;
}

/**
 * キャプションを得る.
 * @return キャプション
 */
const CString& CLogRecord::getCaption() const
{
	return m_caption;
}

/**
 * キャプションをセットする.
 * @param caption キャプション
 */
void CLogRecord::setCaption(const CString& caption)
{
	m_caption = caption;
	m_caption.TrimLeft();
}

/**
* ログ情報をセットする
 * @param string 
 */
bool CLogRecord::setRecord(const CString& string)
{
	const CString separator = " .,-:";
	int pos = 0;
	CString resToken;
	bool success;

	// id
	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, m_id);
	ASSERT(success);
	if(!success)
		return false;

	// code
	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, m_code);
	ASSERT(success);
	if(!success)
		return false;

	// date
	unsigned long month, day, year, hour, min, sec, msec;
	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToMonth(resToken, month);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, day);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, year);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, hour);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, min);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, sec);
	ASSERT(success);
	if(!success)
		return false;

	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, msec);
	ASSERT(success);
	if(!success)
		return false;

	m_date.setDate(year, month, day, hour, min, sec, msec);

	// class
	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToLogclass(resToken, m_logclass);
	ASSERT(success);
	if(!success)
		return false;

	// level
	resToken = CLogString::tokenize(string, separator, pos);
	ASSERT("" != resToken);
	if("" == resToken)
		return false;
	success = CLogString::stringToDigit(resToken, m_level);
	ASSERT(success);
	if(!success)
		return false;

	return true;
}

bool CLogRecord::setData(char *data, unsigned long dataSize)
{
	unsigned long addSize;

	// 基本情報のセット
	{
		if(dataSize < 12)
			return false;

		unsigned char* c;

		c = (unsigned char*)data;
		unsigned long date = toLong(c);
		c = (unsigned char*)&data[4];
		unsigned long work = toLong(c);
		c = (unsigned char*)&data[8];
		m_code = toLong(c);

		_tzset(); // 時刻の環境変数を設定
		date -= _timezone; // local時刻に変換

		if( date > 0x37000000 )
		{
			date = 0x36000000;
		}
		CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
		ct += CTimeSpan( date );
		struct tm t;
		if( ct.GetLocalTm(&t) )
			m_date.setDate(t.tm_year+1900, t.tm_mon+1, t.tm_mday,
				t.tm_hour, t.tm_min, t.tm_sec, work >> 21);

		addSize = (work & 0x001FFF00) >> 8;
		m_logclass = (work & 0x000000F8) >> 3;
		m_level = work & 0x00000007;
	}

	if( m_code == 0x4E000625 )
	{//CFからの読み込みの時ファイルネームを記憶する
		m_strFileName = &data[12+23];
	}
	data += 12;
	dataSize -= 12;
	if(addSize > dataSize)
		addSize = dataSize;

	// 付加情報
	{
		CString strAddition;
		CString strTmp;

		unsigned char* b = (unsigned char*)data;
		unsigned long cnt = 0;
		while(cnt < addSize) {
			strTmp.Format(_T(" %08X"), toLong(b));
			strAddition += strTmp;
			b += 4;
			cnt += 4;
		}

		m_addition = strAddition;
	}
	return true;
}

/**
 * 読み込み.
 * @param ar 
 * @return true:成功 , false:失敗 
 */
unsigned long CLogRecord::load(CArchive& ar)
{
	unsigned long addSize;
	if(!loadRecord(ar, addSize))
		return 0;

	if(addSize > 0)
	{
		if(!loadAddition(ar, addSize))
			return 0;
	}
	return 12+addSize;
}

/**
 * ログの読み込み.
 * @param ar 
 * @param addSize [out] 付加情報のサイズ
 * @return true:成功 , false:失敗 
 */
bool CLogRecord::loadRecord(CArchive& ar, unsigned long& addSize)
{
	unsigned char buf[12];
	if(12 != ar.Read(buf, 12))
		return false;

	unsigned char* c;

	c = buf;
	unsigned long date = toLong(c);
	c = &buf[4];
	unsigned long work = toLong(c);
	c = &buf[8];
	m_code = toLong(c);

	CTime ct( 2000, 1, 1, 0, 0, 0, -1 );
	ct += CTimeSpan( date );
	struct tm* ptm = ct.GetLocalTm(NULL);
	if(NULL != ptm)
		m_date.setDate(ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec, work >> 21);

	addSize = (work & 0x001FFF00) >> 8;
	m_logclass = (work & 0x000000F8) >> 3;
	m_level = work & 0x00000007;

	return true;
}

/**
 * 付加情報の読み込み.
 * @param ar 
 * @param addSize 付加情報のサイズ
 * @return true:成功 , false:失敗 
 */
bool CLogRecord::loadAddition(CArchive& ar, unsigned long addSize)
{
	unsigned char data[256] = {};
	if( ar.Read(data, addSize) != addSize )
		return false;

	// 付加情報
	{
		CString strAddition;
		CString strTmp;

		unsigned char* b = (unsigned char*)data;
		unsigned long cnt = 0;
		while(cnt < addSize) {
			strTmp.Format(_T(" %08X"), toLong(b));
			strAddition += strTmp;
			b += 4;
			cnt += 4;
		}

		m_addition = strAddition;
	}
	return true;
}

/*********************************************************
 * CLogAnalyze.
 *********************************************************/

/**
 * CLogAnalyze Constructor.
 */
CLogAnalyze::CLogAnalyze()
	: CLogRecord()
{
}

/**
 * CLogAnalyze Destructor.
 */
CLogAnalyze::~CLogAnalyze()
{
}

unsigned long CLogAnalyze::GetLogNumber()
{
	CString strText = m_addition;

	int start = 0;
	CString strToken1 ="0x"+CLogString::tokenize( strText, " ", start );	//１番目の４バイト

	unsigned long digit1;
	CLogString::stringToDigit( strToken1, digit1 );	//１番目の４バイト

	return	digit1;
}

CString CLogAnalyze::getFilename()
{
	CString strText = m_addition;

	int start = 0;
//	CLogString::tokenize(strText, " ", start);	//最初は読み飛ばし

	return	CLogString::tokenizeString( strText, " ", start, 64 );
}

/**
 * 文字列を付加情報にもつログ
 */

//文字列を得る.
CString CLogAnalyze::getString()
{
	CString strText = m_addition;

	int start = 0;
	CLogString::tokenize(strText, " ", start);	//最初は読み飛ばし

	return	CLogString::tokenizeString( strText, " ", start, 64 );
}

/**
 * 印刷終了ログ
 */
//ドットカウントを得る.
void CLogAnalyze::getCountDot(unsigned long dot[])
{
	int cnt = 0;
	CString strText = m_addition;

	int start = 0;
	while(cnt < 34)
	{
		CString strToken = CLogString::tokenize(strText, " ", start);

		if(10 <= cnt && cnt < 34)
		{
			CString strDot = "0x" + strToken;
			CLogString::stringToDigit(strDot, dot[cnt-10]);
		}
		cnt++;
	}
}

//インク量を得る.
double CLogAnalyze::dotToCC(unsigned long dotL, unsigned long dotM, unsigned long dotS, unsigned long dpi, bool pale)
{
	double					cc;
	     if( dpi != 1200 )	cc = dotL * 38e-9  +  dotM * 20e-9  +  dotS * 9.92e-9;				// 600dpi,カラー
	else if(     !  pale )	cc = dotL * 16e-9  +  dotM *  8e-9  +  dotS * 3.20e-9;				//1200dpi,カラー
	else				{	cc = dotL * 20e-9  +  dotM * 10e-9  +  dotS * 4.00e-9;	cc /= 0.95;}//1200dpi,白

	return	cc;
}

/**
 * グラフィックスログ
 */
BOOL CLogAnalyze::GetGraphics( char* pColor, char* pWhite, int* pResolution, char* pMultipass, char *pEnhance )
{
	if(!m_addition.IsEmpty())
	{
		CString strText = m_addition;

		int start=0;
								CLogString::tokenize( strText, " ", start );	//最初の４バイト
								CLogString::tokenize( strText, " ", start );	//２番目の４バイト
		CString strToken3 ="0x"+CLogString::tokenize( strText, " ", start );	//３番目の４バイト
								CLogString::tokenize( strText, " ", start );	//４番目の４バイト
		CString strToken5 ="0x"+CLogString::tokenize( strText, " ", start );	//５番目の４バイト
		CString strToken6 ="0x"+CLogString::tokenize( strText, " ", start );	//６番目の４バイト

		unsigned long digit3, digit5, digit6;
		CLogString::stringToDigit( strToken3, digit3 );	//３番目の４バイト
		CLogString::stringToDigit( strToken5, digit5 );	//５番目の４バイト
		CLogString::stringToDigit( strToken6, digit6 );	//６番目の４バイト

		*pColor			= BYTE( digit3 >> 16 );
		*pWhite			= BYTE( digit3 >>  8 );
		*pResolution	= WORD( digit5       );
		*pMultipass		= BYTE( digit6 >> 24 );
		//黒さアップ
		BYTE		n13	= BYTE( digit6 >> 8 );
		BYTE		n14	= BYTE( digit6      );
		*pEnhance		= 0;
		if( n14 & 1 ) {
				 if( n13 <= 25 )	*pEnhance = 1;
			else if( n13 <= 45 )	*pEnhance = 2;
			else if( n13 <= 70 )	*pEnhance = 3;
			else					*pEnhance = 4;
		}

		return true;
	}
	return false;
}

/**
 * 特殊印刷指定を得る
 */
BOOL CLogAnalyze::GetPrintMode( char* pUniDir, char* pEndless, char* pMulti )
{
	if(!m_addition.IsEmpty())
	{
		CString strText = m_addition;

		int start = 0;
		CString strToken = "0x"+CLogString::tokenize(strText, " ", start);

		unsigned long digit;
		CLogString::stringToDigit(strToken, digit);

		*pUniDir  = BYTE( digit >> 24 );
		*pEndless = BYTE( digit >> 16 );
		*pMulti   = BYTE( digit >>  8 );

		return true;
	}
	return false;
}

BOOL CLogAnalyze::GetJobAll( CString* pPlaten, CString* pArpTime, CString* pMachine, CString* pTranscolor,
							char* pSatu, char* pBrig, char* pCont, char* pInkVolume,
							char* pUniDir, char* pBlack, char* pMask, char* pHighlight, char* cMinWhite )
{
	if(!m_addition.IsEmpty())
	{
		CString strText = m_addition;
		int	start = 0;
									CLogString::tokenize( strText, " ", start );	//[ 0]
									CLogString::tokenize( strText, " ", start );	//[ 1]
									CLogString::tokenize( strText, " ", start );	//[ 2]
									CLogString::tokenize( strText, " ", start );	//[ 3]
									CLogString::tokenize( strText, " ", start );	//[ 4]
									CLogString::tokenize( strText, " ", start );	//[ 5]
									CLogString::tokenize( strText, " ", start );	//[ 6]
									CLogString::tokenize( strText, " ", start );	//[ 7]
									CLogString::tokenize( strText, " ", start );	//[ 8]
									CLogString::tokenize( strText, " ", start );	//[ 9]
									CLogString::tokenize( strText, " ", start );	//[10]
									CLogString::tokenize( strText, " ", start );	//[11]
									CLogString::tokenize( strText, " ", start );	//[12]
		*pPlaten			=		CLogString::tokenizeString( strText, " ", start, 15-13 ); //[13][14]プラテン名
									CLogString::tokenize( strText, " ", start );	//[15]
									CLogString::tokenize( strText, " ", start );	//[16]
									CLogString::tokenize( strText, " ", start );	//[17]
									CLogString::tokenize( strText, " ", start );	//[18]
									CLogString::tokenize( strText, " ", start );	//[19]
									CLogString::tokenize( strText, " ", start );	//[20]
									CLogString::tokenize( strText, " ", start );	//[21]
									CLogString::tokenize( strText, " ", start );	//[22]
									CLogString::tokenize( strText, " ", start );	//[23]
									CLogString::tokenize( strText, " ", start );	//[24]
									CLogString::tokenize( strText, " ", start );	//[25]
									CLogString::tokenize( strText, " ", start );	//[26]
									CLogString::tokenize( strText, " ", start );	//[27]
									CLogString::tokenize( strText, " ", start );	//[28]
									CLogString::tokenize( strText, " ", start );	//[29]
									CLogString::tokenize( strText, " ", start );	//[30]
									CLogString::tokenize( strText, " ", start );	//[31]
									CLogString::tokenize( strText, " ", start );	//[32]
									CLogString::tokenize( strText, " ", start );	//[33]
									CLogString::tokenize( strText, " ", start );	//[34]
									CLogString::tokenize( strText, " ", start );	//[35]
									CLogString::tokenize( strText, " ", start );	//[36]
									CLogString::tokenize( strText, " ", start );	//[37]
									CLogString::tokenize( strText, " ", start );	//[38]
		CString strToken39 = "0x" + CLogString::tokenize( strText, " ", start );	//[39]ドライバ設定 n 1- 4
		CString strToken40 = "0x" + CLogString::tokenize( strText, " ", start );	//[40]ドライバ設定 n 5- 8
		CString strToken41 = "0x" + CLogString::tokenize( strText, " ", start );	//[41]ドライバ設定 n 9-12
		CString strToken42 = "0x" + CLogString::tokenize( strText, " ", start );	//[42]ドライバ設定 n13-16
		CString strToken43 = "0x" + CLogString::tokenize( strText, " ", start );	//[43]ドライバ設定 n17-20
		CString strToken44 = "0x" + CLogString::tokenize( strText, " ", start );	//[44]ドライバ設定 n21-24
		CString strToken45 = "0x" + CLogString::tokenize( strText, " ", start );	//[45]ドライバ設定 n25-28
		CString strToken46 = "0x" + CLogString::tokenize( strText, " ", start );	//[46]ドライバ設定 n29-32

		unsigned long digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9;
		CLogString::stringToDigit( strToken39, digit2 );	//２番目の４バイト	1-4
		CLogString::stringToDigit( strToken40, digit3 );	//３番目の４バイト	5-8
		CLogString::stringToDigit( strToken41, digit4 );	//４番目の４バイト	9-12
		CLogString::stringToDigit( strToken42, digit5 );	//５番目の４バイト	13-16
		CLogString::stringToDigit( strToken43, digit6 );	//６番目の４バイト	17-20
		CLogString::stringToDigit( strToken44, digit7 );	//７番目の４バイト	21-24
		CLogString::stringToDigit( strToken45, digit8 );	//８番目の４バイト	25-28
		CLogString::stringToDigit( strToken46, digit9 );	//９番目の４バイト	29-32

		char buf[64] ={0};
		time_t time = (time_t)( BYTE(digit3>>16) << 24 | BYTE(digit3>>24) << 16 | BYTE(digit2) << 8 | BYTE(digit2>>8) );
		struct tm *ftime = localtime(&time);
		strftime( buf, 64, "%d/%m/%Y %H:%M:%S", ftime );
		*pArpTime = buf;

		char machine= BYTE( digit7 >>  8 );
		switch( machine ) {
			case 2:		*pMachine = "GTX-422";	break;
			case 1:		*pMachine = "GTX-411";	break;
			default:	*pMachine = "Unknown";	break;
		}

		if( digit6 >> 24 ) {
			pTranscolor->Format(_T("0x%06X"), digit6 >> 8 );
		}
		else {
			*pTranscolor = "OFF";
		}

		*pSatu		= BYTE( digit3 >>  8 );
		*pBrig		= BYTE( digit9 >> 24 );
		*pCont		= BYTE( digit3       );
		*pInkVolume	= BYTE( digit4 >> 24 );
		*pUniDir	= BYTE( digit4 >>  8 );
		*pBlack		= BYTE( digit4       );
//		*pWGrad		= BYTE( digit5 >> 24 );
		*pMask		= BYTE( digit5 >> 16 );
		*pHighlight	= BYTE( digit5       );
		*cMinWhite	= BYTE( digit9 >> 16 );

		return true;
	}
	return false;
}

BOOL CLogAnalyze::GetPurge( unsigned long* pType, unsigned long* pColor )
{
	if(!m_addition.IsEmpty())
	{
		CString strText = m_addition;

		int start = 0;
		CString strToken1 ="0x"+CLogString::tokenize( strText, " ", start );	//最初の４バイト
		CString strToken2 ="0x"+CLogString::tokenize( strText, " ", start );	//２番目の４バイト

		unsigned long digit1, digit2;
		CLogString::stringToDigit( strToken1, digit1 );	//１番目の４バイト
		CLogString::stringToDigit( strToken2, digit2 );	//２番目の４バイト

		*pType	= digit1;
		*pColor	= digit2;
		return true;
	}
	return false;
}

BOOL CLogAnalyze::GetPcInfo( CString* pOS, CString* pCpu, unsigned short* pRam,
								char* pFile, CString* pApp, unsigned long* pVer )
{
	if(!m_addition.IsEmpty())
	{
		CString strText = m_addition;
		int	start = 0;
									CLogString::tokenize( strText, " ", start );	//[ 0]
		CString strToken1 ="0x"+	CLogString::tokenize( strText, " ", start );	//[ 1] FO, APP, OS
		CString strToken2 ="0x"+	CLogString::tokenize( strText, " ", start );	//[ 2] App vers
		CString strToken3 ="0x"+	CLogString::tokenize( strText, " ", start );	//[ 3] API vers
		CString strToken4 ="0x"+	CLogString::tokenize( strText, " ", start );	//[ 4] Drv vers
		CString strToken5 ="0x"+	CLogString::tokenize( strText, " ", start );	//[ 5] OS  vers
		*pCpu				=		CLogString::tokenizeString( strText, " ", start, 18-6 ); //[ 6][17]  Processor
		CString strToken8 ="0x"+	CLogString::tokenize( strText, " ", start );	//[18] RAM, free
		CString strToken9 ="0x"+	CLogString::tokenize( strText, " ", start );	//[19] virtual

		unsigned long digit1, digit2, digit3, digit4, digit5, digit8, digit9;
		CLogString::stringToDigit( strToken1, digit1 );	//１番目の４バイト
		CLogString::stringToDigit( strToken2, digit2 );	//２番目の４バイト
		CLogString::stringToDigit( strToken3, digit3 );	//３番目の４バイト
		CLogString::stringToDigit( strToken4, digit4 );	//４番目の４バイト
		CLogString::stringToDigit( strToken5, digit5 );	//５番目の４バイト
		CLogString::stringToDigit( strToken8, digit8 );	//18番目の４バイト
		CLogString::stringToDigit( strToken9, digit9 );	//19番目の４バイト

		switch( BYTE( digit1 ) )
		{
		case	0:
			if      ( digit5 == 0x06010000 )	*pOS = "Win7";
			else if ( digit5 == 0x06020000 )	*pOS = "Win8";
			else if ( digit5 == 0x06030000 )	*pOS = "Win8.1";
			else if ( digit5 == 0x0A000000 )	*pOS = "Win10";
			else                                *pOS = "Win";
			*pOS += BYTE( digit1 >> 8 ) ? " 64bit" : " 32bit";
			if      ( digit5 == 0x00000000 )	*pOS = "unknown";
			break;
		case	1:
			pOS->Format(_T("mac %d.%d.%d"), BYTE(digit5>>24), BYTE(digit5>>16), BYTE(digit5>>8) );
			break;
		default:
			*pOS = "unknown";
			break;
		}
		pRam[0]		= WORD( digit8       );
		pRam[1]		= WORD( digit8 >> 16 );

		*pFile		= BYTE( digit1 >> 24 );
		switch( BYTE( digit1 >> 16 ) )
		{
		case	1:		*pApp = "Graphics Lab";			*pVer = digit2;						break;
		case	2:		*pApp = "Graphics Lab Basic";	*pVer = digit2;						break;
		case	3:		*pApp = "Driver";				*pVer = digit4;						break;
		case	4:		*pApp = "API";					*pVer = digit3;						break;
		case	5:		*pApp = "Commandline";			*pVer = digit2;						break;
		default:		*pApp = "unknown";				*pVer = digit3 ? digit3 : digit4;	break;
		}

		return true;
	}

	return false;
}
