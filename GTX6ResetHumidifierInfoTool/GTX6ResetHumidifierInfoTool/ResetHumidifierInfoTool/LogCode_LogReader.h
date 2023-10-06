/**
 * LogCode_LogReader.h
 */

#ifndef _LogCode_H
#define _LogCode_H

#define CODE_POWERON		0x00010000	// 電源オン
#define CODE_PURGESTART		0x92000000	// パージ開始
#define CODE_TESTPRINT		0x12300000	// テスト印刷
/*
#define CODE_PURGE_K		0x02110000	// パージ開始ブラック
#define CODE_PURGE_M		0x02120000	// パージ開始マゼンタ
#define CODE_PURGE_C		0x02130000	// パージ開始シアン
#define CODE_PURGE_Y		0x02140000	// パージ開始イエロー
#define CODE_TESTPRINT		0x02200000	// テスト印字
*/
#define CODE_AUTOPURGE		0x03000000	// 自動パージ開始
#define CODE_MNT_WIPER_C	0x15000000	// メンテ部品掃除交換 ワイパークリーナ交換(カラー)
#define CODE_MNT_WIPER_W	0x15010000	// メンテ部品掃除交換 ワイパークリーナ交換(白)
#define CODE_MNT_FLUSH_C	0x15200000	// メンテ部品掃除交換 フラッシングフォーム交換(カラー)
#define CODE_MNT_FLUSH_W	0x15210000	// メンテ部品掃除交換 フラッシングフォーム交換(白)
/*
#define CODE_JOBSTART		0x20000000	// プリントジョブ受信開始
#define CODE_JOBEND			0x20010000	// プリントジョブ受信完了
*/
#define CODE_JOBNAME		0x90080000	// ログ連番、ジョブネーム
#define CODE_JOBCOMMENT		0x90090000	// ログ連番、ジョブコメント
#define CODE_JOBALL			0x90110000	// ログ連番、諸情報
#define CODE_GRAPHIC		0x90120000	// ログ連番、グラフィック
#define CODE_PCINFO			0x90130000	// ログ連番、PC情報
#define CODE_PRINTSTART		0x91000000	// ログ連番、印刷開始
#define CODE_PRINTEND		0x91010000	// ログ連番、印刷完了
#define CODE_PRINTSTOP		0x91020000	// ログ連番、印刷中止
#define	CODE_HISTORY		0x14000000	// ログ連番、受信履歴から印刷データを選択

#define	CODE_USB_FILE_LOAD	0x12600000	// USBメモリからARP ファイルロード 
/*
#define CODE_EMP_K_INK		0x00002020	// インク空 
#define CODE_EMP_M_INK		0x00002021
#define CODE_EMP_C_INK		0x00002022
#define CODE_EMP_Y_INK		0x00002023
#define CODE_EMP_W1_INK		0x00002024
#define CODE_EMP_W2_INK		0x00002025
#define CODE_EMP_W3_INK		0x00002026
#define CODE_EMP_W4_INK		0x00002027
*/

#define NUM_LOGCLASS			5
#define LOGCLASS_OPERATION		0x01
#define LOGCLASS_STATUS			0x02
#define LOGCLASS_MAINTENANCE 	0x04
#define LOGCLASS_ERROR			0x08
#define LOGCLASS_DEBUG			0x10

#define NUM_LEVEL			8
#define LEVEL_FATAL			0	// 予期しない重大なエラー（故障：システムを停止する）
#define LEVEL_SERIOUS		1	// システムを継続できない重大なエラー（リセットで復旧する）
#define LEVEL_MIDDLE		2	// 現在の処理の中止が必要なほどの重大なエラー
#define LEVEL_WARNING		3	// 現在の処理は継続できるが、その後の印刷に支障がありそうなエラー
#define LEVEL_EVENT1		4	// 重要なイベント
#define LEVEL_EVENT2		5	// 通常のイベント
#define LEVEL_EVENT3		6	// 末節的なイベント
#define LEVEL_INFO			7	// 補足的な情報

#endif
