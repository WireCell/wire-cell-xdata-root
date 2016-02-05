#ifndef WIRECELLXDATAROOT_DEPO
#define WIRECELLXDATAROOT_DEPO

#include <cstdint>


namespace WireCellXdataRoot {

    /// An association of a value and a cell or a blob of cells at a particular time.
    struct Depo {
	Depo();

	/// Indices into cell or blob collection.
	std::vector<uint32_t> cellind;

	/// The time slice associated with the deposition.
	int slice;

	/// The value of the deposition (ie, charge).
	float value;
	/// The uncertainty in this value.
	float uncertainty;
    };

}

#endif
