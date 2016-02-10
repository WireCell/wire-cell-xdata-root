#ifndef WIRECELLXDATAROOT_DECO
#define WIRECELLXDATAROOT_DECO

#include "WireCellXdataRoot/Types.h"

#include "TObject.h"

namespace WireCellXdataRoot {

    /** A "deco" is information about the integrated charge from a
     * deconvolved waveform from a channel over a time slice.
     */
    struct Deco : public TObject {


	Deco(chanid_t chanid=0, slice_t slice=-1,
	     float charge=-1, float uncertainty=-1);

	/// The identity of the wire to which this Deco is associated.
	chanid_t chanid;

	/// The time slice
	slice_t slice;		

	/// The charge value in the time slice
	float charge;

	/// Its uncertainty.
	float uncertainty;

	ClassDef(Deco,1);
    };

}

#endif
