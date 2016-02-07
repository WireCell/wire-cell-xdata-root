#ifndef WIRECELLXDATAROOT_BLOB
#define WIRECELLXDATAROOT_BLOB

#include <cstdint>
#include <vector>

#include "TObject.h"

namespace WireCellXdataRoot {

    /// A collection of cells associated with a time slice and a number of values.
    struct Blob : public TObject {
	Blob();

	/// External, unique identifier.
	uint32_t ident;

	// the time slice
	int slice;		

	/// Indices into cell or blob collection.
	std::vector<std::size_t> cellind;

	/// Any values to associate to the blob
	std::vector<float> values;

	ClassDef(Blob, 1);
    };
}

#endif
