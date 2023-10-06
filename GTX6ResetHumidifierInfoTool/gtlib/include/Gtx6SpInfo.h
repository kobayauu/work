//////////////
///Gtx6SpInfo.h
//////////////
#ifndef _GTX6SPINFO_H
#define _GTX6SPINFO_H


//情報のバージョン
#define	ARMANI_INFO_VERSION			0x00000003

#define JOB_COMENT_MAX_SIZE	 		128
#define JOB_NAME_MAX_SIZE	 		128
#define PLATEN_NAME_MAX_SIZE 		32

#define INK_LIMIT_A_PARAM			1		//InkLimit A Param (K依存率) デフォルト値
#define CUTWHITEOUTLINE				2

#define RATEOFDOORDONOTCOMPRESS		99		//デフォルト値
#define INK_LIMIT					180		//%デフォルト値

//白ラスタデータの縮小				White Raster Compact
typedef enum
{
		AR_WRC_LAYER				= 0,	//disuse
		AR_WRC_USE_ab				= 1,	//disuse
		AR_WRC_ALL_a				= 2,
		AR_WRC_DIVIDE				= 3,
		AR_WRC_INTRLC				= 4,
} AR_WRC;

//機種モード
typedef enum 
{
		MACHINE_MODE_NONE			=-1,
		MACHINE_MODE_GTX611			= 0,
		MACHINE_MODE_GTX622			= 1,
} MACHINE_MODE;

//解像度 X
typedef enum 
{
		RESOLUTION_X_600			= 0,
		RESOLUTION_X_450			= 1,
		RESOLUTION_X_300			= 2,
		RESOLUTION_X_1200			= 3,
		RESOLUTION_X_900			= 4,
} RESOLUTION_X;

//解像度 Y
typedef enum 
{
		RESOLUTION_Y_600			= 0,
		RESOLUTION_Y_450			= 1,
		RESOLUTION_Y_300			= 2,
		RESOLUTION_Y_1200			= 3,
		RESOLUTION_Y_900			= 4,
} RESOLUTION_Y;

//解像度
typedef struct
{
	RESOLUTION_X	XRes;
	RESOLUTION_Y	YRes;
} RESOLUTION;


//INK_VOLUME
typedef enum 
{
		INK_VOLUME_100				= 0,	//Anti-Blur 0
		INK_VOLUME_90				= 1,	//Anti-Blur 1
		INK_VOLUME_80				= 2,	//Anti-Blur 2
		INK_VOLUME_70				= 3,	//Anti-Blur 3
		INK_VOLUME_60				= 4,	//Anti-Blur 4
		INK_VOLUME_50				= 5,	//Anti-Blur 5
		INK_VOLUME_40				= 6,	//Anti-Blur 6
		INK_VOLUME_30				= 7,	//Anti-Blur 7
		INK_VOLUME_20				= 8,	//Anti-Blur 8
		INK_VOLUME_10				= 9,	//Anti-Blur 9
} INK_VOLUME;

//PREVIEW_POS
typedef enum 
{
		PREVIEW_POS_NONE			= 0,	//None
		PREVIEW_POS_HEADER			= 1,	//in Header
		PREVIEW_POS_FOOTER			= 2,	//in Footer
} PREVIEW_POS;

//TRANS_LAYER
typedef enum
{
		TRANS_LAYER_OFF				= 0,	//OFF
		TRANS_LAYER_CREATE			= 1,	//Create ARTR File
		TRANS_LAYER_IMPORT			= 2,	//Import ARTR File
} TRANS_LAYER;

//DOUBLE_PRINT
typedef enum 
{
		DOUBLE_PRINT_OFF			= 0,	//OFF
		DOUBLE_PRINT_DP				= 1,	//DoublePrint 強制的に　INK_VOLUME=100
		DOUBLE_PRINT_TIGER			= 2,	//Tiger (Yellow / Black)
		DOUBLE_PRINT_POLYE			= 3,	//Poly E
} DOUBLE_PRINT;

//2値化タイプ
typedef enum 
{
		BINARIZATION_TYPE_DITHER				= 0,	//ディザ
		BINARIZATION_TYPE_ERR_FROMi2_YASUNARI	= 1,	//やすなり誤差拡散
	//	BINARIZATION_TYPE_ERR_FROM_BH13v2		= 2,	//BH13 誤差拡散2値		//disuse
	//	BINARIZATION_TYPE_ERR_FROM_BH13v4		= 3,	//BH13 誤差拡散4値		//disuse
		BINARIZATION_TYPE_CASE_BH13v4			= 4,	//BH13 場合分け4値
	//	BINARIZATION_TYPE_ERR_FROM_BH13v4v2		= 5,	//BH13 誤差拡散カラー4値白2値	//disuse
		BINARIZATION_TYPE_ERR_FORM_VARIABLE		= 6,	//やすなり誤差拡散 ワーム減少
} BINARIZATION_TYPE;

