/**********************************************************/
/*   LOGcode.h                       03.4.17    k.hayashi */
/**********************************************************/

#ifndef _LOGCODE_H_
#define _LOGCODE_H_



//--- log_level 3bit(1�`5) ----------------------------------------------
#define LVL_FATAL		1		// �v���I�ȃG���[
#define LVL_MIDDLE		2		// �ʏ�N���肤��G���[
#define LVL_WARNING		3		// ���[�j���O
#define LVL_EVENT1		4		// �K�{�ȉғ����O
#define LVL_EVENT2		5		// ��ʂ̉ғ����O



/*--- log_code 4byte ----------------------------------*/
//���O�R�[�h�̍\��
//  �ғ����O�R�[�h�@�@0x00010000�`0x99990000
//  �G���[���O�R�[�h�@  0x00000001�`0x00009999
//
/*--- log_code 4byte ----------------------------------*/

//	2.1 �ғ����O(bit15-12:0000)
//		2.1.1 ��������
//		2.1.1.1 �d��
#define OP_PW_ON					0x00000001	// �d���I��
#define		OP_PW_ON_LVL				LVL_EVENT1
#define OP_PW_OFF					0x00000002	// �d���I�t
#define		OP_PW_OFF_LVL				LVL_EVENT1
///#define OP_SOFT_RESET				0x00000003	// �\�t�g���Z�b�g
///#define		OP_SOFT_RESET_LVL			LVL_EVENT1
///#define OP_OTHER_RESET				0x00000004	// ���̑��̃��Z�b�g
///#define		OP_OTHER_RESET_LVL			LVL_EVENT1
#define	OP_PW_RCV_INIT_CMPLT		0x00000014	// ����������
#define		OP_PW_RCV_INIT_CMPLT_LVL	LVL_EVENT1

#define	OP_USBHOST_REOPEN			0x00000101	// �T�t�����Đڑ�(USB�z�X�g)
#define		OP_USBHOST_REOPEN_LVL		LVL_EVENT1

//		2.1.1.3 ��{����
///#define OP_PR_START					0x00000200	// ����J�n
///#define		OP_PR_START_LVL				LVL_EVENT1
///#define OP_PR_END					0x00000201	// ����I��
///#define		OP_PR_END_LVL				LVL_EVENT1
///#define OP_PR_CAN					0x00000202	// ������~
///#define		OP_PR_CAN_LVL				LVL_EVENT1
///#define OP_PURGE_A					0x00000210	// �p�[�W�J�n�S�F
///#define		OP_PURGE_A_LVL				LVL_EVENT1
///#define OP_PURGE_K					0x00000211	// �p�[�W�J�n�u���b�N
///#define		OP_PURGE_K_LVL				LVL_EVENT1
///#define OP_PURGE_M					0x00000212	// �p�[�W�J�n�}�[���^
///#define		OP_PURGE_M_LVL				LVL_EVENT1
///#define OP_PURGE_C					0x00000213	// �p�[�W�J�n�V�A��
///#define		OP_PURGE_C_LVL				LVL_EVENT1
///#define OP_PURGE_Y					0x00000214	// �p�[�W�J�n�C�G���[
///#define		OP_PURGE_Y_LVL				LVL_EVENT1
///#define OP_PURGE_END				0x00000215	// �p�[�W�I��
///#define		OP_PURGE_END_LVL			LVL_EVENT1
///#define OP_PURGE_CAN				0x00000216	// �p�[�W���~
///#define		OP_PURGE_CAN_LVL			LVL_EVENT1

///#define OP_PR_TEST					0x00000220	// �e�X�g��
///#define		OP_PR_TEST_LVL				LVL_EVENT1

//		2.1.1.4 ��������
//			2.1.1.4.1 �p�[�W
#define	AU_PURGE_START				0x00000300	// �I�[�g�p�[�W�J�n
#define		AU_PURGE_START_LVL			LVL_EVENT1
#define	AU_PURGE_END				0x00000301	// �I�[�g�p�[�W�I��
#define		AU_PURGE_END_LVL			LVL_EVENT1
#define	AU_SUCK_WASH_START			0x00000302	// �L���b�v��̐��t�������J�n�i�I�ƃN���[�j���O�i�L���b�v���j��̕�z���j
#define		AU_SUCK_WASH_START_LVL		LVL_EVENT1
#define	AU_SUCK_WASH_END			0x00000303	// �L���b�v��̐��t�������I���i�I�ƃN���[�j���O�i�L���b�v���j��̕�z���j
#define		AU_SUCK_WASH_END_LVL		LVL_EVENT1

#define	MAINCTL_AUTO_PURGE_START	0x00000304	// �I�[�g�p�[�W�J�n�i���i������̓d���I�����j
#define		MAINCTL_AUTO_PURGE_START_LVL	LVL_EVENT1
#define	MAINCTL_AUTO_PURGE_END		0x00000305	// �I�[�g�p�[�W�I���i���i������̓d���I�����j
#define		MAINCTL_AUTO_PURGE_END_LVL		LVL_EVENT1

#define	AU_CIRCULATION_WHITE_ALL	0x00000310	// ���C���N�z�iAll White�j����I��	�����ł����j���[�ł�
#define		AU_CIRCULATION_WHITE_ALL_LVL	LVL_EVENT1

#define	AU_CIRCULATION_BTN_CANCEL	0x00000311	// ���C���N�z�L�����Z���i�L�����Z���{�^���ł̃L�����Z���j
#define		AU_CIRCULATION_BTN_CANCEL_LVL	LVL_EVENT1

#define	AU_CIRCULATION_MNT_CANCEL	0x00000312	// ���C���N�z�L�����Z���i���̗v���ɂ��L�����Z���J�[�g���b�W�������ꂽ�Ȃǁj
#define		AU_CIRCULATION_MNT_CANCEL_LVL	LVL_EVENT1

#define SW_CLOSURE_PURGE			0x00000320	// �\�t�g�X�C�b�`�����ɂ��I�ƃp�[�W
#define		SW_CLOSURE_PURGE_LVL				LVL_EVENT1
#define SW_CLOSURE_PURGE2			0x00000321	// �\�t�g�X�C�b�`�����ɂ����t�A�C���N�G���v�e�B���̏I�ƃp�[�W
#define		SW_CLOSURE_PURGE2_LVL			LVL_EVENT1

#define AU_CLOSURE_PURGE			0x00000330	// �����W���Ԍo�߂ɂ��I�ƃp�[�W
#define		AU_CLOSURE_PURGE_LVL				LVL_EVENT1
#define AU_CLOSURE_PURGE2			0x00000331	// �����W���Ԍo�߂ɂ����t�A�C���N�G���v�e�B���̏I�ƃp�[�W
#define		AU_CLOSURE_PURGE2_LVL			LVL_EVENT1


#define AU_CYCLOE_TEMP_VALUE		0x00000340	// ���x/���x���O(1���Ԏ����ł̏�������)
#define 	AU_CYCLOE_TEMP_VALUE_LVL		LVL_EVENT1

//			2.1.1.4.2 ���A���^�C���N���b�N


//		2.1.1.5 �񎟓I����
//			2.1.1.5.1 �v���e��

//			2.1.1.5.2 �N���A�����X�Z���T

//			2.1.1.5.3 �L���b�v

//			2.1.1.5.4 ���C�p

//			2.1.1.5.5 �|���v

//			2.1.1.5.6 �L�����b�W
#define CRG_LOG_OUT_LOCK_PWON		0x00000600	// �L�����b�W���d��ON���Ƀ��b�J�[�̊O�ɂ���
#define 	CRG_LOG_OUT_LOCK_PWON_LVL	LVL_EVENT2
#define CRG_LOG_REMOVE_OK			0x00000601	// �L�����b�W���V���[�g�������A�ċN����OK
#define 	CRG_LOG_REMOVE_OK_LVL		LVL_EVENT2
#define CRG_LOG_SPEED_CHECK			0x00000602	// �L�����b�W���x�m�F���O
#define 	CRG_LOG_SPEED_CHECK_LVL		LVL_EVENT2
#define CRG_LOG_SPEED_ADJUST		0x00000603	// �L�����b�W���x�������O
#define 	CRG_LOG_SPEED_ADJUST_LVL	LVL_EVENT1

//			2.1.1.5.7 �t���b�V���O

//			2.1.1.5.8 �o���u

//			2.1.1.5.10 �����e�t�@�[���X�V

//			2.1.1.5.11 CF�J�[�h����

//			2.1.1.5.12 GetJob

//			2.1.1.5.13 ���v�����g�f�[�^����


//		2.1.2 ���샍�O
//		2.1.2.1 �p�l���X�C�b�`

//		2.1.2.2 �P�[�u���ڑ�
//			2.1.2.2.1 �t�r�a�P�[�u��
//			2.1.2.2.2 1284�P�[�u��



//		2.1.2.3 ���j���[����
#define	MN_PURGE_NORM_ALL_CW		0x00001000		// �m�[�}���N���[�j���O���s�iAll Color & White�j
#define		MN_PURGE_NORM_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_NORM_ALL_C			0x00001001		// �m�[�}���N���[�j���O���s�iAll Color�j
#define		MN_PURGE_NORM_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_K				0x00001002		// �m�[�}���N���[�j���O���s�iK�j
#define		MN_PURGE_NORM_K_LVL			LVL_EVENT1
#define	MN_PURGE_NORM_M_C_Y			0x00001003		// �m�[�}���N���[�j���O���s�iMCY�j
#define		MN_PURGE_NORM_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_ALL_W			0x00001004		// �m�[�}���N���[�j���O���s�iAll White�j
#define		MN_PURGE_NORM_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_W1			0x00001005		// �m�[�}���N���[�j���O���s�iW1�j
#define		MN_PURGE_NORM_W1_LVL		LVL_EVENT1
#define	MN_PURGE_NORM_W2_4			0x00001006		// �m�[�}���N���[�j���O���s�iW234�j
#define		MN_PURGE_NORM_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_POWR_ALL_CW		0x00001010		// �p���t���N���[�j���O���s�iAll Color & White�j
#define		MN_PURGE_POWR_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_POWR_ALL_C			0x00001011		// �p���t���N���[�j���O���s�iAll Color�j
#define		MN_PURGE_POWR_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_K				0x00001012		// �p���t���N���[�j���O���s�iK�j
#define		MN_PURGE_POWR_K_LVL			LVL_EVENT1
#define	MN_PURGE_POWR_M_C_Y			0x00001013		// �p���t���N���[�j���O���s�iMCY�j
#define		MN_PURGE_POWR_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_ALL_W			0x00001014		// �p���t���N���[�j���O���s�iAll White�j
#define		MN_PURGE_POWR_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_W1			0x00001015		// �p���t���N���[�j���O���s�iW1�j
#define		MN_PURGE_POWR_W1_LVL		LVL_EVENT1
#define	MN_PURGE_POWR_W2_4			0x00001016		// �p���t���N���[�j���O���s�iW234�j
#define		MN_PURGE_POWR_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_HYPER_ALL_CW		0x00001020		// �X�[�p�[�N���[�j���O���s�iAll Color & White�j
#define		MN_PURGE_POWR_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_ALL_C		0x00001021		// �X�[�p�[�N���[�j���O���s�iAll Color�j
#define		MN_PURGE_HYPER_ALL_C_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_K			0x00001022		// �X�[�p�[�N���[�j���O���s�iK�j
#define		MN_PURGE_HYPER_K_LVL		LVL_EVENT1
#define	MN_PURGE_HYPER_M_C_Y		0x00001023		// �X�[�p�[�N���[�j���O���s�iMCY�j
#define		MN_PURGE_HYPER_M_C_Y_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_ALL_W		0x00001024		// �X�[�p�[�N���[�j���O���s�iAll White�j
#define		MN_PURGE_HYPER_ALL_W_LVL	LVL_EVENT1
#define	MN_PURGE_HYPER_W1			0x00001025		// �X�[�p�[�N���[�j���O���s�iW1�j
#define		MN_PURGE_HYPER_W1_LVL		LVL_EVENT1
#define	MN_PURGE_HYPER_W2_4			0x00001026		// �X�[�p�[�N���[�j���O���s�iW234�j
#define		MN_PURGE_HYPER_W2_4_LVL		LVL_EVENT1

#define	MN_PURGE_INIT_ALL_CW		0x00001030		// �����C���N�������s�iAll Color & White�j
#define		MN_PURGE_INIT_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_INIT_ALL_C			0x00001031		// �����C���N�������s�iAll Color�j
#define		MN_PURGE_INIT_ALL_C_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_K				0x00001032		// �����C���N�������s�iK�j
#define		MN_PURGE_INIT_K_LVL			LVL_EVENT1
#define	MN_PURGE_INIT_M_C_Y			0x00001033		// �����C���N�������s�iMCY�j
#define		MN_PURGE_INIT_M_C_Y_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_ALL_W			0x00001034		// �����C���N�������s�iAll White�j
#define		MN_PURGE_INIT_ALL_W_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_W1			0x00001035		// �����C���N�������s�iW1�j
#define		MN_PURGE_INIT_W1_LVL		LVL_EVENT1
#define	MN_PURGE_INIT_W2_4			0x00001036		// �����C���N�������s�iW234�j
#define		MN_PURGE_INIT_W2_4_LVL		LVL_EVENT1

#define MN_CAP_CLEAN_PURGE_C		0x00001041		// �L���b�v���i�I�ƃN���[�j���O�j���s�iColor�j
#define 	MN_CAP_CLEAN_PURGE_C_LVL	LVL_EVENT1
#define MN_CAP_CLEAN_PURGE_W		0x00001044		// �L���b�v���i�I�ƃN���[�j���O�j���s�iWhite�j
#define 	MN_CAP_CLEAN_PURGE_W_LVL	LVL_EVENT1

#define MN_DISCHARGELIQUID			0x00001050		// �L���b�v��̐��t�������i�I�ƃN���[�j���O�i�L���b�v���j��̕�z���j
#define 	MN_DISCHARGELIQUID_LVL		LVL_EVENT1

