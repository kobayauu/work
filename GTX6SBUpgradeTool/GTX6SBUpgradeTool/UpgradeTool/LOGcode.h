/**********************************************************/
/*   LOGcode.h                       03.4.17    k.hayashi */
/**********************************************************/

#ifndef _LOGCODE_H_
#define _LOGCODE_H_



//--- log_level 3bit(1～5) ----------------------------------------------
#define LVL_FATAL		1		// 致命的なエラー
#define LVL_MIDDLE		2		// 通常起こりうるエラー
#define LVL_WARNING		3		// ワーニング
#define LVL_EVENT1		4		// 必須な稼動ログ
#define LVL_EVENT2		5		// 一般の稼動ログ



/*--- log_code 4byte ----------------------------------*/
//ログコードの構成
//  稼働ログコード　　0x00010000～0x99990000
//  エラーログコード　  0x00000001～0x00009999
//
/*--- log_code 4byte ----------------------------------*/

//	2.1 稼動ログ(bit15-12:0000)
//		2.1.1 内部動作
//		2.1.1.1 電源
#define OP_PW_ON					0x00000001	// 電源オン
#define		OP_PW_ON_LVL				LVL_EVENT1
#define OP_PW_OFF					0x00000002	// 電源オフ
#define		OP_PW_OFF_LVL				LVL_EVENT1
///#define OP_SOFT_RESET				0x00000003	// ソフトリセット
///#define		OP_SOFT_RESET_LVL			LVL_EVENT1
///#define OP_OTHER_RESET				0x00000004	// その他のリセット
///#define		OP_OTHER_RESET_LVL			LVL_EVENT1
#define	OP_PW_RCV_INIT_CMPLT		0x00000014	// 初期化完了
#define		OP_PW_RCV_INIT_CMPLT_LVL	LVL_EVENT1

#define	OP_USBHOST_REOPEN			0x00000101	// サフラン再接続(USBホスト)
#define		OP_USBHOST_REOPEN_LVL		LVL_EVENT1

//		2.1.1.3 基本動作
///#define OP_PR_START					0x00000200	// 印刷開始
///#define		OP_PR_START_LVL				LVL_EVENT1
///#define OP_PR_END					0x00000201	// 印刷終了
///#define		OP_PR_END_LVL				LVL_EVENT1
///#define OP_PR_CAN					0x00000202	// 印刷中止
///#define		OP_PR_CAN_LVL				LVL_EVENT1
///#define OP_PURGE_A					0x00000210	// パージ開始全色
///#define		OP_PURGE_A_LVL				LVL_EVENT1
///#define OP_PURGE_K					0x00000211	// パージ開始ブラック
///#define		OP_PURGE_K_LVL				LVL_EVENT1
///#define OP_PURGE_M					0x00000212	// パージ開始マゼンタ
///#define		OP_PURGE_M_LVL				LVL_EVENT1
///#define OP_PURGE_C					0x00000213	// パージ開始シアン
///#define		OP_PURGE_C_LVL				LVL_EVENT1
///#define OP_PURGE_Y					0x00000214	// パージ開始イエロー
///#define		OP_PURGE_Y_LVL				LVL_EVENT1
///#define OP_PURGE_END				0x00000215	// パージ終了
///#define		OP_PURGE_END_LVL			LVL_EVENT1
///#define OP_PURGE_CAN				0x00000216	// パージ中止
///#define		OP_PURGE_CAN_LVL			LVL_EVENT1

///#define OP_PR_TEST					0x00000220	// テスト印字
///#define		OP_PR_TEST_LVL				LVL_EVENT1

//		2.1.1.4 自動動作
//			2.1.1.4.1 パージ
#define	AU_PURGE_START				0x00000300	// オートパージ開始
#define		AU_PURGE_START_LVL			LVL_EVENT1
#define	AU_PURGE_END				0x00000301	// オートパージ終了
#define		AU_PURGE_END_LVL			LVL_EVENT1
#define	AU_SUCK_WASH_START			0x00000302	// キャップ上の洗浄液を除去開始（終業クリーニング（キャップ洗浄）後の閉空吸引）
#define		AU_SUCK_WASH_START_LVL		LVL_EVENT1
#define	AU_SUCK_WASH_END			0x00000303	// キャップ上の洗浄液を除去終了（終業クリーニング（キャップ洗浄）後の閉空吸引）
#define		AU_SUCK_WASH_END_LVL		LVL_EVENT1

#define	MAINCTL_AUTO_PURGE_START	0x00000304	// オートパージ開始（部品交換後の電源オン時）
#define		MAINCTL_AUTO_PURGE_START_LVL	LVL_EVENT1
#define	MAINCTL_AUTO_PURGE_END		0x00000305	// オートパージ終了（部品交換後の電源オン時）
#define		MAINCTL_AUTO_PURGE_END_LVL		LVL_EVENT1

#define	AU_CIRCULATION_WHITE_ALL	0x00000310	// 白インク循環（All White）正常終了	自動でもメニューでも
#define		AU_CIRCULATION_WHITE_ALL_LVL	LVL_EVENT1

#define	AU_CIRCULATION_BTN_CANCEL	0x00000311	// 白インク循環キャンセル（キャンセルボタンでのキャンセル）
#define		AU_CIRCULATION_BTN_CANCEL_LVL	LVL_EVENT1

#define	AU_CIRCULATION_MNT_CANCEL	0x00000312	// 白インク循環キャンセル（他の要因によるキャンセルカートリッジが抜かれたなど）
#define		AU_CIRCULATION_MNT_CANCEL_LVL	LVL_EVENT1

#define SW_CLOSURE_PURGE			0x00000320	// ソフトスイッチ押下による終業パージ
#define		SW_CLOSURE_PURGE_LVL				LVL_EVENT1
#define SW_CLOSURE_PURGE2			0x00000321	// ソフトスイッチ押下による洗浄液、インクエンプティ時の終業パージ
#define		SW_CLOSURE_PURGE2_LVL			LVL_EVENT1

#define AU_CLOSURE_PURGE			0x00000330	// 印刷後８時間経過による終業パージ
#define		AU_CLOSURE_PURGE_LVL				LVL_EVENT1
#define AU_CLOSURE_PURGE2			0x00000331	// 印刷後８時間経過による洗浄液、インクエンプティ時の終業パージ
#define		AU_CLOSURE_PURGE2_LVL			LVL_EVENT1


#define AU_CYCLOE_TEMP_VALUE		0x00000340	// 温度/湿度ログ(1時間周期での書き込み)
#define 	AU_CYCLOE_TEMP_VALUE_LVL		LVL_EVENT1

//			2.1.1.4.2 リアルタイムクロック


//		2.1.1.5 二次的動作
//			2.1.1.5.1 プラテン

//			2.1.1.5.2 クリアランスセンサ

//			2.1.1.5.3 キャップ

//			2.1.1.5.4 ワイパ

//			2.1.1.5.5 ポンプ

//			2.1.1.5.6 キャリッジ
#define CRG_LOG_OUT_LOCK_PWON		0x00000600	// キャリッジが電源ON時にロッカーの外にいた
#define 	CRG_LOG_OUT_LOCK_PWON_LVL	LVL_EVENT2
#define CRG_LOG_REMOVE_OK			0x00000601	// キャリッジがショートしたが、再起動でOK
#define 	CRG_LOG_REMOVE_OK_LVL		LVL_EVENT2
#define CRG_LOG_SPEED_CHECK			0x00000602	// キャリッジ速度確認ログ
#define 	CRG_LOG_SPEED_CHECK_LVL		LVL_EVENT2
#define CRG_LOG_SPEED_ADJUST		0x00000603	// キャリッジ速度調整ログ
#define 	CRG_LOG_SPEED_ADJUST_LVL	LVL_EVENT1

//			2.1.1.5.7 フラッシング

//			2.1.1.5.8 バルブ

//			2.1.1.5.10 メンテファーム更新

//			2.1.1.5.11 CFカード制御

//			2.1.1.5.12 GetJob

//			2.1.1.5.13 リプリントデータ制御


//		2.1.2 操作ログ
//		2.1.2.1 パネルスイッチ

//		2.1.2.2 ケーブル接続
//			2.1.2.2.1 ＵＳＢケーブル
//			2.1.2.2.2 1284ケーブル



//		2.1.2.3 メニュー操作
#define	MN_PURGE_NORM_ALL_CW		0x00001000		// ノーマルクリーニング実行（All Color & White）
#define		MN_PURGE_NORM_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_NORM_ALL_C			0x00001001		// ノーマルクリーニング実行（All Color）
#define		MN_PURGE_NORM_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_K				0x00001002		// ノーマルクリーニング実行（K）
#define		MN_PURGE_NORM_K_LVL			LVL_EVENT1
#define	MN_PURGE_NORM_M_C_Y			0x00001003		// ノーマルクリーニング実行（MCY）
#define		MN_PURGE_NORM_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_ALL_W			0x00001004		// ノーマルクリーニング実行（All White）
#define		MN_PURGE_NORM_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_W1			0x00001005		// ノーマルクリーニング実行（W1）
#define		MN_PURGE_NORM_W1_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_W2_4			0x00001006		// ノーマルクリーニング実行（W234）
#define		MN_PURGE_NORM_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_POWR_ALL_CW		0x00001010		// パワフルクリーニング実行（All Color & White）
#define		MN_PURGE_POWR_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_POWR_ALL_C			0x00001011		// パワフルクリーニング実行（All Color）
#define		MN_PURGE_POWR_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_K				0x00001012		// パワフルクリーニング実行（K）
#define		MN_PURGE_POWR_K_LVL			LVL_EVENT1
#define	MN_PURGE_POWR_M_C_Y			0x00001013		// パワフルクリーニング実行（MCY）
#define		MN_PURGE_POWR_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_ALL_W			0x00001014		// パワフルクリーニング実行（All White）
#define		MN_PURGE_POWR_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_W1			0x00001015		// パワフルクリーニング実行（W1）
#define		MN_PURGE_POWR_W1_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_W2_4			0x00001016		// パワフルクリーニング実行（W234）
#define		MN_PURGE_POWR_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_HYPER_ALL_CW		0x00001020		// スーパークリーニング実行（All Color & White）
#define		MN_PURGE_POWR_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_ALL_C		0x00001021		// スーパークリーニング実行（All Color）
#define		MN_PURGE_HYPER_ALL_C_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_K			0x00001022		// スーパークリーニング実行（K）
#define		MN_PURGE_HYPER_K_LVL		LVL_EVENT1
#define	MN_PURGE_HYPER_M_C_Y		0x00001023		// スーパークリーニング実行（MCY）
#define		MN_PURGE_HYPER_M_C_Y_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_ALL_W		0x00001024		// スーパークリーニング実行（All White）
#define		MN_PURGE_HYPER_ALL_W_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_W1			0x00001025		// スーパークリーニング実行（W1）
#define		MN_PURGE_HYPER_W1_LVL		LVL_EVENT1
#define	MN_PURGE_HYPER_W2_4			0x00001026		// スーパークリーニング実行（W234）
#define		MN_PURGE_HYPER_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_INIT_ALL_CW		0x00001030		// 初期インク導入実行（All Color & White）
#define		MN_PURGE_INIT_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_INIT_ALL_C			0x00001031		// 初期インク導入実行（All Color）
#define		MN_PURGE_INIT_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_K				0x00001032		// 初期インク導入実行（K）
#define		MN_PURGE_INIT_K_LVL			LVL_EVENT1
#define	MN_PURGE_INIT_M_C_Y			0x00001033		// 初期インク導入実行（MCY）
#define		MN_PURGE_INIT_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_ALL_W			0x00001034		// 初期インク導入実行（All White）
#define		MN_PURGE_INIT_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_W1			0x00001035		// 初期インク導入実行（W1）
#define		MN_PURGE_INIT_W1_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_W2_4			0x00001036		// 初期インク導入実行（W234）
#define		MN_PURGE_INIT_W2_4_LVL		LVL_EVENT1

#define MN_CAP_CLEAN_PURGE_C		0x00001041		// キャップ洗浄（終業クリーニング）実行（Color）
#define 	MN_CAP_CLEAN_PURGE_C_LVL	LVL_EVENT1
#define MN_CAP_CLEAN_PURGE_W		0x00001044		// キャップ洗浄（終業クリーニング）実行（White）
#define 	MN_CAP_CLEAN_PURGE_W_LVL	LVL_EVENT1

#define MN_DISCHARGELIQUID			0x00001050		// キャップ上の洗浄液を除去（終業クリーニング（キャップ洗浄）後の閉空吸引）
#define 	MN_DISCHARGELIQUID_LVL		LVL_EVENT1