//カラーマッチタイプ
typedef enum 
{
		COLORMATCH_TYPE_ICCMGR		= 0,
		COLORMATCH_TYPE_NONE		= 1,
} COLORMATCH_TYPE;

//圧縮方法
typedef enum 
{
	COMPRESSION_TYPE_NONE			= 0,	//なし
	COMPRESSION_TYPE_TIFF			= 1,	//ランレングス
	COMPRESSION_TYPE_ZLIB			= 2,	//Zlib
} COMPRESSION_TYPE;


//白データ情報
typedef enum 
{
		WHITE_IN_PANCAKE			= 0,	//全部Wを打つ Kも打つ
		WHITE_IN_WCMY				= 1,	//WCMY W=255-K , K=0;
		WHITE_IN_WCMY_PLUS_K		= 2,	//WCMY W=255-K , K=K;
		WHITE_IN_MONO				= 3,	//モノクロ　Wしか使わない
} WHITE_IN_TYPE;

//プリントモード
typedef enum 
{
		PRINT_MODE_COLOR_ONLY		= 0,	//カラーのみ
		PRINT_MODE_WHITE_ONLY		= 1,	//白のみ
		PRINT_MODE_WHITE_COLOR		= 2,	//白カラー同時打ち
		PRINT_MODE_COLOR_MONO		= 3,	//黒のみ
} PRINT_MODE;

typedef enum
{
		PRINT_SUBMODE_OFF			= 0,	//なし
		PRINT_SUBMODE_SPECIAL		= 1,	//特色
		PRINT_SUBMODE_FLUOR			= 2,	//蛍光
} PRINT_SUBMODE;

typedef enum
{
	COLOR_MODE_VIBRANT				= 0,	//鮮やか
	COLOR_MODE_NATURAL				= 1,	//ナチュラル
} COLOR_MODE;

typedef struct 
{
	BOOL				bWhite;				//白データを作成するかどうか　
	WHITE_IN_TYPE		InType;				//白データの入力方法　bWhite == TRUE の時有効	
	BOOL				bW4;				//W4打ち　白ヘッド４つでデータをそれぞれ変える	//disuse
	int					iCutOutline_X;		//白輪郭の横の削り幅 0の時は削らない
	int					iCutOutline_Y;		//白輪郭の縦の削り幅 0の時は削らない
	BOOL				bNotCutOnlyWhite;	//単独白は削らない
	int					iCalVolume;			//W用のCalボリューム
	int					iMaskVolume;		//MaskVolume
	int					iWhiteTime;			//印刷時間
	int					iWhiteLight;		//明るさ
	int					iWhiteInkMax;		//インク量の最大値
	int					iWhiteInkMin;		//インク量の最小値
	int					iWhiteCount;		//白の印刷回数
	int					iWhiteMax;			//WhiteMax %
	int					iWhiteMin;			//最低白インク量
	int					iWhiteCompact;		//白データの圧縮方法
	int					iWhiteAll;			//白の印刷で可能なインク量の上限
	BOOL				bWhitePale;			//95% White
	BOOL				bEcoMode;			//エコモード
	BOOL				bNonBleed;			//にじみ軽減
//	BOOL				bFastMode;			//白高速印刷
} WHITEDATA_TYPE;

typedef struct
{
	BYTE				byAppType;			//アプリの種類
	DWORD				dwVersion[3];		//バージョン
	BYTE				byOS[4];			//OSの種類
	BYTE				byCPU[48];			//CPUの種類
	WORD				wMemory[3];			//メモリー容量
} ENVIRONMENT_TYPE;

//プラテン情報
typedef struct
{
	char				cName[PLATEN_NAME_MAX_SIZE+1];
	int					iSizeX;				//600 dpi 単位
	int					iSizeY;
	int					iOffsetX;
	int					iOffsetY;
} PLATEN_INFO;

//プラテン高さ指定
typedef struct
{
	BOOL				bAdjust;
	int					iPos;
} PLATEN_HEIGHT;

