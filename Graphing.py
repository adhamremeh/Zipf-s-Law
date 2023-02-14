import matplotlib.pyplot as plt
from tkinter import *
from tkinter import messagebox
import os
import math
import statistics
import matplotlib.colors as colors
from numpy import absolute

#originalDistribution = input("Enter the same file name")
originalDistribution = "ResultedMap.txt" 

#zipfsEstimatedDistribution = input("Enter the same file name")
zipfsEstimatedDistribution = "ZipfResultedMap.txt"
 
#graphs a sinlge distribution , doesn't perform any operations to the distrubition its given
def drawGraphOfFile(fName ):
    File = open(fName , 'r')
    lines = File.read().splitlines()
    words = []
    x = []
    y = [] 
    for i in lines:
        words.append(i.split())
    for i in words:
        x.append(int(i[0]))
        y.append(int(i[1]))
    # plotting distribution
    plt.plot(x, y)
    
    plt.xlabel('rank')
    plt.ylabel('frequency')

    if(fName[0] == 'R'):
        plt.title("Distribution of original")
    else :
        plt.title("Distribution gussed with Zipf's law")


    plt.show()

   # plt.savefig(fName +"ResultPlot.png")
    plt.figure().clear()
    plt.close()


#plots multiple curves together on one graph , draws the difference visually between curves as a gray area
#to draw the difference we must only be plotting curves related to each other (ie same book or sth) , to draw curves add True when calling the function
#takes a list of fileNames as its main paramter
def compareGraphs(fNames , drawComparison = False):
    #Multidiemnsional array that holds all the y values of all the curves seperately , we dont care about x since x is the same between all of them
    yValues = [[]]
    median = 0.0
    #holds the percentage difference between the Y values of original distribution and Y values of our estimated zipf distribution
    averagePercentageDifference = []
    #draws each curve 
    for  fName in fNames :
        File = open(fName , 'r')
        lines = File.read().splitlines()
        words = []
        x = []
        y = [] 
        for i in lines:
            words.append(i.split())
        for i in words:
            x.append(int(i[0]))
            y.append(int(i[1]))
        # plotting each distribution
        plt.plot(x, y)
        yValues.append(y)
    #toggle drawing the difference on or off , by default it is off
    if(drawComparison):
        plt.fill_between(x , yValues[1]  , yValues[2] , color = 'gray' , interpolate= True )  

        ##finding the percentage difference between each two y values and adding them to our array mentioned above
        index = 0
        for yValue1  , yValue2 in zip(yValues[1] , yValues[2]):
            #percentage difference = difference / average *100
            averagePercentageDifference.append( ( ( (absolute(float(yValue1) - float(yValue2))) / (float(yValue1) + float(yValue2)/2) )*100 ) )
    
    median =  statistics.fmean(averagePercentageDifference)    

    
    plt.xlabel('rank')
    plt.ylabel('frequency')
    plt.title("Compariosn")
    plt.show()
   # plt.savefig(fName +"Comparison.png")
    plt.figure().clear()
    plt.close()
    return     median


# don't remove this variable <3
files = [originalDistribution , zipfsEstimatedDistribution]

#print ("Average Percentage of error = %3.2f %%" % (ErrorPercent))
#print ("Zipfs law is %3.2f %% accurate in this case" % (100.0-ErrorPercent))


window = Tk()

window.title("Zipf's Law APP")

window.geometry('1080x680')

frame = Frame(window)
frame.pack(side="top", expand=True, fill="both")
frame.configure(bg="#34bdb0")

def RUNanother():
    window.destroy()
    os.system("cls")
    os.system("zipfslaw.exe")

def clear_frame():
    for widgets in frame.winfo_children():
        widgets.destroy()

def runError():
    ErrorPercent = compareGraphs(files , True)
    messagebox.showinfo(title="Accuracy", message="Average Percentage of error = %3.2f %%" % (ErrorPercent) + "\n" + "Zipfs law is %3.2f %% accurate in this case" % (100.0-ErrorPercent))
    

def Start():
    sentence = Label(frame, text="Welcome To our application", font=("Arial Bold", 25), bg="#34bdb0", fg="white")
    sentence.pack(pady = (180,10))
    sentence2 = Label(frame, text="Here you can see the different applications of zipf's law", font=("Arial Bold", 22), bg="#34bdb0", fg="white")
    sentence2.pack(pady = 10)
    sentence3 = Label(frame, text="and visualize the result with different types of graphs", font=("Arial Bold", 22), bg="#34bdb0", fg="white")
    sentence3.pack(pady = 10)
    button_border = Frame(frame, highlightbackground = "black", bg = "black", highlightthickness = 0, bd=2)
    button_border.pack(pady = 60)
    startB = Button(button_border, text="Start", bg="#d2bf4a", fg="white", font=("Arial Bold", 18), command = lambda:Choose())
    startB.pack()    

def Choose():
    clear_frame()
    Header = Label(frame, text="Please choose the way you want to show the graph", font=("Arial Bold", 25), bg="#34bdb0", fg="white")

    Header.pack(pady = (150,20))

    button_border2 = Frame(frame, highlightbackground = "black", bg = "black", highlightthickness = 0, bd=2)
    button_border2.pack(pady = (80,20))
    realB = Button(button_border2, text="Real Result Graph", font=("Arial Bold", 15), command = lambda:drawGraphOfFile(originalDistribution), bg="#d2bf4a", fg="white")
    button_border3 = Frame(frame, highlightbackground = "black", bg = "black", highlightthickness = 0, bd=2)
    button_border3.pack(pady = 20)
    zipfsB = Button(button_border3, text="Zipf's Law Graph", font=("Arial Bold", 15), command = lambda:drawGraphOfFile(zipfsEstimatedDistribution), bg="#d2bf4a", fg="white")

    button_border4 = Frame(frame, highlightbackground = "black", bg = "black", highlightthickness = 0, bd=2)
    button_border4.pack(pady = 20)
    compareB = Button(button_border4, text="Comparision between two Graphs", font=("Arial Bold", 15), command = lambda:runError(), bg="#d2bf4a", fg="white")

    button_border5 = Frame(frame, highlightbackground = "black", bg = "black", highlightthickness = 0, bd=2)
    button_border5.pack(pady = 20)
    anotherB = Button(button_border5, text="Run Another File", font=("Arial Bold", 15), command = lambda:RUNanother(), bg="#d2bf4a", fg="white")

    realB.pack()
    zipfsB.pack()
    compareB.pack()
    anotherB.pack()

Start()

window.mainloop()