#define	MN_TUBE_CLEAN_ALL_CW		0x00001060		// �`���[�u�N���[�j���O���s�iAll Color & White�j
#define		MN_TUBE_CLEAN_ALL_CW_LVL	LVL_EVENT1
#define	MN_TUBE_CLEAN_ALL_C			0x00001061		// �`���[�u�N���[�j���O���s�iAll Color�j
#define		MN_TUBE_CLEAN_ALL_C_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_K				0x00001062		// �`���[�u�N���[�j���O���s�iK�j
#define		MN_TUBE_CLEAN_K_LVL			LVL_EVENT1
#define	MN_TUBE_CLEAN_YCM_CW		0x00001063		// �`���[�u�N���[�j���O���s�iMCY�j
#define		MN_TUBE_CLEAN_YCM_CW_LVL	LVL_EVENT1
#define	MN_TUBE_CLEAN_ALL_W			0x00001064		// �`���[�u�N���[�j���O���s�iAll White�j
#define		MN_TUBE_CLEAN_ALL_W_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_W1			0x00001065		// �`���[�u�N���[�j���O���s�iW1�j
#define		MN_TUBE_CLEAN_W1_LVL		LVL_EVENT1
#define	MN_TUBE_CLEAN_W2_4			0x00001066		// �`���[�u�N���[�j���O���s�iW234�j
#define		MN_TUBE_CLEAN_W2_4_LVL		LVL_EVENT1

#define MN_HEAD_CLEAN_ALL_W			0x00001074		// �w�b�h���iAll White�j
#define		MN_HEAD_CLEAN_ALL_W_LVL		LVL_EVENT1
#define MN_HEAD_CLEAN_W1			0x00001075		// �w�b�h���iW1�j
#define		MN_HEAD_CLEAN_W1_LVL		LVL_EVENT1
#define MN_HEAD_CLEAN_W2_4			0x00001076		// �w�b�h���iW234�j
#define		MN_HEAD_CLEAN_W2_4_LVL		LVL_EVENT1

#define	MN_LOAD_WHITE_ALL			0x00001084		// �w�b�h����̃C���N�ē����iAll White�j
#define		MN_LOAD_WHITE_ALL_LVL		LVL_EVENT1
#define	MN_LOAD_WHITE_W1			0x00001085		// �w�b�h����̃C���N�ē����iW1�j
#define		MN_LOAD_WHITE_W1_LVL		LVL_EVENT1
#define	MN_LOAD_WHITE_W2_4			0x00001086		// �w�b�h����̃C���N�ē����iW234�j
#define		MN_LOAD_WHITE_W2_4_LVL		LVL_EVENT1

#define	MN_REFRESH_WHITE_ALL		0x00001094		// ���C���N����ւ��i�m�[�}���j�iAll White�j
#define		MN_REFRESH_WHITE_ALL_LVL	LVL_EVENT1
#define	MN_REFRESH_WHITE_W1			0x00001095		// ���C���N����ւ��i�m�[�}���j�iW1�j
#define		MN_REFRESH_WHITE_W1_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE_W2_4		0x00001096		// ���C���N����ւ��i�m�[�}���j�iW234�j
#define		MN_REFRESH_WHITE_W2_4_LVL	LVL_EVENT1

#define	MN_REFRESH_WHITE_PW_ALL		0x00001104		// ���C���N����ւ��i�p���t���j�iAll White�j
#define		MN_REFRESH_WHITE_PW_ALL_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE__PW_W1		0x00001105		// ���C���N����ւ��i�p���t���j�iW1�j
#define		MN_REFRESH_WHITE__PW_W1_LVL		LVL_EVENT1
#define	MN_REFRESH_WHITE_PW_W2_4	0x00001106		// ���C���N����ւ��i�p���t���j�iW234�j
#define		MN_REFRESH_WHITE_PW_W2_4_LVL	LVL_EVENT1

///#define	MN_CIRCULATION_WHITE_ALL	0x00001114		// ���C���N�z�iAll White�j
///#define		MN_CIRCULATION_WHITE_ALL_LVL	LVL_EVENT1
///#define	MN_CIRCULATION_WHITE_W1		0x00001115		// ���C���N�z�iW1�j
///#define		MN_CIRCULATION_WHITE_W1_LVL		LVL_EVENT1
///#define	MN_CIRCULATION_WHITE_W2_4	0x00001116		// ���C���N�z�iW234�j
///#define		MN_CIRCULATION_WHITE_W2_4_LVL	LVL_EVENT1

#define	MN_PURGE_EXHAUST_ALL_CW		0x00001120		// �r�C�N���[�j���O���s�iAll Color & White�j
#define		MN_PURGE_EXHAUST_ALL_CW_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_ALL_C		0x00001121		// �r�C�N���[�j���O���s�iAll Color�j
#define		MN_PURGE_EXHAUST_ALL_C_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_K			0x00001122		// �r�C�N���[�j���O���s�iK�j
#define		MN_PURGE_EXHAUST_K_LVL		LVL_EVENT1
#define	MN_PURGE_EXHAUST_M_C_Y		0x00001123		// �r�C�N���[�j���O���s�iMCY�j
#define		MN_PURGE_EXHAUST_M_C_Y_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_ALL_W		0x00001124		// �r�C�N���[�j���O���s�iAll White�j
#define		MN_PURGE_EXHAUST_ALL_W_LVL	LVL_EVENT1
#define	MN_PURGE_EXHAUST_W1			0x00001125		// �r�C�N���[�j���O���s�iW1�j
#define		MN_PURGE_EXHAUST_W1_LVL		LVL_EVENT1
#define	MN_PURGE_EXHAUST_W2_4		0x00001126		// �r�C�N���[�j���O���s�iW234�j
#define		MN_PURGE_EXHAUST_W2_4_LVL	LVL_EVENT1

#define	MN_REPLACE_HEAD_CMYK			0x00001201		// �w�b�h�����iColor�j
#define		MN_REPLACE_HEAD_CMYK_LVL		LVL_EVENT1
#define	MN_REPLACE_HEAD_W				0x00001204		// �w�b�h�����iWhite�j
#define		MN_REPLACE_HEAD_W_LVL			LVL_EVENT1

#define	MN_REPLACE_HEAD_CMYK_CANCEL		0x00001211		// �w�b�h�����L�����Z���iColor�j
#define		MN_REPLACE_HEAD_CMYK_CANCEL_LVL	LVL_EVENT1
#define	MN_REPLACE_HEAD_W_CANCEL		0x00001214		// �w�b�h�����L�����Z���iWhite�j
#define		MN_REPLACE_HEAD_W_CANCEL_LVL	LVL_EVENT1

#define MN_REPLACE_HEAD_C_INK_LOAD		0x00001221		// �w�b�h������̃C���N�����iColor�j
#define 	MN_REPLACE_HEAD_C_INK_LOAD_LVL	LVL_EVENT1
#define MN_REPLACE_HEAD_W_INK_LOAD		0x00001224		// �w�b�h������̃C���N�����iWhite�j
#define 	MN_REPLACE_HEAD_W_INK_LOAD_LVL	LVL_EVENT1

#define	MN_TEST_PRINT				0x00001230		// �e�X�g���
#define		MN_TEST_PRINT_LVL			LVL_EVENT1
#define	MN_SOLID_PRINT				0x00001231		// SOLID PRINT
#define		MN_SOLID_PRINT_LVL			LVL_EVENT1

#define	MN_CR_SPEED_ADJUST			0x00001240		// CR���x�p�����[�^����
#define		MN_CR_SPEED_ADJUST_LVL		LVL_EVENT1
///#define	MN_CR_ORIGIN_ADJUST			0x00001241		// CR���_�Z���T�[����
///#define		MN_CR_ORIGIN_ADJUST_LVL		LVL_EVENT1
///#define	MN_TEMP_SNSR_ADJUST			0x00001242		// ���x�Z���T�[�␳
///#define		MN_TEMP_SNSR_ADJUST_LVL		LVL_EVENT1
#define MN_X_PRINT_ADJUST			0x00001243		// X��������ʒu����
#define		MN_X_PRINT_ADJUST_LVL		LVL_EVENT1
#define MN_Y_PRINT_ADJUST			0x00001244		// Y��������ʒu����
#define		MN_Y_PRINT_ADJUST_LVL		LVL_EVENT1

///#define	MNT_MNU_EXC_PARTS			0x00001250		// ��������e���i�̌���
///#define		MNT_MNU_EXC_PARTS_LVL		LVL_EVENT1
#define MNT_PART_CLEANING			0x00001254		// �����e���i�|������
#define 	MNT_PART_CLEANING_LVL		LVL_EVENT1
#define MNT_PART_CLEANING_CANCEL	0x00001255		// �����e���i�|������ �L�����Z��
#define 	MNT_PART_CLEANING_CANCEL_LVL		LVL_EVENT1

#define	MN_AR3_FILE_LOAD			0x00001260		// USB����������AR3�t�@�C�����[�h
#define		MN_AR3_FILE_LOAD_LVL		LVL_EVENT1
#define	MN_LOG_SAVE_USB				0x00001261		// USB�������ւ̃��O�����o��
#define		MN_LOG_SAVE_USB_LVL			LVL_EVENT1
#define	MN_FIRM_UPDATE_USB			0x00001262		// USB����������t�@�[���E�F�A�X�V
#define		MN_FIRM_UPDATE_USB_LVL		LVL_EVENT1

#define	MN_FIRM_VER					0x00001270		// �t�@�[���E�F�A�o�[�W�����\��
#define		MN_FIRM_VER_LVL				LVL_EVENT2
///#define	MN_SHOW_PRT_NUM				0x00001271		// �ݐψ�������\��
///#define		MN_SHOW_PRT_NUM_LVL			LVL_EVENT2
///#define	MN_SHOW_TEMPERATURE			0x00001272		// ���x/���x���̕\��
///#define		MN_SHOW_TEMPERATURE_LVL		LVL_EVENT2
///#define	MN_SHOW_COM_SETTING			0x00001273		// �ʐM�ݒ�̊m�F
///#define		MN_SHOW_COM_SETTING_LVL		LVL_EVENT2

#define	MN_LANGUAGE_SET_ENG			0x00001280		// �\��������p��ɃZ�b�g
#define		MN_LANGUAGE_SET_ENG_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_SPA			0x00001281		// �\��������X�y�C����ɃZ�b�g
#define		MN_LANGUAGE_SET_SPA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_FRA			0x00001282		// �\��������t�����X��ɃZ�b�g
#define		MN_LANGUAGE_SET_FRA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_GER			0x00001283		// �\��������h�C�c��ɃZ�b�g
#define		MN_LANGUAGE_SET_GER_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_ITA			0x00001284		// �\��������C�^���A��ɃZ�b�g
#define		MN_LANGUAGE_SET_ITA_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_JPN			0x00001285		// �\���������{��ɃZ�b�g
#define		MN_LANGUAGE_SET_JPN_LVL		LVL_EVENT1
#define	MN_LANGUAGE_SET_CHN			0x00001286		// �\������𒆍���i�ȑ̎��j�ɃZ�b�g
#define		MN_LANGUAGE_SET_CHN_LVL		LVL_EVENT1

#define	MN_SET_1WAY_AUTO			0x00001290		// ��������������[�h�ݒ�
#define		MN_SET_1WAY_AUTO_LVL		LVL_EVENT1
#define	MN_SET_1WAY_OFF				0x00001291		// �o����������[�h�ݒ�
#define		MN_SET_1WAY_OFF_LVL			LVL_EVENT1
#define	MN_SET_1WAY_FORWARD			0x00001292		// �Е���������[�h�ݒ�(Forward)
#define		MN_SET_1WAY_FORWARD_LVL		LVL_EVENT1
#define	MN_SET_1WAY_BACKWARD		0x00001293		// �Е���������[�h�ݒ�(Backward)
#define		MN_SET_1WAY_BACKWARD_LVL	LVL_EVENT1

#define	MN_TEMPERATURE_SET_F		0x00001300		// �\�����x���؎��ɃZ�b�g
#define		MN_TEMPERATURE_SET_F_LVL	LVL_EVENT2
#define	MN_TEMPERATURE_SET_C		0x00001301		// �\�����x��ێ��ɃZ�b�g
#define		MN_TEMPERATURE_SET_C_LVL	LVL_EVENT2

#define	MN_341_MODE_OFF				0x00001310		// ���x�~���[�h�i341���[�h�j��OFF�ɃZ�b�g
#define		MN_341_MODE_OFF_LVL			LVL_EVENT1
#define	MN_341_MODE_ON				0x00001311		// ���x�~���[�h�i341���[�h�j��ON�ɃZ�b�g
#define		MN_341_MODE_ON_LVL			LVL_EVENT1

#define	MN_JOB_DEL_MODE_OFF			0x00001321		// �W���u�폜���[�h��OFF�ɃZ�b�g
#define		MN_JOB_DEL_MODE_OFF_LVL		LVL_EVENT1
#define	MN_JOB_DEL_MODE_ON			0x00001322		// �W���u�폜���[�h��ON�i�����폜�j�ɃZ�b�g
#define		MN_JOB_DEL_MODE_ON_LVL		LVL_EVENT1

#define	MN_SET_SPEAKER_VOL			0x00001330		// �X�s�[�J�{�����[���ݒ�
#define		MN_SET_SPEAKER_VOL_LVL		LVL_EVENT2
///#define	MN_SET_LCD_CONTRAST			0x00001331		// LCD�R���g���X�g�ݒ�
///#define		MN_SET_LCD_CONTRAST_LVL		LVL_EVENT2
#define	MN_SET_LOG_LEVEL			0x00001332		// ���O���x���ݒ�
#define		MN_SET_LOG_LEVEL_LVL		LVL_EVENT1
#define	MN_SET_SCREEN_TIMEOUT_NON	0x00001333		// ������ʏ����i�����������Ȃ��j
#define		MN_SET_SCREEN_TIMEOUT_NON_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_5M	0x00001334		// ������ʏ����i�T���j
#define		MN_SET_SCREEN_TIMEOUT_5M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_10M	0x00001335		// ������ʏ����i�P�O���j
#define		MN_SET_SCREEN_TIMEOUT_10M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_15M	0x00001336		// ������ʏ����i�P�T���j
#define		MN_SET_SCREEN_TIMEOUT_15M_LVL		LVL_EVENT2
#define	MN_SET_SCREEN_TIMEOUT_30M	0x00001337		// ������ʏ����i�R�O���j
#define		MN_SET_SCREEN_TIMEOUT_30M_LVL		LVL_EVENT2

