import pyautogui
import time
import keyboard
import pyperclip
import subprocess
import ctypes

# グローバル変数
global g_lines
global g_f

FUNC_FILE = 'func.txt'
OUTPUT_FILE = 'output.txt'

#----------------------------------------------------------------------------------------------------#
# PC操作
def auto_GUI(array):
    buf = array.split(',')
    cmt = buf[0]
    cmd = buf[1]
    arg1 = buf[2]
    arg2 = buf[3]
    arg3 = buf[4]
    arg4 = buf[5]

    # コメント行は処理しない
    if cmt != "":
       return
        
    # 待機(Sleep)
    if cmd == "Sleep":
        time.sleep(float(arg1) / 1000)

    # 移動してクリック
    elif cmd == "Click":
        pyautogui.moveTo(int(arg1), int(arg2))
        pyautogui.click(button="left", clicks=int(arg3))

    # 文字入力
    elif cmd == "Input":
        pyperclip.copy(arg1)
        time.sleep(0.1)
        pyautogui.hotkey('ctrl','v')

    # 特定キー押下(2つ同時まで可)
    elif cmd == "KeyPress":
        pyautogui.hotkey(arg1, arg2)

    # ドラッグ
    elif cmd == "Drug":
        pyautogui.moveTo(int(arg1), int(arg2))
        time.sleep(0.05)
        pyautogui.mouseDown()
        time.sleep(0.05)
        pyautogui.moveTo(int(arg3), int(arg4))
        time.sleep(0.05)
        pyautogui.mouseUp()

    # 情報のコピー
    elif cmd == "Copy":
        pyautogui.hotkey('ctrl','c')
        time.sleep(0.1)
        s_copy = pyperclip.paste() + ',' + arg1
        g_f.write(s_copy + '\n')
        print(s_copy)
          
    # ファイルのオープン
    elif cmd == "OpenFile":
        subprocess.Popen(arg1)

    # 関数(使い回す処理のまとまりで別ファイルに記載)
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
# マウス位置記録
def record_pos():
    print('Press Esc key if you want to abort.')
    
    while True:
        if ctypes.windll.user32.GetAsyncKeyState(0x01) != 0:
            x, y = pyautogui.position()
            s_pos = 'X: ' + str(x) + ' Y: ' + str(y)
            g_f.write(s_pos + '\n')
            print(s_pos)

        # 「ESC」キーで中断
        if keyboard.is_pressed('escape'):
            break

        time.sleep(0.1)
#----------------------------------------------------------------------------------------------------#

    
#----------------------------------------------------------------------------------------------------#
# Main
try:
    # 出力ファイルの内容を削除
    g_f = open(OUTPUT_FILE, 'a')
    g_f.truncate(0)

    print('Choose an option the following list:')
    print('\t0 - Start Automatic PC control')
    print('\t1 - Record click position')
    option = input('Your option? ')
    if option == "0":
        # 操作ファイル入力
        file = input('Input scenario file name in the same folder as the app(.txt): ')
        file = file + '.txt'

        # 操作ファイル読込
        f = open(file, 'r', encoding='UTF-8')
        lines = f.readlines()
        f.close()
        
        # 関数ファイル読込
        f = open(FUNC_FILE, 'r', encoding='UTF-8')
        g_lines = f.readlines()
        f.close()

        print('Press Esc key if you want to abort.')
        time.sleep(0.5)
        
        for line in lines:
            auto_GUI(line)

            # 「ESC」キーで中断
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
    
