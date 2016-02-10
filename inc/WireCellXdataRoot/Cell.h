#ifndef WIRECELLXDATAROOT_CELL
#define WIRECELLXDATAROOT_CELL

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Point.h"

#include "TObject.h"

#include <vector>
#include <cstdint>



namespace WireCellXdataRoot {

    cellid_t cell_ident_pack(wireid_t uid, wireid_t vid, wireid_t wid,
			     tilingid_t tiling=0);

    std::vector<uint16_t> cell_ident_unpack(cellid_t ident);



    /// The geometrical information about a cell and its association with bounding wires.
    struct Cell : public TObject {
	Cell();
	Cell(cellid_t ident);
	Cell(wireid_t uid, wireid_t vid, wireid_t wid, tilingid_t tilingid=0);
	void set(wireid_t uid, wireid_t vid, wireid_t wid, tilingid_t tilingid=0);

	/// Cell ID packed as: [tilingid|uid|vid|wid].
	cellid_t ident;

	/// The wire IDs of the associated wire from each plane. 
	wireid_t uid();
	wireid_t vid();
	wireid_t wid();

	/// The tiling is mostly to fill in the remaining two bytes
	/// with something but can be used to indicate which tiling
	/// was used to create the cell in order to account for
	/// differing cells which might otherwise share the same wire
	/// triplet.
	tilingid_t tiling();

	std::vector<wireid_t> wireids();

	// Fixme: the following values are redundant but mildly costly
	// to recalculate.

	/// Cross-sectional area of cell in the drift direction.
	float area;
	
	/// Center point of cell projected to APA origin in drift direction.
	Point center;

	std::vector<uint16_t> unpacked();

	ClassDef(Cell, 1);

    };

}

#endif
