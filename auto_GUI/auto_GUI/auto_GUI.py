#! /usr/bin/env python
# -*- coding: shift_jis -*-
import pyautogui
import time
import keyboard
import pyperclip
import subprocess
import tkinter
from tkinter import filedialog
from tkinter import messagebox
from tkinter import scrolledtext
from pynput import mouse
import threading


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
            if keyboard.is_pressed("ctrl+z"):
                break

            ctrl_motion(line)

    except Exception as e:
        messagebox.showerror("エラー", e)

    finally:
        button_enable("normal")
        button4["state"] = "normal"
        messagebox.showinfo("確認", "操作を終了しました。")

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
# マウス位置記録
def record_pos():
    mouse_listener = mouse.Listener(on_click=on_click)
    mouse_listener.start()
    
    while True:
        # キャンセルボタンがクリックされたか調べる
        if end_flag == True:
            # ボタン等を有効化
            mouse_listener.stop()
            button4["text"] = "記録開始"
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
    if text1.get() == "":
        messagebox.showerror("エラー","操作ファイルを選択してください。")
        return

    if messagebox.askyesno("確認", "自動操作を開始しますか？\n(途中で中断する場合、「Ctrl+z」キーを押し続けてください)"):
        # ボタン等を無効化
        button_enable("disabled")
        button4["state"] = "disabled"

        start_thread(AUTO_GUI)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# 「記録開始」ボタンクリックイベント
def StartRecordClickPosButton_Click():
    if button4["text"] == "記録開始":
        if messagebox.askyesno("確認", "マウスクリック位置の記録を開始しますか？\n(左クリックした座標を記録します)"):
            # ボタン等を無効化
            button_enable("disabled")
            button4["text"] = "記録中断"

            start_thread(GET_POS)

    elif button4["text"] == "記録中断":
        global end_flag
        end_flag = True

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

button4 = tkinter.Button(text="記録開始", command=StartRecordClickPosButton_Click, width=10)
button4.place(x=390, y=127)

button5 = tkinter.Button(text="閉じる", command=CloseButton_Click, width=10)
button5.place(x=390, y=207)

root.mainloop()

#----------------------------------------------------------------------------------------------------#