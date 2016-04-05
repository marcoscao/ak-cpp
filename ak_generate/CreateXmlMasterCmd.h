#ifndef AK_CREATE_XML_MASTER_CMD__
#define AK_CREATE_XML_MASTER_CMD__

#include "core/basecmd.h"

namespace ak {

	class CreateXmlMasterCmd : public BaseCmd {
	public:		
		CreateXmlMasterCmd() = default;

		virtual void init();
		virtual void execute();
	};

}

#endif

