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

	/// Indices into a blob collection.
	std::vector<std::size_t> blobind;

	/// The values which apply to the blotch.
	std::vector<float> value;
    };

}

#endif
