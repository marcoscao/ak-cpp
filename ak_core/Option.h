#ifndef AK_CORE_OPTION_H__
#define AK_CORE_OPTION_H__

#include "ParseOptionsBase.h"
#include <string>


/*
 * sub-macros used by final AK_... macros to help build classes
 */
#define __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
class CLASS_NAME : public Option { \
    template<typename> friend class factory; \
public: \
   /*static const int ID = a_ID;*/ \
\
   static Option * create() { return new CLASS_NAME(); } \
   virtual std::string cmdline_id() { return CMDLINE_ID; } \
   virtual std::string name() { return NAME; } \
   virtual std::string description() { return DESC; } \
   virtual void execute( ParseOptionsBase const & pob ) { ; } \

#define __AK_END_DEFINE_OPTION_CLASS__( CLASS_NAME, ID ) \
private: \
   CLASS_NAME() { set_registered_id( ID ); } \
};

#define __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME, ID ) \
public: \
   DATA get_data() { return data_; } \
private: \
   DATA data_; \
   CLASS_NAME() : data_() { set_registered_id( ID ); } \
}; 



/*
 * Macro to define an Option Class without vars
 */
#define AK_DEFINE_OPTION( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
   __AK_END_DEFINE_OPTION_CLASS__( CLASS_NAME, ID )


/*
 * Macro to define an Option class with a unique value storage
 */
#define AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
public: \
   using DATA = VAR_TYPE; \
   virtual ParseOptionsBase::StorageType * storage_type() \
   { \
      return ParseOptionsBase::set_unique< VAR_TYPE >( &data_ ); \
   } \
   \
   __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME, ID )


/*
 * Macro to define an Option with multiple values
 */
#define AK_DEFINE_OPTION_WITH_MULTIPLE_VALUES( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
public: \
   using DATA = std::vector< VAR_TYPE >; \
   virtual ParseOptionsBase::StorageType * storage_type() \
   { \
      return ParseOptionsBase::set_multiple< VAR_TYPE >( &data_ ); \
   } \
   \
   __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME, ID )



// #define AK_DEFINE_OPTION_MULTIPLE( CLASS_NAME, a_ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
// class CLASS_NAME : public Option { \
//    template<typename> friend class factory; \
// public: \
//         using DATA = std::vector< VAR_TYPE >; \
// 		static const int ID = a_ID; \
// \
// 	 #<{(|CLASS_NAME() : data_( VAR_DEFAULT_VALUE ) { }|)}># \
//       static Option * create() { return new CLASS_NAME(); } \
// 	virtual std::string cmdline_id() { return CMDLINE_ID; } \
// 	virtual std::string name() { return NAME; } \
// 	virtual std::string description() { return DESC; } \
// 	virtual ParseOptionsBase::StorageType * storage_type() \
//          { \
//             return ParseOptionsBase::set_multiple< VAR_TYPE >( &data_ ); \
//          } \
// 	DATA get_data() { return data_; } \
//    inline virtual void execute( ParseOptionsBase const & pob ) { ; } \
// 	\
// private: \
//          DATA data_; \
// 		 \
// 	CLASS_NAME() : data_() { ; } \
// }; 

//factory<Option>::instance().register_item< CLASS_NAME >( ID );


namespace ak {

   class Visitor;

class Option {
   template<typename> friend class factory;

protected:
   Option();

public:
   
   int registered_id() const;

   //! "verbose,v"  
   virtual std::string cmdline_id() = 0;

   //! "verbose"
   virtual std::string name() = 0;

   //! "verbose desc"
   virtual std::string description() = 0;

   virtual ParseOptionsBase::StorageType * storage_type();

   virtual void execute( ParseOptionsBase const & );

   virtual void accept( Visitor & );


protected:
   /*
    * Set automatically by factory
    */
   void set_registered_id( int id );

private:
   int registered_id_;

};


class UserOption : public Option {
public:
};


class SystemOption : public Option {
   public:
};


}








#endif



