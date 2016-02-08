#ifndef WIRECELLXDATAROOT_XDATAFILE
#define WIRECELLXDATAROOT_XDATAFILE

#include "WireCellXdataRoot/RunInfo.h"
#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/Image.h"


#include <string>
#include <vector>

namespace WireCellXdataRoot {

    class XdataFile {

	std::string m_treename;
	Image* m_image;
	RunInfo* m_runinfo;
	Geom* m_geom;

    public:

	XdataFile(const std::string& treename = "xdata");
	~XdataFile();

	std::size_t read(const std::string& url);
	std::size_t write(const std::string& filename);

	/// Access data for reading or writing
	///
	/// Be cautious with "auto", it does a copy!
	/// auto g = xdata.geom();  // don't do this
	/// Geom& g = xdata.gome(); // instead, do this
	RunInfo& runinfo();
	Geom& geom();
	Image& image();

    };

}

#endif
