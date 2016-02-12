#ifndef WIRECELLXDATAROOT_READER
#define WIRECELLXDATAROOT_READER

#include "WireCellXdataRoot/Geom.h"
#include "WireCellXdataRoot/RunInfo.h"
#include "WireCellXdataRoot/Trigger.h"
#include "WireCellXdataRoot/Field.h"
#include "WireCellXdataRoot/Frame.h"
#include "WireCellXdataRoot/Image.h"

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#include <string>

#include <cassert>
#include <iostream>

namespace WireCellXdataRoot {

	    

    class Reader {
	TFile* m_tfile;
    public:
	/// Give caller direct access
	TTreeReader geom_reader;
	TTreeReaderValue<Geom> geom;

	TTreeReader runinfo_reader;
	TTreeReaderValue<RunInfo> runinfo;

	TTreeReader trigger_reader;
	TTreeReaderValue<Trigger> trigger;

	TTreeReader field_reader;
	TTreeReaderValue<Field> field;

	TTreeReader frame_reader;
	TTreeReaderValue<Frame> frame;

	TTreeReader image_reader;
	TTreeReaderValue<Image> image;

	Reader(const std::string& filename)
	    : m_tfile(TFile::Open(filename.c_str()))
	    , geom_reader("geom",m_tfile)
	    , geom(geom_reader, "geom")

	    , runinfo_reader("runinfo",m_tfile)
	    , runinfo(runinfo_reader, "runinfo")

	    , trigger_reader("trig",m_tfile)
	    , trigger(trigger_reader, "trig")

	    , field_reader("field",m_tfile)
	    , field(field_reader, "field")

	    , frame_reader("frame",m_tfile)
	    , frame(frame_reader, "frame")

	    , image_reader("image",m_tfile)
	    , image(image_reader, "image")
	{
	    assert(m_tfile);
	}
	~Reader() {
	    m_tfile->Close();
	    delete m_tfile;
	    m_tfile = 0;
	}

    };

}
#endif

