#include "WireCellXdataRoot/Cell.h"

using namespace WireCellXdataRoot;




Cell::Cell() 
    : ident(0)
    , area(-1)
    , center()
{
}

Cell::Cell(cellid_t ident)
    : ident(ident)
    , area(-1)
    , center() 
{
}
Cell::Cell(wireid_t uid, wireid_t vid, wireid_t wid, tilingid_t tilingid)
    : ident(0)
    , area(-1)
    , center() 
{
    set(uid, vid, wid, tilingid);
}
void Cell::set(wireid_t uid, wireid_t vid, wireid_t wid, tilingid_t tilingid)
{
    ident = cell_ident_pack(uid, vid, wid, tilingid);
}

uint64_t WireCellXdataRoot::cell_ident_pack(uint16_t uid, uint16_t vid, uint16_t wid, uint16_t tilingid)
{
    uint64_t u = uid;
    uint64_t v = vid;
    uint64_t w = wid;
    uint64_t c = tilingid;
    
    uint64_t pc = (0xffff&c)<<48;
    uint64_t pu = (0xffff&u)<<32;
    uint64_t pv = (0xffff&v)<<16;
    uint64_t pw = (0xffff&w);

    return pc | pu | pv | pw;
}
std::vector<uint16_t> WireCellXdataRoot::cell_ident_unpack(uint64_t ident)
{
    uint16_t c = (ident>>48)&0xffff;
    uint16_t u = (ident>>32)&0xffff;
    uint16_t v = (ident>>16)&0xffff;
    uint16_t w = ident&0xffff;

    return std::vector<uint16_t>{u,v,w,c};
}

uint16_t Cell::uid()
{
    return cell_ident_unpack(ident)[0];
}
uint16_t Cell::vid()
{
    return cell_ident_unpack(ident)[1];
}
uint16_t Cell::wid()
{
    return cell_ident_unpack(ident)[2];
}
uint16_t Cell::tiling()
{
    return cell_ident_unpack(ident)[3];
}
std::vector<uint16_t> Cell::unpacked()
{
    return cell_ident_unpack(ident);
}

void Cell::Clear(Option_t* opt)
{
    ident = 0;
    area = -1;
    center = Point();
}
