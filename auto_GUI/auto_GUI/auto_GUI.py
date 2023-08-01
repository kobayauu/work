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
# �X���b�h�J�n
def start_thread(thread_num):
    if thread_num == AUTO_GUI:
        thread = threading.Thread(target=auto_GUI)
    elif thread_num == GET_POS:
        thread = threading.Thread(target=record_pos)
    
    thread.start()

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# PC����
def auto_GUI():
    try:
        # ����t�@�C���Ǎ�
        ctrl_file = text1.get()
        f = open(ctrl_file, "r", encoding="UTF-8")
        lines = f.readlines()
        f.close()
        
        # �֐��t�@�C���Ǎ�
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
            
        messagebox.showinfo("�m�F", "������I�����܂����B")

    except Exception as e:
        messagebox.showerror("�G���[", e)

    finally:
        button_enable("normal")
        button4["state"] = "normal"

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �}�E�X�y�уL�[�{�[�h����
def ctrl_motion(array):
    buf = array.split(",")
    cmt = buf[0]
    cmd = buf[1]
    arg1 = buf[2]
    arg2 = buf[3]
    arg3 = buf[4]
    arg4 = buf[5]

    # �R�����g�s�͏������Ȃ�
    if cmt != "":
       return 0
        
    # �ҋ@(Sleep)
    if cmd == "Sleep":
        time.sleep(float(arg1) / 1000)

    # ���b�Z�[�W�{�b�N�X�\��
    elif cmd == "Message":
        if messagebox.askyesno("�m�F", arg1 + "\n����𒆒f���܂����H"):
            return 1

    # �ړ����ăN���b�N
    elif cmd == "Click":
        pyautogui.moveTo(int(arg1), int(arg2))
        pyautogui.click(button="left", clicks=int(arg3))

    # ��������
    elif cmd == "Input":
        pyperclip.copy(arg1)
        time.sleep(0.1)
        pyautogui.hotkey("ctrl","v")

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
        pyautogui.hotkey("ctrl","c")
        time.sleep(0.1)
        text3.insert(tkinter.END, pyperclip.paste() + "," + arg1 + "\n")
        text3.see("end")
        text3.update()
          
    # �t�@�C���̃I�[�v��
    elif cmd == "OpenFile":
        subprocess.Popen(arg1)

    # �֐�(�g���񂷏����̂܂Ƃ܂�ŕʃt�@�C���ɋL��)
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
# �}�E�X�ʒu�L�^
def record_pos():
    mouse_listener = mouse.Listener(on_click=on_click)
    mouse_listener.start()
    
    while True:
        # �L�����Z���{�^�����N���b�N���ꂽ�����ׂ�
        if stop_flag == True:
            # �{�^������L����
            mouse_listener.stop()
            button4["text"] = "�擾�J�n"
            button_enable("normal")
            
            break

        time.sleep(0.2)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �}�E�X�N���b�N���̃C�x���g
def on_click(x, y, button, pressed):
    if pressed:
        x, y = pyautogui.position()
        text3.insert(tkinter.END, "X: " + str(x).center(4) + " Y: " + str(y) + "\n")
        text3.see("end")
        text3.update()

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �t�@�C���p�X�擾
def get_file_path():
    typ = [("�e�L�X�g�t�@�C��","*txt;*.csv")] 
    fle = filedialog.askopenfilename(filetypes = typ)
    return fle

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �{�^���L��/�����ؑ�
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
# �u�Q�Ɓv�{�^���N���b�N�C�x���g(����t�@�C��)
def SetCtrlFileButton_Click():
    text1.insert(tkinter.END, get_file_path())
    text1.focus_set()
    pyautogui.hotkey("right")

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �u�Q�Ɓv�{�^���N���b�N�C�x���g(�֐��t�@�C��)
def SetFuncFileButton_Click():
    text2.insert(tkinter.END, get_file_path())
    text2.focus_set()
    pyautogui.hotkey("right")

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �u����J�n�v�{�^���N���b�N�C�x���g
def StartCtrlButton_Click():
    if messagebox.askokcancel("�m�F", "����������J�n���܂��B\n(���f����ꍇ�A�uCtrl(Command) + z�v�����������Ă�������)"):
        # �{�^�����𖳌���
        button_enable("disabled")
        button4["state"] = "disabled"

        start_thread(AUTO_GUI)

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �u�L�^�J�n�v�{�^���N���b�N�C�x���g
def StartRecordClickPosButton_Click():
    if button4["text"] == "�擾�J�n":
        if messagebox.askokcancel("�m�F", "�}�E�X�N���b�N���W�̎擾���J�n���܂��B"):
            # �{�^�����𖳌���
            button_enable("disabled")
            button4["text"] = "�擾��~"

            start_thread(GET_POS)

    elif button4["text"] == "�擾��~":
        global stop_flag
        stop_flag = True

#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �u����v�{�^���N���b�N�C�x���g
def CloseButton_Click():
    if messagebox.askyesno("�m�F", "�I�����܂����H"):
        root.destroy()
    
#----------------------------------------------------------------------------------------------------#

#----------------------------------------------------------------------------------------------------#
# �u�~�v�{�^���̖�����
def click_close():
    pass

#----------------------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------------------#
# Main
# �E�B���h�E�쐬
root = tkinter.Tk()
root.title("AutoGUI")
root.geometry("480x250")
root.resizable(False, False)
root.protocol("WM_DELETE_WINDOW", click_close)

# ���x���쐬
label1 = tkinter.Label(text="����t�@�C��")
label1.place(x=10, y=10)
label2 = tkinter.Label(text="�֐��t�@�C��")
label2.place(x=10, y=50)
label3 = tkinter.Label(text="�o�͌���")
label3.place(x=10, y=130)

# �e�L�X�g�{�b�N�X�쐬
text1 = tkinter.Entry(width=50)
text1.place(x=80, y=10)
text2 = tkinter.Entry(width=50)
text2.place(x=80, y=50)
text3= scrolledtext.ScrolledText(root, width=40, height=6)
text3.place(x=80, y=130)

# �{�^���쐬
button1 = tkinter.Button(text="�Q��", command=SetCtrlFileButton_Click, width=10)
button1.place(x=390, y=7)

button2 = tkinter.Button(text="�Q��", command=SetFuncFileButton_Click, width=10)
button2.place(x=390, y=47)

button3 = tkinter.Button(text="����J�n", command=StartCtrlButton_Click, width=10)
button3.place(x=390, y=87)

button4 = tkinter.Button(text="�擾�J�n", command=StartRecordClickPosButton_Click, width=10)
button4.place(x=390, y=127)

button5 = tkinter.Button(text="����", command=CloseButton_Click, width=10)
button5.place(x=390, y=217)

root.mainloop()

#----------------------------------------------------------------------------------------------------#