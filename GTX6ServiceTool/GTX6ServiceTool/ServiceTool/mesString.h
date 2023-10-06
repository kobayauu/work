// tab = 4
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
//		Copyright (c) 2003 Brother Industries, Ltd.
//
//		Version		Date		Editor				Comment
//----------------+-----------+-------------------+---------------------
//		0.0.0.1		2002/2/28	Toshiaki Mizutani	Created
//
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef __MES_STRING_H
#define __MES_STRING_H
//                              |<-------------->| 
// Action Messages -----------------------------------------------------
#define MES_ACT_WELCOME			"Welcome to MAT-1"
#define	MES_ACT_INIT0			"Initializing    "							//2003.10.08ïœçX å„ÇÎÇ…ãÛîíÇí«â¡
#define	MES_ACT_INIT1			"Initializing."
#define	MES_ACT_INIT2			"Initializing.."
#define	MES_ACT_INIT3			"Initializing..."
#define	MES_ACT_INIT4			"Initializing...."
#define	MES_ACT_DT_RCVING		"Receiving..."
#define	MES_ACT_PRINTING		"Printing..."
#define	MES_ACT_WAITING1		"Waiting for head"
#define	MES_ACT_WAITING2		"  cooling down."
#define	MES_ACT_PURGING			"Head Cleaning..."
#define	MES_ACT_AUTOPURGING		"Auto Cleaning..."
#define	MES_ACT_CANCELLING		"Cancelling..."
#define	MES_ACT_SHUTDOWN		"Shutdown..."
#define	MES_ACT_FIRM_UPDATE1	"Firmware"
#define	MES_ACT_FIRM_UPDATE2	"Updating..."
#define	MES_ACT_FIRM_UPD_CMP1	"Firmware updated"
#define	MES_ACT_FIRM_UPD_CMP2	"Wait a moment."
#define	MES_ACT_LOG_SEND		"Log uploading..."

// Error Messages ------------------------------------------------------
#define MES_ERROR				"ERROR"
#define MES_INK_YEL_EMPTY		"EMPTY Yellow"
#define MES_INK_CYN_EMPTY		"EMPTY Cyan"
#define MES_INK_MGT_EMPTY		"EMPTY Magenta"
#define MES_INK_BLK_EMPTY		"EMPTY Black"

#define MES_NOCTRG_YEL			"NO INK Yellow"
#define MES_NOCTRG_CYN			"NO INK Cyan"
#define MES_NOCTRG_MGT			"NO INK Magenta"
#define MES_NOCTRG_BLK			"NO INK Black"

#define	MES_NO_DRN_TANK			"NO WASTE INK BOX"
#define	MES_DRN_TANK_FULL		"WASTE INK FULL"

#define	MES_NO_PLATEN			"NO PLATEN"
#define	MES_ILGL_PLATEN			"ILGL PLATEN SET"
#define	MES_ILGL_PLT_DATA		"ILGL PLATEN DATA"
#define	MES_PLATEN_UNMATCH		"PLATEN MISMATCH"
#define	MES_CLEARNCE_ERR		"OBSTACLE SENSED"

#define	MES_COVER_OPEN1			"Cover is opened,"
#define	MES_COVER_OPEN2			"   Close to run!"

#define	MES_ERROR_CODE1			"Error Code:%d"
#define	MES_ERROR_CODE2			"(%04x-%04x)"

#define	MES_ERR_PC_DATA_BLANK	"Blank Data"
#define	MES_ERR_PC_DATA_ADDR	"Received NG Data"
#define	MES_ERR_PC_DATA			"PC Data Error"
#define	MES_ERR_PC_CONNECT		"PC Comm. Error"
#define	MES_ERR_MECHANICAL		"Machine Error"
#define	MES_ERR_INTERNAL		"Internal Error"

#define	MES_ERR_SEND_RETRY		"Send data again"
#define	MES_ERR_SELF_RECOVERY	"Check & Press OK"
#define	MES_ERR_SELF_RECOVERY2	"Press OK & Retry"
#define	MES_ERR_REBOOT			"Please reboot"
#define	MES_ERR_TURN_OFF		"Please turn off"
#define	MES_ERR_SELF_REBOOT		"Push OK, Reboot"
#define	MES_ERR_SELF_UNLOAD		"Push OK, Unload"

