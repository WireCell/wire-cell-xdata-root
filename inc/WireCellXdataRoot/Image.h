#ifndef WIRECELLXDATAROOT_IMAGE
#define WIRECELLXDATAROOT_IMAGE

#include "WireCellXdataRoot/Deco.h"
#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Field.h"

#include "TClonesArray.h"

namespace WireCellXdataRoot {

    /** A image collects all objects relevant the imaging of one
     * contiguous readout of the wires (aka the "frame").  An image is
     * expressed in terms of cells/blobs vs. constant span time
     * slices.
     */
    struct Image {
	Image(uint64_t ident=0,
	      uint64_t second=0, uint32_t nanosecond=0,
	      double slicespan=2.0, double toffset=0.0);

	~Image();

	/// An identifying number for this image.
	uint64_t ident;		// 64 bits for room to pack

	/// The second in the Unix epoch in which the frame starts.
	uint64_t second;	// force 64 bit time_t

	/// The nanosecond in the second in which the frame starts.
	uint32_t nanosecond;

	/// The time in seconds from the frame.second/frame.nanosecond
	/// time to slice 0 in the image.
	double toffset;

	/// The span of one time slice in milliseconds
	double slicespan;

	/// Call before each fill.
	void clear();

	TClonesArray* decos;
	/// Make and return a new deco allocated at end of array.
	/// Index is set to its location.
	Deco* new_deco(int& index);
	/// Get deco at index
	Deco* get_deco(int index);
	/// get number of decos
	int num_decos();

	TClonesArray* cells;
	/// Make and return a new cell allocated at end of array.
	/// Index is set to its location.
	Cell* new_cell(int& index);
	/// Get cell at index
	Cell* get_cell(int index);
	/// get number of cells
	int num_cells();

	TClonesArray* blobs;
	/// Make and return a new blob allocated at end of array.
	/// Index is set to its location.
	Blob* new_blob(int& index);
	/// Get cell at index
	Blob* get_blob(int index);
	/// get number of blobs
	int num_blobs();

	TClonesArray* fields;
	/// Make and return a new field allocated at end of array.
	/// Index is set to its location.
	Field* new_field(int& index);
	/// Get cell at index
	Field* get_field(int index);
	/// get number of fields
	int num_fields();

    };

}


#endif
