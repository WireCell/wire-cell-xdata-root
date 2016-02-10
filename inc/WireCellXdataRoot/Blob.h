#ifndef WIRECELLXDATAROOT_BLOB
#define WIRECELLXDATAROOT_BLOB

#include "WireCellXdataRoot/Types.h"

#include <vector>

#include "TObject.h"

namespace WireCellXdataRoot {

    /// A collection of cells associated with a time slice and a
    /// number of values.  A blob exists in the context of an overall
    /// image.
    struct Blob : public TObject {

	Blob(blobid_t ident=0, int slice=0, float charge = 0.0);

	/// Identifier for this blob unique to the image.
	blobid_t ident;

	// the time slice
	slice_t slice;		

	/// Charge in blob
	float charge;

	/// The cells in this blob
	std::vector<cellid_t> cellids;

	ClassDef(Blob, 1);
    };
}

#endif
