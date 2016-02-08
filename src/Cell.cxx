#include "WireCellXdataRoot/Cell.h"

using namespace WireCellXdataRoot;

Cell::Cell() 
    : ident(0)
    , area(-1)
    , center()
{
}

Cell::Cell(uint64_t ident)
    : ident(ident)
    , area(-1)
    , center() 
{
}
Cell::Cell(uint16_t uind, uint16_t vind, uint16_t wind, uint16_t context)
    : ident(ident)
    , area(-1)
    , center() 
{
}
void Cell::set(uint16_t uind, uint16_t vind, uint16_t wind, uint16_t context)
{
    ident = Cell::ident_pack(uind, vind, wind, context);
}

uint64_t Cell::ident_pack(uint16_t uind, uint16_t vind, uint16_t wind, uint16_t context)
{
    uint64_t u = uind;
    uint64_t v = vind;
    uint64_t w = wind;
    uint64_t c = context;
    
    uint64_t pc = (0xffff&c)<<48;
    uint64_t pu = (0xffff&u)<<32;
    uint64_t pv = (0xffff&v)<<16;
    uint64_t pw = (0xffff&w);

    return pc | pu | pv | pw;
}
std::vector<uint16_t> Cell::ident_unpack(uint64_t ident)
{
    uint16_t c = (ident>>48)&0xffff;
    uint16_t u = (ident>>32)&0xffff;
    uint16_t v = (ident>>16)&0xffff;
    uint16_t w = ident&0xffff;

    return std::vector<uint16_t>{u,v,w,c};
}

uint16_t Cell::uind()
{
    Cell::ident_unpack(ident)[0];
}
uint16_t Cell::vind()
{
    Cell::ident_unpack(ident)[1];
}
uint16_t Cell::wind()
{
    Cell::ident_unpack(ident)[2];
}
uint16_t Cell::context()
{
    Cell::ident_unpack(ident)[3];
}
std::vector<uint16_t> Cell::unpacked()
{
    return Cell::ident_unpack(ident);
}
