#ifndef AK_GENERATE_PROGRAM_OPTIONS_BASE__
#define AK_GENERATE_PROGRAM_OPTIONS_BASE__

#include <boost/program_options.hpp>
//#include <boost/filesystem.hpp>
#include <memory>
#include <string>
#include <tuple>
#include <vector>


namespace ak {

   class PO {
   public:
      
      enum class OptionType : unsigned int {
         OPTIONAL = 0,
         REQUIRED = 2,
         MULTIPLE = 4,
         //USER_VAR = 8,
         //DEFAULT_VALUE = 16,
         POSITIONAL = 32
      };
    
      friend int operator&( OptionType const & op_1, OptionType const & op_2 )
      {
         return static_cast<int>( static_cast<int>(op_1) & static_cast<int>(op_2) );
      }

      friend OptionType operator|( OptionType const & op_1, OptionType const & op_2 )
      {
         return static_cast<OptionType>( static_cast<int>(op_1) | static_cast<int>(op_2) );
      }


      //! stores ( "command", "desc", *value_semantic* ) tuple
      struct option_def {
         friend class PO;

         option_def( std::string const & command, 
                     std::string const & desc, 
                     boost::program_options::value_semantic * value = nullptr ) 
         :  data_( command, desc, value ) {
         }

         template<class T>
         option_def( std::string const & command, 
                     std::string const & desc, 
                     boost::program_options::value_semantic * value = nullptr,
                     T const & default_value = T()) 
         :  data_( command, desc, value ) {

         }

      private:
         //! tuple ( "command", "desc", *typed_value )  typed_value
         using option_def_tuple = std::tuple< std::string, std::string, boost::program_options::value_semantic* >;

         option_def_tuple data_;
      };


      using option_def_list = std::vector< option_def >;


      PO();

      ~PO();

      //!
      //! Delegates on boost program_options to create typed_value ( value_semantic child )
      //!   T the primitive type used to store a value onto
      //!
      template<class T >
      static boost::program_options::value_semantic * set_value( OptionType op_type, 
                                       void * user_var = nullptr
                                       //void * def_val = nullptr
                                       //T const & def_val=T()  
                                       //,int pos_ocurrences=0
                                    )
      {
         namespace po = boost::program_options;
         boost::program_options::value_semantic * v = nullptr;

         if( op_type & OptionType::MULTIPLE ) 
           //if( op_type & OptionType::USER_VAR )
          
            if( user_var )
               v = po::value< std::vector<T> >( static_cast< std::vector<T>* >( user_var ) );
            else
               v = po::value< std::vector<T> >();
         else 
            if( user_var )
            //if( op_type & OptionType::USER_VAR )
               v = po::value<T>( static_cast< T* >( user_var ) );
            else
               v = po::value<T>();
         
         // if( static_cast<int>(op_type) & static_cast<int>(OptionType::MULTIPLE) ) {
         //    //if( value_var )
         //    //   v = po::value< std::vector<T> >( value_var ); //    //else //       v = po::value< std::vector<T> >();
         // }
         // else { //    if( value_var ) //       v = po::value<T>( value_var ); //    else //       v = po::value<T>(); // }

         // if( op_type & OptionType::POSITIONAL ) //    bpo_positional_.add( "xx", pos_ocurrences );

         //if( op_type & OptionType::DEFAULT_VALUE )
         //if( def_val )
         //   static_cast< po::typed_value<T>* >(v)->default_value( static_cast<T>( *static_cast<T*>(def_val) ) );

         if( op_type & OptionType::REQUIRED )
            static_cast< po::typed_value<T>* >(v)->required();

         return v;
      }
      
      template<class T >
      static boost::program_options::value_semantic * set_optional( void * user_var = nullptr )
      {
         return set_value<T>( OptionType::OPTIONAL, user_var );
      }

      template<class T >
      static boost::program_options::value_semantic * set_optional( T const & def_val )
      {
         auto v = set_value<T>( OptionType::OPTIONAL, nullptr );
         return static_cast< boost::program_options::typed_value<T>* >(v)->default_value( def_val );
      }

      template<class T >
      static boost::program_options::value_semantic * set_required( void * user_var = nullptr )
      {
         return set_value<T>( OptionType::OPTIONAL | OptionType::REQUIRED, user_var );
      }

      template<class T >
      static boost::program_options::value_semantic * set_multiple( void * user_var = nullptr )
      {
         return set_value<T>( OptionType::OPTIONAL | OptionType::MULTIPLE, user_var );
      }



      //    if( user_var ) 
      //
      //       return set_value<T>( op | OptionType::DEFAULT_VALUE, 
      //
      //       op = op | OptionType::USER_VAR;
      //
      //    if( def_val )
      //       return set_value<T>( op | OptionType::DEFAULT_VALUE, 
      //
      //    if( user_var )
      //       return set_value<T>( OptionType::OPTIONAL | OptionType::USER_VAR );
      //       
      //    return set_value<T>( OptionType::OPTIONAL );
      // }

      // template<class T >
      // static boost::program_options::value_semantic* set_value( OptionType op_type, std::vector< T > * value_var  )
      // {
      //    namespace po = boost::program_options;
      //    po::value_semantic * v;
      //    
      //    v = po::value< std::vector<T> >( value_var );
      //
      //    if( op_type & OptionType::REQUIRED )
      //       return static_cast< po::typed_value<T>* >(v)->required();
      //
      //    return v;
      // }
      //

      // template< class T>
      // static set_optional_op(  
      //
      //    set_optional_op< string >();
      //    set_optional_op< string >( &my_var );
      //    set_optional_op< string >( &my_var, "def" );
      //    
      //    set_required_op< string >();
      //    set_required_op< string >( &my_var );
      //
      //    set_multiple_op< string >();
      //    set_multiple_op< string >( &my_multiple );
      //    set_multiple_op< string >( &my_multiple, true );  // multiple and required
      //
      //
      //    set_positional_op< string >( &my_pos_1, 1 );
      //    set_positional_op< std::vector<string> >( &my_pos_various, 3 );


      //void add_options( option_def_list const & v, option_def_list const & v_positional = option_def_list() );

      void add_group( std::string const & title, option_def_list const & v );

      //void process_command_line( int argc, char** argv );

      bool has_option( std::string const & ) const;

      //! True if user hasn't pass any option
      bool no_user_option( ) const;

      template< typename T>
      T option_value( std::string const & op_name ) const
      {
         return bpo_vm_[ op_name ].as<T>();
      }

      void print_usage( const std::string & title ) const;

      //! Checks/verifies that passed arguments meet user rules
      void process_command_line_arguments( int argc, char** argv );

   private:
      //int argc_;
      //char** argv_;
      //std::string title_;

      boost::program_options::options_description bpo_desc_;
      boost::program_options::positional_options_description bpo_positional_;
      boost::program_options::variables_map bpo_vm_;
      
   };

}

#endif

