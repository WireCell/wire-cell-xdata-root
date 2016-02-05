#!/usr/bin/env python

import os
import ROOT

ROOT.gSystem.Load("libWireCellXdataRoot.so")
wc = ROOT.WireCellXdataRoot     # C++ namespace


myfile = os.path.realpath(__file__)
testdir = os.path.dirname(myfile)
topdir = os.path.dirname(testdir)
incdir = os.path.join(topdir, "inc/WireCellXdataRoot")

def test_create():
    structs = list()
    
    for maybe in os.listdir(incdir):
        if not maybe.endswith('.h'):
            continue
        maybe = os.path.join(incdir, maybe)
        for line in open(maybe):
            if not ' struct ' in line:
                continue
            structs.append(line.split()[1])

    for struct in structs:
        print struct
        Type = getattr(wc, struct)
        obj = Type()
        print obj


if '__main__' == __name__:
    test_create()
    
