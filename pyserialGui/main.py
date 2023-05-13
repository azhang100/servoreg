
from tkinter import *
from tkinter import ttk

from terminal import *
from variables import *
from graph import *
from logger import *

class Master:
    def __init__(self, comPort):
    
        #============ make a TkInter Window ==============
        
        self.root = Tk()
        self.root.geometry("1280x800")
        self.root.wm_title("Servoregulator Interface")
        self.root.protocol("WM_DELETE_WINDOW", self.onClosing)
        
        self.note = ttk.Notebook(self.root)
    
        #============ make features ==============
        
        frame = ttk.Frame(self.note)
        frame.pack(fill="both", expand=True)
        self.terminal = Terminal(self, frame, comPort)
        self.note.add(frame, text="terminal")
        
        self.logger = Logger()
        
        frame = ttk.Frame(self.note)
        frame.pack(fill="both", expand=True)
        self.variableManager = VariableManager(self, self.note)
        self.note.add(frame, text="variables")

        # must come after variableManager
        frame = ttk.Frame(self.note)
        frame.pack(fill="both", expand=True)
        self.graphA = Graph(self, self.note, updatePeriod=100, xStep=50)
        self.note.add(frame, text="short graph")
        
        frame = ttk.Frame(self.note)
        frame.pack(fill="both", expand=True)
        self.graphB = Graph(self, self.note, updatePeriod=6000, xStep=50)
        self.note.add(frame, text="long graph")
    
    def onClosing(self):
        self.root.destroy()
        self.terminal.close()
        self.logger.close()

class GetComPort():
    def __init__(self):
        self.root= Tk() # Create an instance of Tkinter frame
        self.root.geometry("300x100")
        #Initialize a Label to display the User Input
        label=Label(self.root, text="Enter Com Port")
        label.pack()
        #Create an Entry widget to accept User Input
        self.entry= Entry(self.root, width=40)
        self.entry.focus_set()
        self.entry.pack()
        #Create a Button to validate Entry Widget
        Button(self.root, text= "Okay",width= 20, command=self.accept).pack(pady=20)
        self.root.bind('<Return>', self.accept)
        self.root.mainloop()
        
    def accept(self, event=None):
        self.result = self.entry.get()
        print("using:", self.result)
        self.root.destroy()
        
    def get(self):
        return self.result
        
#============== run TKInter ==========

comPort = GetComPort().get()
        
master = Master(comPort)
master.root.mainloop()
