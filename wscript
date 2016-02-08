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

    opt.add_option('--build-debug', default='-O2',
                   help="Build with debug symbols")


def configure(cfg):
    cfg.env.CXXFLAGS += [cfg.options.build_debug]

    cfg.load('smplpkgs')
    cfg.load('rootsys')

    # fixme: this should move into rootsys waf tool
    cfg.check_cxx(header_name="Rtypes.h", use='ROOTSYS',
                  mandatory=True)

    # JSONCPP
    cfg.check_cfg(package='jsoncpp', uselib_store='JSONCPP',
                  args='--cflags --libs', mandatory=True)
    cfg.check(header_name="json/json.h", use='JSONCPP', mandatory=True)
    # fixme: make this optional.  It's just for apps/xdata-json



def build(bld):
    bld.load('smplpkgs')
    bld.smplpkg('WireCellXdataRoot', use='ROOTSYS', app_use='JSONCPP')
    
