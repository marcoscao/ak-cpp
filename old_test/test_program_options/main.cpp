#include "ak_core/ProgramOptionsBase.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace ak;


class TestProgramOptions : public PO {
public:
   
   TestProgramOptions() 
   :rate_(),
   	freq_(), 
	submode_(),
	mode_(),
   	sources_(),
	devices_(),
	positionals_() {

   }

   void initialize()
   {
      // Optional options with no associated value ( they are like a boolean type, TRUE when the option has been passed )
		add_group( "Optional Flags Options Group", option_def_list { 
	
         	option_def{ "help", "help command" }, 

               // adding shorthand to the option
			// no callback function assigned in this case
         	option_def{ "dry-run", "doing the operation in simulation mode, with no side effects" },

         	// only shorthand
			// again with no callback
         	option_def{ ",v", "optinally activate verbose mode" }
			}
		);


		// Required options which also has an associated value, either managed automatically or by the user
		add_group( "Required Options", option_def_list { 

			// required and automatically managed
			option_def{ "mode", "required main mode number", set_unique_required<double>(), 
				std::bind( &TestProgramOptions::process_mode_op_, this ) },

			// required multiple and managed also by the user
			option_def{ "device", "required one or many devices ids", set_multiple_required<string>( &devices_ ),
				std::bind( &TestProgramOptions::process_device_op_, this ) },
      		}
		);


		// Miscelanean options
		add_group( "Miscelaneaum Options Group", option_def_list { 

			// optional unique and automatically managed
         	option_def{ "freq,b", "sets the frequency", set_unique<double>(),  
				std::bind( &TestProgramOptions::process_freq_op_, this ) },

			// optional unique with default value
         	option_def{ "threshold,c", "sets the threadshold. By default the value is 2.5", set_unique<double>( 2.5 ),
				std::bind( &TestProgramOptions::process_threshold_op_, this ) },

			// optional unique managed by the user with default value
         	option_def{ "rate", "establish desired rate", set_unique<double>( &rate_, 23.45 ),
				std::bind( &TestProgramOptions::process_rate_op_, this ) },
        
			// multiple managed by the user
         	option_def{ "source,g", "sets multiples sources, note that can be added many sources", set_multiple< string >( &sources_ ),
				std::bind( &TestProgramOptions::process_source_op_, this ) },
				
			// multiple managed by the user
         	option_def{ "songs,w", "sets multiples positionals songs", set_unique< vector<string> >( &positionals_ ),
				std::bind( &TestProgramOptions::process_positionals_op_, this ) },

			// multiple managed automatically
         	option_def{ "metadata,h", "sets multiples metadatas, note that can be added many sources", set_multiple< string >(),
				std::bind( &TestProgramOptions::process_metadata_op_, this ) },

         	// set_positional_op< string >( &my_pos_1, 1 );
         	// set_positional_op< std::vector<string> >( &my_pos_various, 3 );
      		}
		);

		add_positional( "songs" );
   }

   void process_no_callbacks()
   {
      if( has_option( "-v" ) ) 
         cout << "* 'verbose' option found" << endl;

      if( has_option( "dry-run" ) ) 
         cout << "* 'dry-run' option found" << endl;

   }


private:
   double rate_;
   double freq_;
   double submode_;
   bool dry_run_;
   int mode_;
   vector<string> sources_;
   vector<string> devices_;
   vector<string> positionals_;

   

   void process_help_op_()
   {
		print_usage( "testing_program_options" );
	}

   void process_mode_op_()
   {
		cout << "!!! Great automatically called by the engine" << endl;
        cout << "* required option 'mode' found with value: " << option_value<double>("mode" ) << endl;
   }

   void process_device_op_() 
   {
        cout << "* required multiple 'device' option found with values: " << endl;
        for( auto i : devices_ )
            cout << "  - device: " << i << endl;
   }

   void process_freq_op_()
   {
         cout << "* 'freq' option found with value: " << option_value<double>("freq" ) << endl;
  }

   void process_threshold_op_()
   {
         cout << "* 'threshold' option found with value: " << option_value<double>("threshold" ) << endl;
   }

   void process_rate_op_()
   {
         cout << "* 'rate' option found with value: " << option_value<double>("rate" ) << endl;
   }

   void process_source_op_() 
   {
         cout << "*multiple 'source' option found with values: " << endl;
         for( auto i : devices_ )
            cout << "  - source: " << i << endl;
   }

   void process_positionals_op_() 
   {
         cout << "* positionals 'songs' option found with values: " << endl;
         for( auto i : positionals_ )
            cout << "  - song: " << i << endl;
   }

   void process_metadata_op_() 
   {
         cout << "* multiple 'metadata' option found with values: " << endl;
         //for( auto i : metadata_ )
          //  cout << "  - metadata: " << i << endl;
   }

};



int main(int argc, char** argv )
{
   
   TestProgramOptions tpo;

   // Sets the options groups
   tpo.initialize();

   tpo.process_command_line_arguments( argc, argv );
   
   // This iterate over available options calling those with callbacks
   //tpo.execute( argc, argv );

   // process all those options we do not register with callbacks
   tpo.process_no_callbacks();
}

