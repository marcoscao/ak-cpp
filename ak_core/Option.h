#ifndef AK_CORE_OPTION_H__
#define AK_CORE_OPTION_H__

#include "ParseOptionsBase.h"
#include <string>

namespace ak {

   class Visitor;

class Option {
   template<typename> friend class factory;

public:
   Option();
   
   int registered_id() const;

   //! "verbose,v"  
   virtual std::string cmdline_id() = 0;

   //! "verbose"
   virtual std::string name() = 0;

   //! "verbose desc"
   virtual std::string description() = 0;

   virtual ParseOptionsBase::StorageType * storage_type();

   virtual void execute( ParseOptionsBase const & ) = 0;

   virtual void accept( Visitor & );

private:
   int registered_id_;

   /*
    * Set automatically by factory
    */
   void set_registered_id_( int id );

};


class UserOption : public Option {
public:
};


class SystemOption : public Option {
   public:
};


}



//enum { MEDIA_OP_ID = 5, ... };
//
//DEFINE_STANDARD_OP( MediaOp, MEDIA_OP_ID, "media-type", "media", "lkdlkals dka lsd", media_ )
//DEFINE_MULTIPLE_OP( SourcesOp, SOURCE_OP_ID, "source-path", "sources", "lkdlkals dka lsd", sources_ )
//
//
//#define DEFINE_STANDARD_OPTION( CLASS_NAME, ID, CMD_LINE, NAME, DESC, VAR ) \
//	class ID : public Option { \
//	public: \
//		static const int ID = ID; \
//		\
//	private: \
//		\
//	};



#define AK_OPTION( ID, CMDLINE_ID, NAME, DESC ) \
	private: \
	int id() { return ID; } \
	virtual std::string cmdline_id() { return CMDLINE_ID; } \
	virtual std::string name() { return NAME } \
	virtual std::string description() { return DESC } \


//#define AK_CLASS_OPTION( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE, VAR_DEFAULT_VALUE ) 

#define AK_MULTIPLE_OPTION( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
class CLASS_NAME : public Option { \
public: \
        using DATA = std::vector< VAR_TYPE >; \
\
	 /*CLASS_NAME() : data_( VAR_DEFAULT_VALUE ) { }*/ \
	CLASS_NAME() : data_() { } \
	int id() { return ID; } \
	virtual std::string cmdline_id() { return CMDLINE_ID; } \
	virtual std::string name() { return NAME; } \
	virtual std::string description() { return DESC; } \
	virtual ParseOptionsBase::StorageType * storage_type() \
         { \
            return ParseOptionsBase::set_multiple< VAR_TYPE >( &data_ ); \
         } \
	DATA get_data() { return data_; } \
	\
private: \
         DATA data_; \
}; 

//factory<Option>::instance().register_item< CLASS_NAME >( ID );




#endif



