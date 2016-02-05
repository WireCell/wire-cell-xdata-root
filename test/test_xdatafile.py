#!/usr/bin/env python

import ROOT

ROOT.gSystem.Load("libWireCellXdataRoot.so")
wc = ROOT.WireCellXdataRoot     # C++ namespace


def test_write():
    url = "test_xdatafile.root"
    xf = wc.XdataFile(url,'w')
    ri = wc.RunInfo(1, "testdet")
    siz = xf.write(ri)
    print siz

    for number in range(100000):
        f = wc.Frame(number)
        siz = xf.append(f);
        print number, siz, f.ident


if '__main__' == __name__:
    test_write()
    
