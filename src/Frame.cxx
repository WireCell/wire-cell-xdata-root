#include "WireCellXdataRoot/Frame.h"
#include "TClonesArray.h"

using namespace WireCellXdataRoot;

Frame::Frame(frameid_t ident,
	      trigid_t trigid,
	      geomid_t geomid,
	      double toffset,
	      double slicespan)
    : ident(ident)
    , trigid(trigid)
    , geomid(geomid)
    , toffset(toffset)
    , slicespan(slicespan)
    , decos(new TClonesArray("WireCellXdataRoot::Deco"))
{
}

Frame::~Frame()
{
    delete decos; decos = nullptr;
}


