#pragma once
#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

   class institution_create_evaluator : public evaluator<institution_create_evaluator>
   {
      public:
         typedef institution_create_operation operation_type;

         void_result do_evaluate( const operation_type& o );
         object_id_type do_apply( const operation_type& o );
   };

   class institution_update_evaluator : public evaluator<institution_update_evaluator>
   {
      public:
         typedef institution_update_operation operation_type;

         const institution_object* _institution;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

} } // graphene::chain
