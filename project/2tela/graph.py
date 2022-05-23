import random
import time
from tkinter import *

import math  
	  
root = Tk()
    
root['bg'] = "black"
root.title('Two object quest')
root.wm_attributes()
root.geometry('1500x1500')
root.resizable(width = True, height = True)

f_ptr = open('crd.txt', 'r')

x1 = 0.0
x2 = 0.0
y1 = 0.0
y2 = 0.0

flag = 0

size = 24
line = f_ptr.readline()

dist = 555
size_cof = 50


canvas = Canvas(root, height = 1500, width = 1500, bg = "black")
#text_dist = Label(root, text = "dist == " + str(dist))
#text_dist.grid(column = 0, row = 0)

while (flag < 12000):
    line  = line.rstrip('\n')
    line  = line.rstrip(' ')
    #print(flag)


    #print(2)
    if(flag % 4 == 0):
        x1 = float(line)
        #print("x1 ==" + str(x1))
    if(flag % 4 == 1):
        y1 = float(line)
        #print("y1 == " + str(y1))
    if(flag % 4 == 2):
        x2 = float(line)
        #print("x2 == " + str(x2))
    if(flag % 4 == 3):
        y2 = float(line)
        #print("y2 == " + str(y2))
        
        canvas.create_line(x1/size_cof + 500, y1/size_cof + 500, x1/size_cof + 500 + 1, y1/size_cof + 500 + 1, width = 3, fill = "red")
        
        canvas.create_line(x2/size_cof + 500,y2/size_cof + 500,x2/size_cof + 500 + 1, y2/size_cof + 500 + 1, width = 3, fill = "green")
        #canvas.create_line(int(x1/10),int(y1/10),int(x1+1/10), int(y1+1/100), width = 25, fill = "red")
        #canvas.create_line(int(x2/10),int(y2/10),int(x2+1/10), int(y2+1/100), width = 25, fill = "green")
        canvas.pack()
        if(1):
            root.update_idletasks()
            root.update()
            #time.sleep(0.01)
            

    flag += 1
    line = f_ptr.readline()
    
canvas.pack()
root.mainloop()





