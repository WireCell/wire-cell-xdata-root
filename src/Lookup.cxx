#include "WireCellXdataRoot/Lookup.h"

using namespace WireCellXdataRoot;

Lookup::Lookup(Geom& geom, Image& image)
    : m_geom(geom)
    , m_image(image)
{
}


Wire* Lookup::wire(std::size_t ind)
{
    if (ind >= m_geom.wires.size()) { return nullptr; }
    return m_geom.wires[ind];

}
Cell* Lookup::cell(std::size_t ind)
{
    return m_image.get_cell(ind);
}
Blob* Lookup::blob(std::size_t ind)
{
    return m_image.get_blob(ind);
}

Wire* Lookup::operator()(Deco* deco)
{
    return wire(deco->wireind);
}

std::vector<Wire*> Lookup::operator()(Cell* cell)
{
    auto up = cell->unpacked();
    return std::vector<Wire*>{wire(up[0]), wire(up[1]), wire(up[2])};
}

std::vector<Cell*> Lookup::operator()(Blob* blob)
{
    std::vector<Cell*> ret;
    for (auto cind : blob->cellind) {
	ret.push_back(m_image.get_cell(cind));
    }
    return ret;
}
