#include <graphene/chain/database.hpp>
#include <graphene/chain/institution_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/institution_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

   void_result institution_create_evaluator::do_evaluate(const institution_create_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }
   
   object_id_type institution_create_evaluator::do_apply(const institution_create_evaluator::operation_type& o)
   { try {
      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
         for_id = get_next_vote_id(p, vote_id_type::institution);
         against_id = get_next_vote_id(p, vote_id_type::institution);
      });
   
      return d.create<institution_object>([&](institution_object& w) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.phone = o.phone;
         w.address = o.address;
         w.customs = o.customs;
         w.admins = o.admins;
         w.vote_for = for_id;
         w.vote_against = against_id;
      }).id;
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result institution_update_evaluator::do_evaluate(const institution_update_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result institution_update_evaluator::do_apply(const institution_update_evaluator::operation_type& o)
   { try {

      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
          for_id = get_next_vote_id(p, vote_id_type::institution);
          against_id = get_next_vote_id(p, vote_id_type::institution);
      });

      d.modify( d.get(o.institution), [&]( institution_object& w ) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.phone = o.phone;
         w.address = o.address;
         w.customs = o.customs;
         w.admins = o.admins;
         w.vote_for = for_id; // TODO:: what is?
         w.vote_against = against_id; // TODO:: what is?
      });

      return void_result();

   } FC_CAPTURE_AND_RETHROW( (o) ) }

} } // graphene::chain
