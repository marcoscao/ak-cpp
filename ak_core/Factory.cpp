#include "Factory.h"
#include "Option.h"


namespace ak {

//	Factory<Option> & get_factory_instance()
//	{
//		static Factory<Option> f;
//		return f;
//	}

	options_factory & get_options_factory()
	{
		static factory< Option > f;
		return f;
	}

//	commands_factory & get_commands_factory()
//	{
//		static factory< Option, factory_item_creator<Option> > f;
//		return f;
//	}

}



