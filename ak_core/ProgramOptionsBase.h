#ifndef AK_GENERATE_PROGRAM_OPTIONS_BASE__
#define AK_GENERATE_PROGRAM_OPTIONS_BASE__

#include <boost/program_options.hpp>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>


namespace ak {

   class Command;

   class PO {
   public:

      using CallbackFn = std::function< void() >;
      using CommandPtr = std::shared_ptr< Command >;

      //! stores ( "command", "desc", *value_semantic* ) tuple
      struct option_def {
         friend class PO;

         option_def( std::string const & command, 
                     std::string const & desc, 
                     boost::program_options::value_semantic * value = nullptr,
                     CallbackFn callback_fn = CallbackFn(),
		     CommandPtr cmd_ptr = CommandPtr() )
         :  data_( command, desc, value, callback_fn, cmd_ptr ) {
         }


      private:
         using option_def_tuple = std::tuple< 
                     std::string, 
		     std::string, 
		     boost::program_options::value_semantic*, 
		     CallbackFn,
		     CommandPtr >;

         option_def_tuple data_;
      };


      using option_def_list = std::vector< option_def >;



      PO();

      ~PO();

      /*
       * Checks/verifies that passed arguments meet user rules
       */
      void process_command_line_arguments( int argc, char** argv );

      /*
       * Executes callback or command ordered for passed options
       * note: throws if the option is not registered in the invokers
       */
      void execute_options( std::vector< std::string > const & ops_names );

      /*
       *
       * Relies on boost program_options to create typed_value ( value_semantic child )
       *   T the primitive type used to store a value onto
       */
      template<class T> 
      static boost::program_options::value_semantic * set_value( T * user_var = nullptr )
      {
         boost::program_options::value_semantic * v = nullptr;

         if( user_var )
            v = boost::program_options::value<T>( user_var );
         else
            v = boost::program_options::value<T>();

         return v;
      }

      // sets this option as unique
      template<class T >
      static boost::program_options::value_semantic * set_unique( T * user_var = nullptr )
      {
         return set_value( user_var );
      }

      // sets this option as unique with a optional default value
      template<class T >
      static boost::program_options::value_semantic * set_unique( T * user_var, T const & def_val )
      {
         auto v = set_unique<T>( user_var );
         return static_cast< boost::program_options::typed_value<T>* >(v)->default_value( def_val );
      }
      
      // sets the option unique with default value
      template<class T >
      static boost::program_options::value_semantic * set_unique( T const & def_val )
      {
         return set_unique<T>( nullptr, def_val );	
      }

      // sets the option as holding multiple values
      template<class T >
      static boost::program_options::value_semantic * set_multiple( std::vector<T> * user_var = nullptr )
      {
	 return set_value( user_var );
      }

      // unique and required ( so no sense for default value )
      template<class T >
      static boost::program_options::value_semantic * set_unique_required( T * user_var = nullptr )
      {
         auto v = set_value<T>( user_var );
         return static_cast< boost::program_options::typed_value<T>* >(v)->required();
      }

      // unique and required ( so no sense for default value )
      template<class T >
      static boost::program_options::value_semantic * set_multiple_required( std::vector<T> * user_var = nullptr )
      {
         auto v = set_value< std::vector<T> >( user_var );
         return static_cast< boost::program_options::typed_value<std::vector<T>>*>(v)->required();
      }


      // template<class T>
      // static boost::program_options::value_semantic * set_positional( std::vector<T> * user_var = nullptr )
      // {
      //
      // }

      void add_group( std::string const & title, option_def_list const & v );

      // Unlimited ocurrences by default
      void add_positional( std::string const & option_name, int num_ocurrences = -1 );
   	
      void add_positional( std::vector< std::string > const & option_names );

      bool has_option( std::string const & ) const;

      //! True if user hasn't pass any option
      bool no_user_option( ) const;

      template< typename T>
      T option_value( std::string const & op_name ) const
      {
         return bpo_vm_[ op_name ].as<T>();
      }

      void print_usage( const std::string & title ) const;



   private:
      boost::program_options::options_description bpo_desc_;
      boost::program_options::positional_options_description bpo_positional_;
      boost::program_options::variables_map bpo_vm_;

      // stores all defined options, that does not mean the option is currently in po::vm since only will be if it was passed on the command line
      // and this set contains all the options defined on initialization
      std::map< std::string, std::pair< CallbackFn, CommandPtr > > option_invokers_;

   	
      // splits "option_name" into ( large, short ) and store twice for internal purposes ( callbacks, etc... )
      // boost user stores option as one of: ",v" ,  "verbose" or  "verbose,v"
      // which will be called as:  "-v", "verbose", "verbose"
      void mapping_option_invokers_( option_def const & );

   };

}

#endif

