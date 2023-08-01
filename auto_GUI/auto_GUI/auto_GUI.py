#! /usr/bin/env python
# -*- coding: shift_jis -*-
import os
import pyautogui
import time
import keyboard
import pyperclip
import subprocess
import threading
import tkinter
from tkinter import filedialog
from tkinter import messagebox
from tkinter import scrolledtext
from pynput import mouse


AUTO_GUI =0
GET_POS = 1


#----------------------------------------------------------------------------------------------------#
# スレッド開始
def start_thread(thread_num):
    if thread_num == AUTO_GUI:
        thread = threading.Thread(target=auto_GUI)
    elif thread_num == GET_POS:
        thread = threading.Thread(target=record_pos)
    
    thread.start()

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# PC操作
def auto_GUI():
    try:
        # 操作ファイル読込
        ctrl_file = text1.get()
        f = open(ctrl_file, "r", encoding="UTF-8")
        lines = f.readlines()
        f.close()
        
        # 関数ファイル読込
        global g_lines
        func_file = text2.get()
        if func_file != "":
            f = open(func_file, "r", encoding="UTF-8")
            g_lines = f.readlines()
            f.close()
        
        for line in lines:
            if keyboard.is_pressed("ctrl+z"):
                break

            if ctrl_motion(line) != 0:
                break
            
        messagebox.showinfo("確認", "操作を終了しました。")

    except Exception as e:
        messagebox.showerror("エラー", e)

    finally:
        button_enable("normal")
        button4["state"] = "normal"

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# マウス及びキーボード操作
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
       return 0
        
    # 待機(Sleep)
    if cmd == "Sleep":
        time.sleep(float(arg1) / 1000)

    # メッセージボックス表示
    elif cmd == "Message":
        if messagebox.askyesno("確認", arg1 + "\n操作を中断しますか？"):
            return 1

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

    return 0

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# マウス位置記録
def record_pos():
    mouse_listener = mouse.Listener(on_click=on_click)
    mouse_listener.start()
    
    while True:
        # キャンセルボタンがクリックされたか調べる
        if stop_flag == True:
            # ボタン等を有効化
            mouse_listener.stop()
            button4["text"] = "取得開始"
            button_enable("normal")
            
            break

        time.sleep(0.2)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# マウスクリック時のイベント
def on_click(x, y, button, pressed):
    if pressed:
        x, y = pyautogui.position()
        text3.insert(tkinter.END, "X: " + str(x).center(4) + " Y: " + str(y) + "\n")
        text3.see("end")
        text3.update()

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# ファイルパス取得
def get_file_path():
    typ = [("テキストファイル","*txt;*.csv")] 
    fle = filedialog.askopenfilename(filetypes = typ)
    return fle

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# ボタン有効/無効切替
def button_enable(is_enabled):
        global stop_flag
        stop_flag = False

        text1["state"] = is_enabled
        text2["state"] = is_enabled
        button1["state"] = is_enabled
        button2["state"] = is_enabled
        button3["state"] = is_enabled
        button5["state"] = is_enabled

        if is_enabled == "disabled":
            text3.delete("1.0","end")
    
#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# 「参照」ボタンクリックイベント(操作ファイル)
def SetCtrlFileButton_Click():
    text1.insert(tkinter.END, get_file_path())
    text1.focus_set()
    pyautogui.hotkey("right")

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「参照」ボタンクリックイベント(関数ファイル)
def SetFuncFileButton_Click():
    text2.insert(tkinter.END, get_file_path())
    text2.focus_set()
    pyautogui.hotkey("right")

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「操作開始」ボタンクリックイベント
def StartCtrlButton_Click():
    if messagebox.askokcancel("確認", "自動操作を開始します。\n(中断する場合、「Ctrl(Command) + z」を押し続けてください)"):
        # ボタン等を無効化
        button_enable("disabled")
        button4["state"] = "disabled"

        start_thread(AUTO_GUI)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「記録開始」ボタンクリックイベント
def StartRecordClickPosButton_Click():
    if button4["text"] == "取得開始":
        if messagebox.askokcancel("確認", "マウスクリック座標の取得を開始します。"):
            # ボタン等を無効化
            button_enable("disabled")
            button4["text"] = "取得停止"

            start_thread(GET_POS)

    elif button4["text"] == "取得停止":
        global stop_flag
        stop_flag = True

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「閉じる」ボタンクリックイベント
def CloseButton_Click():
    if messagebox.askyesno("確認", "終了しますか？"):
        root.destroy()
    
#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「×」ボタンの無効化
def click_close():
    pass

#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# Main
# ウィンドウ作成
root = tkinter.Tk()
root.title("AutoGUI")
root.geometry("480x250")
root.resizable(False, False)
root.protocol("WM_DELETE_WINDOW", click_close)

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

button4 = tkinter.Button(text="取得開始", command=StartRecordClickPosButton_Click, width=10)
button4.place(x=390, y=127)

button5 = tkinter.Button(text="閉じる", command=CloseButton_Click, width=10)
button5.place(x=390, y=217)

root.mainloop()

#----------------------------------------------------------------------------------------------------#