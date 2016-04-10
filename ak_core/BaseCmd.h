#ifndef AK_BASE_CMD__
#define AK_BASE_CMD__

namespace ak {

	class BaseCmd {
	public:
		BaseCmd();

		virtual ~BaseCmd() = default; 

		virtual void init() = 0;

		virtual void execute() = 0;
	};

}

#endif

