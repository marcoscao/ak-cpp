#include "ak_core/ProgramOptionsBase.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace ak;


class TestProgramOptions : public PO {
public:
   
   TestProgramOptions() 
   :  dry_run_( false ) {
   
   }

   void process_the_options()
   {
      process_config_file();
      process_sources();
      process_dry_run();

      if( has_option("-a") )
         cout << "* option -a found " << endl;

      if( has_option("-b") )
         cout << "* option -b found with value: " << option_value<double>("-b") << endl;

      if( has_option("-c") )
         cout << "* option -c found with value: " << option_value<double>("-c") << endl;

      if( has_option("-d") ) {
         cout << "* option -d found with managed value: " << option_value<double>("-d") << endl;
         cout << "* option -d found with user managed value: " << rate_ << endl;
      }
   }

   void process_sources() 
   {
      if( has_option( "source" ) ) {
         cout << "* source option found: " << endl;
         for( auto i : sources_ )
            cout << "  - passed source: " << i << endl;
      }
   }

   void process_dry_run()
   {
      if( has_option( "dry-run" ) ) {
         cout << "* dry-run mode found: " << endl;
         cout << "  value: " << option_value<int>("dry-run" ) << endl;
      }
   }

   void process_config_file()
   {
      if( has_option("config-file") ) {
         cout << "* config-file option found: " << endl;
         cout << "  value: " << option_value<string>( "config-file" ) << endl;
      }
   }

   void initialize()
   {
      option_def_list l{ 

         // optional option with no associated value 
         //   is like a boolean type, if has_option("help") returns true means this option was passed
         option_def{ "help", "help command" }, 

         // optional option with also shorthand
         option_def{ "verbose,v", "doing the operation in verbose way" },

         // optional option with only shorthand
         option_def{ ",a", "optinally activate flag a" },
         
         // optional option with only shorthand
         // in this case we use "-a" to access its value, ex: option_value<double>( "-a" )
         option_def{ "freq,b", "sets the frequency", set_optional<double>() },

         option_def{ "threshold,c", "sets the threadshold. By default the value is 2.5", set_optional<double>( 2.5 ) },

         option_def{ "rate,d", "establish desired rate", set_optional<double>( &rate_ ) },

         option_def{ "mode,e", "required main mode number", set_required<double>() },

         option_def{ "submode,f", "required submode number", set_required<double>( &submode_ ) },
        
         option_def{ "source,g", "sets multiples sources, note that can be added many sources", set_multiple< string >( &sources_ ) },

         option_def{ "metadata,h", "sets multiples metadatas, note that can be added many sources", set_multiple< string >( &sources_ ) },

         // set_multiple_op< string >( &my_multiple, true );  // multiple and required

         // set_positional_op< string >( &my_pos_1, 1 );
         // set_positional_op< std::vector<string> >( &my_pos_various, 3 );

      };

      add_group( "One Options Group", l );

      // PO::option_def_list l2{ 
      //       PO::option_def{ "xtra-mode", "extra mode command", set_value<int>( OptionType::OPTIONAL, &mode_ ) },
      //       PO::option_def{ "xtra-help", "extra help command"},
      //  	    PO::option_def{ "xv", "extra verbose operation", nullptr },
      // // 	PO::option_def{ "xsource", "source" },
      // // 	PO::option_def{ "xtarget,p", "target" },
      //  	    PO::option_def{ "xtra-dry-run", "extra dry-run mode", nullptr }
      // };
      // //
      // add_group( "Real Live Options", l2 );

   }

private:
   double rate_;
   double freq_;
   double submode_;
   bool dry_run_;
   int mode_;
   vector<string> sources_;

};



int main(int argc, char** argv )
{
   //cout << "Testing program_options..." << endl;
   
   TestProgramOptions tpo;

   tpo.initialize();

   // verify/check passed options
   tpo.process_command_line_arguments( argc, argv );
   


   if( tpo.has_option( "help" ) || tpo.no_user_option() ) 
          tpo.print_usage( "testing_program_options" );

   if( tpo.has_option( "verbose" ) ) {
          cout << "........" << endl;
          cout << "... doing verbose....." << endl;
          cout << "........" << endl;
   }


   tpo.process_the_options();
		
}

