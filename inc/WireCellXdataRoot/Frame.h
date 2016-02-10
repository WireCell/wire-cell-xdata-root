#ifndef WIRECELLXDATAROOT_FRAME
#define WIRECELLXDATAROOT_FRAME

#include "WireCellXdataRoot/Types.h"
#include "WireCellXdataRoot/Deco.h"

class TClonesArray;

namespace WireCellXdataRoot {

    /** A time frame over which the deconvolved waveforms from
     * channels have been sliced.  Each slice spanning some number of
     * FADC "ticks"
     */
    struct Frame {

	Frame(frameid_t ident=0,
	      trigid_t trigid=0,
	      double toffset=0.0,     // in seconds
	      double slicespan=2.0e-6 // in seconds
	    );
	~Frame();

	/// An identifying number for this frame, at least unique to the trigger.
	frameid_t ident;

	/// The identity of the associated trigger.
	trigid_t trigid;

	/// A local offset in time (in seconds) from the absolute
	/// frame start time to the origin of the slice numbering used
	/// by the decos.
	double toffset;

	/// The time span for a slice, in seconds.
	double slicespan;

	/// The sliced, deconvolved waveforms.
	TClonesArray* decos;
    };

}


#endif
