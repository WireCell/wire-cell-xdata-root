#include "WireCellXdataRoot/Geom.h"

#include "TClonesArray.h"

using namespace WireCellXdataRoot;

Geom::Geom(geomid_t ident, const std::string& description,
	   const Ray& wire_bounds)
    : ident(ident)
    , description(description)
    , wire_bounds(wire_bounds)
    , pitches()
    , wires(new TClonesArray("WireCellXdataRoot::Wire"))
    , cells(new TClonesArray("WireCellXdataRoot::Cell"))
{
}
Geom::~Geom()
{
    delete cells;
    cells = 0;
    delete wires;
    wires = 0;
}    