#define	MN_TUBE_CLEAN_ALL_CW		0x00001060		// チューブクリーニング実行（All Color & White）
#define		MN_TUBE_CLEAN_ALL_CW_LVL	LVL_EVENT1
#define	MN_TUBE_CLEAN_ALL_C			0x00001061		// チューブクリーニング実行（All Color）
#define		MN_TUBE_CLEAN_ALL_C_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_K				0x00001062		// チューブクリーニング実行（K）
#define		MN_TUBE_CLEAN_K_LVL			LVL_EVENT1
#define	MN_TUBE_CLEAN_YCM_CW		0x00001063		// チューブクリーニング実行（MCY）
#define		MN_TUBE_CLEAN_YCM_CW_LVL	LVL_EVENT1
#define	MN_TUBE_CLEAN_ALL_W			0x00001064		// チューブクリーニング実行（All White）
#define		MN_TUBE_CLEAN_ALL_W_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_W1			0x00001065		// チューブクリーニング実行（W1）
#define		MN_TUBE_CLEAN_W1_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_W2_4			0x00001066		// チューブクリーニング実行（W234）
#define		MN_TUBE_CLEAN_W2_4_LVL		LVL_EVENT1

#define MN_HEAD_CLEAN_ALL_W			0x00001074		// ヘッド洗浄（All White）
#define		MN_HEAD_CLEAN_ALL_W_LVL		LVL_EVENT1
#define MN_HEAD_CLEAN_W1			0x00001075		// ヘッド洗浄（W1）
#define		MN_HEAD_CLEAN_W1_LVL		LVL_EVENT1
#define MN_HEAD_CLEAN_W2_4			0x00001076		// ヘッド洗浄（W234）
#define		MN_HEAD_CLEAN_W2_4_LVL		LVL_EVENT1

#define	MN_LOAD_WHITE_ALL			0x00001084		// ヘッド洗浄後のインク再導入（All White）
#define		MN_LOAD_WHITE_ALL_LVL		LVL_EVENT1
#define	MN_LOAD_WHITE_W1			0x00001085		// ヘッド洗浄後のインク再導入（W1）
#define		MN_LOAD_WHITE_W1_LVL		LVL_EVENT1
#define	MN_LOAD_WHITE_W2_4			0x00001086		// ヘッド洗浄後のインク再導入（W234）
#define		MN_LOAD_WHITE_W2_4_LVL		LVL_EVENT1

#define	MN_REFRESH_WHITE_ALL		0x00001094		// 白インク入れ替え（ノーマル）（All White）
#define		MN_REFRESH_WHITE_ALL_LVL	LVL_EVENT1
#define	MN_REFRESH_WHITE_W1			0x00001095		// 白インク入れ替え（ノーマル）（W1）
#define		MN_REFRESH_WHITE_W1_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE_W2_4		0x00001096		// 白インク入れ替え（ノーマル）（W234）
#define		MN_REFRESH_WHITE_W2_4_LVL	LVL_EVENT1

#define	MN_REFRESH_WHITE_PW_ALL		0x00001104		// 白インク入れ替え（パワフル）（All White）
#define		MN_REFRESH_WHITE_PW_ALL_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE__PW_W1		0x00001105		// 白インク入れ替え（パワフル）（W1）
#define		MN_REFRESH_WHITE__PW_W1_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE_PW_W2_4	0x00001106		// 白インク入れ替え（パワフル）（W234）
#define		MN_REFRESH_WHITE_PW_W2_4_LVL	LVL_EVENT1

///#define	MN_CIRCULATION_WHITE_ALL	0x00001114		// 白インク循環（All White）
///#define		MN_CIRCULATION_WHITE_ALL_LVL	LVL_EVENT1
///#define	MN_CIRCULATION_WHITE_W1		0x00001115		// 白インク循環（W1）
///#define		MN_CIRCULATION_WHITE_W1_LVL		LVL_EVENT1
///#define	MN_CIRCULATION_WHITE_W2_4	0x00001116		// 白インク循環（W234）
///#define		MN_CIRCULATION_WHITE_W2_4_LVL	LVL_EVENT1

#define	MN_PURGE_EXHAUST_ALL_CW		0x00001120		// 排気クリーニング実行（All Color & White）
#define		MN_PURGE_EXHAUST_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_ALL_C		0x00001121		// 排気クリーニング実行（All Color）
#define		MN_PURGE_EXHAUST_ALL_C_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_K			0x00001122		// 排気クリーニング実行（K）
#define		MN_PURGE_EXHAUST_K_LVL		LVL_EVENT1
#define	MN_PURGE_EXHAUST_M_C_Y		0x00001123		// 排気クリーニング実行（MCY）
#define		MN_PURGE_EXHAUST_M_C_Y_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_ALL_W		0x00001124		// 排気クリーニング実行（All White）
#define		MN_PURGE_EXHAUST_ALL_W_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_W1			0x00001125		// 排気クリーニング実行（W1）
#define		MN_PURGE_EXHAUST_W1_LVL		LVL_EVENT1
#define	MN_PURGE_EXHAUST_W2_4		0x00001126		// 排気クリーニング実行（W234）
#define		MN_PURGE_EXHAUST_W2_4_LVL	LVL_EVENT1

#define	MN_REPLACE_HEAD_CMYK			0x00001201		// ヘッド交換（Color）
#define		MN_REPLACE_HEAD_CMYK_LVL		LVL_EVENT1
#define	MN_REPLACE_HEAD_W				0x00001204		// ヘッド交換（White）
#define		MN_REPLACE_HEAD_W_LVL			LVL_EVENT1

#define	MN_REPLACE_HEAD_CMYK_CANCEL		0x00001211		// ヘッド交換キャンセル（Color）
#define		MN_REPLACE_HEAD_CMYK_CANCEL_LVL	LVL_EVENT1
#define	MN_REPLACE_HEAD_W_CANCEL		0x00001214		// ヘッド交換キャンセル（White）
#define		MN_REPLACE_HEAD_W_CANCEL_LVL	LVL_EVENT1

#define MN_REPLACE_HEAD_C_INK_LOAD		0x00001221		// ヘッド交換後のインク導入（Color）
#define 	MN_REPLACE_HEAD_C_INK_LOAD_LVL	LVL_EVENT1
#define MN_REPLACE_HEAD_W_INK_LOAD		0x00001224		// ヘッド交換後のインク導入（White）
#define 	MN_REPLACE_HEAD_W_INK_LOAD_LVL	LVL_EVENT1

#define	MN_TEST_PRINT				0x00001230		// テスト印刷
#define		MN_TEST_PRINT_LVL			LVL_EVENT1
#define	MN_SOLID_PRINT				0x00001231		// SOLID PRINT
#define		MN_SOLID_PRINT_LVL			LVL_EVENT1

#define	MN_CR_SPEED_ADJUST			0x00001240		// CR速度パラメータ調整
#define		MN_CR_SPEED_ADJUST_LVL		LVL_EVENT1
///#define	MN_CR_ORIGIN_ADJUST			0x00001241		// CR原点センサー調整
///#define		MN_CR_ORIGIN_ADJUST_LVL		LVL_EVENT1
///#define	MN_TEMP_SNSR_ADJUST			0x00001242		// 温度センサー補正
///#define		MN_TEMP_SNSR_ADJUST_LVL		LVL_EVENT1
#define MN_X_PRINT_ADJUST			0x00001243		// X方向印刷位置調整
#define		MN_X_PRINT_ADJUST_LVL		LVL_EVENT1
#define MN_Y_PRINT_ADJUST			0x00001244		// Y方向印刷位置調整
#define		MN_Y_PRINT_ADJUST_LVL		LVL_EVENT1

///#define	MNT_MNU_EXC_PARTS			0x00001250		// 定期メンテ部品の交換
///#define		MNT_MNU_EXC_PARTS_LVL		LVL_EVENT1
#define MNT_PART_CLEANING			0x00001254		// メンテ部品掃除交換
#define 	MNT_PART_CLEANING_LVL		LVL_EVENT1
#define MNT_PART_CLEANING_CANCEL	0x00001255		// メンテ部品掃除交換 キャンセル
#define 	MNT_PART_CLEANING_CANCEL_LVL		LVL_EVENT1

#define	MN_AR3_FILE_LOAD			0x00001260		// USBメモリからAR3ファイルロード
#define		MN_AR3_FILE_LOAD_LVL		LVL_EVENT1
#define	MN_LOG_SAVE_USB				0x00001261		// USBメモリへのログ書き出し
#define		MN_LOG_SAVE_USB_LVL			LVL_EVENT1
#define	MN_FIRM_UPDATE_USB			0x00001262		// USBメモリからファームウェア更新
#define		MN_FIRM_UPDATE_USB_LVL		LVL_EVENT1

#define	MN_FIRM_VER					0x00001270		// ファームウェアバージョン表示
#define		MN_FIRM_VER_LVL				LVL_EVENT2
///#define	MN_SHOW_PRT_NUM				0x00001271		// 累積印刷枚数表示
///#define		MN_SHOW_PRT_NUM_LVL			LVL_EVENT2
///#define	MN_SHOW_TEMPERATURE			0x00001272		// 温度/湿度情報の表示
///#define		MN_SHOW_TEMPERATURE_LVL		LVL_EVENT2
///#define	MN_SHOW_COM_SETTING			0x00001273		// 通信設定の確認
///#define		MN_SHOW_COM_SETTING_LVL		LVL_EVENT2

#define	MN_LANGUAGE_SET_ENG			0x00001280		// 表示言語を英語にセット
#define		MN_LANGUAGE_SET_ENG_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_SPA			0x00001281		// 表示言語をスペイン語にセット
#define		MN_LANGUAGE_SET_SPA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_FRA			0x00001282		// 表示言語をフランス語にセット
#define		MN_LANGUAGE_SET_FRA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_GER			0x00001283		// 表示言語をドイツ語にセット
#define		MN_LANGUAGE_SET_GER_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_ITA			0x00001284		// 表示言語をイタリア語にセット
#define		MN_LANGUAGE_SET_ITA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_JPN			0x00001285		// 表示言語を日本語にセット
#define		MN_LANGUAGE_SET_JPN_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_CHN			0x00001286		// 表示言語を中国語（簡体字）にセット
#define		MN_LANGUAGE_SET_CHN_LVL		LVL_EVENT1

#define	MN_SET_1WAY_AUTO			0x00001290		// 自動方向印刷モード設定
#define		MN_SET_1WAY_AUTO_LVL		LVL_EVENT1
#define	MN_SET_1WAY_OFF				0x00001291		// 双方向印刷モード設定
#define		MN_SET_1WAY_OFF_LVL			LVL_EVENT1
#define	MN_SET_1WAY_FORWARD			0x00001292		// 片方向印刷モード設定(Forward)
#define		MN_SET_1WAY_FORWARD_LVL		LVL_EVENT1
#define	MN_SET_1WAY_BACKWARD		0x00001293		// 片方向印刷モード設定(Backward)
#define		MN_SET_1WAY_BACKWARD_LVL	LVL_EVENT1

#define	MN_TEMPERATURE_SET_F		0x00001300		// 表示温度を華氏にセット
#define		MN_TEMPERATURE_SET_F_LVL	LVL_EVENT2
#define	MN_TEMPERATURE_SET_C		0x00001301		// 表示温度を摂氏にセット
#define		MN_TEMPERATURE_SET_C_LVL	LVL_EVENT2

#define	MN_341_MODE_OFF				0x00001310		// 白休止モード（341モード）をOFFにセット
#define		MN_341_MODE_OFF_LVL			LVL_EVENT1
#define	MN_341_MODE_ON				0x00001311		// 白休止モード（341モード）をONにセット
#define		MN_341_MODE_ON_LVL			LVL_EVENT1

#define	MN_JOB_DEL_MODE_OFF			0x00001321		// ジョブ削除モードをOFFにセット
#define		MN_JOB_DEL_MODE_OFF_LVL		LVL_EVENT1
#define	MN_JOB_DEL_MODE_ON			0x00001322		// ジョブ削除モードをON（自動削除）にセット
#define		MN_JOB_DEL_MODE_ON_LVL		LVL_EVENT1

#define	MN_SET_SPEAKER_VOL			0x00001330		// スピーカボリューム設定
#define		MN_SET_SPEAKER_VOL_LVL		LVL_EVENT2
///#define	MN_SET_LCD_CONTRAST			0x00001331		// LCDコントラスト設定
///#define		MN_SET_LCD_CONTRAST_LVL		LVL_EVENT2
#define	MN_SET_LOG_LEVEL			0x00001332		// ログレベル設定
#define		MN_SET_LOG_LEVEL_LVL		LVL_EVENT1
#define	MN_SET_SCREEN_TIMEOUT_NON	0x00001333		// 自動画面消去（自動消去しない）
#define		MN_SET_SCREEN_TIMEOUT_NON_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_5M	0x00001334		// 自動画面消去（５分）
#define		MN_SET_SCREEN_TIMEOUT_5M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_10M	0x00001335		// 自動画面消去（１０分）
#define		MN_SET_SCREEN_TIMEOUT_10M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_15M	0x00001336		// 自動画面消去（１５分）
#define		MN_SET_SCREEN_TIMEOUT_15M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_30M	0x00001337		// 自動画面消去（３０分）
#define		MN_SET_SCREEN_TIMEOUT_30M_LVL		LVL_EVENT2

