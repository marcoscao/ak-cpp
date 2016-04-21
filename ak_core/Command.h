#ifndef AK_CORE_COMMAND_H__
#define AK_CORE_COMMAND_H__

namespace ak {

	//class Engine;

	class Command {
	public:
		//Command( Engine & );
		Command( );
		
		virtual void execute() = 0;

		//Engine & engine();

		//const Engine & engine() const;

	private:
		//Engine & engine_;

	};

}

#endif

