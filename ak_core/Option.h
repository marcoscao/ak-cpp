#ifndef AK_OPTION_H__
#define AK_OPTION_H__

namespace ak {

   class Option {
   public:
      struct option_def {
         std::string large_name;
         std::string short_name;
         std::string description;
      };

      Option() 
      { 
      }

      virtual void definition() = 0;
      
      virtual void run() = 0;
   
   private:

   };


   class UserOption : public Option {
   };

   class SystemOption : public Option {
   };


   class SourcesOption : public UserOption {
   public:
      static int ID;

      virtual std::string const & id() {
         return "sources";
      }

      virtual Option::option_def definition()
      {
         return { "sources", "sources", "s", "Sets source paths to iterate over" };
      }

   };


   
   class AppManager {
   public:
      
      void initializa() 
      { 
         register_options_(); 
      }

      virtual void add_options() 
      { 
      }

      void run()
      {
      }

   protected:
	void register_option( int id, OptionsFactory::RegFn fn > )
        {
           OptionsFactory::instance().register_option( id, fn ); 
        }

   private:
	virtual void register_options_() = 0;

   };







   const int SOURCES_OP_ID = 1;
   const int HELP_OP_ID = 2;
   const int VERBOSE_OP_ID = 3;

   class AkGenApp : public AppMgr {
   public:
      void add_options()
      {
         add_option( SOURCES_OP_ID );

      }
   private:
      void register_options_() {

         OptionsFactory & of = OptionsFactory::instance();

         of.register( SOURCES_OP_ID, &SourcesOption::create );
         of.register( HELP_OP_ID, &HelpOption::create );
         of.register( VERBOSE_OP_ID, &VerboseOption::create );

      }

};


namespace ak { namespace gen {

   ProgramOptions::ProgramOptions() 
   : sources_cmd_( std::shared_ptr< SourcesCmd >( new SourcesCmd() ) ) 
   {
   }

   void ProgramOptions::initialize()
   {
      //std::shared_ptr< SourcesCmd > src_p( new SourcesCmd() ); 
      
      // Basic and required  options
      add_group( "Basic Options", option_def_list { 
				
         option_def{ "help", "help command", nullptr, std::bind( &ProgramOptions::help_op_callback_, this ) },
         option_def{ "verbose,v", "sets verbose mode", nullptr, std::bind( &ProgramOptions::verbose_op_callback_, this ) },
        
         // sources managed by a customized command
         option_def{ "source-path,s", "sets the source paths to process files. Note that can be assigned multiple source paths", 
		  set_multiple< string >( &sources_cmd_->source_paths() ),
		  nullptr,
		  sources_cmd_ }
         } 
      );

      // Extended and miscelanean options
      add_group( "Extended Options", option_def_list { 
            option_def{ "dry-run", "simulation. executes the command but with no side effects" },
            option_def{ "version", "current version", nullptr, std::bind( &ProgramOptions::version_op_callback_, this ) },
            }  
      );
   }

   void ProgramOptions::process( int argc, char** argv )
   {
      // let boost do the first processing stuff
      process_command_line_arguments( argc, argv );

      show_current_settings_();

      if( ak::util::prompt_question() == false ) {
         LOG_I( "Operation aborted by the user before start" )
         return;
      }

      // execute callback and command options in order
      if( has_option("verbose") )
         execute_options( { "-v" } );
      
      execute_options( { "dry-run", "-s" } );
   }

   void ProgramOptions::help_op_callback_()
   {
      cout << "ak_generate " << endl;
      version_op_callback_();

      cout << endl << endl;
      cout << "   usage  ak_generate -source_path [ --source_path ... ]"; 
      cout << endl << endl;
      cout << "   # example 1: Copyng from different sources" << endl;
      cout << "   ak_generate -s /Vol/media/a -s /Vol/media/d" << endl;
      cout << endl << endl;

      print_usage( "" );
   }

   void ProgramOptions::version_op_callback_()
   {
      cout << "Built April 2016" << endl; 
      cout << "version  2016.04.001" << endl;
   }

   void ProgramOptions::verbose_op_callback_()
   {
      cout << "verbose stuff here" << endl; 
   }

   void ProgramOptions::show_current_settings_()
   {
      cout << endl;
      LOG_CONSOLE( "Going to execute with the following options\n" )

      if( has_option("dry-run") )
         LOG_CONSOLE( " - dry-run mode :", "YES" )
	 
      if( has_option("source-path")  && ( sources_cmd_->source_paths().empty() == false ) ) {

         stringstream ss;
         auto const & v = sources_cmd_->source_paths();
         auto it = begin(v);
         do {
            ss << "\"" << *it << "\"";

            if( ++it != end(v) )
               ss << endl << "             ";
 
         } while( it != end(v) );

         LOG_CONSOLE( " - sources :", ss.str() )
      }

      if( has_option( "verbose" ) )
         LOG_CONSOLE( " - verbose :", "YES" )
      else
         LOG_CONSOLE( " - verbose :", "NO" )

      cout << endl;
   }

} } // end namespaces