#define	MN_SET_AUTO_CLN				0x00001340		// オートパージ間隔（枚数)設定
#define		MN_SET_AUTO_CLN_LVL			LVL_EVENT1
#define	MN_SET_FLUSH_CYCLE			0x00001341		// フラッシング間隔（頻度)設定
#define		MN_SET_FLUSH_CYCLE_LVL		LVL_EVENT1
#define	MN_SET_FLUSH_DROPS			0x00001342		// フラッシング吐出量設定
#define		MN_SET_FLUSH_DROPS_LVL		LVL_EVENT1
///#define	MN_SET_REFRESH_W			0x00001343		// 白インク入れ替え インク廃棄量設定
///#define		MN_SET_REFRESH_W_LVL		LVL_EVENT1
#define MN_SET_AUTO_PURGE_SET_BEFORE	0x00001344	// オートパージ開始時期（印刷前に実施）
#define 	MN_SET_AUTO_PURGE_SET_BEFORE_LVL	LVL_EVENT1
#define MN_SET_AUTO_PURGE_SET_AFTER		0x00001345	// オートパージ開始時期（印刷後に実施）
#define 	MN_SET_AUTO_PURGE_SET_AFTER_LVL		LVL_EVENT1

///#define	MN_PUMP_PRESS_CAP			0x00001350		// ポンプ負圧測定実行（キャップ上で測定）
///#define		MN_PUMP_PRESS_CAP_LVL		LVL_EVENT1
///#define	MN_PUMP_PRESS_CR			0x00001351		// ポンプ負圧測定実行（キャリッジ上で測定）
///#define		MN_PUMP_PRESS_CR_LVL		LVL_EVENT1

#define MN_MENU_TIMEOUT_SET_MIN		0x00001355		// メニュータイムアウト設定 １分
#define		MN_MENU_TIMEOUT_SET_MIN_LVL		LVL_EVENT1
#define MN_MENU_TIMEOUT_SET_MIDDLE	0x00001356		// メニュータイムアウト設定 ３分
#define		MN_MENU_TIMEOUT_SET_MIDDLE_LVL	LVL_EVENT1
#define MN_MENU_TIMEOUT_SET_MAX		0x00001357		// メニュータイムアウト設定 ５分
#define		MN_MENU_TIMEOUT_SET_MAX_LVL		LVL_EVENT1

#define MN_MENU_LOW_TEMP_PRINT_ENABLE	0x00001360	// 低温時の印刷動作設定　有効
#define		MN_MENU_LOW_TEMP_PRINT_ENABLE_LVL		LVL_EVENT1
#define MN_MENU_LOW_TEMP_PRINT_DISABLE	0x00001361	// 低温時の印刷動作設定　無効
#define		MN_MENU_LOW_TEMP_PRINT_DISABLE_LVL		LVL_EVENT1

///#define	MN_RESET_HEAD_FILTER_K		0x00001360		// Ｋのヘッドフィルター交換ワーニングのリセットを実行
///#define		MN_RESET_HEAD_FILTER_K_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_M		0x00001361		// Ｍのヘッドフィルター交換ワーニングのリセットを実行
///#define		MN_RESET_HEAD_FILTER_M_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_C		0x00001362		// Ｃのヘッドフィルター交換ワーニングのリセットを実行
///#define		MN_RESET_HEAD_FILTER_C_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_Y		0x00001363		// Ｙのヘッドフィルター交換ワーニングのリセットを実行
///#define		MN_RESET_HEAD_FILTER_Y_LVL	LVL_EVENT1

///#define MN_RESET_FANFILTER		0x00001365		// ファンフィルター交換時期
///#define 	MN_RESET_FANFILTER_LVL			LVL_EVENT1
///#define MN_RESET_ABSORBER		0x00001366		// フラッシング用吸収材交換時期
///#define 	MN_RESET_ABSORBER_LVL			LVL_EVENT1

#define	MN_RECEIVING_SETTING_OFF	0x00001370		// 印刷中受信・受信中印刷 無効
#define		MN_RECEIVING_SETTING_OFF_LVL		LVL_EVENT1
#define	MN_RECEIVING_SETTING_ON		0x00001371		// 印刷中受信・受信中印刷 有効
#define		MN_RECEIVING_SETTING_ON_LVL			LVL_EVENT1

#define MN_EXCHANGE_FILTER_K		0x0001380		// Ｋのフィルター交換
#define		MN_EXCHANGE_FILTER_K_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_Y		0x0001381		// Ｙのフィルター交換
#define		MN_EXCHANGE_FILTER_Y_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_C		0x0001382		// Ｃのフィルター交換
#define		MN_EXCHANGE_FILTER_C_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_M		0x0001383		// Ｍのフィルター交換
#define		MN_EXCHANGE_FILTER_M_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W1		0x0001384		// Ｗ１のフィルター交換
#define		MN_EXCHANGE_FILTER_W1_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W2		0x0001385		// Ｗ２のフィルター交換
#define		MN_EXCHANGE_FILTER_W2_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W3		0x0001386		// Ｗ３のフィルター交換
#define		MN_EXCHANGE_FILTER_W3_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W4		0x0001387		// Ｗ４のフィルター交換
#define		MN_EXCHANGE_FILTER_W4_LVL		LVL_EVENT1

#define MN_EXCHANGE_FILTER_CANCEL	0x0001388		// フィルター交換キャンセル
#define		MN_EXCHANGE_FILTER_CANCEL_LVL		LVL_EVENT1

#define MN_EXCHANGE_FILTER_K_LOAD_INK	0x0001390		// Ｋのフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_K_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_Y_LOAD_INK	0x0001391		// Ｙのフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_Y_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_C_LOAD_INK	0x0001392		// Ｃのフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_C_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_M_LOAD_INK	0x0001393		// Ｍのフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_M_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W1_LOAD_INK	0x0001394		// Ｗ１のフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_W1_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W2_LOAD_INK	0x0001395		// Ｗ２のフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_W2_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W3_LOAD_INK	0x0001396		// Ｗ３のフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_W3_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W4_LOAD_INK	0x0001397		// Ｗ４のフィルター交換後のインク再導入
#define		MN_EXCHANGE_FILTER_W4_LOAD_INK_LVL	LVL_EVENT1

//　以下GT-X のメニュー項目の新規追加部分
#define	MN_RECEIVE_HISTORY			0x00001400		// 受信履歴
#define		MN_RECEIVE_HISTORY_LVL				LVL_EVENT1


#define	MN_MAITE_UNIT_CLEANING		0x00001450		// メンテ洗浄
#define		MN_MAITE_UNIT_CLEANING_LVL			LVL_EVENT1
#define MN_IP_ADDRESS_ASSIGN		0x00001460		// IP アドレス設定
#define		MN_IP_ADDRESS_ASSIGN_LVL			LVL_EVENT1
#define	MN_BACKLIGHT				0x00001471		// バックライト調整
#define		MN_BACKLIGHT_LVL					LVL_EVENT1

#define	MN_RESTORE_DATA_SET			0x00001480		// リストア実行
#define		MN_RESTORE_DATA_SET_LVL				LVL_EVENT1

#define	MN_WIPER_CLEANER_REPLACE_C	0x00001500		// ワイパークリーナー交換　カラー
#define		MN_WIPER_CLEANER_REPLACE_C_LVL	LVL_EVENT1
#define	MN_WIPER_CLEANER_REPLACE_W	0x00001501		// ワイパークリーナー交換　白
#define		MN_WIPER_CLEANER_REPLACE_W_LVL	LVL_EVENT1
///#define	MN_WIPER_BLADE_REPLACE_C	0x00001510		// ワイパー交換　カラー
///#define		MN_WIPER_BLADE_REPLACE_C_LVL	LVL_EVENT1
///#define	MN_WIPER_BLADE_REPLACE_W	0x00001511		// ワイパー交換　白
///#define		MN_WIPER_BLADE_REPLACE_W_LVL	LVL_EVENT1
#define	MN_FLUSHING_FROM_C_RESET	0x00001520		// フラッシングフォームリセット カラー
#define		MNFLUSHING_FROM_C_RESET_LVL		LVL_EVENT1
#define	MN_FLUSHING_FROM_W_RESET	0x00001521		// フラッシングフォームリセット 白
#define		MNFLUSHING_FROM_W_RESET_LVL		LVL_EVENT1
#define MNT_CLEAN_CAPWIPE			0x00001530		// キャップ／ワイパー掃除
#define		MNT_CLEAN_CAPWIPE_LVL			LVL_EVENT1
#define MNT_CLEAN_NOZZLE			0x00001540		// ノズル側面掃除
#define		MNT_CLEAN_NOZZLE_LVL			LVL_EVENT1
#define	MN_FAN_FILTER_RESET			0x00001550		// ファンフィルターリセット
#define		MN_FAN_FILTER_RESET_LVL			LVL_EVENT1
///#define MNT_CLEAN_CR_STRIP		0x00001560		// エンコーダーストリップ掃除
///#define		MNT_CLEAN_CR_STRIP_LVL		LVL_EVENT1

//		2.1.2.4 PCコマンド
#define	PC_PRT_JOB_START			0x00002000		// プリントジョブ受信開始
#define		PC_PRT_JOB_START_LVL		LVL_EVENT2
#define	PC_PRT_JOB_END				0x00002001		// プリントジョブ受信完了
#define		PC_PRT_JOB_END_LVL			LVL_EVENT2
#define	PC_PRT_JOB_CANCEL			0x00002002		// プリントジョブキャンセル終了
#define		PC_PRT_JOB_CANCEL_LVL		LVL_EVENT1
#define	PC_PRT_JOB_ERROR			0x00002003		// プリントジョブエラー終了
#define		PC_PRT_JOB_ERROR_LVL		LVL_EVENT1
#define	PC_PRT_JOB_DELETE			0x00002004		// プリントジョブ削除要求受信
#define		PC_PRT_JOB_DELETE_LVL		LVL_EVENT1

#define	PC_UPDATE_FIRM_PPC			0x00002010		// 更新用PPCファームウェア受信
#define		PC_UPDATE_FIRM_PPC_LVL		LVL_EVENT1
#define	PC_UPDATE_FIRM_MNT			0x00002011		// 更新用メンテファームウェア受信
#define		PC_UPDATE_FIRM_MNT_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_FONT			0x00002012		// 更新用フォントデータ受信
#define		PC_UPDATE_DATA_FONT_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_MES			0x00002013		// 更新用文字列データ受信
#define		PC_UPDATE_DATA_MES_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_PRINT		0x00002014		// 更新用テスト印刷データ受信
#define		PC_UPDATE_DATA_PRINT_LVL	LVL_EVENT1
#define	PC_UPDATE_FIRM_HEAD_SAFFRON		0x00002015		// 更新用ヘッド制御サフランファームウェア受信
#define		PC_UPDATE_FIRM_HEAD_SAFFRON_LVL	LVL_EVENT1
#define	PC_UPDATE_FIRM_LCD_SAFFRON		0x00002016		// 更新用LCD制御サフランファームウェア受信
#define		PC_UPDATE_FIRM_LCD_SAFFRON_LVL	LVL_EVENT1

#define	PC_EPPROM_WRITE				0x00002020		// PCコマンドによるEEPROMブロック更新
#define		PC_EPPROM_WRITE_LVL			LVL_EVENT1

#define	PC_CLOCK_SET				0x00002030		// PCコマンドによるリアルタイムクロック日時設定
#define		PC_CLOCK_SET_LVL			LVL_EVENT1

#define	PC_SND_LOG					0x00002040		// PCへログデータを送信
#define		PC_SND_LOG_LVL				LVL_EVENT2
#define	PC_SND_EPPROM				0x00002041		// PCへEEPROMブロックデータを送信
#define		PC_SND_EPPROM_LVL			LVL_EVENT2
#define	PC_SND_EPPROM_LIST			0x00002042		// PCへEEPROMブロックリストを送信
#define		PC_SND_EPPROM_LIST_LVL		LVL_EVENT2

#define	PC_INIT_STATISTICS			0x00002050		// PCコマンドによる稼働状況初期化
#define		PC_INIT_STATISTICS_LVL		LVL_EVENT1

