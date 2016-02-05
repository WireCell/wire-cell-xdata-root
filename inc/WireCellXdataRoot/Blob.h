#ifndef WIRECELLXDATAROOT_BLOB
#define WIRECELLXDATAROOT_BLOB

#include <cstdint>
#include <vector>


namespace WireCellXdataRoot {

    /// The geometrical information about a "blob" or "merged cell"
    struct Blob {
	Blob();

	/// True if indices reference primitive cells instead of other blobs.
	bool iscells;

	/// Indices into cell or blob collection.
	std::vector<std::size_t> index;
    };

}

#endif
