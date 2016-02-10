#include "WireCellXdataRoot/Blob.h"

using namespace WireCellXdataRoot;

Blob::Blob(blobid_t ident, int slice, float charge)
    : ident(ident)
    , slice(slice)
    , charge(charge)
{
}
