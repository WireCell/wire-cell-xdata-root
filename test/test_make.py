#!/usr/bin/env python

import ROOT

ROOT.gSystem.Load("libWireCellXdataRoot.so")
wc = ROOT.WireCellXdataRoot     # C++ namespace

def test_create():
    for Type in [wc.Point, wc.Wire, wc.Cell, wc.Blob, wc.Locus, wc.Blotch, wc.FieldPoint, wc.Field]:
        obj = Type()
        print obj


if '__main__' == __name__:
    test_create()
    
