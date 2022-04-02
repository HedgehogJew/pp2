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

x1_a = [0.0]
x2_a = [0.0]
x3_a = [0.0]
y1_a = [0.0]
y2_a = [0.0]
y3_a = [0.0]



size = 24
line = f_ptr.readline()
line  = line.rstrip('\n')
line  = line.rstrip(' ')

body_num = int(line)

line = f_ptr.readline()

dist = 555
size_cof = 30

flag = 0
check = 0
steps = 8000

print("body num == "+ str(body_num))

while (flag < (steps *  body_num * 2)):
    line  = line.rstrip('\n')
    line  = line.rstrip(' ')
    #print(flag)


    #print(2)
    if((flag % (body_num * 2) == 0) and (check <= body_num * 2)):
        x1_a.append(float(line))
        check += 1
        #print("x1 ==" + str(x1_a[int(flag/4)]))
    if((flag % (body_num * 2) == 1) and (check <= body_num * 2)):
        y1_a.append(float(line))
        check += 1
        #print("y1 == " + str(y1_a[int(flag/4)]))
    if((flag % (body_num * 2) == 2) and (check <= body_num * 2)):
        x2_a.append(float(line))
        check += 1
        #print("x2 == " + str(x2_a[int(flag/4)]))
    if((flag % (body_num * 2) == 3) and (check <= body_num * 2)):
        y2_a.append(float(line))
        check += 1
        #print("y2_a[] == " + str(y2_a[int(flag/4)]))

    if((flag % (body_num * 2) == 4) and (check <= body_num * 2)):
        x3_a.append(float(line))
        check += 1
    if((flag % (body_num * 2) == 5) and (check <= body_num * 2)):
        y3_a.append(float(line))
        check += 1
    
    if(check >= body_num * 2):
        check = 0

    flag += 1
    line = f_ptr.readline()
    #print(line)

if (0):
    for j in range (steps * body_num) :
        print ("j == " + str(j))
        print("x1 ==" + str(x1_a[int(j)]))
        print("y1 == " + str(y1_a[int(j)]))
        print("x2 == " + str(x2_a[int(j)]))
        print("y2_a[] == " + str(y2_a[int(j)]))


canvas = Canvas(root, height = 1500, width = 1500, bg = "black")
i = 0
#text_dist = Label(root, text = "dist == " + str(dist))
#text_dist.grid(column = 0, row = 0)

for i in range (steps * body_num) :
        canvas.create_line((x1_a[i])/size_cof + 500, (y1_a[i])/size_cof + 500, (x1_a[i])/size_cof + 500 + 1, (y1_a[i])/size_cof + 500 + 1, width = 3, fill = "red")

        canvas.create_line(x2_a[i]/size_cof + 500,y2_a[i]/size_cof + 500,x2_a[i]/size_cof + 500 + 1, y2_a[i]/size_cof + 500 + 1, width = 3, fill = "green")
        canvas.create_line(x3_a[i]/size_cof + 500,y3_a[i]/size_cof + 500,x3_a[i]/size_cof + 500 + 1, y3_a[i]/size_cof + 500 + 1, width = 3, fill = "blue")
        #canvas.create_line(int(x1/10),int(y1/10),int(x1+1/10), int(y1+1/100), width = 25, fill = "red")
        #canvas.create_line(int(x2/10),int(y2/10),int(x2+1/10), int(y2+1/100), width = 25, fill = "green")
        canvas.pack()
        
        if(1):
            root.update_idletasks()
            root.update()
            #time.sleep(0.01)

    
canvas.pack()
root.mainloop()





