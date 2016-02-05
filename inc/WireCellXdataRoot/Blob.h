#ifndef WIRECELLXDATAROOT_BLOB
#define WIRECELLXDATAROOT_BLOB

#include <cstdint>
#include <vector>


namespace WireCellXdataRoot {

    /// The geometrical information about a "blob" or "merged cell"
    struct Blob {
	Blob();

	/// Indices into cell collection for constituent cells.
	std::vector<uint32_t> cellind;
    };

}

#endif
