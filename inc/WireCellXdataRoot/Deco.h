#ifndef WIRECELLXDATAROOT_DECO
#define WIRECELLXDATAROOT_DECO

#include "WireCellXdataRoot/Point.h"

#include <cstdint>
#include <vector>

#include "TObject.h"

namespace WireCellXdataRoot {

    /** A "deco" is information about the integrated charge from a
     * deconvolved waveform from a wire over a time slice.
     */
    struct Deco : public TObject {
	Deco();

	/// Index into wire store of wire
	uint32_t wireind;

	/// The time slice
	int slice;		

	/// The information. 
	std::vector<float> values;
	// fixme: is float enough precision for charge/charge_err?

	ClassDef(Deco,1);
    };

}

#endif
