#pragma once
#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

   class application_create_evaluator : public evaluator<application_create_evaluator>
   {
      public:
         typedef application_create_operation operation_type;

         void_result do_evaluate( const operation_type& o );
         object_id_type do_apply( const operation_type& o );
   };

   class application_update_evaluator : public evaluator<application_update_evaluator>
   {
      public:
         typedef application_update_operation operation_type;

         const application_object* _application;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

} } // graphene::chain