#define	PC_BY4_ADJUST				0x00002060		// PCコマンドによる吐出タイミング調整
#define		PC_BY4_ADJUST_LVL			LVL_EVENT1
#define	PC_CR_SPEED_ADJUST			0x00002061		// PCコマンドによるCRスピード調整
#define		PC_CR_SPEED_ADJUST_LVL		LVL_EVENT1
#define	PC_CR_TEMP_ADJUST			0x00002062		// PCコマンドによる環境温度センサー調整
#define		PC_CR_TEMP_ADJUST_LVL		LVL_EVENT1
#define	PC_CW_POS_ADJUST			0x00002063		// PCコマンドによる白カラー位置合わせ
#define		PC_CW_POS_ADJUST_LVL		LVL_EVENT1
#define	PC_ORIGIN_ADJUST			0x00002064		// PCコマンドによる原点位置調整
#define		PC_ORIGIN_ADJUST_LVL		LVL_EVENT1
#define	PC_IPADDR_SET				0x00002065		// PCコマンドによるIPaddress設定
#define		PC_IPADDR_SET_LVL			LVL_EVENT1
#define	PC_SET_HEAD_RANK			0x00002066		// PCコマンドによるヘッドランク設定
#define		PC_SET_HEAD_RANK_LVL		LVL_EVENT1
#define	PC_SET_PRODUCT_STATUS		0x00002067		// PCコマンドによる組み立て中フラグの変更
#define		PC_SET_PRODUCT_STATUS_LVL	LVL_EVENT1
#define	PC_SET_WHITE_OFF			0x00002068		// PCコマンドによる白休止モードの変更
#define		PC_SET_WHITE_OFF_LVL		LVL_EVENT1
#define	PC_SET_INITIAL_PUEGE_DONE	0x00002069		// PCコマンドによる初期導入モードの変更
#define		PC_SET_INITIAL_PUEGE_DONE_LVL	LVL_EVENT1


///#define	PC_PRINT_DATA_DELETE		0x00002070		// 受信済み印刷データの消去
///#define		PC_PRINT_DATA_DELETE_LVL	LVL_EVENT1

#define	PC_WRITE_18_CODES			0x00002071		// PCコマンドによる18桁コードの書き込み
#define		PC_WRITE_18_CODES_LVL		LVL_EVENT1
#define	PC_WRITE_SERIAL_NUM			0x00002072		// PCコマンドによるシリアルナンバーの書き込み
#define		PC_WRITE_SERIAL_NUM_LVL		LVL_EVENT1
#define	PC_WRITE_MAC_ACCRESS		0x00002073		// PCコマンドによるMACアドレスの書き込み
#define		PC_WRITE_MAC_ACCRESS_LVL	LVL_EVENT1

#define	PC_CR_FWD_RVS_ADJUST			0x00002080		// PCコマンドによるCRの往復印刷の位置合わせ
#define		PC_CR_FWD_RVS_ADJUST_LVL		LVL_EVENT1
#define	PC_BELT_HEAD_ADJUST			0x00002090		// PCコマンドによるベルトピッチ・ヘッド長補正
#define		PC_BELT_HEAD_ADJUST_LVL		LVL_EVENT1
/*-------------------------------------------------------*/
//	2.2 ステータスログ(bit15-12:0001)
//		2.2.1 インクカートリッジの状態
///#define STS_INK_CARTRIDGE			0x00003000		// インク残量センサの現在値
///#define		STS_INK_CARTRIDGE_LVL		LVL_EVENT1

//		2.2.2 廃インクタンクの状態

//		2.2.3 ワイパークリーナの状態

//		2.2.4 カバーセンサの状態

//		2.2.5 プラテン種別センサの状態

//		2.2.6 プラテン位置センサの状態

//		2.2.7 クリアランスセンサの状態

//		2.2.8 キャリッジの状態

//		2.2.9 温度センサの状態
///#define	STS_SUR_TEMP				0x00003800	// 印字保証温度
///#define		STS_SUR_TEMP_LVL			LVL_EVENT1
											//	付加情報サイズ：内容は SH-BY通信コマンド
///#define		STS_SUR_TEMP_ADDSZ			4	//	                0x8005(印刷終了)のt1,stと同じ

//		2.2.10 プログラム実行の状態

//		2.2.11 リアルタイムクロックの状態
///#define	STS_RTC_STOP				0x00004000	// RTC制御レジスタの発振停止ビットが立っていた
///#define		STS_RTC_STOP_LVL			LVL_EVENT1


/*-------------------------------------------------------*/
//	2.3 メンテナンスログ(bit15-12:0010)
//		2.3.1 メニューからのメンテナンス
//			2.3.1.1 メニューでの設定

//			2.3.1.2 メニューでの交換
//				2.3.1.2.1 ヘッド交換
//				2.3.1.2.2 ワイパブレード交換
//				2.3.1.2.3 ワイパークリーニングカセット交換

//			2.3.1.3 メニューでの検査
//				2.3.1.3.1 ソレノイド検査
//				2.3.1.3.2 ヘッド検査
//				2.3.1.3.3 メンテナンスユニット検査
//				2.3.1.3.4 プラテン検査

//			2.3.1.4 メニューでの情報取得

//			2.3.1.5 メニューでのプログラム更新

//			2.3.1.6 メニューでの掃除


//		2.3.2 パネルボタンによる操作
//			2.3.1.1 単機能ボタン


//		2.3.3 パラメータ更新
#define	MNT_PARM_B11				0x00006000	// EEPROM Block 11 
#define		MNT_PARM_B11_LVL			LVL_EVENT2
#define	MNT_PARM_B12				0x00006001	// EEPROM Block 12
#define		MNT_PARM_B12_LVL			LVL_EVENT2
#define	MNT_PARM_B13				0x00006002	// EEPROM Block 13
#define		MNT_PARM_B13_LVL			LVL_EVENT2
#define	MNT_PARM_B14				0x00006003	// EEPROM Block 14
#define		MNT_PARM_B14_LVL			LVL_EVENT2
#define	MNT_PARM_B15				0x00006004	// EEPROM Block 15
#define		MNT_PARM_B15_LVL			LVL_EVENT2
#define	MNT_PARM_B16				0x00006005	// EEPROM Block 16
#define		MNT_PARM_B16_LVL			LVL_EVENT2
#define	MNT_PARM_B17				0x00006006	// EEPROM Block 17
#define		MNT_PARM_B17_LVL			LVL_EVENT2

/*-------------------------------------------------------*/
//	2.4 インフォメーション(bit15-12:0011)
//		2.4.1 システムインフォメーション
//
#define	INF_PARM_INIT_B11			0x00007000	// EEPROM Block 11 を初期化した
#define		INF_PARM_INIT_B11_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B12			0x00007001	// EEPROM Block 12 を初期化した
#define		INF_PARM_INIT_B12_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B13			0x00007002	// EEPROM Block 13を初期化した
#define		INF_PARM_INIT_B13_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B14			0x00007003	// EEPROM Block 14 を初期化した
#define		INF_PARM_INIT_B14_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B15			0x00007004	// EEPROM Block 15 を初期化した
#define		INF_PARM_INIT_B15_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B16			0x00007005	// EEPROM Block 16 を初期化した
#define		INF_PARM_INIT_B16_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B17			0x00007006	// EEPROM Block 17 を初期化した
#define		INF_PARM_INIT_B17_LVL		LVL_EVENT1

///#define INF_FROM_LG_SAVE			0x00007105	// フラッシュロムにログ保存した
///#define		INF_FROM_LG_SAVE_LVL		LVL_EVENT1
#define INF_LOG_LOST				0x00007107	// ログバッファ終端に達した
#define		INF_LOG_LOST_LVL			LVL_EVENT1
///#define	INF_DBG_COMMENT				0x00007109
///#define		INF_DBG_COMMENT_LVL			LVL_INFO


//======================================================//
//	解析用稼動ログ										//
//======================================================//

//--------------------------------------//
//	印刷データロード完了（I/F側のみ）			//	// ロード完了したARPデータの諸情報
//--------------------------------------//	// 9000～90XXのログが全てほぼ連続して記録される
///#define	ARP_LOADED_JOB_ID			0x00009000			// ログ連番、ジョブID、（Ver,Source,CMYK,WxN）、（Block,Platen,印刷中受信,*）
///#define		ARP_LOADED_JOB_ID_LVL		LVL_EVENT1
///#define	ARP_LOADED_PRT_NUM			0x00009001			// ログ連番、印刷指示枚数
///#define		ARP_LOADED_PRT_NUM_LVL		LVL_EVENT1
///#define	ARP_LOADED_SPECIAL			0x00009002			// ログ連番、特殊印刷指定
///#define		ARP_LOADED_SPECIAL_LVL		LVL_EVENT1
///#define	ARP_LOADED_PLATEN			0x00009003			// ログ連番、プラテン名
///#define		ARP_LOADED_PLATEN_LVL		LVL_EVENT1
///#define	ARP_LOADED_DOT_CMYK			0x00009004			// ログ連番、インク総量値K、インク総量値M、インク総量値C、インク総量値Y
///#define		ARP_LOADED_DOT_CMYK_LVL		LVL_EVENT1
///#define	ARP_LOADED_DOT_WWWW			0x00009005			// ログ連番、インク総量値W1、インク総量値W2、インク総量値W3、インク総量値W4
///#define		ARP_LOADED_DOT_WWWW_LVL		LVL_EVENT1
///#define	ARP_LOADED_DRV_SET			0x00009006			// ログ連番、ドライバ設定状況
///#define		ARP_LOADED_DRV_SET_LVL		LVL_EVENT1
///#define	ARP_LOADED_GRAPHIC_BLK		0x00009007			// ログ連番、（ブロック番号,CMYK版,W版,Interlace）、（Repeat,Compress,Course,*）、（2xResolveH,2xResolveV）、（PileUp,WaitFlg,WaitSec,*）
///#define		ARP_LOADED_GRAPHIC_BLK_LVL	LVL_EVENT1
#define	ARP_LOADED_JOB_NAME			0x00009008			// ログ連番、ジョブネーム
#define		ARP_LOADED_JOB_NAME_LVL		LVL_EVENT1
#define	ARP_LOADED_JOB_COMMENT		0x00009009			// ログ連番、ジョブコメント
#define		ARP_LOADED_JOB_COMMENT_LVL	LVL_EVENT1
///#define	ARP_LOADED_FILE_NAME		0x00009010			// ログ連番、AR3ファイル名
///#define		ARP_LOADED_FILE_NAME_LVL	LVL_EVENT2

// ログエリアの削減用にGT-X用に新設
#define	ARP_LOADED_JOB_ALL			0x00009011			// 0x9000～0x9006までを1つにまとめたログ
#define		ARP_LOADED_JOB_ALL_LVL			LVL_EVENT1
#define	ARP_LOADED_GRAPHIC_BLK_ALL	0x00009012			// グラフィックブロック情報(0x9007)を1つにまとめたログ
#define		ARP_LOADED_GRAPHIC_BLK_ALL_LVL	LVL_EVENT1
								//  0x00009013～0x00009099 System Reserved

//--------------------------------------//
//	ユーザーの印刷操作						//
//--------------------------------------//
#define	USER_PRINT_START			0x00009100	// 印刷開始		ログ連番、ジョブID、（受信中印刷,*,*,*）
#define		USER_PRINT_START_LVL		LVL_EVENT1
#define	USER_PRINT_FINISH			0x00009101	// 印刷完了		ログ連番、ジョブID、環境温度、湿度、カラーヘッド VTEMP、カラーヘッド サーミスタ、ホワイトヘッド VTEMP、ホワイトヘッド サーミスタ、印刷時CR最高速度、印刷時CR最低速度、吐出カウント[8色x大中小ドット]
#define		USER_PRINT_FINISH_LVL		LVL_EVENT1
#define	USER_PRINT_STOP				0x00009102	// 印刷中止（cancel, obstacle error）		上と同じ
#define		USER_PRINT_STOP_LVL			LVL_EVENT1

//--------------------------------------//
//	メンテナンスシーケンス実行					//
//--------------------------------------//
#define	MNT_SEQUENCE_START			0x00009200	// メンテナンスシーケンス開始	シーケンス種別、対象色、開始条件
#define		MNT_SEQUENCE_START_LVL		LVL_EVENT1
#define	MNT_SEQUENCE_END			0x00009201	// メンテナンスシーケンス終了	シーケンス種別、対象色、終了理由
#define		MNT_SEQUENCE_END_LVL		LVL_EVENT1


// 個別情報は定義しない


/*-------------------------------------------------------*/
//	2.5 エラーログ
/*-------------------------------------------------------*/
//		2.5.1 操作ミス(bit15-12:0000)
/*-------------------------------------------------------*/
//		2.5.2 運用ヲーニング(bit15-12:0001)
//			2.5.2.1 インク量

#define WRN_WASH_BOTTLE_EMPTY			0x00001000	//	洗浄ボトルエンプティ(ワーニング)
#define 		WRN_WASH_BOTTLE_EMPTY_LVL	LVL_WARNING
#define ERR_WASH_BOTTLE_EMPTY			0x00001001	//	洗浄ボトルエンプティ(エラー)
#define 		ERR_WASH_BOTTLE_EMPTY_LVL	LVL_MIDDLE

