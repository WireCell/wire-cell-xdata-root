#ifndef WIRECELLXDATAROOT_XDATAFILE
#define WIRECELLXDATAROOT_XDATAFILE

#include "WireCellXdataRoot/RunInfo.h"
#include "WireCellXdataRoot/Wire.h"
#include "WireCellXdataRoot/Frame.h"


#include <string>
#include <vector>

class TFile;

namespace WireCellXdataRoot {

    class XdataFile {
	TFile* m_tfile;
	Frame* m_frame;
	RunInfo* m_ri;
	WireSet* m_ws;
    public:
	XdataFile(const std::string& url,
		  const std::string& mode = "r");
	~XdataFile();

	/// Save run info.  Return number of bytes written. 
	std::size_t write(const RunInfo& ri);
	/// Read run info, filling ri.
	std::size_t read(RunInfo& ri);

	/// Save wire set.  Return number of bytes written. 
	std::size_t write(const WireSet& ws);
	/// Read wire set, filling ws.
	std::size_t read(WireSet& ws);

	/// Append one frame.  Return entry number written. 
	std::size_t append(const Frame& frame);
	/// Return total number of frames
	std::size_t frames();
	/// Get the n'th frame
	std::size_t read(Frame& frame, std::size_t entry);

	// etc for sim
    };

}

#endif
