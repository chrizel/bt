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
from tkFileDialog import *
import bt

class Editor(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()

        self.master.title("BT Editor")

        self.btitle = Button(self)
        self.btitle["text"] = "Bermuda Triangle\nLevel Editor Controls"
        self.btitle["bg"] = "#efefaf"
        self.btitle["command"] = self.hi_test
        self.btitle.pack(fill="both")

        self.bopen = Button(self)
        self.bopen["text"] = "Open Map"
        self.bopen["command"] = self.bt_open
        self.bopen.pack(fill="both")

        self.bsave = Button(self)
        self.bsave["text"] = "Save Map"
        self.bsave["command"] = self.bt_save
        self.bsave.pack(fill="both")

        self.bexit = Button(self)
        self.bexit["text"] = "Quit BT"
        self.bexit["bg"] = "#efafaf"
        self.bexit["command"] = self.bt_exit
        self.bexit.pack(fill="both")

        print "Python: new editor created"

    def hi_test(self):
        print "hiho"

    def bt_exit(self):
        bt.exit()

    def bt_save(self):
        bt.save_map("mein_test.map")

    def bt_open(self):
        file = askopenfilename(defaultextension="*.map", filetypes=[('Map files', '*.map'), ('All files', '*.*')])
        if file != "":
            bt.open_map(file)

        
