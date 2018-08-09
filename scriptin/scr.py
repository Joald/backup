from os import walk

## Replaces the instances of 'std::shared_ptr<T>' with 'T*'.
## Doesn't work if T is templated or if there are multiple
## templates in one line. 

def replacer(fil):
    f = open(fil, 'r')
    print("entering " + fil + "...")
    toWrite = []
    toAmend = []
    for line in f:
        if("std::shared_ptr<" in line):
            toWrite.append(line.replace("std::shared_ptr<", "", 1).replace(">", "*", 1))
            print('switching line:\n' + line + "with:\n" + toWrite[-1])
        else:
            toWrite.append(line)
    
    w = open(fil, 'w')
    w.write("".join(toWrite))                
                


## Calls replacer on every file in the directory and its subdirectories.
## This script is omitted from the calling.

def walker():
    files = []
    for (dirpath, dirnames, filenames) in walk("."):
        for i in filenames:
            files.append(dirpath[2:] + ("/" if dirpath[2:] != "" else "") + i)
    for i in files:
        if(i != "scr.py"):
            replacer(i)

## Script function call
walker()
