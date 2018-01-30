#include <graphene/chain/database.hpp>
#include <graphene/chain/document_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/document_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

   void_result document_create_evaluator::do_evaluate(const document_create_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }
   
   object_id_type document_create_evaluator::do_apply(const document_create_evaluator::operation_type& o)
   { try {
      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
         for_id = get_next_vote_id(p, vote_id_type::document);
         against_id = get_next_vote_id(p, vote_id_type::document);
      });
   
      return d.create<document_object>([&](document_object& w) {
         w.owner = o.owner;
         w.institution = o.institution;
//         w.issue_date = o.issue_date;
//         w.expiry_date = o.expiry_date;
//         w.first_name = o.first_name;
//         w.last_name = o.last_name;
//         w.middle_name = o.middle_name;
//         w.birth_date = o.birth_date;
//         w.document_name = o.document_name;
//         w.phone = o.phone;
//         w.email = o.email;
//         w.identity_card_number = o.identity_card_number;
//         w.identity_card_type_name = o.identity_card_type_name;
//         w.text = o.text;
//         w.public_custom = o.public_custom;
//         w.hidden_custom = o.hidden_custom;
         w.confirming_admins = o.confirming_admins;
         w.confirmed_admins = o.confirmed_admins;
         w.status = o.status;
         w.admin_private_data = o.admin_private_data;
         w.student_private_data = o.student_private_data;
         w.vote_for = for_id;
         w.vote_against = against_id;
      }).id;
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_update_evaluator::do_evaluate(const document_update_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_update_evaluator::do_apply(const document_update_evaluator::operation_type& o)
   { try {
      database& d = db();
//      vote_id_type for_id, against_id;
//      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
//          for_id = get_next_vote_id(p, vote_id_type::document);
//          against_id = get_next_vote_id(p, vote_id_type::document);
//      });

      d.modify( d.get(o.document), [&]( document_object& w ) {
//          w.owner = o.owner;
          w.institution = o.institution;
//          w.issue_date = o.issue_date;
//          w.expiry_date = o.expiry_date;
//          w.first_name = o.first_name;
//          w.last_name = o.last_name;
//          w.middle_name = o.middle_name;
//          w.birth_date = o.birth_date;
//          w.document_name = o.document_name;
//          w.phone = o.phone;
//          w.email = o.email;
//          w.identity_card_number = o.identity_card_number;
//          w.identity_card_type_name = o.identity_card_type_name;
//          w.text = o.text;
//          w.public_custom = o.public_custom;
//          w.hidden_custom = o.hidden_custom;
          w.confirming_admins = o.confirming_admins;
          w.confirmed_admins = o.confirmed_admins;
          w.status = o.status;
          w.admin_private_data = o.admin_private_data;
          w.student_private_data = o.student_private_data;
//          w.vote_for = for_id; // TODO:: what is?
//          w.vote_against = against_id; // TODO:: what is?
      });

      return void_result();

   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_confirming_evaluator::do_evaluate(const document_confirming_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_confirming_evaluator::do_apply(const document_confirming_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.document), [&]( document_object& w ) {
          w.confirmed_admins = o.confirmed_admins;
          w.status = o.status;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_annuling_evaluator::do_evaluate(const document_annuling_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_annuling_evaluator::do_apply(const document_annuling_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.document), [&]( document_object& w ) {
         w.status = o.status;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_hash_update_evaluator::do_evaluate(const document_hash_update_evaluator::operation_type& o)
   { try {

      if( o.public_hash.size() ) {
         bool hash_flag = false;

         database& d = db();
         const auto &document_idx = d.get_index_type<document_index>().indices().get<by_id>();
         for (auto elem: document_idx) {
            if (elem.public_hash == o.public_hash) {
               hash_flag = true;
               break;
            }
         }

         FC_ASSERT( !hash_flag );
      }

      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result document_hash_update_evaluator::do_apply(const document_hash_update_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.document), [&]( document_object& w ) {
          w.public_hash = o.public_hash;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

} } // graphene::chain