///#define WRN_INK_FEW_K				0x00001000	// インクニアエンプティ ブラック
///#define		WRN_INK_FEW_K_LVL			LVL_WARNING
///#define WRN_INK_FEW_M				0x00001001	// インクニアエンプティ マゼンタ
///#define		WRN_INK_FEW_M_LVL			LVL_WARNING
///#define WRN_INK_FEW_C				0x00001002	// インクニアエンプティ シアン
///#define		WRN_INK_FEW_C_LVL			LVL_WARNING
///#define WRN_INK_FEW_Y				0x00001003	// インクニアエンプティ イエロー
///#define		WRN_INK_FEW_Y_LVL			LVL_WARNING
///#define WRN_INK_FEW_W1				0x00001004	// インクニアエンプティ  ホワイト１
///#define		WRN_INK_FEW_W1_LVL			LVL_WARNING
///#define WRN_INK_FEW_W2				0x00001005	// インクニアエンプティ  ホワイト２
///#define		WRN_INK_FEW_W2_LVL			LVL_WARNING
///#define WRN_INK_FEW_W3				0x00001006	// インクニアエンプティ  ホワイト３
///#define		WRN_INK_FEW_W3_LVL			LVL_WARNING
///#define WRN_INK_FEW_W4				0x00001007	// インクニアエンプティ  ホワイト４
///#define		WRN_INK_FEW_W4_LVL			LVL_WARNING

//			2.5.2.3 ワイパ
//#define	WRN_WIPER_CLN				0x00001020	// ワイパクリーナ使用回数超  ***************　表示されない
//#define		WRN_WIPER_CLN_LVL			LVL_WARNING
//#define	WRN_WIPER_BLD				0x00001021	// ワイパブレード使用回数超  　　************** 使われてない
//#define		WRN_WIPER_BLD_LVL			LVL_WARNING

//			2.5.2.4 ヘッド温度
#define	WRN_HEAD_TEMP_C				0x00001030	// カラーヘッド 注意温度
#define		WRN_HEAD_TEMP_C_LVL			LVL_WARNING
#define	WRN_HEAD_TEMP_W				0x00001031	// ホワイトヘッド注意温度
#define		WRN_HEAD_TEMP_W_LVL			LVL_WARNING

#define	WRN_CRG_MTR_LIFE			0x00001051	// キャリッジモータの寿命
#define		WRN_CRG_MTR_LIFE_LVL		LVL_WARNING

//			2.5.2.7 環境温度センサの状態
#define	WRN_SUR_TEMP_LOW			0x00001060	// 印字保証温度未満（ワーニング）
#define		WRN_SUR_TEMP_LOW_LVL		LVL_WARNING
#define	WRN_SUR_TEMP_HIGH			0x00001061	// 印字保証温度以上（ワーニング）
#define		WRN_SUR_TEMP_HIGH_LVL		LVL_WARNING

#define	WRN_SUR_HUMI_LOW			0x00001064	// 印字保証湿度未満（ワーニング）
#define		WRN_SUR_HUMI_LOW_LVL		LVL_WARNING
#define	WRN_SUR_HUMI_HIGH			0x00001065	// 印字保証湿度以上（ワーニング）
#define		WRN_SUR_HUMI_HIGH_LVL		LVL_WARNING

//			2.5.2.8 バッテリーの状態
#define	WRN_BATTERY_LIFE			0x00001070	//バッテリー寿命（リチウム電池寿命）　ログなし
#define		WRN_BATTERY_LIFE_LVL		LVL_WARNING

//			2.5.2.9 クロックの状態
#define	WRN_RTC_NO_SET				0x00001080	//時計がセットされていない　ログなし
#define		WRN_RTC_NO_SET_LVL			LVL_WARNING

#define ERR_RTC_NO_SET				0x00001085	//時計がセットされていない(WaitOk)　ログなし
#define		ERR_RTC_NO_SETLVL			LVL_WARNING

//			2.5.2.10 キャップ/ワイパーの状態
#define	WRN_CAP_WIPER_CLEAN				0x00001090	//キャップ/ワイパーの清掃が必要な状態（ワーニング）
#define		WRN_CAP_WIPER_CLEAN_LVL			LVL_WARNING
#define ERR_CAP_WIPER_CLEAN				0x00001091	//キャップ/ワイパーの清掃が必要な状態（エラー）
#define 	ERR_CAP_WIPER_CLEAN_LVL			LVL_MIDDLE

#define WRN_WIPER_CLEANER_LIFE_WHITE	0x00001092	//ワイパークリーナー寿命　白（ワーニング）
#define 	WRN_WIPER_CLEANER_LIFE_WHITE_LVL	LVL_WARNING
#define ERR_WIPER_CLEANER_LIFE_WHITE	0x00001093	//ワイパークリーナー寿命 白（エラー）
#define 	ERR_WIPER_CLEANER_LIFE_WHITE_LVL	LVL_MIDDLE

#define WRN_WIPER_CLEANER_LIFE_COLOR	0x00001095	//ワイパークリーナー寿命　カラー（ワーニング）
#define 	WRN_WIPER_CLEANER_LIFE_COLOR_LVL	LVL_WARNING
#define ERR_WIPER_CLEANER_LIFE_COLOR	0x00001096	//ワイパークリーナー寿命 カラー（エラー）
#define 	ERR_WIPER_CLEANER_LIFE_COLOR_LVL	LVL_MIDDLE

#define	WRN_PUMP_TUBE_LIFE				0x00001100	// メンテのポンプチューブが交換時期（寿命切れ）
#define		WRN_PUMP_TUBE_LIFE_LVL			LVL_MIDDLE

//			2.5.2.11 白インクチューブの状態

//			白ヘッド洗浄
#define ERR_W_HEAD_CLEAN_EXEC			0x00001125	// 白ヘッド洗浄中エラー
#define 	ERR_W_HEAD_CLEAN_EXEC_LVL			LVL_MIDDLE

//			2.5.2.12 定期メンテナンス
#define	ERR_WHITTE_STIRRING				0x00001202	// 白インク撹拌（エラー）
#define		ERR_WHITTE_STIRRING_LVL			LVL_MIDDLE

//			2.5.2.13 ミスト対策ファンのロック検知
#define	WRN_MIST_FAN_LOCKED				0x00001210	// ミスト対策ファンのロック検知
#define		WRN_MIST_FAN_LOCKED_LVL			LVL_WARNING

//			2.5.2.14 ヘッドフィルター交換
#define ERR_EXCHANGE_FILTER				0x00001401	// フィルター交換後のエラー（WaitOk2エラー）
#define		ERR_EXCHANGE_FILTER_LVL			LVL_MIDDLE

//			2.5.2.15 ファンフィルター交換
#define WRN_EXG_FANFILTER				0x00001501	// ファンフィルター交換時期(ワーニング)
#define 	WRN_EXG_FANFILTER_LVL			LVL_WARNING

//			2.5.2.16 フラッシングフォーム交換時期
#define WRN_EXG_ABSORBER_W				0x00001601	// フラッシングフォーム交換 白(ワーニング)
#define 	WRN_EXG_ABSORBER_W_LVL			LVL_WARNING
#define ERR_EXG_ABSORBER_W				0x00001602	// フラッシングフォーム交換 白(エラー)
#define 	ERR_EXG_ABSORBER_W_LVL			LVL_MIDDLE

#define WRN_EXG_ABSORBER_C				0x00001605	// フラッシングフォーム交換 カラー(ワーニング)
#define 	WRN_EXG_ABSORBER_C_LVL			LVL_WARNING
#define ERR_EXG_ABSORBER_C				0x00001606	// フラッシングフォーム交換 カラー(エラー)
#define 	ERR_EXG_ABSORBER_C_LVL			LVL_MIDDLE

//			ノズル側面の掃除時期
#define WRN_EXG_NOZZLE_TIME				0x00001700	// ノズル側面（ノズルガード）の掃除時期（ワーニング）
#define 	WRN_EXG_NOZZLE_TIME_LVL			LVL_WARNING
#define ERR_EXG_NOZZLE_TIME				0x00001701	// ノズル側面（ノズルガード）の掃除時期（エラー）
#define 	ERR_EXG_NOZZLE_TIME_LVL			LVL_MIDDLE

//			ヘッド交換中エラー
#define ERR_EXG_HEAD_EXEC				0x00001801	//	ヘッド交換中エラー
#define 	ERR_EXG_HEAD_EXEC_LVL			LVL_MIDDLE

//			初期インク導入要求エラー
#define ERR_INK_LOAD_EXECUTION			0x00001901	//　初期インク導入が必要
#define 	ERR_INK_LOAD_EXECUTION_LVL		LVL_MIDDLE

//			白インク休止キャンセルエラー
#define ERR_WHITE_INK_MODE_CANCEL		0x00001905	//　白インク休止を最後まで実行されていない
#define 	ERR_WHITE_INK_MODE_CANCEL_LVL	LVL_MIDDLE

/*-------------------------------------------------------*/
//		運用エラー
//			カートリッジ無し
#define ERR_NO_CTRG_K				0x00002000	// カートリッジ取り外し ブラック　ログなし
#define		ERR_NO_CTRG_K_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_M				0x00002001	// カートリッジ取り外し マゼンタ　ログなし
#define		ERR_NO_CTRG_M_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_C				0x00002002	// カートリッジ取り外し シアン　ログなし
#define		ERR_NO_CTRG_C_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_Y				0x00002003	// カートリッジ取り外し イエロー　ログなし
#define		ERR_NO_CTRG_Y_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_W1				0x00002004	// カートリッジ取り外し  ホワイト１２　ログなし
#define		ERR_NO_CTRG_W1_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_W2				0x00002005	// カートリッジ取り外し  ホワイト３４　ログなし
#define		ERR_NO_CTRG_W2_LVL			LVL_MIDDLE

//			インク残量
#define ERR_INK_EMP_K				0x00002020	// インク空 ブラック　ログなし
#define		ERR_INK_EMP_K_LVL			LVL_MIDDLE
#define ERR_INK_EMP_M				0x00002021	// インク空 マゼンタ　ログなし
#define		ERR_INK_EMP_M_LVL			LVL_MIDDLE
#define ERR_INK_EMP_C				0x00002022	// インク空 シアン　ログなし
#define		ERR_INK_EMP_C_LVL			LVL_MIDDLE
#define ERR_INK_EMP_Y				0x00002023	// インク空 イエロー　ログなし
#define		ERR_INK_EMP_Y_LVL			LVL_MIDDLE
#define ERR_INK_EMP_W1				0x00002024	// インク空 ホワイト１２　ログなし
#define		ERR_INK_EMP_W1_LVL			LVL_MIDDLE
#define ERR_INK_EMP_W2				0x00002025	// インク空 ホワイト３４　ログなし
#define		ERR_INK_EMP_W2_LVL			LVL_MIDDLE

// 			ICチップ異常
#define ERR_IC_CHIP_K				0x00002030	// ICチップ異常 ブラック
#define		ERR_IC_CHIP_K_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_M				0x00002031	// ICチップ異常 マゼンタ
#define		ERR_IC_CHIP_M_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_C				0x00002032	// ICチップ異常 シアン
#define		ERR_IC_CHIP_C_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_Y				0x00002033	// ICチップ異常 イエロー
#define		ERR_IC_CHIP_Y_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_W1				0x00002034	// ICチップ異常 ホワイト１２
#define		ERR_IC_CHIP_W1_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_W2				0x00002035	// ICチップ異常 ホワイト３４
#define		ERR_IC_CHIP_W2_LVL			LVL_MIDDLE

#define ERR_IC_CHIP_MAIN_C			0x00002036	// ICチップ異常 メイン基板カラー
#define		ERR_IC_CHIP_MAIN_C_LVL		LVL_FATAL
#define ERR_IC_CHIP_MAIN_W			0x00002037	// ICチップ異常 メイン基板ホワイト
#define		ERR_IC_CHIP_MAIN_W_LVL		LVL_FATAL


//			2.5.3.3 ワイパクリーナ
#define	ERR_WIPER_CLN1				0x00002041	// カラー側ワイパクリーナカセット1抜け
#define		ERR_WIPER_CLN1_LVL			LVL_FATAL
#define	ERR_WIPER_CLN2				0x00002042	// 白側ワイパクリーナカセット2抜け
#define		ERR_WIPER_CLN2_LVL			LVL_FATAL

#define	ERR_SUR_TEMP_LOW			0x00002050	// 動作温度未満
#define		ERR_SUR_TEMP_LOW_LVL		LVL_MIDDLE
#define	ERR_SUR_TEMP_HIGH			0x00002051	// 動作温度異常
#define		ERR_SUR_TEMP_HIGH_LVL		LVL_MIDDLE