#define	MN_SET_AUTO_CLN				0x00001340		// �I�[�g�p�[�W�Ԋu�i����)�ݒ�
#define		MN_SET_AUTO_CLN_LVL			LVL_EVENT1
#define	MN_SET_FLUSH_CYCLE			0x00001341		// �t���b�V���O�Ԋu�i�p�x)�ݒ�
#define		MN_SET_FLUSH_CYCLE_LVL		LVL_EVENT1
#define	MN_SET_FLUSH_DROPS			0x00001342		// �t���b�V���O�f�o�ʐݒ�
#define		MN_SET_FLUSH_DROPS_LVL		LVL_EVENT1
///#define	MN_SET_REFRESH_W			0x00001343		// ���C���N����ւ� �C���N�p���ʐݒ�
///#define		MN_SET_REFRESH_W_LVL		LVL_EVENT1
#define MN_SET_AUTO_PURGE_SET_BEFORE	0x00001344	// �I�[�g�p�[�W�J�n�����i����O�Ɏ��{�j
#define 	MN_SET_AUTO_PURGE_SET_BEFORE_LVL	LVL_EVENT1
#define MN_SET_AUTO_PURGE_SET_AFTER		0x00001345	// �I�[�g�p�[�W�J�n�����i�����Ɏ��{�j
#define 	MN_SET_AUTO_PURGE_SET_AFTER_LVL		LVL_EVENT1

///#define	MN_PUMP_PRESS_CAP			0x00001350		// �|���v����������s�i�L���b�v��ő���j
///#define		MN_PUMP_PRESS_CAP_LVL		LVL_EVENT1
///#define	MN_PUMP_PRESS_CR			0x00001351		// �|���v����������s�i�L�����b�W��ő���j
///#define		MN_PUMP_PRESS_CR_LVL		LVL_EVENT1

#define MN_MENU_TIMEOUT_SET_MIN		0x00001355		// ���j���[�^�C���A�E�g�ݒ� �P��
#define		MN_MENU_TIMEOUT_SET_MIN_LVL		LVL_EVENT1
#define MN_MENU_TIMEOUT_SET_MIDDLE	0x00001356		// ���j���[�^�C���A�E�g�ݒ� �R��
#define		MN_MENU_TIMEOUT_SET_MIDDLE_LVL	LVL_EVENT1
#define MN_MENU_TIMEOUT_SET_MAX		0x00001357		// ���j���[�^�C���A�E�g�ݒ� �T��
#define		MN_MENU_TIMEOUT_SET_MAX_LVL		LVL_EVENT1

#define MN_MENU_LOW_TEMP_PRINT_ENABLE	0x00001360	// �ቷ���̈������ݒ�@�L��
#define		MN_MENU_LOW_TEMP_PRINT_ENABLE_LVL		LVL_EVENT1
#define MN_MENU_LOW_TEMP_PRINT_DISABLE	0x00001361	// �ቷ���̈������ݒ�@����
#define		MN_MENU_LOW_TEMP_PRINT_DISABLE_LVL		LVL_EVENT1

///#define	MN_RESET_HEAD_FILTER_K		0x00001360		// �j�̃w�b�h�t�B���^�[�������[�j���O�̃��Z�b�g�����s
///#define		MN_RESET_HEAD_FILTER_K_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_M		0x00001361		// �l�̃w�b�h�t�B���^�[�������[�j���O�̃��Z�b�g�����s
///#define		MN_RESET_HEAD_FILTER_M_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_C		0x00001362		// �b�̃w�b�h�t�B���^�[�������[�j���O�̃��Z�b�g�����s
///#define		MN_RESET_HEAD_FILTER_C_LVL	LVL_EVENT1
///#define	MN_RESET_HEAD_FILTER_Y		0x00001363		// �x�̃w�b�h�t�B���^�[�������[�j���O�̃��Z�b�g�����s
///#define		MN_RESET_HEAD_FILTER_Y_LVL	LVL_EVENT1

///#define MN_RESET_FANFILTER		0x00001365		// �t�@���t�B���^�[��������
///#define 	MN_RESET_FANFILTER_LVL			LVL_EVENT1
///#define MN_RESET_ABSORBER		0x00001366		// �t���b�V���O�p�z���ތ�������
///#define 	MN_RESET_ABSORBER_LVL			LVL_EVENT1

#define	MN_RECEIVING_SETTING_OFF	0x00001370		// �������M�E��M����� ����
#define		MN_RECEIVING_SETTING_OFF_LVL		LVL_EVENT1
#define	MN_RECEIVING_SETTING_ON		0x00001371		// �������M�E��M����� �L��
#define		MN_RECEIVING_SETTING_ON_LVL			LVL_EVENT1

#define MN_EXCHANGE_FILTER_K		0x0001380		// �j�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_K_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_Y		0x0001381		// �x�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_Y_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_C		0x0001382		// �b�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_C_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_M		0x0001383		// �l�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_M_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W1		0x0001384		// �v�P�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_W1_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W2		0x0001385		// �v�Q�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_W2_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W3		0x0001386		// �v�R�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_W3_LVL		LVL_EVENT1
#define MN_EXCHANGE_FILTER_W4		0x0001387		// �v�S�̃t�B���^�[����
#define		MN_EXCHANGE_FILTER_W4_LVL		LVL_EVENT1

#define MN_EXCHANGE_FILTER_CANCEL	0x0001388		// �t�B���^�[�����L�����Z��
#define		MN_EXCHANGE_FILTER_CANCEL_LVL		LVL_EVENT1

#define MN_EXCHANGE_FILTER_K_LOAD_INK	0x0001390		// �j�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_K_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_Y_LOAD_INK	0x0001391		// �x�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_Y_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_C_LOAD_INK	0x0001392		// �b�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_C_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_M_LOAD_INK	0x0001393		// �l�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_M_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W1_LOAD_INK	0x0001394		// �v�P�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_W1_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W2_LOAD_INK	0x0001395		// �v�Q�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_W2_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W3_LOAD_INK	0x0001396		// �v�R�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_W3_LOAD_INK_LVL	LVL_EVENT1
#define MN_EXCHANGE_FILTER_W4_LOAD_INK	0x0001397		// �v�S�̃t�B���^�[������̃C���N�ē���
#define		MN_EXCHANGE_FILTER_W4_LOAD_INK_LVL	LVL_EVENT1

//�@�ȉ�GT-X �̃��j���[���ڂ̐V�K�ǉ�����
#define	MN_RECEIVE_HISTORY			0x00001400		// ��M����
#define		MN_RECEIVE_HISTORY_LVL				LVL_EVENT1


#define	MN_MAITE_UNIT_CLEANING		0x00001450		// �����e���
#define		MN_MAITE_UNIT_CLEANING_LVL			LVL_EVENT1
#define MN_IP_ADDRESS_ASSIGN		0x00001460		// IP �A�h���X�ݒ�
#define		MN_IP_ADDRESS_ASSIGN_LVL			LVL_EVENT1
#define	MN_BACKLIGHT				0x00001471		// �o�b�N���C�g����
#define		MN_BACKLIGHT_LVL					LVL_EVENT1

#define	MN_RESTORE_DATA_SET			0x00001480		// ���X�g�A���s
#define		MN_RESTORE_DATA_SET_LVL				LVL_EVENT1

#define	MN_WIPER_CLEANER_REPLACE_C	0x00001500		// ���C�p�[�N���[�i�[�����@�J���[
#define		MN_WIPER_CLEANER_REPLACE_C_LVL	LVL_EVENT1
#define	MN_WIPER_CLEANER_REPLACE_W	0x00001501		// ���C�p�[�N���[�i�[�����@��
#define		MN_WIPER_CLEANER_REPLACE_W_LVL	LVL_EVENT1
///#define	MN_WIPER_BLADE_REPLACE_C	0x00001510		// ���C�p�[�����@�J���[
///#define		MN_WIPER_BLADE_REPLACE_C_LVL	LVL_EVENT1
///#define	MN_WIPER_BLADE_REPLACE_W	0x00001511		// ���C�p�[�����@��
///#define		MN_WIPER_BLADE_REPLACE_W_LVL	LVL_EVENT1
#define	MN_FLUSHING_FROM_C_RESET	0x00001520		// �t���b�V���O�t�H�[�����Z�b�g �J���[
#define		MNFLUSHING_FROM_C_RESET_LVL		LVL_EVENT1
#define	MN_FLUSHING_FROM_W_RESET	0x00001521		// �t���b�V���O�t�H�[�����Z�b�g ��
#define		MNFLUSHING_FROM_W_RESET_LVL		LVL_EVENT1
#define MNT_CLEAN_CAPWIPE			0x00001530		// �L���b�v�^���C�p�[�|��
#define		MNT_CLEAN_CAPWIPE_LVL			LVL_EVENT1
#define MNT_CLEAN_NOZZLE			0x00001540		// �m�Y�����ʑ|��
#define		MNT_CLEAN_NOZZLE_LVL			LVL_EVENT1
#define	MN_FAN_FILTER_RESET			0x00001550		// �t�@���t�B���^�[���Z�b�g
#define		MN_FAN_FILTER_RESET_LVL			LVL_EVENT1
///#define MNT_CLEAN_CR_STRIP		0x00001560		// �G���R�[�_�[�X�g���b�v�|��
///#define		MNT_CLEAN_CR_STRIP_LVL		LVL_EVENT1

//		2.1.2.4 PC�R�}���h
#define	PC_PRT_JOB_START			0x00002000		// �v�����g�W���u��M�J�n
#define		PC_PRT_JOB_START_LVL		LVL_EVENT2
#define	PC_PRT_JOB_END				0x00002001		// �v�����g�W���u��M����
#define		PC_PRT_JOB_END_LVL			LVL_EVENT2
#define	PC_PRT_JOB_CANCEL			0x00002002		// �v�����g�W���u�L�����Z���I��
#define		PC_PRT_JOB_CANCEL_LVL		LVL_EVENT1
#define	PC_PRT_JOB_ERROR			0x00002003		// �v�����g�W���u�G���[�I��
#define		PC_PRT_JOB_ERROR_LVL		LVL_EVENT1
#define	PC_PRT_JOB_DELETE			0x00002004		// �v�����g�W���u�폜�v����M
#define		PC_PRT_JOB_DELETE_LVL		LVL_EVENT1

#define	PC_UPDATE_FIRM_PPC			0x00002010		// �X�V�pPPC�t�@�[���E�F�A��M
#define		PC_UPDATE_FIRM_PPC_LVL		LVL_EVENT1
#define	PC_UPDATE_FIRM_MNT			0x00002011		// �X�V�p�����e�t�@�[���E�F�A��M
#define		PC_UPDATE_FIRM_MNT_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_FONT			0x00002012		// �X�V�p�t�H���g�f�[�^��M
#define		PC_UPDATE_DATA_FONT_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_MES			0x00002013		// �X�V�p������f�[�^��M
#define		PC_UPDATE_DATA_MES_LVL		LVL_EVENT1
#define	PC_UPDATE_DATA_PRINT		0x00002014		// �X�V�p�e�X�g����f�[�^��M
#define		PC_UPDATE_DATA_PRINT_LVL	LVL_EVENT1
#define	PC_UPDATE_FIRM_HEAD_SAFFRON		0x00002015		// �X�V�p�w�b�h����T�t�����t�@�[���E�F�A��M
#define		PC_UPDATE_FIRM_HEAD_SAFFRON_LVL	LVL_EVENT1
#define	PC_UPDATE_FIRM_LCD_SAFFRON		0x00002016		// �X�V�pLCD����T�t�����t�@�[���E�F�A��M
#define		PC_UPDATE_FIRM_LCD_SAFFRON_LVL	LVL_EVENT1

#define	PC_EPPROM_WRITE				0x00002020		// PC�R�}���h�ɂ��EEPROM�u���b�N�X�V
#define		PC_EPPROM_WRITE_LVL			LVL_EVENT1

#define	PC_CLOCK_SET				0x00002030		// PC�R�}���h�ɂ�郊�A���^�C���N���b�N�����ݒ�
#define		PC_CLOCK_SET_LVL			LVL_EVENT1

#define	PC_SND_LOG					0x00002040		// PC�փ��O�f�[�^�𑗐M
#define		PC_SND_LOG_LVL				LVL_EVENT2
#define	PC_SND_EPPROM				0x00002041		// PC��EEPROM�u���b�N�f�[�^�𑗐M
#define		PC_SND_EPPROM_LVL			LVL_EVENT2
#define	PC_SND_EPPROM_LIST			0x00002042		// PC��EEPROM�u���b�N���X�g�𑗐M
#define		PC_SND_EPPROM_LIST_LVL		LVL_EVENT2

#define	PC_INIT_STATISTICS			0x00002050		// PC�R�}���h�ɂ��ғ��󋵏�����
#define		PC_INIT_STATISTICS_LVL		LVL_EVENT1

#define	PC_BY4_ADJUST				0x00002060		// PC�R�}���h�ɂ��f�o�^�C�~���O����
#define		PC_BY4_ADJUST_LVL			LVL_EVENT1
#define	PC_CR_SPEED_ADJUST			0x00002061		// PC�R�}���h�ɂ��CR�X�s�[�h����
#define		PC_CR_SPEED_ADJUST_LVL		LVL_EVENT1
#define	PC_CR_TEMP_ADJUST			0x00002062		// PC�R�}���h�ɂ������x�Z���T�[����
#define		PC_CR_TEMP_ADJUST_LVL		LVL_EVENT1
#define	PC_CW_POS_ADJUST			0x00002063		// PC�R�}���h�ɂ�锒�J���[�ʒu���킹
#define		PC_CW_POS_ADJUST_LVL		LVL_EVENT1
#define	PC_ORIGIN_ADJUST			0x00002064		// PC�R�}���h�ɂ�錴�_�ʒu����
#define		PC_ORIGIN_ADJUST_LVL		LVL_EVENT1
#define	PC_IPADDR_SET				0x00002065		// PC�R�}���h�ɂ��IPaddress�ݒ�
#define		PC_IPADDR_SET_LVL			LVL_EVENT1
#define	PC_SET_HEAD_RANK			0x00002066		// PC�R�}���h�ɂ��w�b�h�����N�ݒ�
#define		PC_SET_HEAD_RANK_LVL		LVL_EVENT1
#define	PC_SET_PRODUCT_STATUS		0x00002067		// PC�R�}���h�ɂ��g�ݗ��Ē��t���O�̕ύX
#define		PC_SET_PRODUCT_STATUS_LVL	LVL_EVENT1
#define	PC_SET_WHITE_OFF			0x00002068		// PC�R�}���h�ɂ�锒�x�~���[�h�̕ύX
#define		PC_SET_WHITE_OFF_LVL		LVL_EVENT1
#define	PC_SET_INITIAL_PUEGE_DONE	0x00002069		// PC�R�}���h�ɂ�鏉���������[�h�̕ύX
#define		PC_SET_INITIAL_PUEGE_DONE_LVL	LVL_EVENT1


