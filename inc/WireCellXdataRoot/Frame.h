#ifndef WIRECELLXDATAROOT_FRAME
#define WIRECELLXDATAROOT_FRAME

#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Blotch.h"
#include "WireCellXdataRoot/Field.h"

namespace WireCellXdataRoot {

    /** A frame collects all objects relevant for one contiguous
     * readout of the wires.
     *
     */
    struct Frame {
	Frame(int ident=-1);

	/// An identifying number for this frame.
	int ident;

	/// All the primitive cells referenced elsewhere.
	std::vector<Cell> cells;

	/// Any organization of cells into blobs
	std::vector<Blob> blobs;

	/// Associations between blobs and values 
	std::vector<Blotch> blotches;

	/// Associations between 3D points and values 
	std::vector<Field> fields;

	/// Assignment.
	Frame& operator=(const Frame& other);

    };

}


#endif
