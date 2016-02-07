#ifndef WIRECELLXDATAROOT_IMAGE
#define WIRECELLXDATAROOT_IMAGE

#include "WireCellXdataRoot/Cell.h"
#include "WireCellXdataRoot/Blob.h"
#include "WireCellXdataRoot/Blotch.h"
#include "WireCellXdataRoot/Field.h"

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
	uint64_t ident;

	/// The second in the Unix epoch in which the frame starts.
	uint64_t second;

	/// The nanosecond in the second in which the frame starts.
	uint32_t nanosecond;

	/// The time in seconds from the frame.second/frame.nanosecond
	/// time to slice 0 in the image.
	double toffset;

	/// The span of one time slice in milliseconds
	double slicespan;

	/// All the primitive cells referenced elsewhere.
	std::vector<Cell*> cells;

	/// Any organization of cells into blobs
	std::vector<Blob*> blobs;

	/// Associations between blobs and values 
	std::vector<Blotch*> blotches;

	/// Associations between 3D points and values 
	std::vector<Field*> fields;
    };

}


#endif
