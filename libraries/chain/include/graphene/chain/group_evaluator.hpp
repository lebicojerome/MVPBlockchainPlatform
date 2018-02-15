#pragma once
#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

   class group_create_evaluator : public evaluator<group_create_evaluator>
   {
      public:
         typedef group_create_operation operation_type;

         void_result do_evaluate( const operation_type& o );
         object_id_type do_apply( const operation_type& o );
   };

   class group_update_evaluator : public evaluator<group_update_evaluator>
   {
      public:
         typedef group_update_operation operation_type;

         const group_object* _group;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

} } // graphene::chain
