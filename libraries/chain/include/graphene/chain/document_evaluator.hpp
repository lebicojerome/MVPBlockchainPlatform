#pragma once
#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

   class document_create_evaluator : public evaluator<document_create_evaluator>
   {
      public:
         typedef document_create_operation operation_type;

         void_result do_evaluate( const operation_type& o );
         object_id_type do_apply( const operation_type& o );
   };

   class document_update_evaluator : public evaluator<document_update_evaluator>
   {
      public:
         typedef document_update_operation operation_type;

         const document_object* _document;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class document_confirming_evaluator : public evaluator<document_confirming_evaluator>
   {
   public:
         typedef document_confirming_operation operation_type;

         const document_object* _document;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class document_publishing_evaluator : public evaluator<document_publishing_evaluator>
   {
   public:
         typedef document_publishing_operation operation_type;

         const document_object* _document;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

   class document_annuling_evaluator : public evaluator<document_annuling_evaluator>
   {
   public:
         typedef document_annuling_operation operation_type;

         const document_object* _document;

         void_result do_evaluate( const operation_type& o );
         void_result do_apply( const operation_type& o );
   };

} } // graphene::chain