///#define	PC_PRINT_DATA_DELETE		0x00002070		// ��M�ς݈���f�[�^�̏���
///#define		PC_PRINT_DATA_DELETE_LVL	LVL_EVENT1

#define	PC_WRITE_18_CODES			0x00002071		// PC�R�}���h�ɂ��18���R�[�h�̏�������
#define		PC_WRITE_18_CODES_LVL		LVL_EVENT1
#define	PC_WRITE_SERIAL_NUM			0x00002072		// PC�R�}���h�ɂ��V���A���i���o�[�̏�������
#define		PC_WRITE_SERIAL_NUM_LVL		LVL_EVENT1
#define	PC_WRITE_MAC_ACCRESS		0x00002073		// PC�R�}���h�ɂ��MAC�A�h���X�̏�������
#define		PC_WRITE_MAC_ACCRESS_LVL	LVL_EVENT1

#define	PC_CR_FWD_RVS_ADJUST			0x00002080		// PC�R�}���h�ɂ��CR�̉�������̈ʒu���킹
#define		PC_CR_FWD_RVS_ADJUST_LVL		LVL_EVENT1
#define	PC_BELT_HEAD_ADJUST			0x00002090		// PC�R�}���h�ɂ��x���g�s�b�`�E�w�b�h���␳
#define		PC_BELT_HEAD_ADJUST_LVL		LVL_EVENT1
/*-------------------------------------------------------*/
//	2.2 �X�e�[�^�X���O(bit15-12:0001)
//		2.2.1 �C���N�J�[�g���b�W�̏��
///#define STS_INK_CARTRIDGE			0x00003000		// �C���N�c�ʃZ���T�̌��ݒl
///#define		STS_INK_CARTRIDGE_LVL		LVL_EVENT1

//		2.2.2 �p�C���N�^���N�̏��

//		2.2.3 ���C�p�[�N���[�i�̏��

//		2.2.4 �J�o�[�Z���T�̏��

//		2.2.5 �v���e����ʃZ���T�̏��

//		2.2.6 �v���e���ʒu�Z���T�̏��

//		2.2.7 �N���A�����X�Z���T�̏��

//		2.2.8 �L�����b�W�̏��

//		2.2.9 ���x�Z���T�̏��
///#define	STS_SUR_TEMP				0x00003800	// �󎚕ۏ؉��x
///#define		STS_SUR_TEMP_LVL			LVL_EVENT1
											//	�t�����T�C�Y�F���e�� SH-BY�ʐM�R�}���h
///#define		STS_SUR_TEMP_ADDSZ			4	//	                0x8005(����I��)��t1,st�Ɠ���

//		2.2.10 �v���O�������s�̏��

//		2.2.11 ���A���^�C���N���b�N�̏��
///#define	STS_RTC_STOP				0x00004000	// RTC���䃌�W�X�^�̔��U��~�r�b�g�������Ă���
///#define		STS_RTC_STOP_LVL			LVL_EVENT1


/*-------------------------------------------------------*/
//	2.3 �����e�i���X���O(bit15-12:0010)
//		2.3.1 ���j���[����̃����e�i���X
//			2.3.1.1 ���j���[�ł̐ݒ�

//			2.3.1.2 ���j���[�ł̌���
//				2.3.1.2.1 �w�b�h����
//				2.3.1.2.2 ���C�p�u���[�h����
//				2.3.1.2.3 ���C�p�[�N���[�j���O�J�Z�b�g����

//			2.3.1.3 ���j���[�ł̌���
//				2.3.1.3.1 �\���m�C�h����
//				2.3.1.3.2 �w�b�h����
//				2.3.1.3.3 �����e�i���X���j�b�g����
//				2.3.1.3.4 �v���e������

//			2.3.1.4 ���j���[�ł̏��擾

//			2.3.1.5 ���j���[�ł̃v���O�����X�V

//			2.3.1.6 ���j���[�ł̑|��


//		2.3.2 �p�l���{�^���ɂ�鑀��
//			2.3.1.1 �P�@�\�{�^��


//		2.3.3 �p�����[�^�X�V
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
//	2.4 �C���t�H���[�V����(bit15-12:0011)
//		2.4.1 �V�X�e���C���t�H���[�V����
//
#define	INF_PARM_INIT_B11			0x00007000	// EEPROM Block 11 ������������
#define		INF_PARM_INIT_B11_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B12			0x00007001	// EEPROM Block 12 ������������
#define		INF_PARM_INIT_B12_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B13			0x00007002	// EEPROM Block 13������������
#define		INF_PARM_INIT_B13_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B14			0x00007003	// EEPROM Block 14 ������������
#define		INF_PARM_INIT_B14_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B15			0x00007004	// EEPROM Block 15 ������������
#define		INF_PARM_INIT_B15_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B16			0x00007005	// EEPROM Block 16 ������������
#define		INF_PARM_INIT_B16_LVL		LVL_EVENT1
#define	INF_PARM_INIT_B17			0x00007006	// EEPROM Block 17 ������������
#define		INF_PARM_INIT_B17_LVL		LVL_EVENT1

///#define INF_FROM_LG_SAVE			0x00007105	// �t���b�V�������Ƀ��O�ۑ�����
///#define		INF_FROM_LG_SAVE_LVL		LVL_EVENT1
#define INF_LOG_LOST				0x00007107	// ���O�o�b�t�@�I�[�ɒB����
#define		INF_LOG_LOST_LVL			LVL_EVENT1
///#define	INF_DBG_COMMENT				0x00007109
///#define		INF_DBG_COMMENT_LVL			LVL_INFO


//======================================================//
//	��͗p�ғ����O										//
//======================================================//

//--------------------------------------//
//	����f�[�^���[�h�����iI/F���̂݁j			//	// ���[�h��������ARP�f�[�^�̏����
//--------------------------------------//	// 9000�`90XX�̃��O���S�ĂقژA�����ċL�^�����
///#define	ARP_LOADED_JOB_ID			0x00009000			// ���O�A�ԁA�W���uID�A�iVer,Source,CMYK,WxN�j�A�iBlock,Platen,�������M,*�j
///#define		ARP_LOADED_JOB_ID_LVL		LVL_EVENT1
///#define	ARP_LOADED_PRT_NUM			0x00009001			// ���O�A�ԁA����w������
///#define		ARP_LOADED_PRT_NUM_LVL		LVL_EVENT1
///#define	ARP_LOADED_SPECIAL			0x00009002			// ���O�A�ԁA�������w��
///#define		ARP_LOADED_SPECIAL_LVL		LVL_EVENT1
///#define	ARP_LOADED_PLATEN			0x00009003			// ���O�A�ԁA�v���e����
///#define		ARP_LOADED_PLATEN_LVL		LVL_EVENT1
///#define	ARP_LOADED_DOT_CMYK			0x00009004			// ���O�A�ԁA�C���N���ʒlK�A�C���N���ʒlM�A�C���N���ʒlC�A�C���N���ʒlY
///#define		ARP_LOADED_DOT_CMYK_LVL		LVL_EVENT1
///#define	ARP_LOADED_DOT_WWWW			0x00009005			// ���O�A�ԁA�C���N���ʒlW1�A�C���N���ʒlW2�A�C���N���ʒlW3�A�C���N���ʒlW4
///#define		ARP_LOADED_DOT_WWWW_LVL		LVL_EVENT1
///#define	ARP_LOADED_DRV_SET			0x00009006			// ���O�A�ԁA�h���C�o�ݒ��
///#define		ARP_LOADED_DRV_SET_LVL		LVL_EVENT1
///#define	ARP_LOADED_GRAPHIC_BLK		0x00009007			// ���O�A�ԁA�i�u���b�N�ԍ�,CMYK��,W��,Interlace�j�A�iRepeat,Compress,Course,*�j�A�i2xResolveH,2xResolveV�j�A�iPileUp,WaitFlg,WaitSec,*�j
///#define		ARP_LOADED_GRAPHIC_BLK_LVL	LVL_EVENT1
#define	ARP_LOADED_JOB_NAME			0x00009008			// ���O�A�ԁA�W���u�l�[��
#define		ARP_LOADED_JOB_NAME_LVL		LVL_EVENT1
#define	ARP_LOADED_JOB_COMMENT		0x00009009			// ���O�A�ԁA�W���u�R�����g
#define		ARP_LOADED_JOB_COMMENT_LVL	LVL_EVENT1
///#define	ARP_LOADED_FILE_NAME		0x00009010			// ���O�A�ԁAAR3�t�@�C����
///#define		ARP_LOADED_FILE_NAME_LVL	LVL_EVENT2

// ���O�G���A�̍팸�p��GT-X�p�ɐV��
#define	ARP_LOADED_JOB_ALL			0x00009011			// 0x9000�`0x9006�܂ł�1�ɂ܂Ƃ߂����O
#define		ARP_LOADED_JOB_ALL_LVL			LVL_EVENT1
#define	ARP_LOADED_GRAPHIC_BLK_ALL	0x00009012			// �O���t�B�b�N�u���b�N���(0x9007)��1�ɂ܂Ƃ߂����O
#define		ARP_LOADED_GRAPHIC_BLK_ALL_LVL	LVL_EVENT1
								//  0x00009013�`0x00009099 System Reserved

//--------------------------------------//
//	���[�U�[�̈������						//
//--------------------------------------//
#define	USER_PRINT_START			0x00009100	// ����J�n		���O�A�ԁA�W���uID�A�i��M�����,*,*,*�j
#define		USER_PRINT_START_LVL		LVL_EVENT1
#define	USER_PRINT_FINISH			0x00009101	// �������		���O�A�ԁA�W���uID�A�����x�A���x�A�J���[�w�b�h VTEMP�A�J���[�w�b�h �T�[�~�X�^�A�z���C�g�w�b�h VTEMP�A�z���C�g�w�b�h �T�[�~�X�^�A�����CR�ō����x�A�����CR�Œᑬ�x�A�f�o�J�E���g[8�Fx�咆���h�b�g]
#define		USER_PRINT_FINISH_LVL		LVL_EVENT1
#define	USER_PRINT_STOP				0x00009102	// ������~�icancel, obstacle error�j		��Ɠ���
#define		USER_PRINT_STOP_LVL			LVL_EVENT1

//--------------------------------------//
//	�����e�i���X�V�[�P���X���s					//
//--------------------------------------//
#define	MNT_SEQUENCE_START			0x00009200	// �����e�i���X�V�[�P���X�J�n	�V�[�P���X��ʁA�ΏېF�A�J�n����
#define		MNT_SEQUENCE_START_LVL		LVL_EVENT1
#define	MNT_SEQUENCE_END			0x00009201	// �����e�i���X�V�[�P���X�I��	�V�[�P���X��ʁA�ΏېF�A�I�����R
#define		MNT_SEQUENCE_END_LVL		LVL_EVENT1


// �ʏ��͒�`���Ȃ�


/*-------------------------------------------------------*/
//	2.5 �G���[���O
/*-------------------------------------------------------*/
//		2.5.1 ����~�X(bit15-12:0000)
/*-------------------------------------------------------*/
//		2.5.2 �^�p���[�j���O(bit15-12:0001)
//			2.5.2.1 �C���N��

#define WRN_WASH_BOTTLE_EMPTY			0x00001000	//	���{�g���G���v�e�B(���[�j���O)
#define 		WRN_WASH_BOTTLE_EMPTY_LVL	LVL_WARNING
#define ERR_WASH_BOTTLE_EMPTY			0x00001001	//	���{�g���G���v�e�B(�G���[)
#define 		ERR_WASH_BOTTLE_EMPTY_LVL	LVL_MIDDLE

///#define WRN_INK_FEW_K				0x00001000	// �C���N�j�A�G���v�e�B �u���b�N
///#define		WRN_INK_FEW_K_LVL			LVL_WARNING
///#define WRN_INK_FEW_M				0x00001001	// �C���N�j�A�G���v�e�B �}�[���^
///#define		WRN_INK_FEW_M_LVL			LVL_WARNING
///#define WRN_INK_FEW_C				0x00001002	// �C���N�j�A�G���v�e�B �V�A��
///#define		WRN_INK_FEW_C_LVL			LVL_WARNING
///#define WRN_INK_FEW_Y				0x00001003	// �C���N�j�A�G���v�e�B �C�G���[
///#define		WRN_INK_FEW_Y_LVL			LVL_WARNING
///#define WRN_INK_FEW_W1				0x00001004	// �C���N�j�A�G���v�e�B  �z���C�g�P
///#define		WRN_INK_FEW_W1_LVL			LVL_WARNING
///#define WRN_INK_FEW_W2				0x00001005	// �C���N�j�A�G���v�e�B  �z���C�g�Q
///#define		WRN_INK_FEW_W2_LVL			LVL_WARNING
///#define WRN_INK_FEW_W3				0x00001006	// �C���N�j�A�G���v�e�B  �z���C�g�R
///#define		WRN_INK_FEW_W3_LVL			LVL_WARNING
///#define WRN_INK_FEW_W4				0x00001007	// �C���N�j�A�G���v�e�B  �z���C�g�S
///#define		WRN_INK_FEW_W4_LVL			LVL_WARNING