#define	ERR_PLTN_UNLOAD				0x00002062	// アンロードで原点まで戻らず動作終わる（脱調？） ログのみ
#define		ERR_PLTN_UNLOAD_LVL			LVL_MIDDLE
#define	ERR_PLTN_LOAD				0x00002063	// ロード時に脱調した可能性あり(または原点外で手で手前に動かした)　ログのみ
#define		ERR_PLTN_LOAD_LVL			LVL_MIDDLE
#define	ERR_CLRNS_SNSR				0x00002070	// 障害物検知
#define		ERR_CLRNS_SNSR_LVL			LVL_MIDDLE

//			パウチ巻取り不良
#define ESBT_POUCH_TAKE_UP_K_ERR		0x00002080	// パウチ巻取り不良 ブラック
#define ESBT_POUCH_TAKE_UP_K_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_M_ERR		0x00002081	// パウチ巻取り不良 マゼンタ
#define ESBT_POUCH_TAKE_UP_M_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_C_ERR		0x00002082	// パウチ巻取り不良 シアン
#define ESBT_POUCH_TAKE_UP_C_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_Y_ERR		0x00002083	// パウチ巻取り不良 イエロー
#define ESBT_POUCH_TAKE_UP_Y_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_W12_ERR		0x00002084	// パウチ巻取り不良 ホワイト１２
#define ESBT_POUCH_TAKE_UP_W12_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_W34_ERR		0x00002085	// パウチ巻取り不良 ホワイト３４
#define ESBT_POUCH_TAKE_UP_W34_ERR_LVL		LVL_MIDDLE


//			ICチップ残量超過
#define ERR_IC_INK_EXCESS_K				0x00002090	// ICチップ残量超過 ブラック
#define		ERR_IC_INK_EXCESS_K_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_M				0x00002091	// ICチップ残量超過 マゼンタ
#define		ERR_IC_INK_EXCESS_M_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_C				0x00002092	// ICチップ残量超過 シアン
#define		ERR_IC_INK_EXCESS_C_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_Y				0x00002093	// ICチップ残量超過 イエロー
#define		ERR_IC_INK_EXCESS_Y_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_W1			0x00002094	// ICチップ残量超過 ホワイト１２
#define		ERR_IC_INK_EXCESS_W1_LVL		LVL_MIDDLE
#define ERR_IC_INK_EXCESS_W2			0x00002095	// ICチップ残量超過 ホワイト３４
#define		ERR_IC_INK_EXCESS_W2_LVL		LVL_MIDDLE

//			2.5.3.10 USBメモリ
#define	ERR_NO_CFCARD				0x00002100	// USBメモリなし　ログなし
#define		ERR_NO_CFCARD_LVL			LVL_MIDDLE
#define	ERR_NOAREA_CFCARD			0x00002101	// USBメモリ空きなし
#define		ERR_NOAREA_CFCARD_LVL		LVL_MIDDLE
#define	ERR_NOT_RUN_BULK_SERV		0x00002102	// tUsbBulkXbdService起動せず　ログのみ
#define		ERR_NOT_RUN_BULK_SERV_LVL	LVL_MIDDLE

//#define	ERR_CF_IN_USB_RECEIVING		0x00002104	// USB受信中にCFカードからデータを読み込もうとした　　************** 使われてない
//#define		ERR_CF_IN_USB_RECEIVING_LVL	LVL_MIDDLE

#define	ERR_NO_VALID_FILE			0x00002105	// 有効ファイル/フォルダなし　ログなし
#define		ERR_NO_VALID_FILE_LVL		LVL_MIDDLE

//			2.5.3.11 受信履歴参照

#define	ERR_RECEIVING_NODATA		0x00002110			// 受信履歴なし		ログなし
#define		ERR_RECEIVING_NODATA_LVL	LVL_MIDDLE

#define ERR_JOB_DEL_MODE_ON			0x00002120			// ジョブ自動消去有効	ログなし
#define		ERR_JOB_DEL_MODE_ON_LVL	LVL_MIDDLE

#define ERR_WHITE_INK_PAUSE_MODE	0x00002130			// 白インク休止モードのため実行不可
#define 	ERR_WHITE_INK_PAUSE_MODE_LVL	LVL_MIDDLE


//			メンテカートリッジ装着（インク使用時のメンテカートリッジ装着など）
#define ERR_MNT_CTRG_K				0x00002200	// メンテナンスカートリッジ装着 ブラック　ログなし
#define		ERR_MNT_CTRG_K_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_M				0x00002201	// メンテナンスカートリッジ装着 マゼンタ　ログなし
#define		ERR_MNT_CTRG_M_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_C				0x00002202	// メンテナンスカートリッジ装着 シアン　ログなし
#define		ERR_MNT_CTRG_C_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_Y				0x00002203	// メンテナンスカートリッジ装着 イエロー　ログなし
#define		ERR_MNT_CTRG_Y_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_W1				0x00002204	// メンテナンスカートリッジ装着  ホワイト１２　ログなし
#define		ERR_MNT_CTRG_W1_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_W2				0x00002205	// メンテナンスカートリッジ装着  ホワイト３４　ログなし
#define		ERR_MNT_CTRG_W2_LVL			LVL_MIDDLE

//			インクカートリッジ装着（白インク休止中のインクカートリッジ装着など）
#define ERR_W_OFF_INK_CTRG_W1		0x00002214	// インクカートリッジ装着  ホワイト１２　ログなし
#define		ERR_W_OFF_INK_CTRG_W1_LVL	LVL_MIDDLE
#define ERR_W_OFF_INK_CTRG_W2		0x00002215	// インクカートリッジ装着  ホワイト３４　ログなし
#define		ERR_W_OFF_INK_CTRG_W2_LVL	LVL_MIDDLE

//			特殊モード設定
#define ERR_SPECIAL_MODE			0x00002300	// 特殊モード設定
#define		ERR_SPECIAL_MODE_LVL		LVL_MIDDLE

/*-------------------------------------------------------*/
//		2.5.4 ＰＣインタフェースエラー(bit15-12:0011)
#define	EPC_RCV_TOUT				0x00003000	// PCからのコマンド受信タイムアウト
#define		EPC_RCV_TOUT_LVL			LVL_MIDDLE
#define	EPC_SND_TOUT				0x00003001	// PCへのコマンド送信タイムアウト
#define		EPC_SND_TOUT_LVL			LVL_MIDDLE
#define	EPC_NG_CMD					0x00003002	// PCコマンドのコマンド内容不正
#define		EPC_NG_CMD_LVL				LVL_MIDDLE
#define	EPC_CMD_VER					0x00003003	// PCコマンドのバージョン不整合
#define		EPC_CMD_VER_LVL				LVL_MIDDLE
#define	EPC_FIRM_CHKS				0x00003004	// ファームウェア更新コマンドのチェックサム異常
#define		EPC_FIRM_CHKS_LVL			LVL_MIDDLE
#define	EPC_EROM_CHKS				0x00003005	// EEPROM更新コマンドのチェックサム異常
#define		EPC_EROM_CHKS_LVL			LVL_MIDDLE
///#define	EPC_NG_CMD_ADDR				0x00003006	// PCコマンドが奇数アドレス上に受信されている　　************** 使われてない
///#define		EPC_NG_CMD_ADDR_LVL			LVL_MIDDLE
///#define	EPC_CMD_SEQ_NO				0x00003007	// コマンドシーケンス番号が不連続　　************** 使われてない
///#define		EPC_CMD_SEQ_NO_LVL			LVL_MIDDLE
///#define	EPC_CMD_CMD_CHKS			0x00003008	// コマンド単位でのチェックサム異常　　************** 使われてない
///#define		EPC_CMD_CMD_CHKS_LVL		LVL_MIDDLE
///#define	EPC_CMD_POS					0x00003009	// ジョブ内におけるコマンド位置不正　　************** 使われてない
///#define		EPC_CMD_POS_LVL				LVL_MIDDLE
#define	EPC_MAINTE_CMD				0x00003010	// 保守モード専用コマンドを非保守モード時に受信
#define		EPC_MAINTE_CMD_LVL			LVL_MIDDLE
///#define	EPC_NOT_CMD_DATA			0x00003011	// JobStart～End間に非コマンドデータが入っている　　************** 使われてない
///#define		EPC_NOT_CMD_DATA_LVL		LVL_MIDDLE
///#define	EPC_CMD_JOB_CHKS			0x00003012	// ジョブ単位でのチェックサム異常　　************** 使われてない
///#define		EPC_CMD_JOB_CHKS_LVL		LVL_MIDDLE

#define	EPC_PC_REQ_JOB_ERR			0x00003013	// PCがジョブエンドコマンドでエラー終了要求
#define		EPC_PC_REQ_JOB_ERR_LVL		LVL_MIDDLE
#define	EPC_NG_CMD_LEN				0x00003014	// PCコマンドのコマンド長不正
#define		EPC_NG_CMD_LEN_LVL			LVL_MIDDLE
#define	EPC_NG_TOO_MANY_DATA		0x00003015	// 印刷中に多すぎる(100個以上)のデータが送られた
#define		EPC_NG_TOO_MANY_DATA_LVL	LVL_MIDDLE

#define	EPC_341_WHITE_DATA			0x00003100	// 白休止モード中に白インクを使う印刷データが送られた
#define		EPC_341_WHITE_DATA_LVL		LVL_MIDDLE


/*-------------------------------------------------------*/
//		2.5.5 データエラー(bit15-12:0100)
//			2.5.5.1 印刷データの異常
#define	EDT_ILGL_CMDLEN				0x00003400	// 印刷コマンド長異常　　展開エラーで印刷をとめるのに必要　明日再検討
#define		EDT_ILGL_CMDLEN_LVL			LVL_MIDDLE
#define	EDT_ILGL_CMD				0x00003401	// 未定義印刷コマンド  展開エラーで印刷をとめるのに必要　明日再検討
#define		EDT_ILGL_CMD_LVL			LVL_MIDDLE
#define	EDT_ILGL_CMDSEQ1			0x00003402	// シーケンス異常（印刷データスタートが来ていないときの印刷データ）　展開エラーで印刷をとめるのに必要　明日再検討
#define		EDT_ILGL_CMDSEQ1_LVL		LVL_MIDDLE
//#define	EDT_ILGL_CMDSEQ2			0x00003403	// シーケンス異常（グラフィックデータ受信中にその他のコマンド）
//#define		EDT_ILGL_CMDSEQ2_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_LONG			0x00003404	// １行が長すぎる
//#define		EDT_LINE_TOO_LONG_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_MANY			0x00003405	// 行が多すぎる
//#define		EDT_LINE_TOO_MANY_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_WIDE			0x00003406	// 印刷幅が広すぎる
//#define		EDT_LINE_TOO_WIDE_LVL		LVL_MIDDLE
#define	EDT_NO_LINE					0x00003407	// 中身がない
#define		EDT_NO_LINE_LVL				LVL_MIDDLE
#define	EDT_JOB_BIG					0x00003408	// ジョブサイズが大きすぎる
#define		EDT_JOB_BIG_LVL				LVL_MIDDLE

#define EDT_ILGL_CMDSEQ4            0x00003410  // シーケンス異常（グラフィックデータスタートコマンドの位置が不正）
#define		EDT_ILGL_CMDSEQ4_LVL		LVL_MIDDLE
#define EDT_ILGL_CMDSEQ5            0x00003411  // シーケンス異常（グラフィックデータエンドコマンドの位置が不正）
#define		EDT_ILGL_CMDSEQ5_LVL		LVL_MIDDLE
#define EDT_NO_JOB_START            0x00003412  // ジョブスタートコマンドが存在しない
#define		EDT_NO_JOB_START_LVL		LVL_MIDDLE


//			2.5.5.3 ファームアップデートファイルの異常
//			ファームアップデートファイルの仕様に合わせて再定義する。


//			2.5.5.5 ファイルシステムエラー
#define	EFFS_FILE_OPEN				0x00004100	// ファイルオープンエラー
#define		EFFS_FILE_OPEN_LVL			LVL_MIDDLE
#define	EFFS_FILE_CREATE			0x00004101	// ファイルクリエイトエラー
#define		EFFS_FILE_CREATE_LVL		LVL_MIDDLE
///#define	EFFS_FILE_CLOSE				0x00004102	// ファイルクローズエラー
///#define		EFFS_FILE_CLOSE_LVL			LVL_MIDDLE
#define	EFFS_FILE_SEEK				0x00004103	// ファイルシークエラー
#define		EFFS_FILE_SEEK_LVL			LVL_MIDDLE
#define	EFFS_FILE_READ				0x00004104	// ファイルリードエラー
#define		EFFS_FILE_READ_LVL			LVL_MIDDLE
#define	EFFS_FILE_WRITE				0x00004105	// ファイルライトエラー
#define		EFFS_FILE_WRITE_LVL			LVL_MIDDLE
#define	EFFS_FILE_DATA				0x00004106	// ファイルの中身（データ）が異常
#define		EFFS_FILE_DATA_LVL			LVL_MIDDLE
///#define	EFFS_FILE_SIZE				0x00004107	// ファイルのサイズが異常
///#define		EFFS_FILE_SIZE_LVL			LVL_MIDDLE
#define	EFFS_FILE_GETSIZE			0x00004108	// ファイルサイズ取得失敗
#define		EFFS_FILE_GETSIZE_LVL		LVL_MIDDLE
///#define	EFFS_FILE_FIND				0x00004109	// ファイル検索失敗
///#define		EFFS_FILE_FIND_LVL			LVL_MIDDLE
///#define	EFFS_NO_FILE				0x00004110	// あるハズのファイルが無い
///#define		EFFS_NO_FILE_LVL			LVL_MIDDLE

