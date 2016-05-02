#ifndef AK_CORE_VISITOR_H__
#define AK_CORE_VISITOR_H__

namespace ak {

   class Option;

class Visitor {

public:
   Visitor();
   
   virtual void visit( Option & );
};


}

#endif