//			2.5.2.3 ���C�p
//#define	WRN_WIPER_CLN				0x00001020	// ���C�p�N���[�i�g�p�񐔒�  ***************�@�\������Ȃ�
//#define		WRN_WIPER_CLN_LVL			LVL_WARNING
//#define	WRN_WIPER_BLD				0x00001021	// ���C�p�u���[�h�g�p�񐔒�  �@�@************** �g���ĂȂ�
//#define		WRN_WIPER_BLD_LVL			LVL_WARNING

//			2.5.2.4 �w�b�h���x
#define	WRN_HEAD_TEMP_C				0x00001030	// �J���[�w�b�h ���Ӊ��x
#define		WRN_HEAD_TEMP_C_LVL			LVL_WARNING
#define	WRN_HEAD_TEMP_W				0x00001031	// �z���C�g�w�b�h���Ӊ��x
#define		WRN_HEAD_TEMP_W_LVL			LVL_WARNING

#define	WRN_CRG_MTR_LIFE			0x00001051	// �L�����b�W���[�^�̎���
#define		WRN_CRG_MTR_LIFE_LVL		LVL_WARNING

//			2.5.2.7 �����x�Z���T�̏��
#define	WRN_SUR_TEMP_LOW			0x00001060	// �󎚕ۏ؉��x�����i���[�j���O�j
#define		WRN_SUR_TEMP_LOW_LVL		LVL_WARNING
#define	WRN_SUR_TEMP_HIGH			0x00001061	// �󎚕ۏ؉��x�ȏ�i���[�j���O�j
#define		WRN_SUR_TEMP_HIGH_LVL		LVL_WARNING

#define	WRN_SUR_HUMI_LOW			0x00001064	// �󎚕ۏ؎��x�����i���[�j���O�j
#define		WRN_SUR_HUMI_LOW_LVL		LVL_WARNING
#define	WRN_SUR_HUMI_HIGH			0x00001065	// �󎚕ۏ؎��x�ȏ�i���[�j���O�j
#define		WRN_SUR_HUMI_HIGH_LVL		LVL_WARNING

//			2.5.2.8 �o�b�e���[�̏��
#define	WRN_BATTERY_LIFE			0x00001070	//�o�b�e���[�����i���`�E���d�r�����j�@���O�Ȃ�
#define		WRN_BATTERY_LIFE_LVL		LVL_WARNING

//			2.5.2.9 �N���b�N�̏��
#define	WRN_RTC_NO_SET				0x00001080	//���v���Z�b�g����Ă��Ȃ��@���O�Ȃ�
#define		WRN_RTC_NO_SET_LVL			LVL_WARNING

#define ERR_RTC_NO_SET				0x00001085	//���v���Z�b�g����Ă��Ȃ�(WaitOk)�@���O�Ȃ�
#define		ERR_RTC_NO_SETLVL			LVL_WARNING

//			2.5.2.10 �L���b�v/���C�p�[�̏��
#define	WRN_CAP_WIPER_CLEAN				0x00001090	//�L���b�v/���C�p�[�̐��|���K�v�ȏ�ԁi���[�j���O�j
#define		WRN_CAP_WIPER_CLEAN_LVL			LVL_WARNING
#define ERR_CAP_WIPER_CLEAN				0x00001091	//�L���b�v/���C�p�[�̐��|���K�v�ȏ�ԁi�G���[�j
#define 	ERR_CAP_WIPER_CLEAN_LVL			LVL_MIDDLE

#define WRN_WIPER_CLEANER_LIFE_WHITE	0x00001092	//���C�p�[�N���[�i�[�����@���i���[�j���O�j
#define 	WRN_WIPER_CLEANER_LIFE_WHITE_LVL	LVL_WARNING
#define ERR_WIPER_CLEANER_LIFE_WHITE	0x00001093	//���C�p�[�N���[�i�[���� ���i�G���[�j
#define 	ERR_WIPER_CLEANER_LIFE_WHITE_LVL	LVL_MIDDLE

#define WRN_WIPER_CLEANER_LIFE_COLOR	0x00001095	//���C�p�[�N���[�i�[�����@�J���[�i���[�j���O�j
#define 	WRN_WIPER_CLEANER_LIFE_COLOR_LVL	LVL_WARNING
#define ERR_WIPER_CLEANER_LIFE_COLOR	0x00001096	//���C�p�[�N���[�i�[���� �J���[�i�G���[�j
#define 	ERR_WIPER_CLEANER_LIFE_COLOR_LVL	LVL_MIDDLE

#define	WRN_PUMP_TUBE_LIFE				0x00001100	// �����e�̃|���v�`���[�u�����������i�����؂�j
#define		WRN_PUMP_TUBE_LIFE_LVL			LVL_MIDDLE

//			2.5.2.11 ���C���N�`���[�u�̏��

//			���w�b�h���
#define ERR_W_HEAD_CLEAN_EXEC			0x00001125	// ���w�b�h��򒆃G���[
#define 	ERR_W_HEAD_CLEAN_EXEC_LVL			LVL_MIDDLE

//			2.5.2.12 ��������e�i���X
#define	ERR_WHITTE_STIRRING				0x00001202	// ���C���N�h�a�i�G���[�j
#define		ERR_WHITTE_STIRRING_LVL			LVL_MIDDLE

//			2.5.2.13 �~�X�g�΍�t�@���̃��b�N���m
#define	WRN_MIST_FAN_LOCKED				0x00001210	// �~�X�g�΍�t�@���̃��b�N���m
#define		WRN_MIST_FAN_LOCKED_LVL			LVL_WARNING

//			2.5.2.14 �w�b�h�t�B���^�[����
#define ERR_EXCHANGE_FILTER				0x00001401	// �t�B���^�[������̃G���[�iWaitOk2�G���[�j
#define		ERR_EXCHANGE_FILTER_LVL			LVL_MIDDLE

//			2.5.2.15 �t�@���t�B���^�[����
#define WRN_EXG_FANFILTER				0x00001501	// �t�@���t�B���^�[��������(���[�j���O)
#define 	WRN_EXG_FANFILTER_LVL			LVL_WARNING

//			2.5.2.16 �t���b�V���O�t�H�[����������
#define WRN_EXG_ABSORBER_W				0x00001601	// �t���b�V���O�t�H�[������ ��(���[�j���O)
#define 	WRN_EXG_ABSORBER_W_LVL			LVL_WARNING
#define ERR_EXG_ABSORBER_W				0x00001602	// �t���b�V���O�t�H�[������ ��(�G���[)
#define 	ERR_EXG_ABSORBER_W_LVL			LVL_MIDDLE

#define WRN_EXG_ABSORBER_C				0x00001605	// �t���b�V���O�t�H�[������ �J���[(���[�j���O)
#define 	WRN_EXG_ABSORBER_C_LVL			LVL_WARNING
#define ERR_EXG_ABSORBER_C				0x00001606	// �t���b�V���O�t�H�[������ �J���[(�G���[)
#define 	ERR_EXG_ABSORBER_C_LVL			LVL_MIDDLE

//			�m�Y�����ʂ̑|������
#define WRN_EXG_NOZZLE_TIME				0x00001700	// �m�Y�����ʁi�m�Y���K�[�h�j�̑|�������i���[�j���O�j
#define 	WRN_EXG_NOZZLE_TIME_LVL			LVL_WARNING
#define ERR_EXG_NOZZLE_TIME				0x00001701	// �m�Y�����ʁi�m�Y���K�[�h�j�̑|�������i�G���[�j
#define 	ERR_EXG_NOZZLE_TIME_LVL			LVL_MIDDLE

//			�w�b�h�������G���[
#define ERR_EXG_HEAD_EXEC				0x00001801	//	�w�b�h�������G���[
#define 	ERR_EXG_HEAD_EXEC_LVL			LVL_MIDDLE

//			�����C���N�����v���G���[
#define ERR_INK_LOAD_EXECUTION			0x00001901	//�@�����C���N�������K�v
#define 	ERR_INK_LOAD_EXECUTION_LVL		LVL_MIDDLE

//			���C���N�x�~�L�����Z���G���[
#define ERR_WHITE_INK_MODE_CANCEL		0x00001905	//�@���C���N�x�~���Ō�܂Ŏ��s����Ă��Ȃ�
#define 	ERR_WHITE_INK_MODE_CANCEL_LVL	LVL_MIDDLE

/*-------------------------------------------------------*/
//		�^�p�G���[
//			�J�[�g���b�W����
#define ERR_NO_CTRG_K				0x00002000	// �J�[�g���b�W���O�� �u���b�N�@���O�Ȃ�
#define		ERR_NO_CTRG_K_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_M				0x00002001	// �J�[�g���b�W���O�� �}�[���^�@���O�Ȃ�
#define		ERR_NO_CTRG_M_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_C				0x00002002	// �J�[�g���b�W���O�� �V�A���@���O�Ȃ�
#define		ERR_NO_CTRG_C_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_Y				0x00002003	// �J�[�g���b�W���O�� �C�G���[�@���O�Ȃ�
#define		ERR_NO_CTRG_Y_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_W1				0x00002004	// �J�[�g���b�W���O��  �z���C�g�P�Q�@���O�Ȃ�
#define		ERR_NO_CTRG_W1_LVL			LVL_MIDDLE
#define ERR_NO_CTRG_W2				0x00002005	// �J�[�g���b�W���O��  �z���C�g�R�S�@���O�Ȃ�
#define		ERR_NO_CTRG_W2_LVL			LVL_MIDDLE

//			�C���N�c��
#define ERR_INK_EMP_K				0x00002020	// �C���N�� �u���b�N�@���O�Ȃ�
#define		ERR_INK_EMP_K_LVL			LVL_MIDDLE
#define ERR_INK_EMP_M				0x00002021	// �C���N�� �}�[���^�@���O�Ȃ�
#define		ERR_INK_EMP_M_LVL			LVL_MIDDLE
#define ERR_INK_EMP_C				0x00002022	// �C���N�� �V�A���@���O�Ȃ�
#define		ERR_INK_EMP_C_LVL			LVL_MIDDLE
#define ERR_INK_EMP_Y				0x00002023	// �C���N�� �C�G���[�@���O�Ȃ�
#define		ERR_INK_EMP_Y_LVL			LVL_MIDDLE
#define ERR_INK_EMP_W1				0x00002024	// �C���N�� �z���C�g�P�Q�@���O�Ȃ�
#define		ERR_INK_EMP_W1_LVL			LVL_MIDDLE
#define ERR_INK_EMP_W2				0x00002025	// �C���N�� �z���C�g�R�S�@���O�Ȃ�
#define		ERR_INK_EMP_W2_LVL			LVL_MIDDLE

// 			IC�`�b�v�ُ�
#define ERR_IC_CHIP_K				0x00002030	// IC�`�b�v�ُ� �u���b�N
#define		ERR_IC_CHIP_K_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_M				0x00002031	// IC�`�b�v�ُ� �}�[���^
#define		ERR_IC_CHIP_M_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_C				0x00002032	// IC�`�b�v�ُ� �V�A��
#define		ERR_IC_CHIP_C_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_Y				0x00002033	// IC�`�b�v�ُ� �C�G���[
#define		ERR_IC_CHIP_Y_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_W1				0x00002034	// IC�`�b�v�ُ� �z���C�g�P�Q
#define		ERR_IC_CHIP_W1_LVL			LVL_MIDDLE
#define ERR_IC_CHIP_W2				0x00002035	// IC�`�b�v�ُ� �z���C�g�R�S
#define		ERR_IC_CHIP_W2_LVL			LVL_MIDDLE

#define ERR_IC_CHIP_MAIN_C			0x00002036	// IC�`�b�v�ُ� ���C����J���[
#define		ERR_IC_CHIP_MAIN_C_LVL		LVL_FATAL
#define ERR_IC_CHIP_MAIN_W			0x00002037	// IC�`�b�v�ُ� ���C����z���C�g
#define		ERR_IC_CHIP_MAIN_W_LVL		LVL_FATAL


//			2.5.3.3 ���C�p�N���[�i
#define	ERR_WIPER_CLN1				0x00002041	// �J���[�����C�p�N���[�i�J�Z�b�g1����
#define		ERR_WIPER_CLN1_LVL			LVL_FATAL
#define	ERR_WIPER_CLN2				0x00002042	// �������C�p�N���[�i�J�Z�b�g2����
#define		ERR_WIPER_CLN2_LVL			LVL_FATAL

#define	ERR_SUR_TEMP_LOW			0x00002050	// ���쉷�x����
#define		ERR_SUR_TEMP_LOW_LVL		LVL_MIDDLE
#define	ERR_SUR_TEMP_HIGH			0x00002051	// ���쉷�x�ُ�
#define		ERR_SUR_TEMP_HIGH_LVL		LVL_MIDDLE

#define	ERR_PLTN_UNLOAD				0x00002062	// �A�����[�h�Ō��_�܂Ŗ߂炸����I���i�E���H�j ���O�̂�
#define		ERR_PLTN_UNLOAD_LVL			LVL_MIDDLE
#define	ERR_PLTN_LOAD				0x00002063	// ���[�h���ɒE�������\������(�܂��͌��_�O�Ŏ�Ŏ�O�ɓ�������)�@���O�̂�
#define		ERR_PLTN_LOAD_LVL			LVL_MIDDLE
#define	ERR_CLRNS_SNSR				0x00002070	// ��Q�����m
#define		ERR_CLRNS_SNSR_LVL			LVL_MIDDLE

//			�p�E�`�����s��
#define ESBT_POUCH_TAKE_UP_K_ERR		0x00002080	// �p�E�`�����s�� �u���b�N
#define ESBT_POUCH_TAKE_UP_K_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_M_ERR		0x00002081	// �p�E�`�����s�� �}�[���^
#define ESBT_POUCH_TAKE_UP_M_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_C_ERR		0x00002082	// �p�E�`�����s�� �V�A��
#define ESBT_POUCH_TAKE_UP_C_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_Y_ERR		0x00002083	// �p�E�`�����s�� �C�G���[
#define ESBT_POUCH_TAKE_UP_Y_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_W12_ERR		0x00002084	// �p�E�`�����s�� �z���C�g�P�Q
#define ESBT_POUCH_TAKE_UP_W12_ERR_LVL		LVL_MIDDLE
#define ESBT_POUCH_TAKE_UP_W34_ERR		0x00002085	// �p�E�`�����s�� �z���C�g�R�S
#define ESBT_POUCH_TAKE_UP_W34_ERR_LVL		LVL_MIDDLE


