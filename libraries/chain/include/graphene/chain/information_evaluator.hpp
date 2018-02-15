#pragma once
#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

   class information_create_evaluator : public evaluator<information_create_evaluator>
   {
      public:
         typedef information_create_operation operation_type;

         void_result do_evaluate( const operation_type& o );
         object_id_type do_apply( const operation_type& o );
   };

   class information_update_evaluator : public evaluator<information_update_evaluator>
   {
      public:
         typedef information_update_operation operation_type;

         const information_object* _information;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class information_confirming_evaluator : public evaluator<information_confirming_evaluator>
   {
   public:
         typedef information_confirming_operation operation_type;

         const information_object* _information;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class information_annuling_evaluator : public evaluator<information_annuling_evaluator>
   {
   public:
         typedef information_annuling_operation operation_type;

         const information_object* _information;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class information_hash_update_evaluator : public evaluator<information_hash_update_evaluator>
   {
   public:
         typedef information_hash_update_operation operation_type;

         const information_object* _information;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class information_binding_evaluator : public evaluator<information_binding_evaluator>
   {
   public:
         typedef information_binding_operation operation_type;

         const information_object* _information;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

} } // graphene::chain
