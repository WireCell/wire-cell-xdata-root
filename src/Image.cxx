#include "WireCellXdataRoot/Image.h"

#include "TClonesArray.h"

using namespace WireCellXdataRoot;


Image::Image(imageid_t ident,
	     frameid_t frameid)
    : ident(ident)
    , frameid(frameid)
    , blobs(new TClonesArray("WireCellXdataRoot::Blob"))
{

}
Image::~Image()
{
    delete blobs;
}
