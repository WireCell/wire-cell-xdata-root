#include "WireCellXdataRoot/Blob.h"

using namespace WireCellXdataRoot;

Blob::Blob(blobid_t ident, int slice, float charge)
    : ident(ident)
    , slice(slice)
    , charge(charge)
{
}



void Blob::Clear(Option_t* opt)
{
    ident = 0;
    slice = 0;
    charge = 0;
    cellids.clear();
}
