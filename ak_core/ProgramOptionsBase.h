#ifndef AK_GENERATE_PROGRAM_OPTIONS_BASE__
#define AK_GENERATE_PROGRAM_OPTIONS_BASE__

#include <boost/program_options.hpp>
//#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace ak {

   class PO {
   public:
      using option_def = std::tuple< std::string, std::string >;
      using option_def_list = std::vector< option_def >;


      PO();

      void add_options( option_def_list const & v, option_def_list const & v_positional = option_def_list() );

      void process_command_line( int argc, char** argv );

      bool has_option( std::string const & ) const;

      std::string option_value( std::string const & ) const;


   private:
      boost::program_options::options_description bpo_desc_;
      boost::program_options::positional_options_description bpo_positional_;
      boost::program_options::variables_map bpo_vm_;
   };

}

#endif
