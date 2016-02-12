#include "WireCellXdataRoot/Deco.h"
using namespace WireCellXdataRoot;

Deco::Deco(chanid_t chanid, slice_t slice,
	   float charge, float uncertainty)
    : chanid(chanid)
    , slice(slice)
    , charge(charge)
    , uncertainty(uncertainty)
{
}


void Deco::Clear(Option_t* opt)
{
    chanid=0;
    slice=0;
    charge=-1;
    uncertainty=-1;
}
