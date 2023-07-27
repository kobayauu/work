import pyautogui
import time
import keyboard
import pyperclip
import subprocess
import ctypes

# �O���[�o���ϐ�
global g_lines
global g_f

FUNC_FILE = 'func.txt'
OUTPUT_FILE = 'output.txt'

#----------------------------------------------------------------------------------------------------#
# PC����
def auto_GUI(array):
    buf = array.split(',')
    cmt = buf[0]
    cmd = buf[1]
    arg1 = buf[2]
    arg2 = buf[3]
    arg3 = buf[4]
    arg4 = buf[5]

    # �R�����g�s�͏������Ȃ�
    if cmt != "":
       return
        
    # �ҋ@(Sleep)
    if cmd == "Sleep":
        time.sleep(float(arg1) / 1000)

    # �ړ����ăN���b�N
    elif cmd == "Click":
        pyautogui.moveTo(int(arg1), int(arg2))
        pyautogui.click(button="left", clicks=int(arg3))

    # ��������
    elif cmd == "Input":
        pyperclip.copy(arg1)
        time.sleep(0.1)
        pyautogui.hotkey('ctrl','v')

    # ����L�[����(2�����܂ŉ�)
    elif cmd == "KeyPress":
        pyautogui.hotkey(arg1, arg2)

    # �h���b�O
    elif cmd == "Drug":
        pyautogui.moveTo(int(arg1), int(arg2))
        time.sleep(0.05)
        pyautogui.mouseDown()
        time.sleep(0.05)
        pyautogui.moveTo(int(arg3), int(arg4))
        time.sleep(0.05)
        pyautogui.mouseUp()

    # ���̃R�s�[
    elif cmd == "Copy":
        pyautogui.hotkey('ctrl','c')
        time.sleep(0.1)
        s_copy = pyperclip.paste() + ',' + arg1
        g_f.write(s_copy + '\n')
        print(s_copy)
          
    # �t�@�C���̃I�[�v��
    elif cmd == "OpenFile":
        subprocess.Popen(arg1)

    # �֐�(�g���񂷏����̂܂Ƃ܂�ŕʃt�@�C���ɋL��)
    elif cmd == "Func":
        end_flag = False
            
        for func_line in g_lines:
            func_buf = func_line.split(',')
            func = func_buf[1]
                    
            if end_flag == False and func == arg1:
                end_flag = True
            elif end_flag == True and func != "":
                auto_GUI(func_line)
            elif end_flag == True and func == "":
                break

#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# �}�E�X�ʒu�L�^
def record_pos():
    print('Press Esc key if you want to abort.')
    
    while True:
        if ctypes.windll.user32.GetAsyncKeyState(0x01) != 0:
            x, y = pyautogui.position()
            s_pos = 'X: ' + str(x) + ' Y: ' + str(y)
            g_f.write(s_pos + '\n')
            print(s_pos)

        # �uESC�v�L�[�Œ��f
        if keyboard.is_pressed('escape'):
            break

        time.sleep(0.1)
#----------------------------------------------------------------------------------------------------#

    
#----------------------------------------------------------------------------------------------------#
# Main
try:
    # �o�̓t�@�C���̓��e���폜
    g_f = open(OUTPUT_FILE, 'a')
    g_f.truncate(0)

    print('Choose an option the following list:')
    print('\t0 - Start Automatic PC control')
    print('\t1 - Record click position')
    option = input('Your option? ')
    if option == "0":
        # ����t�@�C������
        file = input('Input scenario file name in the same folder as the app(.txt): ')
        file = file + '.txt'

        # ����t�@�C���Ǎ�
        f = open(file, 'r', encoding='UTF-8')
        lines = f.readlines()
        f.close()
        
        # �֐��t�@�C���Ǎ�
        f = open(FUNC_FILE, 'r', encoding='UTF-8')
        g_lines = f.readlines()
        f.close()

        print('Press Esc key if you want to abort.')
        time.sleep(0.5)
        
        for line in lines:
            auto_GUI(line)

            # �uESC�v�L�[�Œ��f
            if keyboard.is_pressed('escape'):
                break

    elif option == "1":
        record_pos()

except Exception as e:
    print(e)
    
finally:
    g_f.close()
    input('Press Enter key to close the app...')
#----------------------------------------------------------------------------------------------------#
    

