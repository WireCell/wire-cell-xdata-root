#ifndef WIRECELLXDATAROOT_RUNINFO
#define WIRECELLXDATAROOT_RUNINFO

#include <cstdint>
#include <string>

namespace WireCellXdataRoot {

    /// Information about one contiguous period of DAQ/Sim running.
    struct RunInfo {
	RunInfo(int ident=-1, const std::string& detector="");

	/// A canonical name for the associated detector.
	std::string detector;

	/// An identifier for the run
	uint64_t ident;

	RunInfo& operator=(const RunInfo& other);

    };

}

#endif