//			IC�`�b�v�c�ʒ���
#define ERR_IC_INK_EXCESS_K				0x00002090	// IC�`�b�v�c�ʒ��� �u���b�N
#define		ERR_IC_INK_EXCESS_K_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_M				0x00002091	// IC�`�b�v�c�ʒ��� �}�[���^
#define		ERR_IC_INK_EXCESS_M_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_C				0x00002092	// IC�`�b�v�c�ʒ��� �V�A��
#define		ERR_IC_INK_EXCESS_C_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_Y				0x00002093	// IC�`�b�v�c�ʒ��� �C�G���[
#define		ERR_IC_INK_EXCESS_Y_LVL			LVL_MIDDLE
#define ERR_IC_INK_EXCESS_W1			0x00002094	// IC�`�b�v�c�ʒ��� �z���C�g�P�Q
#define		ERR_IC_INK_EXCESS_W1_LVL		LVL_MIDDLE
#define ERR_IC_INK_EXCESS_W2			0x00002095	// IC�`�b�v�c�ʒ��� �z���C�g�R�S
#define		ERR_IC_INK_EXCESS_W2_LVL		LVL_MIDDLE

//			2.5.3.10 USB������
#define	ERR_NO_CFCARD				0x00002100	// USB�������Ȃ��@���O�Ȃ�
#define		ERR_NO_CFCARD_LVL			LVL_MIDDLE
#define	ERR_NOAREA_CFCARD			0x00002101	// USB�������󂫂Ȃ�
#define		ERR_NOAREA_CFCARD_LVL		LVL_MIDDLE
#define	ERR_NOT_RUN_BULK_SERV		0x00002102	// tUsbBulkXbdService�N�������@���O�̂�
#define		ERR_NOT_RUN_BULK_SERV_LVL	LVL_MIDDLE

//#define	ERR_CF_IN_USB_RECEIVING		0x00002104	// USB��M����CF�J�[�h����f�[�^��ǂݍ������Ƃ����@�@************** �g���ĂȂ�
//#define		ERR_CF_IN_USB_RECEIVING_LVL	LVL_MIDDLE

#define	ERR_NO_VALID_FILE			0x00002105	// �L���t�@�C��/�t�H���_�Ȃ��@���O�Ȃ�
#define		ERR_NO_VALID_FILE_LVL		LVL_MIDDLE

//			2.5.3.11 ��M�����Q��

#define	ERR_RECEIVING_NODATA		0x00002110			// ��M�����Ȃ�		���O�Ȃ�
#define		ERR_RECEIVING_NODATA_LVL	LVL_MIDDLE

#define ERR_JOB_DEL_MODE_ON			0x00002120			// �W���u���������L��	���O�Ȃ�
#define		ERR_JOB_DEL_MODE_ON_LVL	LVL_MIDDLE

#define ERR_WHITE_INK_PAUSE_MODE	0x00002130			// ���C���N�x�~���[�h�̂��ߎ��s�s��
#define 	ERR_WHITE_INK_PAUSE_MODE_LVL	LVL_MIDDLE


//			�����e�J�[�g���b�W�����i�C���N�g�p���̃����e�J�[�g���b�W�����Ȃǁj
#define ERR_MNT_CTRG_K				0x00002200	// �����e�i���X�J�[�g���b�W���� �u���b�N�@���O�Ȃ�
#define		ERR_MNT_CTRG_K_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_M				0x00002201	// �����e�i���X�J�[�g���b�W���� �}�[���^�@���O�Ȃ�
#define		ERR_MNT_CTRG_M_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_C				0x00002202	// �����e�i���X�J�[�g���b�W���� �V�A���@���O�Ȃ�
#define		ERR_MNT_CTRG_C_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_Y				0x00002203	// �����e�i���X�J�[�g���b�W���� �C�G���[�@���O�Ȃ�
#define		ERR_MNT_CTRG_Y_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_W1				0x00002204	// �����e�i���X�J�[�g���b�W����  �z���C�g�P�Q�@���O�Ȃ�
#define		ERR_MNT_CTRG_W1_LVL			LVL_MIDDLE
#define ERR_MNT_CTRG_W2				0x00002205	// �����e�i���X�J�[�g���b�W����  �z���C�g�R�S�@���O�Ȃ�
#define		ERR_MNT_CTRG_W2_LVL			LVL_MIDDLE

//			�C���N�J�[�g���b�W�����i���C���N�x�~���̃C���N�J�[�g���b�W�����Ȃǁj
#define ERR_W_OFF_INK_CTRG_W1		0x00002214	// �C���N�J�[�g���b�W����  �z���C�g�P�Q�@���O�Ȃ�
#define		ERR_W_OFF_INK_CTRG_W1_LVL	LVL_MIDDLE
#define ERR_W_OFF_INK_CTRG_W2		0x00002215	// �C���N�J�[�g���b�W����  �z���C�g�R�S�@���O�Ȃ�
#define		ERR_W_OFF_INK_CTRG_W2_LVL	LVL_MIDDLE

//			���ꃂ�[�h�ݒ�
#define ERR_SPECIAL_MODE			0x00002300	// ���ꃂ�[�h�ݒ�
#define		ERR_SPECIAL_MODE_LVL		LVL_MIDDLE

/*-------------------------------------------------------*/
//		2.5.4 �o�b�C���^�t�F�[�X�G���[(bit15-12:0011)
#define	EPC_RCV_TOUT				0x00003000	// PC����̃R�}���h��M�^�C���A�E�g
#define		EPC_RCV_TOUT_LVL			LVL_MIDDLE
#define	EPC_SND_TOUT				0x00003001	// PC�ւ̃R�}���h���M�^�C���A�E�g
#define		EPC_SND_TOUT_LVL			LVL_MIDDLE
#define	EPC_NG_CMD					0x00003002	// PC�R�}���h�̃R�}���h���e�s��
#define		EPC_NG_CMD_LVL				LVL_MIDDLE
#define	EPC_CMD_VER					0x00003003	// PC�R�}���h�̃o�[�W�����s����
#define		EPC_CMD_VER_LVL				LVL_MIDDLE
#define	EPC_FIRM_CHKS				0x00003004	// �t�@�[���E�F�A�X�V�R�}���h�̃`�F�b�N�T���ُ�
#define		EPC_FIRM_CHKS_LVL			LVL_MIDDLE
#define	EPC_EROM_CHKS				0x00003005	// EEPROM�X�V�R�}���h�̃`�F�b�N�T���ُ�
#define		EPC_EROM_CHKS_LVL			LVL_MIDDLE
///#define	EPC_NG_CMD_ADDR				0x00003006	// PC�R�}���h����A�h���X��Ɏ�M����Ă���@�@************** �g���ĂȂ�
///#define		EPC_NG_CMD_ADDR_LVL			LVL_MIDDLE
///#define	EPC_CMD_SEQ_NO				0x00003007	// �R�}���h�V�[�P���X�ԍ����s�A���@�@************** �g���ĂȂ�
///#define		EPC_CMD_SEQ_NO_LVL			LVL_MIDDLE
///#define	EPC_CMD_CMD_CHKS			0x00003008	// �R�}���h�P�ʂł̃`�F�b�N�T���ُ�@�@************** �g���ĂȂ�
///#define		EPC_CMD_CMD_CHKS_LVL		LVL_MIDDLE
///#define	EPC_CMD_POS					0x00003009	// �W���u���ɂ�����R�}���h�ʒu�s���@�@************** �g���ĂȂ�
///#define		EPC_CMD_POS_LVL				LVL_MIDDLE
#define	EPC_MAINTE_CMD				0x00003010	// �ێ烂�[�h��p�R�}���h���ێ烂�[�h���Ɏ�M
#define		EPC_MAINTE_CMD_LVL			LVL_MIDDLE
///#define	EPC_NOT_CMD_DATA			0x00003011	// JobStart�`End�Ԃɔ�R�}���h�f�[�^�������Ă���@�@************** �g���ĂȂ�
///#define		EPC_NOT_CMD_DATA_LVL		LVL_MIDDLE
///#define	EPC_CMD_JOB_CHKS			0x00003012	// �W���u�P�ʂł̃`�F�b�N�T���ُ�@�@************** �g���ĂȂ�
///#define		EPC_CMD_JOB_CHKS_LVL		LVL_MIDDLE

#define	EPC_PC_REQ_JOB_ERR			0x00003013	// PC���W���u�G���h�R�}���h�ŃG���[�I���v��
#define		EPC_PC_REQ_JOB_ERR_LVL		LVL_MIDDLE
#define	EPC_NG_CMD_LEN				0x00003014	// PC�R�}���h�̃R�}���h���s��
#define		EPC_NG_CMD_LEN_LVL			LVL_MIDDLE
#define	EPC_NG_TOO_MANY_DATA		0x00003015	// ������ɑ�������(100�ȏ�)�̃f�[�^������ꂽ
#define		EPC_NG_TOO_MANY_DATA_LVL	LVL_MIDDLE

#define	EPC_341_WHITE_DATA			0x00003100	// ���x�~���[�h���ɔ��C���N���g������f�[�^������ꂽ
#define		EPC_341_WHITE_DATA_LVL		LVL_MIDDLE


/*-------------------------------------------------------*/
//		2.5.5 �f�[�^�G���[(bit15-12:0100)
//			2.5.5.1 ����f�[�^�ُ̈�
#define	EDT_ILGL_CMDLEN				0x00003400	// ����R�}���h���ُ�@�@�W�J�G���[�ň�����Ƃ߂�̂ɕK�v�@�����Č���
#define		EDT_ILGL_CMDLEN_LVL			LVL_MIDDLE
#define	EDT_ILGL_CMD				0x00003401	// ����`����R�}���h  �W�J�G���[�ň�����Ƃ߂�̂ɕK�v�@�����Č���
#define		EDT_ILGL_CMD_LVL			LVL_MIDDLE
#define	EDT_ILGL_CMDSEQ1			0x00003402	// �V�[�P���X�ُ�i����f�[�^�X�^�[�g�����Ă��Ȃ��Ƃ��̈���f�[�^�j�@�W�J�G���[�ň�����Ƃ߂�̂ɕK�v�@�����Č���
#define		EDT_ILGL_CMDSEQ1_LVL		LVL_MIDDLE
//#define	EDT_ILGL_CMDSEQ2			0x00003403	// �V�[�P���X�ُ�i�O���t�B�b�N�f�[�^��M���ɂ��̑��̃R�}���h�j
//#define		EDT_ILGL_CMDSEQ2_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_LONG			0x00003404	// �P�s����������
//#define		EDT_LINE_TOO_LONG_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_MANY			0x00003405	// �s����������
//#define		EDT_LINE_TOO_MANY_LVL		LVL_MIDDLE
//#define	EDT_LINE_TOO_WIDE			0x00003406	// ��������L������
//#define		EDT_LINE_TOO_WIDE_LVL		LVL_MIDDLE
#define	EDT_NO_LINE					0x00003407	// ���g���Ȃ�
#define		EDT_NO_LINE_LVL				LVL_MIDDLE
#define	EDT_JOB_BIG					0x00003408	// �W���u�T�C�Y���傫������
#define		EDT_JOB_BIG_LVL				LVL_MIDDLE

#define EDT_ILGL_CMDSEQ4            0x00003410  // �V�[�P���X�ُ�i�O���t�B�b�N�f�[�^�X�^�[�g�R�}���h�̈ʒu���s���j
#define		EDT_ILGL_CMDSEQ4_LVL		LVL_MIDDLE
#define EDT_ILGL_CMDSEQ5            0x00003411  // �V�[�P���X�ُ�i�O���t�B�b�N�f�[�^�G���h�R�}���h�̈ʒu���s���j
#define		EDT_ILGL_CMDSEQ5_LVL		LVL_MIDDLE
#define EDT_NO_JOB_START            0x00003412  // �W���u�X�^�[�g�R�}���h�����݂��Ȃ�
#define		EDT_NO_JOB_START_LVL		LVL_MIDDLE


//			2.5.5.3 �t�@�[���A�b�v�f�[�g�t�@�C���ُ̈�
//			�t�@�[���A�b�v�f�[�g�t�@�C���̎d�l�ɍ��킹�čĒ�`����B


//			2.5.5.5 �t�@�C���V�X�e���G���[
#define	EFFS_FILE_OPEN				0x00004100	// �t�@�C���I�[�v���G���[
#define		EFFS_FILE_OPEN_LVL			LVL_MIDDLE
#define	EFFS_FILE_CREATE			0x00004101	// �t�@�C���N���G�C�g�G���[
#define		EFFS_FILE_CREATE_LVL		LVL_MIDDLE
///#define	EFFS_FILE_CLOSE				0x00004102	// �t�@�C���N���[�Y�G���[
///#define		EFFS_FILE_CLOSE_LVL			LVL_MIDDLE
#define	EFFS_FILE_SEEK				0x00004103	// �t�@�C���V�[�N�G���[
#define		EFFS_FILE_SEEK_LVL			LVL_MIDDLE
#define	EFFS_FILE_READ				0x00004104	// �t�@�C�����[�h�G���[
#define		EFFS_FILE_READ_LVL			LVL_MIDDLE
#define	EFFS_FILE_WRITE				0x00004105	// �t�@�C�����C�g�G���[
#define		EFFS_FILE_WRITE_LVL			LVL_MIDDLE
#define	EFFS_FILE_DATA				0x00004106	// �t�@�C���̒��g�i�f�[�^�j���ُ�
#define		EFFS_FILE_DATA_LVL			LVL_MIDDLE
///#define	EFFS_FILE_SIZE				0x00004107	// �t�@�C���̃T�C�Y���ُ�
///#define		EFFS_FILE_SIZE_LVL			LVL_MIDDLE
#define	EFFS_FILE_GETSIZE			0x00004108	// �t�@�C���T�C�Y�擾���s
#define		EFFS_FILE_GETSIZE_LVL		LVL_MIDDLE
///#define	EFFS_FILE_FIND				0x00004109	// �t�@�C���������s
///#define		EFFS_FILE_FIND_LVL			LVL_MIDDLE
///#define	EFFS_NO_FILE				0x00004110	// ����n�Y�̃t�@�C��������
///#define		EFFS_NO_FILE_LVL			LVL_MIDDLE

