#ifndef WIRECELLXDATAROOT_CELL
#define WIRECELLXDATAROOT_CELL

#include "WireCellXdataRoot/Point.h"

#include "TObject.h"

#include <vector>
#include <cstdint>



namespace WireCellXdataRoot {

    /// The geometrical information about a cell and its association with bounding wires.
    struct Cell : public TObject {
	Cell();
	Cell(uint64_t ident);
	Cell(uint16_t uind, uint16_t vind, uint16_t wind, uint16_t context=0);
	void set(uint16_t uind, uint16_t vind, uint16_t wind, uint16_t context=0);

	/// Cell ID packed as: [context|uind|vind|wind].
	uint64_t ident;

	/// Indices into Geom::wires for of U, V and W wires
	/// associated with this cell as well as the context for those
	/// wires.
	uint16_t uind();
	uint16_t vind();
	uint16_t wind();
	uint16_t context();

	std::vector<uint16_t> unpacked();

	// Fixme: the following values are redundant with knowing the
	// associated wires and the tiling algorithm.

	/// Cross-sectional area of cell in the drift direction.
	float area;
	
	/// Center point of cell projected to APA origin in drift direction.
	Point center;

	ClassDef(Cell, 1);

	static 
	uint64_t ident_pack(uint16_t uind, uint16_t vind, uint16_t wind,
			    uint16_t context=0);
	static
	std::vector<uint16_t> ident_unpack(uint64_t ident);


    };

}

#endif
