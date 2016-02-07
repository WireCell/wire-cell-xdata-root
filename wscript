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
    opt.load('rootsys')
    opt.load('boost')
    opt.add_option('--build-debug', default='-O2',
                   help="Build with debug symbols")


def configure(cfg):
    cfg.load('smplpkgs')
    cfg.load('rootsys')
    cfg.load('boost')
    cfg.check_cxx(header_name="Rtypes.h", use='ROOTSYS',
                  mandatory=True)
    cfg.check_boost(lib='system filesystem program_options',
                    mandatory=True)
    cfg.env.CXXFLAGS += [cfg.options.build_debug]

def build(bld):
    bld.load('smplpkgs')
    bld.smplpkg('WireCellXdataRoot', use='ROOTSYS')
    
