#include <graphene/chain/database.hpp>
#include <graphene/chain/information_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/information_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

   void_result information_create_evaluator::do_evaluate(const information_create_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }
   
   object_id_type information_create_evaluator::do_apply(const information_create_evaluator::operation_type& o)
   { try {
      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
         for_id = get_next_vote_id(p, vote_id_type::information);
         against_id = get_next_vote_id(p, vote_id_type::information);
      });
   
      return d.create<information_object>([&](information_object& w) {
         w.owner = o.owner;
         w.group = o.group;
         w.confirming_admins = o.confirming_admins;
         w.confirmed_admins = o.confirmed_admins;
         w.status = o.status;
         w.admin_private_data_hash = o.admin_private_data_hash;
         w.student_private_data_hash = o.student_private_data_hash;
         w.custom_data = o.custom_data;
         w.vote_for = for_id;
         w.vote_against = against_id;
      }).id;
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_update_evaluator::do_evaluate(const information_update_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_update_evaluator::do_apply(const information_update_evaluator::operation_type& o)
   { try {
      database& d = db();
//      vote_id_type for_id, against_id;
//      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
//          for_id = get_next_vote_id(p, vote_id_type::information);
//          against_id = get_next_vote_id(p, vote_id_type::information);
//      });

      d.modify( d.get(o.information), [&]( information_object& w ) {
          w.group = o.group;
          w.confirming_admins = o.confirming_admins;
          w.confirmed_admins = o.confirmed_admins;
          w.status = o.status;
          w.admin_private_data_hash = o.admin_private_data_hash;
          w.student_private_data_hash = o.student_private_data_hash;
          w.custom_data = o.custom_data;
//          w.vote_for = for_id; // TODO:: what is?
//          w.vote_against = against_id; // TODO:: what is?
      });

      return void_result();

   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_confirming_evaluator::do_evaluate(const information_confirming_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_confirming_evaluator::do_apply(const information_confirming_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.information), [&]( information_object& w ) {
          w.confirmed_admins = o.confirmed_admins;
          w.status = o.status;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_annuling_evaluator::do_evaluate(const information_annuling_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_annuling_evaluator::do_apply(const information_annuling_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.information), [&]( information_object& w ) {
         w.status = o.status;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_hash_update_evaluator::do_evaluate(const information_hash_update_evaluator::operation_type& o)
   { try {

      if( o.public_hash.size() ) {
         bool hash_flag = false;

         database& d = db();
         const auto &information_idx = d.get_index_type<information_index>().indices().get<by_id>();
         for (auto elem: information_idx) {
            if (elem.public_hash == o.public_hash) {
               hash_flag = true;
               break;
            }
         }

         FC_ASSERT( !hash_flag );
      }

      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_hash_update_evaluator::do_apply(const information_hash_update_evaluator::operation_type& o)
   { try {
      database& d = db();
      d.modify( d.get(o.information), [&]( information_object& w ) {
          w.public_hash = o.public_hash;
      });
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_binding_evaluator::do_evaluate(const information_binding_evaluator::operation_type& o)
   { try {
        return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result information_binding_evaluator::do_apply(const information_binding_evaluator::operation_type& o)
   { try {
     database& d = db();
     d.modify( d.get(o.information), [&]( information_object& w ) {
         w.student_owner = o.student;
     });
     return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

} } // graphene::chain
