#!/usr/bin/env python

import ROOT

ROOT.gSystem.Load("libWireCellXdataRoot.so")
wc = ROOT.WireCellXdataRoot     # C++ namespace

url = "test_xdatafile.root"

def test_write():

    xf = wc.XdataFile(url,'w')
    ri = wc.RunInfo(1, "testdet")
    siz = xf.write(ri)
    print siz

    for number in range(1000):
        f = wc.Frame(number)
        siz = xf.append(f);
        #print number, siz, f.ident

def test_read():
    xf = wc.XdataFile(url,'r')
    ri = wc.RunInfo()
    siz = xf.read(ri)
    print siz, ri.ident, ri.detector

    nframes = xf.frames();
    frame = wc.Frame()
    for iframe in range(nframes):
        xf.read(frame, iframe)

if '__main__' == __name__:
    test_write()
    test_read()
    
