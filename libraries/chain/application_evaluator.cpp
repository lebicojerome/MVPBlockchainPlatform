#include <graphene/chain/database.hpp>
#include <graphene/chain/application_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/application_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

   void_result application_create_evaluator::do_evaluate(const application_create_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   object_id_type application_create_evaluator::do_apply(const application_create_evaluator::operation_type& o)
   { try {
      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
         for_id = get_next_vote_id(p, vote_id_type::application);
         against_id = get_next_vote_id(p, vote_id_type::application);
      });

      return d.create<application_object>([&](application_object& w) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.customs = o.customs;
         w.vote_for = for_id;
         w.vote_against = against_id;
      }).id;
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result application_update_evaluator::do_evaluate(const application_update_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result application_update_evaluator::do_apply(const application_update_evaluator::operation_type& o)
   { try {

      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
          for_id = get_next_vote_id(p, vote_id_type::application);
          against_id = get_next_vote_id(p, vote_id_type::application);
      });

      d.modify( d.get(o.application), [&]( application_object& w ) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.customs = o.customs;
         w.vote_for = for_id; // TODO:: what is?
         w.vote_against = against_id; // TODO:: what is?
      });

      return void_result();

   } FC_CAPTURE_AND_RETHROW( (o) ) }

} } // graphene::chain
