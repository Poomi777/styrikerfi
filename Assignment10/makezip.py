#!/usr/bin/env python3

import os
import subprocess


def getsubfile(dir):
    try: 
       fn = subprocess.check_output(['make', '-f', dir+"/Makefile", "showsrc"]).decode('utf-8').strip()
       return dir+"/"+fn;
    except:
       return None

files = []
if s1 := getsubfile("p1"): files.append(s1)
if s2 := getsubfile("p2"): files.append(s2)

print("\nSelected files for inclusion: ", files)

user1 = os.getlogin()
print("\nUser name 1:", user1)

user2 = input("\nEnter user name 2 (leave empty if not a group submission): ")

a = input("\nEnter assignment number: ")

filename = "assignment"+a+"-"+user1
if len(user2)>0:
    filename += "-"+user2
filename += ".zip"

print("\n\nCreating file", os.path.abspath(filename))
cmd = ['zip', filename]
cmd += files
subprocess.call(cmd)
