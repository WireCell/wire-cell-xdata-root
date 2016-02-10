#include "WireCellXdataRoot/Frame.h"
#include "TClonesArray.h"

using namespace WireCellXdataRoot;

Frame::Frame(frameid_t ident,
	      trigid_t trigid,
	      double toffset,
	      double slicespan)
    : ident(ident)
    , trigid(trigid)
    , toffset(toffset)
    , slicespan(slicespan)
    , decos(new TClonesArray("WireCellXdataRoot::Deco"))
{
}

Frame::~Frame()
{
    delete decos; decos = nullptr;
}


