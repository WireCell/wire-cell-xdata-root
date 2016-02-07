#include "WireCellXdataRoot/Image.h"
using namespace WireCellXdataRoot;

Image::Image(uint64_t ident,
	     uint64_t second, uint32_t nanosecond,
	     double slicespan, double toffset)
    : ident(ident)
    , second(second)
    , nanosecond(nanosecond)
    , slicespan(slicespan)
    , toffset(toffset)
    , decos(new TClonesArray("WireCellXdataRoot::Deco"))
    , cells(new TClonesArray("WireCellXdataRoot::Cell"))
    , blobs(new TClonesArray("WireCellXdataRoot::Blob"))
    , fields(new TClonesArray("WireCellXdataRoot::Field"))
{
}
Image::~Image()
{
    this->clear();
    delete decos;
    delete cells;
    delete blobs;
    delete fields;
}

void Image::clear()
{
    ident = second = nanosecond = 0;
    slicespan = toffset = 0;

    // fixme: add test to see if I need to clear the individual objects in the arrays.
    cells->Clear();
    blobs->Clear();
    fields->Clear();
}

Deco* Image::new_deco(int& index)
{
    index = num_decos();
    Deco* ret = (Deco*)decos->ConstructedAt(index);
    ret->Clear();
    return ret;
}
Deco* Image::get_deco(int index)
{
    return (Deco*)decos->At(index);
}
int Image::num_decos() {
    return decos->GetEntriesFast(); 
}

Cell* Image::new_cell(int& index)
{
    index = num_cells();
    Cell* ret = (Cell*)cells->ConstructedAt(index);
    ret->Clear();
    return ret;
}
Cell* Image::get_cell(int index)
{
    return (Cell*)cells->At(index);
}
int Image::num_cells() {
    return cells->GetEntriesFast(); 
}

Blob* Image::new_blob(int& index)
{
    index = num_blobs();
    Blob* ret = (Blob*)blobs->ConstructedAt(index);
    ret->Clear();
    return ret;
}
Blob* Image::get_blob(int index)
{
    return (Blob*)blobs->At(index);
}
int Image::num_blobs() {
    return blobs->GetEntriesFast(); 
}

Field* Image::new_field(int& index)
{
    index = num_fields();
    Field* ret = (Field*)fields->ConstructedAt(index);
    ret->Clear();
    return ret;
}
Field* Image::get_field(int index)
{
    return (Field*)fields->At(index);
}
int Image::num_fields() {
    return fields->GetEntriesFast(); 
}
