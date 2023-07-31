#! /usr/bin/env python
# -*- coding: shift_jis -*-
import pyautogui
import time
import keyboard
import pyperclip
import subprocess
import ctypes
import sys
import tkinter
from tkinter import filedialog
from tkinter import messagebox
from tkinter import scrolledtext
import threading


# グローバル変数
global end_flag

AUTO_GUI =0
CHECK_FLAG = 1
GET_POS = 2


#----------------------------------------------------------------------------------------------------#
# スレッド開始
def start_thread(thread_num):
    if thread_num == AUTO_GUI:

        thread = threading.Thread(target=auto_GUI)
    elif thread_num == CHECK_FLAG:
        thread = threading.Thread(target=check_flag)
    elif thread_num == GET_POS:
        thread = threading.Thread(target=record_pos)
    
    thread.start()

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# PC操作
def auto_GUI():
    try:
        # 操作ファイル読込
        f = open(text1.get(), "r", encoding="UTF-8")
        lines = f.readlines()
        f.close()
        
        # 関数ファイル読込
        global g_lines
        if text2.get() != "":
            f = open(text2.get(), "r", encoding="UTF-8")
            g_lines = f.readlines()
            f.close()
        
        for line in lines:
            if end_flag == True:
                button_enable("normal")
                button4["state"] = "normal"
                break

            ctrl_motion(line)

        if end_flag == False:
            messagebox.showinfo("確認", "操作が完了しました。")
        else:
            messagebox.showinfo("確認", "操作を中止しました。")

    except Exception as e:
        messagebox.showerror("エラー", e)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# PC操作
def ctrl_motion(array):
    buf = array.split(",")
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
        pyautogui.hotkey("ctrl","v")

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
        pyautogui.hotkey("ctrl","c")
        time.sleep(0.1)
        text3.insert(tkinter.END, pyperclip.paste() + "," + arg1 + "\n")
        text3.see("end")
        text3.update()
          
    # ファイルのオープン
    elif cmd == "OpenFile":
        subprocess.Popen(arg1)

    # 関数(使い回す処理のまとまりで別ファイルに記載)
    elif cmd == "Func":
        end_flag = False
            
        for func_line in g_lines:
            func_buf = func_line.split(",")
            func = func_buf[1]
                    
            if end_flag == False and func == arg1:
                end_flag = True
            elif end_flag == True and func != "":
                ctrl_motion(func_line)
            elif end_flag == True and func == "":
                break

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# PC操作終了フラグチェック
def check_flag():
    global end_flag
    
    # 「ESC」キーで中断
    while True:
        if keyboard.is_pressed("escape"):
            end_flag = True
            break

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# マウス位置記録
def record_pos():
    start_flag = False

    while True:
        # キャンセルボタンがクリックされたか調べる
        if end_flag == True:
            # ボタン等を有効化
            button4["text"] = "記録開始"
            button_enable("normal")
            break

        if ctypes.windll.user32.GetAsyncKeyState(0x01) != 0:
            if start_flag == True:
                x, y = pyautogui.position()
                text3.insert(tkinter.END, "X: " + str(x) + " Y: " + str(y) + "\n")
                text3.see("end")
                text3.update()

            else:
                start_flag = True

            time.sleep(0.1)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# ファイルパス取得
def get_file_path():
    typ = [('テキストファイル','*.txt')] 
    fle = filedialog.askopenfilename(filetypes = typ)
    return fle

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# ボタン有効/無効切替
def button_enable(is_enabled):
        global end_flag
        end_flag = False

        text1["state"] = is_enabled
        text2["state"] = is_enabled
        button1["state"] = is_enabled
        button2["state"] = is_enabled
        button3["state"] = is_enabled
        button5["state"] = is_enabled
    
#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# 「参照」ボタンクリックイベント
def SetCtrlFileButton_Click():
    text1.insert(tkinter.END, get_file_path())

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「参照」ボタンクリックイベント
def SetFuncFileButton_Click():
    text2.insert(tkinter.END, get_file_path())

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「操作開始」ボタンクリックイベント
def StartCtrlButton_Click():
    if text1.get() == "":
        messagebox.showerror("エラー","操作ファイルを選択してください。")
        return

    if messagebox.askokcancel("確認", "自動操作を開始します。"):
        # ボタン等を無効化
        button_enable("disabled")
        button4["state"] = "disabled"
        text3.delete("1.0","end")

        start_thread(AUTO_GUI)
        start_thread(CHECK_FLAG)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「記録開始」ボタンクリックイベント
def StartRecordClickPosButton_Click():
    if button4["text"] == "記録開始":
        if messagebox.askokcancel("確認", "マウスクリック位置の記録を開始します。"):
            # ボタン等を無効化
            button_enable("disabled")
            button4["text"] = "記録中断"
            text3.delete("1.0","end")

            start_thread(GET_POS)

    elif button4["text"] == "記録中断":
        global end_flag
        end_flag = True

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「閉じる」ボタンクリックイベント
def CloseButton_Click():
    if messagebox.askokcancel("確認", "終了しますか？"):
        root.destroy()
    
#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# Main
# ウィンドウ作成
root = tkinter.Tk()
root.title("AutoGUI")
root.geometry("480x250")
root.resizable(False, False)

# ラベル作成
label1 = tkinter.Label(text="操作ファイル")
label1.place(x=10, y=10)
label2 = tkinter.Label(text="関数ファイル")
label2.place(x=10, y=50)
label3 = tkinter.Label(text="出力結果")
label3.place(x=10, y=130)

# テキストボックス作成
text1 = tkinter.Entry(width=50)
text1.place(x=80, y=10)
text2 = tkinter.Entry(width=50)
text2.place(x=80, y=50)
text3= scrolledtext.ScrolledText(root, width=40, height=6)
text3.place(x=80, y=130)

# ボタン作成
button1 = tkinter.Button(text="参照", command=SetCtrlFileButton_Click, width=10)
button1.place(x=390, y=7)

button2 = tkinter.Button(text="参照", command=SetFuncFileButton_Click, width=10)
button2.place(x=390, y=47)

button3 = tkinter.Button(text="操作開始", command=StartCtrlButton_Click, width=10)
button3.place(x=390, y=87)

button4 = tkinter.Button(text="記録開始", command=StartRecordClickPosButton_Click, width=10)
button4.place(x=390, y=127)

button5 = tkinter.Button(text="閉じる", command=CloseButton_Click, width=10)
button5.place(x=390, y=207)

root.mainloop()

#----------------------------------------------------------------------------------------------------#