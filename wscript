#!/usr/bin/env wcb
'''
This uses the included "wcb" program.

 $ ./wcb configure --prefix=/path/to/install
 $ ./wcb 
 $ ./wcb install
'''


TOP = '.'
APPNAME = 'WireCellXdataRoot'

def options(opt):
    opt.load('smplpkgs')

def configure(cfg):
    cfg.load('smplpkgs')
    cfg.check_cxx(header_name="Rtypes.h", use='ROOTSYS',
                  mandatory=True)
def build(bld):
    bld.load('smplpkgs')
    bld.smplpkg('WireCellXdataRoot', use='ROOTSYS')
    
