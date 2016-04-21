#ifndef AK_GENERATE_SOURCE_PATH_COMMAND_H__
#define AK_GENERATE_SOURCE_PATH_COMMAND_H__

namespace ak {
namespace gen {

	class SourcePathCmd : public Command {
	public:
      	using StrContainer = std::vector< std::string >;

		SourcePathCmd( );
		
		virtual void execute();

	private:
   		void traverse_source_path_( std::string const & sp );

	};

} }

#endif

