#!/usr/bin/python
# Bermuda Triangle - action adventure game
# Copyright (C) 2004 Christian Zeller <chrizel@gmx.net>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

from Tkinter import *
import bt

class Console(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.master.title("Python console")

        self.textbox = Text(self, width=100, height=10)
        self.textbox["bg"] = "white"
        self.textbox.pack(fill="both")

        self.bexec = Button(self)
        self.bexec["text"] = "Execute Python Code"
        self.bexec["command"] = self.exec_code
        self.bexec.pack(fill="both")

        print "Python: new console created"

    def exec_code(self):
        code = self.textbox.get(1.0, END)
        bt.exec_code(code)
        print "Code executed"
