#ifndef WIRECELLXDATAROOT_RUNINFO
#define WIRECELLXDATAROOT_RUNINFO

#include "WireCellXdataRoot/Types.h"

#include <string>

namespace WireCellXdataRoot {

    /// Information about one contiguous period of DAQ/Sim running.
    struct RunInfo {

	RunInfo(runid_t ident=0);

	/// An identifier for the run
	runid_t ident;

    };

}

#endif
