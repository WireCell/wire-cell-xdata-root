#ifndef WIRECELLXDATAROOT_BLOTCH
#define WIRECELLXDATAROOT_BLOTCH

#include <vector>
#include <cstdint>


namespace WireCellXdataRoot {

    /// An association of values with a collection of cells at slice of time.
    struct Blotch {
	Blotch();

	/// The time slice associated with the deposition.
	int slice;

	/// Indices into cell or blob collection.
	std::vector<uint32_t> cellind;

	/// The values which apply to the blotch.
	std::vector<float> value;
    };

}

#endif
