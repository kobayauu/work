/**
 * LogCode_LogReader.h
 */

#ifndef _LogCode_H
#define _LogCode_H

#define CODE_POWERON		0x00010000	// �d���I��
#define CODE_PURGESTART		0x92000000	// �p�[�W�J�n
#define CODE_TESTPRINT		0x12300000	// �e�X�g���
/*
#define CODE_PURGE_K		0x02110000	// �p�[�W�J�n�u���b�N
#define CODE_PURGE_M		0x02120000	// �p�[�W�J�n�}�[���^
#define CODE_PURGE_C		0x02130000	// �p�[�W�J�n�V�A��
#define CODE_PURGE_Y		0x02140000	// �p�[�W�J�n�C�G���[
#define CODE_TESTPRINT		0x02200000	// �e�X�g��
*/
#define CODE_AUTOPURGE		0x03000000	// �����p�[�W�J�n
#define CODE_MNT_WIPER_C	0x15000000	// �����e���i�|������ ���C�p�[�N���[�i����(�J���[)
#define CODE_MNT_WIPER_W	0x15010000	// �����e���i�|������ ���C�p�[�N���[�i����(��)
#define CODE_MNT_FLUSH_C	0x15200000	// �����e���i�|������ �t���b�V���O�t�H�[������(�J���[)
#define CODE_MNT_FLUSH_W	0x15210000	// �����e���i�|������ �t���b�V���O�t�H�[������(��)
/*
#define CODE_JOBSTART		0x20000000	// �v�����g�W���u��M�J�n
#define CODE_JOBEND			0x20010000	// �v�����g�W���u��M����
*/
#define CODE_JOBNAME		0x90080000	// ���O�A�ԁA�W���u�l�[��
#define CODE_JOBCOMMENT		0x90090000	// ���O�A�ԁA�W���u�R�����g
#define CODE_JOBALL			0x90110000	// ���O�A�ԁA�����
#define CODE_GRAPHIC		0x90120000	// ���O�A�ԁA�O���t�B�b�N
#define CODE_PCINFO			0x90130000	// ���O�A�ԁAPC���
#define CODE_PRINTSTART		0x91000000	// ���O�A�ԁA����J�n
#define CODE_PRINTEND		0x91010000	// ���O�A�ԁA�������
#define CODE_PRINTSTOP		0x91020000	// ���O�A�ԁA������~
#define	CODE_HISTORY		0x14000000	// ���O�A�ԁA��M�����������f�[�^��I��

#define	CODE_USB_FILE_LOAD	0x12600000	// USB����������ARP �t�@�C�����[�h 
/*
#define CODE_EMP_K_INK		0x00002020	// �C���N�� 
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
#define LEVEL_FATAL			0	// �\�����Ȃ��d��ȃG���[�i�̏�F�V�X�e�����~����j
#define LEVEL_SERIOUS		1	// �V�X�e�����p���ł��Ȃ��d��ȃG���[�i���Z�b�g�ŕ�������j
#define LEVEL_MIDDLE		2	// ���݂̏����̒��~���K�v�Ȃقǂ̏d��ȃG���[
#define LEVEL_WARNING		3	// ���݂̏����͌p���ł��邪�A���̌�̈���Ɏx�Ⴊ���肻���ȃG���[
#define LEVEL_EVENT1		4	// �d�v�ȃC�x���g
#define LEVEL_EVENT2		5	// �ʏ�̃C�x���g
#define LEVEL_EVENT3		6	// ���ߓI�ȃC�x���g
#define LEVEL_INFO			7	// �⑫�I�ȏ��

#endif
