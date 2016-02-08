#ifndef WIRECELLXDATAROOT_LOOKUP
#define WIRECELLXDATAROOT_LOOKUP

#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/Image.h"

#include <vector>

namespace WireCellXdataRoot {

    /** Lookup provides simple de-referencing of indices by
     * maintaining a reverse lookup.  This can be helpful for when
     * writing converters between Xdata and application specific
     * transient data models.
     */
    class Lookup {
	Geom& m_geom;
	Image& m_image;
    public:
	Lookup(Geom& geom, Image& image);

	/// Simple wrappers around lookups into the image.
	Wire* wire(std::size_t wind);
	Cell* cell(std::size_t cind);
	Blob* blob(std::size_t bind);

	/// return wire associated with deco.
	Wire* operator()(Deco* deco);

	/// return wires associated with cell
	std::vector<Wire*> operator()(Cell* cell);

	/// Return cells associated with blob
	std::vector<Cell*> operator()(Blob* blob);
    };


}


#endif
