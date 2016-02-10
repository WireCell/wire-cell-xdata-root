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