//			2.5.5.6 �����f�[�^�G���[
#define	EFFS_STR_NOT_FOUND				0x00004200	// �w�肳�ꂽID�̕�����f�[�^��������Ȃ�
#define		EFFS_STR_NOT_FOUND_LVL			LVL_MIDDLE
#define	EFFS_STR_VERSION_MISMATCH		0x00004201	// �w�肳�ꂽID�̕�����f�[�^�̓o�[�W�����~�X�}�b�`
#define		EFFS_STR_VERSION_MISMATCH_LVL	LVL_MIDDLE
#define	EFFS_STR_CHECKSUM_MISMATCH		0x00004202	// �w�肳�ꂽID�̕�����f�[�^�̓`�F�b�N�T������v���Ȃ�
#define		EFFS_STR_CHECKSUM_MISMATCH_LVL	LVL_MIDDLE

#define	EDT_TST_PRT_NOT_FOUND			0x00004400	// �e�X�g����f�[�^��������Ȃ�
#define		EDT_TST_PRT_NOT_FOUND_LVL		LVL_MIDDLE
#define	EDT_TST_PRT_VER_MISMATCH		0x00004401	// �e�X�g����f�[�^�̃o�[�W�����~�X�}�b�`
#define		EDT_TST_PRT_VER_MISMATCH_LVL	LVL_MIDDLE
#define	EDT_TST_PRT_CHKSUM_MISMATCH		0x00004402	// �e�X�g����f�[�^�̃`�F�b�N�T������v���Ȃ�
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
#define	ELAN_IP_ADDRESS_SET_ERROR			0x00004504	// IP Address Set Error�@���O�Ȃ�
#define		ELAN_IP_ADDRESS_SET_ERROR_LVL	LVL_MIDDLE

#define	ELAN_EEPROM_BACKUP_ERROR			0x00004505	// EEPROM�ۑ��G���[
#define		ELAN_EEPROM_BACKUP_ERROR_LVL	LVL_MIDDLE

#define ELAN_EEPROM_RESTORE_ERROR			0x00004506	// �ݒ��񃊃X�g�A�G���[
#define		ELAN_EEPROM_RESTORE_ERROR_LVL	LVL_MIDDLE

/*-------------------------------------------------------*/

//					2.5.6.1.1.2 �v�����g�R���g���[��
#define	ECM_DATA_TOUT				0x00005010	// ����f�[�^�W�J�^�C���A�E�g
#define		ECM_DATA_TOUT_LVL			LVL_MIDDLE

#define	ECM_CR_MOVE_TOUT			0x00005020	// �L�����b�W�ړ������҂��^�C���A�E�g
#define		ECM_CR_MOVE_TOUT_LVL		LVL_FATAL
#define	ECM_FLUSH_TOUT				0x00005021	// �t���b�V���O�����҂��^�C���A�E�g
#define		ECM_FLUSH_TOUT_LVL			LVL_FATAL
#define	ECM_HEAD_RCV_TOUT			0x00005022	// �w�b�h���슮���҂��^�C���A�E�g
#define		ECM_HEAD_RCV_TOUT_LVL		LVL_FATAL


//					2.5.6.2.1 �v�����g�R���g���[��
#define	ECM_MNT_REQ_TOUT			0x00005080	// �����e�i���X���샊�N�G�X�g�^�C���A�E�g
#define		ECM_MNT_REQ_TOUT_LVL		LVL_FATAL
#define	ECM_MNT_RCV_TOUT			0x00005081	// �����e�i���X���슮���҂��^�C���A�E�g
#define		ECM_MNT_RCV_TOUT_LVL		LVL_FATAL

#define	ECM_BYSH_PLTN_LD			0x00005094	// �v���e�����[�h���N�G�X�g�^�C���A�E�g
#define		ECM_BYSH_PLTN_LD_LVL		LVL_FATAL
#define	ECM_BYSH_PLTN_UNLD			0x00005095	// �v���e���A�����[�h���N�G�X�g�^�C���A�E�g
#define		ECM_BYSH_PLTN_UNLD_LVL		LVL_FATAL
#define	ECM_BYSH_PLTN_LF			0x00005096	// LF�^�C���A�E�g
#define		ECM_BYSH_PLTN_LF_LVL		LVL_FATAL




/*-------------------------------------------------------*/
//		�����e�i���X��Ƃ̒ʐM	�i52xx�ԑ�j

#define	ECM_SHMT_SND_TOUT			0x00005200	// �����e���j�b�g���X�|���X�҂��^�C���A�E�g
#define		ECM_SHMT_SND_TOUT_LVL		LVL_FATAL
#define	ECM_SHMT_FMT				0x00005201	// �����e���j�b�g���X�|���X�t�H�[�}�b�g�G���[
#define		ECM_SHMT_FMT_LVL			LVL_FATAL

#define	ECM_SHMT_COM_SEND			0x00005230	// �����e���j�b�g�ւ̃R�}���h���M�G���[
#define		ECM_SHMT_COM_SEND_LVL		LVL_FATAL
#define	ECM_SHMT_RCV_UNEXPECT_CMD	0x00005231	// �����e���j�b�g�ւ̃��N�G�X�g�Ƃ͈قȂ郌�X�|���X����M����
#define		ECM_SHMT_RCV_UNEXPECT_CMD_LVL	LVL_FATAL
#define	ECM_SHMT_CRC_CALC			0x00005232	// �����e���j�b�g�����M�������X�|���X��CRC����v���Ȃ�
#define		ECM_SHMT_CRC_CALC_LVL		LVL_FATAL
#define	ECM_SHMT_CRC_INEXACT		0x00005233	// �����e���j�b�g�����M�������X�|���X��CRC�̏������s��
#define		ECM_SHMT_CRC_INEXACT_LVL	LVL_FATAL

#define	ECM_MNT_SIO_OPEN			0x00005240	// �����e���j�b�g�Ƃ̒ʐM�p�V���A���|�[�g���I�[�v���ł��Ȃ�
#define		ECM_MNT_SIO_OPEN_LVL		LVL_FATAL
#define	ECM_MNT_SIO_READ			0x00005241	// �����e���j�b�g����̃V���A����M�G���[	// <- �g���Ă��Ȃ����Ǐ�������ʖ�!	reserved
#define		ECM_MNT_SIO_READ_LVL		LVL_FATAL								// <- �g���Ă��Ȃ����Ǐ�������ʖ�!	reserved

#define	ECM_MNT_INCORRECT_REC		0x00005250	// �����e���j�b�g�t�@�[���X�V�f�[�^���R�[�h�ُ̈�
#define		ECM_MNT_INCORRECT_REC_LVL	LVL_FATAL

#define	ECM_MNT_VER_UNSUPPORT		0x00005260	// �����e���j�b�g�t�@�[���Ƃ̃o�[�W�����~�X�}�b�`
#define		ECM_MNT_VER_UNSUPPORT_LVL	LVL_FATAL


/*-------------------------------------------------------*/
//		�����e�i���X���j�b�g����	�i53xx�`4xx�ԑ�j

// 53xx/54xx�ԑ�́A�����e���j�b�g�t�@�[������̃G���[���X�|���X��M�i�����e���j�b�g�t�@�[�����G���[�����o���āA���C����ւ��̓��e��ʒm���Ă����j
//   xx�����̓����e���j�b�g�t�@�[���̃G���[�R�[�h�Ɠ��l
//   �G���[���x���͂��ׂ�ECM_MNT_BASE_LVL
//   53xx�ԑ�̓J���[���A54xx�ԑ�͔���
#define	ECM_MNT_BASE_C				0x00005300	// �J���[�������e���j�b�g�t�@�[���E�F�A����̃G���[�ʒm�̃x�[�X�ԍ��i���̔ԍ����͖̂��g�p�j
#define	ECM_MNT_BASE_W				0x00005400	// ���������e���j�b�g�t�@�[���E�F�A����̃G���[�ʒm�̃x�[�X�ԍ��i���̔ԍ����͖̂��g�p�j
#define		ECM_MNT_BASE_LVL			LVL_FATAL
#define	ECM_CMD_LEN					      0x01	// �R�}���h���ُ�
#define	ECM_CMD_ARGC				      0x02	// �����̌��̕����񂪕s��
#define ECM_CMD_ARGV				      0x03	// �����̕����񂪕s��
#define ECM_CMD_ARG_CNT				      0x04	// �����̌����R�}���h�d�l�ƈ�v����
#define	ECM_CMD_CRC_STR				      0x05	// CRC�̕����񂪕s��
#define	ECM_CMD_UNKNOWN				      0x06	// ����`�R�}���h
#define	ECM_CMD_SEQ_STR	 			      0x07	// �V�[�P���X�ԍ��̕����񂪕s��
#define	ECM_COM_CRC					      0x11	// CRC��v����
#define	ECM_COM_OVERRUN				      0x12	// �I�[�o�����G���[
#define	ECM_COM_PARITY				      0x13	// �p���e�B�G���[
#define	ECM_COM_FRAMING				      0x14	// �t���[�~���O�G���[
#define	ECM_CAM_INIT				      0x20	// �����e�J����������
#define	ECM_CAM_SNSR1				      0x21	// �����e�J�����[�^�[/�Z���T�[�G���[�P�i�������̃Z���T�[�l���z��O�j
#define	ECM_CAM_SNSR2				      0x22	// �����e�J�����[�^�[/�Z���T�[�G���[�Q�i�K��X�e�b�v���Ɋ��������j
#define	ECM_CAM_SNSR3				      0x23	// �����e�J�����[�^�[/�Z���T�[�G���[�R�i���g���C�A�E�g�j
#define	ECM_CLEANER_INIT			      0x30	// ���C�p�[�N���[�i�[��������
#define	ECM_CLEANER_SNSR1			      0x31	// ���C�p�[�N���[�i�[���[�^�[/�Z���T�[�G���[�P�i�������̃Z���T�[�l���z��O�j
#define	ECM_CLEANER_SNSR2			      0x32	// ���C�p�[�N���[�i�[���[�^�[/�Z���T�[�G���[�Q�i�K��X�e�b�v���Ɋ��������j
#define	ECM_CLEANER_SNSR3			      0x33	// ���C�p�[�N���[�i�[���[�^�[/�Z���T�[�G���[�R�i���g���C�A�E�g�j
#define	ECM_WIPER_INIT				      0x40	// ���C�p�[��������
#define	ECM_WIPER_SNSR1			          0x41	// ���C�p�[���[�^�[/�Z���T�[�G���[�P�i�������̃Z���T�[�l���z��O�j
#define	ECM_WIPER_SNSR2				      0x42	// ���C�p�[���[�^�[/�Z���T�[�G���[�Q�i�K��X�e�b�v���Ɋ��������j
#define	ECM_WIPER_SNSR3				      0x43	// ���C�p�[���[�^�[/�Z���T�[�G���[�R�i���g���C�A�E�g�j
#define	ECM_UPDATE_READY			      0x50	// �A�b�v�f�[�g�J�n��������
#define	ECM_FLASH_WRITE				      0x51	// �t���b�V�����C�g�G���[
#define	ECM_FLASH_VERIFY			      0x52	// �t���b�V�����C�g��x���t�@�C�G���[
#define	ECM_FLASH_ERASE				      0x53	// �t���b�V�������G���[
#define	ECM_UPDATE_BLKNO			      0x54	// �A�b�v�f�[�g�f�[�^ �u���b�N�A�Ԉُ�
#define	ECM_UPDATE_DATA				      0x55	// �A�b�v�f�[�g�f�[�^ �f�[�^���R�[�h�ُ�
#define	ECM_UPDATE_TOTAL			      0x56	// �A�b�v�f�[�g�f�[�^ �����R�[�h���s��v
#define	ECM_UPDATE_SUM				      0x57	// �A�b�v�f�[�g�f�[�^ �`�F�b�N�T���s��v
#define	ECM_FLASH_LIB				      0x58	// �t���b�V�����C�u�����G���[
#define	ECM_UPDATE_RECNUM			      0x59	// �A�b�v�f�[�g�f�[�^ �u���b�N�����R�[�h���ُ�
#define	ECM_SOL_PRE_ADDING			      0x61	// �\���m�C�h����v���d��
#define	ECM_INK_IIC_SND_ERR1		      0x71	// �C���N�Z���T���[�hIIC���M�G���[�i�G���[�P�j
#define	ECM_INK_IIC_SND_ERR2		      0x72	// �C���N�Z���T���[�hIIC���M�G���[�i�G���[�Q�j
#define	ECM_INK_IIC_SND_OTHER		      0x73	// �C���N�Z���T���[�hIIC���M�G���[�i���̑��̃G���[�j
#define	ECM_INK_IIC_SND_TOUT		      0x74	// �C���N�Z���T���[�hIIC���M�G���[�i���M�������j
#define	ECM_INK_IIC_RCV_ERR1		      0x75	// �C���N�Z���T���[�hIIC��M�G���[�i�G���[�P�j
#define	ECM_INK_IIC_RCV_ERR2	          0x76	// �C���N�Z���T���[�hIIC��M�G���[�i�G���[�Q�j
#define	ECM_INK_IIC_RCV_OTHER		      0x77	// �C���N�Z���T���[�hIIC��M�G���[�i���̑��̃G���[�j
#define	ECM_INK_IIC_RCV_TOUT		      0x78	// �C���N�Z���T���[�hIIC��M�G���[�i���M�������j
#define	ECM_INTERNAL				      0x91	// �����G���[�i�����e�t�@�[���E�F�A�j
// 0x000054FF�܂ŗ\��ς�


/*-------------------------------------------------------*/
//		�T�u�^���N		�i55xx�ԑ�j

