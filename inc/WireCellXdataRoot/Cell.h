#ifndef WIRECELLXDATAROOT_CELL
#define WIRECELLXDATAROOT_CELL

#include "WireCellXdataRoot/Point.h"
#include <cstdint>


namespace WireCellXdataRoot {

    /// The geometrical information about a cell and its association with bounding wires.
    struct Cell {
	Cell();
	Cell(uint32_t uind, uint32_t vind, uint32_t wind);

	/// Index into Wires array for the U, V and W wires associated with this cell.
	uint32_t uind, vind, wind;

	/// Cross-sectional area of cell in the drift direction.
	float area;
	
	/// Center point of cell projected to APA origin in drift direction.
	Point center;
    };

}

#endif
