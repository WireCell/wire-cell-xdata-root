#include "WireCellXdataRoot/Trigger.h"

using namespace WireCellXdataRoot;


Trigger::Trigger(trigid_t ident,
		 trigger_t type,
		 runid_t runid,
		 second_t second,
		 nanosecond_t nanosecond)
    : ident(ident)
    , type(type)
    , runid(runid)
    , second(second)
    , nanosecond(nanosecond)
{  }

Trigger::~Trigger() 
{ 
}