//			2.5.5.6 内蔵データエラー
#define	EFFS_STR_NOT_FOUND				0x00004200	// 指定されたIDの文字列データが見つからない
#define		EFFS_STR_NOT_FOUND_LVL			LVL_MIDDLE
#define	EFFS_STR_VERSION_MISMATCH		0x00004201	// 指定されたIDの文字列データはバージョンミスマッチ
#define		EFFS_STR_VERSION_MISMATCH_LVL	LVL_MIDDLE
#define	EFFS_STR_CHECKSUM_MISMATCH		0x00004202	// 指定されたIDの文字列データはチェックサムが一致しない
#define		EFFS_STR_CHECKSUM_MISMATCH_LVL	LVL_MIDDLE

#define	EDT_TST_PRT_NOT_FOUND			0x00004400	// テスト印刷データが見つからない
#define		EDT_TST_PRT_NOT_FOUND_LVL		LVL_MIDDLE
#define	EDT_TST_PRT_VER_MISMATCH		0x00004401	// テスト印刷データのバージョンミスマッチ
#define		EDT_TST_PRT_VER_MISMATCH_LVL	LVL_MIDDLE
#define	EDT_TST_PRT_CHKSUM_MISMATCH		0x00004402	// テスト印刷データのチェックサムが一致しない
#define		EDT_TST_PRT_CHKSUM_MISMATCH_LVL	LVL_MIDDLE

//			ipAttach/IP Address/ifconfig/routeAdd
#define	ELAN_IPATTACH_ERROR				0x00004500	// ipAttach Error
#define		ELAN_IPATTACH_ERROR_LVL			LVL_MIDDLE
#define	ELAN_IP_ADDRESS_ERROR			0x00004501	// IP Address Error
#define		ELAN_IP_ADDRESS_ERROR_LVL		LVL_MIDDLE
#define	ELAN_IFCONFIG_ERROR			0x00004502	// ifconfig Error
#define		ELAN_IFCONFIG_ERROR_LVL		LVL_MIDDLE
#define	ELAN_ROUTE_ADD_ERROR		0x00004503	// routeAdd Error
#define		ELAN_ROUTE_ADD_ERROR_LVL	LVL_MIDDLE
#define	ELAN_IP_ADDRESS_SET_ERROR			0x00004504	// IP Address Set Error　ログなし
#define		ELAN_IP_ADDRESS_SET_ERROR_LVL	LVL_MIDDLE

#define	ELAN_EEPROM_BACKUP_ERROR			0x00004505	// EEPROM保存エラー
#define		ELAN_EEPROM_BACKUP_ERROR_LVL	LVL_MIDDLE

#define ELAN_EEPROM_RESTORE_ERROR			0x00004506	// 設定情報リストアエラー
#define		ELAN_EEPROM_RESTORE_ERROR_LVL	LVL_MIDDLE

/*-------------------------------------------------------*/

//					2.5.6.1.1.2 プリントコントロール
#define	ECM_DATA_TOUT				0x00005010	// 印刷データ展開タイムアウト
#define		ECM_DATA_TOUT_LVL			LVL_MIDDLE

#define	ECM_CR_MOVE_TOUT			0x00005020	// キャリッジ移動完了待ちタイムアウト
#define		ECM_CR_MOVE_TOUT_LVL		LVL_FATAL
#define	ECM_FLUSH_TOUT				0x00005021	// フラッシング完了待ちタイムアウト
#define		ECM_FLUSH_TOUT_LVL			LVL_FATAL
#define	ECM_HEAD_RCV_TOUT			0x00005022	// ヘッド動作完了待ちタイムアウト
#define		ECM_HEAD_RCV_TOUT_LVL		LVL_FATAL


//					2.5.6.2.1 プリントコントロール
#define	ECM_MNT_REQ_TOUT			0x00005080	// メンテナンス動作リクエストタイムアウト
#define		ECM_MNT_REQ_TOUT_LVL		LVL_FATAL
#define	ECM_MNT_RCV_TOUT			0x00005081	// メンテナンス動作完了待ちタイムアウト
#define		ECM_MNT_RCV_TOUT_LVL		LVL_FATAL

#define	ECM_BYSH_PLTN_LD			0x00005094	// プラテンロードリクエストタイムアウト
#define		ECM_BYSH_PLTN_LD_LVL		LVL_FATAL
#define	ECM_BYSH_PLTN_UNLD			0x00005095	// プラテンアンロードリクエストタイムアウト
#define		ECM_BYSH_PLTN_UNLD_LVL		LVL_FATAL
#define	ECM_BYSH_PLTN_LF			0x00005096	// LFタイムアウト
#define		ECM_BYSH_PLTN_LF_LVL		LVL_FATAL




/*-------------------------------------------------------*/
//		メンテナンス基板との通信	（52xx番台）

#define	ECM_SHMT_SND_TOUT			0x00005200	// メンテユニットレスポンス待ちタイムアウト
#define		ECM_SHMT_SND_TOUT_LVL		LVL_FATAL
#define	ECM_SHMT_FMT				0x00005201	// メンテユニットレスポンスフォーマットエラー
#define		ECM_SHMT_FMT_LVL			LVL_FATAL

#define	ECM_SHMT_COM_SEND			0x00005230	// メンテユニットへのコマンド送信エラー
#define		ECM_SHMT_COM_SEND_LVL		LVL_FATAL
#define	ECM_SHMT_RCV_UNEXPECT_CMD	0x00005231	// メンテユニットへのリクエストとは異なるレスポンスを受信した
#define		ECM_SHMT_RCV_UNEXPECT_CMD_LVL	LVL_FATAL
#define	ECM_SHMT_CRC_CALC			0x00005232	// メンテユニットから受信したレスポンスのCRCが一致しない
#define		ECM_SHMT_CRC_CALC_LVL		LVL_FATAL
#define	ECM_SHMT_CRC_INEXACT		0x00005233	// メンテユニットから受信したレスポンスのCRCの書式が不正
#define		ECM_SHMT_CRC_INEXACT_LVL	LVL_FATAL

#define	ECM_MNT_SIO_OPEN			0x00005240	// メンテユニットとの通信用シリアルポートがオープンできない
#define		ECM_MNT_SIO_OPEN_LVL		LVL_FATAL
#define	ECM_MNT_SIO_READ			0x00005241	// メンテユニットからのシリアル受信エラー	// <- 使っていないけど消しちゃ駄目!	reserved
#define		ECM_MNT_SIO_READ_LVL		LVL_FATAL								// <- 使っていないけど消しちゃ駄目!	reserved

#define	ECM_MNT_INCORRECT_REC		0x00005250	// メンテユニットファーム更新データレコードの異常
#define		ECM_MNT_INCORRECT_REC_LVL	LVL_FATAL

#define	ECM_MNT_VER_UNSUPPORT		0x00005260	// メンテユニットファームとのバージョンミスマッチ
#define		ECM_MNT_VER_UNSUPPORT_LVL	LVL_FATAL


/*-------------------------------------------------------*/
//		メンテナンスユニット制御	（53xx～4xx番台）

// 53xx/54xx番台は、メンテユニットファームからのエラーレスポンス受信（メンテユニットファームがエラーを検出して、メイン基板へその内容を通知してきた）
//   xx部分はメンテユニットファームのエラーコードと同値
//   エラーレベルはすべてECM_MNT_BASE_LVL
//   53xx番台はカラー側、54xx番台は白側
#define	ECM_MNT_BASE_C				0x00005300	// カラー側メンテユニットファームウェアからのエラー通知のベース番号（この番号自体は未使用）
#define	ECM_MNT_BASE_W				0x00005400	// 白側メンテユニットファームウェアからのエラー通知のベース番号（この番号自体は未使用）
#define		ECM_MNT_BASE_LVL			LVL_FATAL
#define	ECM_CMD_LEN					      0x01	// コマンド長異常
#define	ECM_CMD_ARGC				      0x02	// 引数の個数の文字列が不正
#define ECM_CMD_ARGV				      0x03	// 引数の文字列が不正
#define ECM_CMD_ARG_CNT				      0x04	// 引数の個数がコマンド仕様と一致せず
#define	ECM_CMD_CRC_STR				      0x05	// CRCの文字列が不正
#define	ECM_CMD_UNKNOWN				      0x06	// 未定義コマンド
#define	ECM_CMD_SEQ_STR	 			      0x07	// シーケンス番号の文字列が不正
#define	ECM_COM_CRC					      0x11	// CRC一致せず
#define	ECM_COM_OVERRUN				      0x12	// オーバランエラー
#define	ECM_COM_PARITY				      0x13	// パリティエラー
#define	ECM_COM_FRAMING				      0x14	// フレーミングエラー
#define	ECM_CAM_INIT				      0x20	// メンテカム未初期化
#define	ECM_CAM_SNSR1				      0x21	// メンテカムモーター/センサーエラー１（完了時のセンサー値が想定外）
#define	ECM_CAM_SNSR2				      0x22	// メンテカムモーター/センサーエラー２（規定ステップ内に完了せず）
#define	ECM_CAM_SNSR3				      0x23	// メンテカムモーター/センサーエラー３（リトライアウト）
#define	ECM_CLEANER_INIT			      0x30	// ワイパークリーナー未初期化
#define	ECM_CLEANER_SNSR1			      0x31	// ワイパークリーナーモーター/センサーエラー１（完了時のセンサー値が想定外）
#define	ECM_CLEANER_SNSR2			      0x32	// ワイパークリーナーモーター/センサーエラー２（規定ステップ内に完了せず）
#define	ECM_CLEANER_SNSR3			      0x33	// ワイパークリーナーモーター/センサーエラー３（リトライアウト）
#define	ECM_WIPER_INIT				      0x40	// ワイパー未初期化
#define	ECM_WIPER_SNSR1			          0x41	// ワイパーモーター/センサーエラー１（完了時のセンサー値が想定外）
#define	ECM_WIPER_SNSR2				      0x42	// ワイパーモーター/センサーエラー２（規定ステップ内に完了せず）
#define	ECM_WIPER_SNSR3				      0x43	// ワイパーモーター/センサーエラー３（リトライアウト）
#define	ECM_UPDATE_READY			      0x50	// アップデート開始準備未完
#define	ECM_FLASH_WRITE				      0x51	// フラッシュライトエラー
#define	ECM_FLASH_VERIFY			      0x52	// フラッシュライト後ベリファイエラー
#define	ECM_FLASH_ERASE				      0x53	// フラッシュ消去エラー
#define	ECM_UPDATE_BLKNO			      0x54	// アップデートデータ ブロック連番異常
#define	ECM_UPDATE_DATA				      0x55	// アップデートデータ データレコード異常
#define	ECM_UPDATE_TOTAL			      0x56	// アップデートデータ 総レコード数不一致
#define	ECM_UPDATE_SUM				      0x57	// アップデートデータ チェックサム不一致
#define	ECM_FLASH_LIB				      0x58	// フラッシュライブラリエラー
#define	ECM_UPDATE_RECNUM			      0x59	// アップデートデータ ブロック内レコード数異常
#define	ECM_SOL_PRE_ADDING			      0x61	// ソレノイド制御要求重複
#define	ECM_INK_IIC_SND_ERR1		      0x71	// インクセンサリードIIC送信エラー（エラー１）
#define	ECM_INK_IIC_SND_ERR2		      0x72	// インクセンサリードIIC送信エラー（エラー２）
#define	ECM_INK_IIC_SND_OTHER		      0x73	// インクセンサリードIIC送信エラー（その他のエラー）
#define	ECM_INK_IIC_SND_TOUT		      0x74	// インクセンサリードIIC送信エラー（送信未完了）
#define	ECM_INK_IIC_RCV_ERR1		      0x75	// インクセンサリードIIC受信エラー（エラー１）
#define	ECM_INK_IIC_RCV_ERR2	          0x76	// インクセンサリードIIC受信エラー（エラー２）
#define	ECM_INK_IIC_RCV_OTHER		      0x77	// インクセンサリードIIC受信エラー（その他のエラー）
#define	ECM_INK_IIC_RCV_TOUT		      0x78	// インクセンサリードIIC受信エラー（送信未完了）
#define	ECM_INTERNAL				      0x91	// 内部エラー（メンテファームウェア）
// 0x000054FFまで予約済み


