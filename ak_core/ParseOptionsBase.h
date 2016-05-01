#ifndef AK_GENERATE_PARSE_OPTIONS_BASE__
#define AK_GENERATE_PARSE_OPTIONS_BASE__

#include <boost/program_options.hpp>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace ak {
   
   class Option;

   template<typename T=Option>
   class factory;


   class ParseOptionsBase {
   public:

      using StorageType = boost::program_options::value_semantic;
      using OptionsList = std::vector< Option* >;


      ParseOptionsBase();

      ~ParseOptionsBase();

      /*
       * User register its options
       */
      virtual void register_options( factory<Option> & ) = 0;


      /*
       * Checks/verifies that passed arguments meet user rules
       */
      void process_command_line_arguments( int argc, char** argv );

      virtual void execute() = 0;


      /*
       *
       * Relies on boost program_options to create typed_value ( value_semantic child )
       *   T the primitive type used to store a value onto
       */
      template<class T> 
      static StorageType * set_value( T * user_var = nullptr )
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
      static StorageType * set_unique( T * user_var = nullptr )
      {
         return set_value( user_var );
      }

      // sets this option as unique with a optional default value
      template<class T >
      static StorageType * set_unique( T * user_var, T const & def_val )
      {
         auto v = set_unique<T>( user_var );
         return static_cast< boost::program_options::typed_value<T>* >(v)->default_value( def_val );
      }
      
      // sets the option unique with default value
      template<class T >
      static StorageType * set_unique( T const & def_val )
      {
         return set_unique<T>( nullptr, def_val );	
      }

      // sets the option as holding multiple values
      template<class T >
      static StorageType * set_multiple( std::vector<T> * user_var = nullptr )
      {
	 return set_value( user_var );
      }

      // unique and required ( so no sense for default value )
      template<class T >
      static StorageType * set_unique_required( T * user_var = nullptr )
      {
         auto v = set_value<T>( user_var );
         return static_cast< boost::program_options::typed_value<T>* >(v)->required();
      }

      // unique and required ( so no sense for default value )
      template<class T >
      static StorageType * set_multiple_required( std::vector<T> * user_var = nullptr )
      {
         auto v = set_value< std::vector<T> >( user_var );
         return static_cast< boost::program_options::typed_value<std::vector<T>>*>(v)->required();
      }

      // template<class T>
      // static boost::program_options::value_semantic * set_positional( std::vector<T> * user_var = nullptr )
      // {
      //
      // }

      //void add_group( std::string const & title, option_def_list const & v );
      void add_group( std::string const & title, OptionsList const & v );

      // Unlimited ocurrences by default
      //void add_positional( std::string const & option_name, int num_ocurrences = -1 );
      //void add_positional( std::vector< std::string > const & option_names );

      /*
       * has user entered such option?
       */
      //bool has_entered_option( std::string const & ) const;

      bool has_user_entered_option( int registered_id ) const;

      /*
       * True if user has not set such option
       */
      bool no_user_options( ) const;

      /*
       * execute registered option only if it was entered by the user
       * if force = TRUE means that it will be execute although it was not entered by the user
       * it throws if option is not register
       * Returns true if option has been executed
       */
      bool execute_option_if( int registered_id, bool force = false );

      /*
       * Returns Option* instance associtated to registered_id
       * It throws if no registered_id has been added to map
       */
      Option * option_ptr( int registered_id ) const;


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

      // Stores Option classes indexed by registered_id
      using OptionsMap = std::map< int, Option* >;

      // stores all added options.
      // note that this does not mean that the option is currently in po::vm ( passed by command line ) 
      // this container holds only all those available to be used by the user
      OptionsMap added_options_;
   	
   };

}

#endif