#define	ESBT_FILL_TOUT_K			0x00005501	// �T�u�^���N K �[�U�҂��^�C���A�E�g
#define		ESBT_FILL_TOUT_K_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_M			0x00005502	// �T�u�^���N M �[�U�҂��^�C���A�E�g
#define		ESBT_FILL_TOUT_M_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_C			0x00005503	// �T�u�^���N C �[�U�҂��^�C���A�E�g
#define		ESBT_FILL_TOUT_C_LVL		LVL_FATAL
#define	ESBT_FILL_TOUT_Y			0x00005504	// �T�u�^���N Y �[�U�҂��^�C���A�E�g
#define		ESBT_FILL_TOUT_Y_LVL		LVL_FATAL


/*-------------------------------------------------------*/
//		IC�`�b�v����	�i56xx�ԑ�j

#define	ESBT_IC_CHIP_READ_ERR			0x00005600	// IC�`�b�v���[�h�G���[�iAPI���v�����󂯕t���Ȃ��j
#define		ESBT_IC_CHIP_READ_ERR_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_WRITE_ERR			0x00005601	// IC�`�b�v���C�g�G���[
#define		ESBT_IC_CHIP_WRITE_ERR_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_READ_TOUT			0x00005602	// IC�`�b�v���[�h�^�C���A�E�g
#define		ESBT_IC_CHIP_READ_TOUT_LVL		LVL_FATAL
#define	ESBT_IC_CHIP_WRITE_TOUT			0x00005603	// IC�`�b�v���C�g�^�C���A�E�g
#define		ESBT_IC_CHIP_WRITE_TOUT_LVL		LVL_FATAL


/*-------------------------------------------------------*/
//		���C���N�z��	�i57xx�ԑ�j


/*-------------------------------------------------------*/
//		PPC-�T�t�����Ԃ̒ʐM		�i58xx�ԑ�j

#define	EUH_SAFFRON_OPEN			0x00005801	// �T�t������USB�v�����^�Ƃ��ăI�[�v�����s
#define	EUH_SAFFRON_READ			0x00005802	// �T�t��������f�[�^��M���s
#define	EUH_SAFFRON_WRITE			0x00005803	// �T�t�����ւ̃f�[�^���M���s
#define	EUH_SAFFRON_LINK			0x00005804	// �T�t�����Ƃ̒ʐM���m�����Ȃ�(�������Ԃ��Ă��Ȃ�)


/*-------------------------------------------------------*/
//		2.5.7 �n�[�h�E�F�A�̏�(bit15-12:0110)
//			2.5.7.1 SH��
//				2.5.7.1.1 �v���e��
//#define	EHW_PLTN_LOAD				0x00006000	// �v���e�����[�h�G���[
//#define		EHW_PLTN_LOAD_LVL			LVL_FATAL
//#define	EHW_PLTN_IN					0x00006003	// �v���e�����[�G���[
//#define		EHW_PLTN_IN_LVL				LVL_FATAL
#define	EHW_CLRNS_SNSR				0x00006004	// �N���A�����X�Z���T�[�̏�
#define		EHW_CLRNS_SNSR_LVL			LVL_FATAL

//				2.5.7.1.2 �������[
#define	EHW_SH_EROM_WRITE			0x00006010	// ���C�����EEPROM�������ݎ��s
#define		EHW_SH_EROM_WRITE_LVL		LVL_FATAL
#define	EHW_SH_FLUSH_ERASE			0x00006011	// ���C����t���b�V���������s
#define		EHW_SH_FLUSH_ERASE_LVL		LVL_FATAL
#define	EHW_SH_FLUSH_WRITE			0x00006012	// ���C����t���b�V���������ݎ��s
#define		EHW_SH_FLUSH_WRITE_LVL		LVL_FATAL


//				2.5.7.1.3 RTC
///#define	EHW_SH_RTCFAULT				0x00006020	// RTC�ُ�
///#define		EHW_SH_RTCFAULT_LVL			LVL_FATAL
#define	EHW_NO_BATTERY				0x00006021	// �o�b�e���[�؂�@���O�Ȃ�
#define		EHW_NO_BATTERY_LVL			LVL_FATAL

// 				2.5.7.1.4 Panel
#define	EHW_PANEL_BTN1				0x00006031	// �N�����Ƀp�l���{�^����������Ă���(platen�{�^��)�B
#define		EHW_PANEL_BTN1_LVL			LVL_FATAL

#define	EHW_PANEL_BTN2				0x00006032	// �N�����Ƀp�l���{�^����������Ă���(print�{�^��)�B
#define		EHW_PANEL_BTN2_LVL			LVL_FATAL

#define	EHW_PANEL_BTN3				0x00006033	// �N�����Ƀp�l���{�^����������Ă���(cancel�{�^��)�B
#define		EHW_PANEL_BTN3_LVL			LVL_FATAL

#define	EHW_PANEL_BTN4				0x00006034	// �N�����Ƀp�l���{�^����������Ă���(back/left�{�^��)�B
#define		EHW_PANEL_BTN4_LVL			LVL_FATAL

#define	EHW_PANEL_BTN5				0x00006035	// �N�����Ƀp�l���{�^����������Ă���(right�{�^��)�B
#define		EHW_PANEL_BTN5_LVL			LVL_FATAL

#define	EHW_PANEL_BTN6				0x00006036	// �N�����Ƀp�l���{�^����������Ă���(down�{�^��)�B
#define		EHW_PANEL_BTN6_LVL			LVL_FATAL

#define	EHW_PANEL_BTN7				0x00006037	// �N�����Ƀp�l���{�^����������Ă���(up�{�^��)�B
#define		EHW_PANEL_BTN7_LVL			LVL_FATAL

#define	EHW_PANEL_BTN8				0x00006038	// �N�����Ƀp�l���{�^����������Ă���(purge�{�^��)�B
#define		EHW_PANEL_BTN8_LVL			LVL_FATAL

#define	EHW_PANEL_BTN9				0x00006039	// �N�����Ƀp�l���{�^����������Ă���(OK/menu�{�^��)�B
#define		EHW_PANEL_BTN9_LVL			LVL_FATAL


// 				2.5.7.1.5 Head Memory


//			2.5.7.2 BY��
//				2.5.7.2.1 �L�����b�W�̏��

#define	EHW_CRG_ERR_BASE			0x00006100
#define		EHW_CRG_ERR_LVL				LVL_FATAL
#define	EHW_CRG_ERR_BUSY			0x00006101
#define	EHW_CRG_ERR_STOP			0x00006102	// �ُ��~
#define	EHW_CRG_ERR_LOCK_ERROR		0x00006103	// �L���b�v���b�N���s
#define	EHW_CRG_ERR_NOT_MOVE		0x00006104	// �܂����������Ȃ�
#define	EHW_CRG_ERR_INIT			0x00006105	// ���_�������Ɏ��s
#define	EHW_CRG_ERR_BUMP_FRAME		0x00006106	// �t���[���ɏՓ˂����\������
#define	EHW_CRG_ERR_BACK_MOVE		0x00006107	// ���]�쓮�����o
#define	EHW_CRG_ERR_SPEED_DOWN		0x00006108	// ���x�ُ̈�ቺ
#define	EHW_CRG_ERR_PRINT_STOP		0x00006109	// ����͈͓� �ُ��~
#define	EHW_CRG_ERR_IN_LOCK			0x00006110	// ���b�J�[�ʒu����o���Ȃ�
#define	EHW_CRG_ERR_CAP_ERR			0x00006111	// �L���b�v�ɏ��グ���Ȃ�

#define	EHW_CRG_ERR_WATCHDOG		0x00006119	// �E�H�b�`�h�b�O���o
#define	EHW_CRG_ERR_REMOVE			0x00006120	// CR��~�ʒu�V���[�g��A�ċN����OK
												//(�G���[�ɂ͂��Ȃ��B�w�b�h�Ƃ�IF��`�̂���Reserve)

#define	EHW_CRG_LOWSPEED			0x00006130	// ���x�ቺ�G���[
#define		EHW_CRG_LOWSPEED_LVL		LVL_MIDDLE
#define	EHW_CRG_HIGHSPEED			0x00006131	// ���x���߃G���[
#define		EHW_CRG_HIGHSPEED_LVL		LVL_MIDDLE
#define	EHW_CRG_STOP_ADJUST			0x00006132	// ��~�����G���[
#define		EHW_CRG_STOP_ADJUST_LVL		LVL_MIDDLE
#define	EHW_CRG_ADJUST_RVS			0x00006133	// ���x�����G���[(RVS)
#define		EHW_CRG_ADJUST_RVS_LVL		LVL_FATAL
#define	EHW_CRG_ADJUST_FWD			0x00006134	// ���x�����G���[(FWD)
#define		EHW_CRG_ADJUST_FWD_LVL		LVL_FATAL

//				2.5.7.2.3 �w�b�h���x�ُ�
#define	EHW_HEAD_TEMP_C				0x00006220	// �J���[�w�b�h ���x�ُ�
#define		EHW_HEAD_TEMP_C_LVL			LVL_FATAL
#define	EHW_HEAD_TEMP_W				0x00006221	// �z���C�g�w�b�h���x�ُ�
#define		EHW_HEAD_TEMP_W_LVL			LVL_FATAL

//				2.5.7.2.4 �w�b�h�d���ُ�
#define	EHW_HEAD_VLTG_C				0x00006230	// �J���[�w�b�h�d���ُ�
#define		EHW_HEAD_VLTG_C_LVL			LVL_FATAL
#define	EHW_HEAD_VLTG_W				0x00006231	// �z���C�g�w�b�h�d���ُ�
#define		EHW_HEAD_VLTG_W_LVL			LVL_FATAL

//				2.5.7.2.5 �w�b�h�̏�
#define	EHW_HEAD_FFC_C				0x00006240	// �J���[�w�b�h FFC �ُ�
#define		EHW_HEAD_FFC_C_LVL			LVL_FATAL
#define	EHW_HEAD_FFC_W				0x00006241	// �z���C�g�w�b�h FFC �ُ�
#define		EHW_HEAD_FFC_W_LVL			LVL_FATAL

//				2.5.7.2.6 �����x�Z���T�ُ�
///#define	EHW_SUR_TEMP				0x00006260	// �����x�Z���T�ُ�
///#define		EHW_SUR_TEMP_LVL			LVL_FATAL

//			2.5.7.3 �����e��
//				2.5.7.3.1 �h���C�o�[�A���[��

/*----------------------------------------------------------------------*/
//		2.5.8 �v���O�����G���[(bit15-12:0111)
//
//				�y7000�ԑ�̃G���[���O�̓��ꃋ�[���z
//					(1) �t�я���1���[�h�ځi�擪4�o�C�g�j�́A�\�[�X��̔������������B
//							1�o�C�g�ځF		�^�X�N�ԍ�
//							2�o�C�g�ځF		�\�[�X�t�@�C���ԍ��i�^�X�N���j
//							3~4�o�C�g�ځF	�ʒu�ԍ��i�\�[�X�t�@�C�����j
/*----------------------------------------------------------------------*/
#define	EPG_SH_SYSCALL				0x00007000		// �V�X�e���R�[���G���[
#define		EPG_SH_SYSCALL_LVL			LVL_FATAL

//#define	EPG_PPC_MALLOC				0x00007003	// �������A���P�[�g���s   �@�@************** �V�X�e���R�[���G���[�ɓ���
//#define		EPG_PPC_MALLOC_LVL			LVL_FATAL
//#define	EPG_SH_FUNC_ARG				0x00007010	// �����ُ�@���폜  �@	************** ��ʃv���O�����G���[�ɓ���
//#define		EPG_SH_FUNC_ARG_LVL			LVL_FATAL
//#define	EPG_SH_FUNC_RTN				0x00007011	// �߂�l�ُ�@���폜  �@	************** ��ʃv���O�����G���[�ɓ���
//#define		EPG_SH_FUNC_RTN_LVL			LVL_FATAL

#define	EPG_TASK_EVENT_TIMEOUT		0x00007012		// ���^�X�N���瑗���Ă���͂��̃C�x���g�����Ȃ��i�C�x���g��M�҂��^�C���A�E�g�j
#define		EPG_TASK_EVENT_TIMEOUT_LVL	LVL_FATAL

#define	EPG_SH_PROG_ERR				0x00007013		// ��ʃv���O�����G���[ �@�@************** �c���@OS�֌W�ȊO�̃\�t�g�E�F�A�G���[
#define		EPG_SH_PROG_ERR_LVL			LVL_FATAL



#define	EPG_SH_WAIT_PRT_END_TIMOUT	0x00007015	// ������I���Ȃ��̂Ŏ��̈���f�[�^����M�ł��Ȃ�
#define		EPG_SH_WAIT_PRT_END_TIMOUT_LVL	LVL_MIDDLE





//==============================================================================//
//	�^�X�N�ԍ�	 �i���O�̔��������������߁A�^�X�N���ɒ�߂�1�o�C�g�̐��l�B���O�̕t�я��̐擪�Ɏc���B�j	//
//==============================================================================//
#define	TNO_MAIN			0x01	// ���C���^�X�N
#define	TNO_DEBUG			0x05	// debug/ �ȉ�
#define	TNO_LIB				0x06	// lib/ �ȉ�
#define TNO_MAIN_CTL		0x10	// �S�̐���^�X�N
#define	TNO_DRIVER			0x13	// driver/ �ȉ�
#define TNO_MAIN_CYCLE		0x15	// �����^�X�N
#define	TNO_MENU			0x20	// ���j���[�^�X�N
#define	TNO_PANEL			0x21	// �p�l���^�X�N
#define	TNO_LCD				0x22	// LCD�^�X�N
#define TNO_INKCTRG			0x25	// �C���N�J�[�g���b�W�^�X�N
#define TNO_SUB_TANK		0x27	// �T�u�^���N�^�X�N
#define TNO_PRINT_MASTER	0x30	// �v�����g�}�X�^�[�^�X�N
#define TNO_ARMANI			0x31	// �A���}�[�j�^�X�N
#define TNO_DATA_EXPAND		0x32	// �f�[�^�W�J�^�X�N
#define	TNO_MNT				0x50	// �����e�^�X�N
#define	TNO_PCIF			0x54	// PCIF���^�X�N
#define	TNO_USB_F			0x55	// USB�t�@���N�V�����^�X�N
#define	TNO_LAN2			0x91	// LAN2 �^�X�N
#define	TNO_LAN3			0x92	// LAN3 �^�X�N
#define	TNO_LOG				0x94	// log �^�X�N



#endif
