#ifndef WIRECELLXDATAROOT_GEOM
#define WIRECELLXDATAROOT_GEOM

#include "WireCellXdataRoot/Wire.h"


namespace WireCellXdataRoot {

    /// Collect all geometry info.
    struct Geom {
	Geom();
	~Geom();

	std::vector<Wire*> wires;
    };

}

#endif