//印刷情報
typedef struct
{
	PRINT_MODE			PrintMode;							//プリントモード
	PRINT_SUBMODE		PrintSubMode;						//プリントサブモード
	PLATEN_INFO			PlatenInfo;							//プラテン情報
	PLATEN_HEIGHT		PlatenHeight;						//プラテン高さ指定
	COMPRESSION_TYPE	CompressionType;					//圧縮の種類
	int					iRateOfCompress;					//圧縮するかどうかの割合
	int					iNumOfCopies;						//印刷指示枚数
	char				cJobComent[JOB_COMENT_MAX_SIZE+1];	//ジョブコメント
	char				cJobName[JOB_NAME_MAX_SIZE+1];		//ジョブ名
	BOOL				bHeadFastMoving;					//ヘッド高速化移動するかどうか
	DOUBLE_PRINT		DoublePrint;						//Double Print Mode
	BOOL				bUniDirection;						//片方印刷

	BOOL				bChksum;							//コマンド毎にチェックサム出すかどうかfor debug
	BOOL				bEndlessPrn;						//無限印字（２度うちの変形） for debug

	MACHINE_MODE		MachineMode;						//機種モード
	BOOL				bBlackTs;							//黒インクを使用する
	BOOL				bMultiPass;							//マルチパス
	int					iEnhancedBlack;						//黒さアップ

	BOOL				bColorToWhite;						//CMYK → W1W2W3W4
} PRINT_INFO;

//出力画像データ情報
typedef struct
{
	RESOLUTION			Resolution;							//解像度
	BOOL				bHighQuality;						//高画質モード
	DOUBLE_PRINT		DoublePrint;						//Double Print Mode
	PREVIEW_POS			PreviewPos;							//プレビューの位置(なし,ヘッダ,フッタ)
	BOOL				bAutoSetting;						//解像度、メディアによって各パラメータを自動決定するかどうか
	WHITEDATA_TYPE		WhiteDataType;						//白データ情報
	BOOL				bTransColor;						//透明色を指定するかどうか　WhiteDataType!=WHITEDATA_NOの時有効
	COLORREF			colorTrans;							//下地の色
	int					iTRRange;							//透明色の影響範囲
	int					iChromaUp;							//彩度アップ量 0-40
	int					iBrightness;						//明度アップ量 0-40
	int					iVivid;								//Vivid        0-40
	BOOL				bPause;								//白カラー間隔印刷
    int                 iPauseSpan;
    BOOL                bDivide;                            //白分割印刷
    int                 iDivideSpan;
	int					iCyanBalance;						//カラーバランス(シアン)	-5~+5
	int					iMagentaBalance;					//カラーバランス(マゼンタ)
	int					iYellowBalance;						//カラーバランス(イエロー)
	int					iBlackBalance;						//カラーバランス(ブラック)
	int					iSpecial1Balance;					//カラーバランス(特色1)
	int					iSpecial2Balance;					//カラーバランス(特色2)
	COLOR_MODE			ColorMode;							//カラーモード

//↓bAutoSettingが有効の時必要なもの
	INK_VOLUME			InkVolume;							//InkVolume（bAutoSettingの時有効）
//↑bAutoSettingが有効の時必要なもの

//↓bAutoSettingが有効の時無効となるもの
	char				cCalFilePath[MAX_PATH];				//Calファイルのパス
	char				cProfileFilePath[MAX_PATH];			//プロファイルのパス ""の時は自動的に判断
	char				cImproveFilePath[MAX_PATH];			//Improveファイルのパス ""の時は行わない
	int					iInkLimit;							//インク総量値(%)0を入れると自動的に判断
	COLORMATCH_TYPE		colormatch_type;					//カラーマッチングタイプ
	BINARIZATION_TYPE	BinarizationType;					//２値化タイプ
	BOOL				bUseCalInInputCMYK;					//InputCMYKの時Calibrationを行うかどうか
	float				fInkLimit_A_Param;					//インク総量 K依存率(a) 1～1000　1:Normal 1000:CMYK平等
//↑bAutoSettingが有効の時無効となるもの
	MACHINE_MODE		MachineMode;						//機種モード
	BOOL				bWhiteGrad;							//白インクのグラディエーション

	TRANS_LAYER			TransLayer;							//透明レイヤー
	char				cTransFilePath[MAX_PATH];			//透明ファイルのファイル名
	BOOL				bPureCMYK;							//単インク印刷
	BOOL				bInputCMYK;							//CMYK直接入力
	int					iWidthCMYK;
	int					iHeightCMYK;
	char				cCMYKFilePath[MAX_PATH];
	BOOL				bInputBH13TBL;						//BH13の誤差拡散テーブルの入力
	char				cBH13TBLFilePath[MAX_PATH];
	int					iColorType;							//指定した色のみ表示
	int					iColorSize;							//指定したサイズのみ表示

	ENVIRONMENT_TYPE	EnvironType;						//アプリ&PC環境
} OUTPUT_INFO;


#endif /*_GTX6SPINFO_H*/