#define	MES_ERR_BY_INTERNAL		"BY Internal"							//2003.10.08í«â¡

// Warning Messages ----------------------------------------------------
#define MES_WARNING				"WARNING"
#define MES_INK_YEL_NEMPTY		"INK LOW Yellow"
#define MES_INK_CYN_NEMPTY		"INK LOW Cyan"
#define MES_INK_MGT_NEMPTY		"INK LOW Magenta"
#define MES_INK_BLK_NEMPTY		"INK LOW Black"

#define MES_WP_BLD_LIFE			"  Wp-Blade Life"						//2003.10.08í«â¡
#define MES_WP_CLNR_LIFE		" Wp-Cleaner Life"						//2003.10.08í«â¡
#define MES_RTC_NOT_ADJ			"RTC not Adjusted"						//2003.10.08í«â¡
#define MES_CR_MTR_LIFE			"  CR Motor Life"						//2003.10.08í«â¡
#define MES_BTRY_LIFE			"  Battery Life"						//2003.10.08í«â¡
#define MES_HEAD_BLK_TEMP		"  K Head Temp"							//2003.10.08í«â¡
#define MES_HEAD_MGT_TEMP		"  M Head Temp"							//2003.10.08í«â¡
#define MES_HEAD_CYN_TEMP		"  C Head Temp"							//2003.10.08í«â¡
#define MES_HEAD_YEL_TEMP		"  Y Head Temp"							//2003.10.08í«â¡
#define MES_HEAD_BLK_LIFE		"  K Head Life"							//2003.10.08í«â¡
#define MES_HEAD_MGT_LIFE		"  M Head Life"							//2003.10.08í«â¡
#define MES_HEAD_CYN_LIFE		"  C Head Life"							//2003.10.08í«â¡
#define MES_HEAD_YEL_LIFE		"  Y Head Life"							//2003.10.08í«â¡

// Condition Messages --------------------------------------------------
#define	MES_CON_DT_EMPTY		"No Print Data"
#define	MES_CON_DT_READY		"Print Ready"

#define	MES_CON_TEMP_LOW		"Temp Low:"								//2003.10.08í«â¡
#define	MES_CON_TEMP_HIGH		"Temp High:"							//2003.10.08í«â¡

// Menu Messages -------------------------------------------------------
#define	MES_MNU_OK				"Push OK button"
#define	MES_MNU_OKCANCEL		"Push OK / CANCEL"
#define	MES_MNU_ALL				"Push any button"
#define	MES_MNU_TO_SET			"Push OK to set"
#define	MES_MNU_TO_START		"Push OK to start"
#define	MES_MNU_SELECT			"Select & Push OK"

#define MES_MNU_PUR_CONFIRM		"Cleaning Ready"
#define	MES_MNU_DEL_CONFIRM		"Clear Ready"

#define MES_MNU_ALL_HEAD		"All Heads ?"
#define MES_MNU_BLK_HEAD		"Black Head ?"
#define MES_MNU_MGT_HEAD		"Magenta Head ?"
#define MES_MNU_YLW_HEAD		"Yellow Head ?"
#define MES_MNU_CYN_HEAD		"Cyan Head ?"
#define MES_MNU_BLADE_CONFIRM	"Blade Exchanged?"
#define	MES_MNU_CLEANER_CONFIRM	"Wiper Exchanged?"

#define	MES_MNU_SET_YEAR		"Set Year & OK"
#define	MES_MNU_SET_MONTH		"Set Month & OK"
#define	MES_MNU_SET_DAY			"Set Day & OK"
#define	MES_MNU_SET_HOUR		"Set Hour & OK"
#define	MES_MNU_SET_MINUTE		"Set Minute & OK"
#define	MES_MNU_SET_SECOND		"Set Second & OK"

// Job Messages --------------------------------------------------------

#endif // __MES_STRING_H