/*-------------------------------------------------------*/
//		サブタンク		（55xx番台）

#define	ESBT_FILL_TOUT_K			0x00005501	// サブタンク K 充填待ちタイムアウト
#define		ESBT_FILL_TOUT_K_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_M			0x00005502	// サブタンク M 充填待ちタイムアウト
#define		ESBT_FILL_TOUT_M_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_C			0x00005503	// サブタンク C 充填待ちタイムアウト
#define		ESBT_FILL_TOUT_C_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_Y			0x00005504	// サブタンク Y 充填待ちタイムアウト
#define		ESBT_FILL_TOUT_Y_LVL		LVL_FATAL


/*-------------------------------------------------------*/
//		ICチップ制御	（56xx番台）

#define	ESBT_IC_CHIP_READ_ERR			0x00005600	// ICチップリードエラー（APIが要求を受け付けない）
#define		ESBT_IC_CHIP_READ_ERR_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_WRITE_ERR			0x00005601	// ICチップライトエラー
#define		ESBT_IC_CHIP_WRITE_ERR_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_READ_TOUT			0x00005602	// ICチップリードタイムアウト
#define		ESBT_IC_CHIP_READ_TOUT_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_WRITE_TOUT			0x00005603	// ICチップライトタイムアウト
#define		ESBT_IC_CHIP_WRITE_TOUT_LVL		LVL_FATAL


/*-------------------------------------------------------*/
//		白インク循環	（57xx番台）


/*-------------------------------------------------------*/
//		PPC-サフラン間の通信		（58xx番台）

#define	EUH_SAFFRON_OPEN			0x00005801	// サフランをUSBプリンタとしてオープン失敗
#define	EUH_SAFFRON_READ			0x00005802	// サフランからデータ受信失敗
#define	EUH_SAFFRON_WRITE			0x00005803	// サフランへのデータ送信失敗
#define	EUH_SAFFRON_LINK			0x00005804	// サフランとの通信が確立しない(応答が返ってこない)


/*-------------------------------------------------------*/
//		2.5.7 ハードウェア故障(bit15-12:0110)
//			2.5.7.1 SH側
//				2.5.7.1.1 プラテン
//#define	EHW_PLTN_LOAD				0x00006000	// プラテンロードエラー
//#define		EHW_PLTN_LOAD_LVL			LVL_FATAL
//#define	EHW_PLTN_IN					0x00006003	// プラテン収納エラー
//#define		EHW_PLTN_IN_LVL				LVL_FATAL
#define	EHW_CLRNS_SNSR				0x00006004	// クリアランスセンサー故障
#define		EHW_CLRNS_SNSR_LVL			LVL_FATAL

//				2.5.7.1.2 メモリー
#define	EHW_SH_EROM_WRITE			0x00006010	// メイン基板EEPROM書き込み失敗
#define		EHW_SH_EROM_WRITE_LVL		LVL_FATAL
#define	EHW_SH_FLUSH_ERASE			0x00006011	// メイン基板フラッシュ消去失敗
#define		EHW_SH_FLUSH_ERASE_LVL		LVL_FATAL
#define	EHW_SH_FLUSH_WRITE			0x00006012	// メイン基板フラッシュ書き込み失敗
#define		EHW_SH_FLUSH_WRITE_LVL		LVL_FATAL


//				2.5.7.1.3 RTC
///#define	EHW_SH_RTCFAULT				0x00006020	// RTC異常
///#define		EHW_SH_RTCFAULT_LVL			LVL_FATAL
#define	EHW_NO_BATTERY				0x00006021	// バッテリー切れ　ログなし
#define		EHW_NO_BATTERY_LVL			LVL_FATAL

// 				2.5.7.1.4 Panel
#define	EHW_PANEL_BTN1				0x00006031	// 起動時にパネルボタンが押されている(platenボタン)。
#define		EHW_PANEL_BTN1_LVL			LVL_FATAL

#define	EHW_PANEL_BTN2				0x00006032	// 起動時にパネルボタンが押されている(printボタン)。
#define		EHW_PANEL_BTN2_LVL			LVL_FATAL

#define	EHW_PANEL_BTN3				0x00006033	// 起動時にパネルボタンが押されている(cancelボタン)。
#define		EHW_PANEL_BTN3_LVL			LVL_FATAL

#define	EHW_PANEL_BTN4				0x00006034	// 起動時にパネルボタンが押されている(back/leftボタン)。
#define		EHW_PANEL_BTN4_LVL			LVL_FATAL

#define	EHW_PANEL_BTN5				0x00006035	// 起動時にパネルボタンが押されている(rightボタン)。
#define		EHW_PANEL_BTN5_LVL			LVL_FATAL

#define	EHW_PANEL_BTN6				0x00006036	// 起動時にパネルボタンが押されている(downボタン)。
#define		EHW_PANEL_BTN6_LVL			LVL_FATAL

#define	EHW_PANEL_BTN7				0x00006037	// 起動時にパネルボタンが押されている(upボタン)。
#define		EHW_PANEL_BTN7_LVL			LVL_FATAL

#define	EHW_PANEL_BTN8				0x00006038	// 起動時にパネルボタンが押されている(purgeボタン)。
#define		EHW_PANEL_BTN8_LVL			LVL_FATAL

#define	EHW_PANEL_BTN9				0x00006039	// 起動時にパネルボタンが押されている(OK/menuボタン)。
#define		EHW_PANEL_BTN9_LVL			LVL_FATAL


// 				2.5.7.1.5 Head Memory


//			2.5.7.2 BY側
//				2.5.7.2.1 キャリッジの状態

#define	EHW_CRG_ERR_BASE			0x00006100
#define		EHW_CRG_ERR_LVL				LVL_FATAL
#define	EHW_CRG_ERR_BUSY			0x00006101
#define	EHW_CRG_ERR_STOP			0x00006102	// 異常停止
#define	EHW_CRG_ERR_LOCK_ERROR		0x00006103	// キャップロック失敗
#define	EHW_CRG_ERR_NOT_MOVE		0x00006104	// まったく動かない
#define	EHW_CRG_ERR_INIT			0x00006105	// 原点初期化に失敗
#define	EHW_CRG_ERR_BUMP_FRAME		0x00006106	// フレームに衝突した可能性あり
#define	EHW_CRG_ERR_BACK_MOVE		0x00006107	// 反転駆動を検出
#define	EHW_CRG_ERR_SPEED_DOWN		0x00006108	// 速度の異常低下
#define	EHW_CRG_ERR_PRINT_STOP		0x00006109	// 印刷範囲内 異常停止
#define	EHW_CRG_ERR_IN_LOCK			0x00006110	// ロッカー位置から出られない
#define	EHW_CRG_ERR_CAP_ERR			0x00006111	// キャップに乗り上げられない

#define	EHW_CRG_ERR_WATCHDOG		0x00006119	// ウォッチドッグ検出
#define	EHW_CRG_ERR_REMOVE			0x00006120	// CR停止位置ショート後、再起動でOK
												//(エラーにはしない。ヘッドとのIF定義のためReserve)

#define	EHW_CRG_LOWSPEED			0x00006130	// 速度低下エラー
#define		EHW_CRG_LOWSPEED_LVL		LVL_MIDDLE
#define	EHW_CRG_HIGHSPEED			0x00006131	// 速度超過エラー
#define		EHW_CRG_HIGHSPEED_LVL		LVL_MIDDLE
#define	EHW_CRG_STOP_ADJUST			0x00006132	// 停止調整エラー
#define		EHW_CRG_STOP_ADJUST_LVL		LVL_MIDDLE
#define	EHW_CRG_ADJUST_RVS			0x00006133	// 速度調整エラー(RVS)
#define		EHW_CRG_ADJUST_RVS_LVL		LVL_FATAL
#define	EHW_CRG_ADJUST_FWD			0x00006134	// 速度調整エラー(FWD)
#define		EHW_CRG_ADJUST_FWD_LVL		LVL_FATAL

//				2.5.7.2.3 ヘッド温度異常
#define	EHW_HEAD_TEMP_C				0x00006220	// カラーヘッド 温度異常
#define		EHW_HEAD_TEMP_C_LVL			LVL_FATAL
#define	EHW_HEAD_TEMP_W				0x00006221	// ホワイトヘッド温度異常
#define		EHW_HEAD_TEMP_W_LVL			LVL_FATAL

//				2.5.7.2.4 ヘッド電圧異常
#define	EHW_HEAD_VLTG_C				0x00006230	// カラーヘッド電圧異常
#define		EHW_HEAD_VLTG_C_LVL			LVL_FATAL
#define	EHW_HEAD_VLTG_W				0x00006231	// ホワイトヘッド電圧異常
#define		EHW_HEAD_VLTG_W_LVL			LVL_FATAL

//				2.5.7.2.5 ヘッド故障
#define	EHW_HEAD_FFC_C				0x00006240	// カラーヘッド FFC 異常
#define		EHW_HEAD_FFC_C_LVL			LVL_FATAL
#define	EHW_HEAD_FFC_W				0x00006241	// ホワイトヘッド FFC 異常
#define		EHW_HEAD_FFC_W_LVL			LVL_FATAL

//				2.5.7.2.6 環境温度センサ異常
///#define	EHW_SUR_TEMP				0x00006260	// 環境温度センサ異常
///#define		EHW_SUR_TEMP_LVL			LVL_FATAL

//			2.5.7.3 メンテ側
//				2.5.7.3.1 ドライバーアラーム

/*----------------------------------------------------------------------*/
//		2.5.8 プログラムエラー(bit15-12:0111)
//
//				【7000番台のエラーログの統一ルール】
//					(1) 付帯情報の1ワード目（先頭4バイト）は、ソース上の発生個所を示す。
//							1バイト目：		タスク番号
//							2バイト目：		ソースファイル番号（タスク内）
//							3~4バイト目：	位置番号（ソースファイル内）
/*----------------------------------------------------------------------*/
#define	EPG_SH_SYSCALL				0x00007000		// システムコールエラー
#define		EPG_SH_SYSCALL_LVL			LVL_FATAL

//#define	EPG_PPC_MALLOC				0x00007003	// メモリアロケート失敗   　　************** システムコールエラーに統合
//#define		EPG_PPC_MALLOC_LVL			LVL_FATAL
//#define	EPG_SH_FUNC_ARG				0x00007010	// 引数異常　→削除  　	************** 一般プログラムエラーに統合
//#define		EPG_SH_FUNC_ARG_LVL			LVL_FATAL
//#define	EPG_SH_FUNC_RTN				0x00007011	// 戻り値異常　→削除  　	************** 一般プログラムエラーに統合
//#define		EPG_SH_FUNC_RTN_LVL			LVL_FATAL

#define	EPG_TASK_EVENT_TIMEOUT		0x00007012		// 他タスクから送られてくるはずのイベントが来ない（イベント受信待ちタイムアウト）
#define		EPG_TASK_EVENT_TIMEOUT_LVL	LVL_FATAL

#define	EPG_SH_PROG_ERR				0x00007013		// 一般プログラムエラー 　　************** 残す　OS関係以外のソフトウェアエラー
#define		EPG_SH_PROG_ERR_LVL			LVL_FATAL



#define	EPG_SH_WAIT_PRT_END_TIMOUT	0x00007015	// 印刷が終わらないので次の印刷データを受信できない
#define		EPG_SH_WAIT_PRT_END_TIMOUT_LVL	LVL_MIDDLE





//==============================================================================//
//	タスク番号	 （ログの発生個所を示すため、タスク毎に定めた1バイトの数値。ログの付帯情報の先頭に残す。）	//
//==============================================================================//
#define	TNO_MAIN			0x01	// メインタスク
#define	TNO_DEBUG			0x05	// debug/ 以下
#define	TNO_LIB				0x06	// lib/ 以下
#define TNO_MAIN_CTL		0x10	// 全体制御タスク
#define	TNO_DRIVER			0x13	// driver/ 以下
#define TNO_MAIN_CYCLE		0x15	// 周期タスク
#define	TNO_MENU			0x20	// メニュータスク
#define	TNO_PANEL			0x21	// パネルタスク
#define	TNO_LCD				0x22	// LCDタスク
#define TNO_INKCTRG			0x25	// インクカートリッジタスク
#define TNO_SUB_TANK		0x27	// サブタンクタスク
#define TNO_PRINT_MASTER	0x30	// プリントマスタータスク
#define TNO_ARMANI			0x31	// アルマーニタスク
#define TNO_DATA_EXPAND		0x32	// データ展開タスク
#define	TNO_MNT				0x50	// メンテタスク
#define	TNO_PCIF			0x54	// PCIFンタスク
#define	TNO_USB_F			0x55	// USBファンクションタスク
#define	TNO_LAN2			0x91	// LAN2 タスク
#define	TNO_LAN3			0x92	// LAN3 タスク
#define	TNO_LOG				0x94	// log タスク



#endif
