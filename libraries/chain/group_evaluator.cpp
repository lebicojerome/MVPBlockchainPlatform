#include <graphene/chain/database.hpp>
#include <graphene/chain/group_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/group_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

   void_result group_create_evaluator::do_evaluate(const group_create_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }
   
   object_id_type group_create_evaluator::do_apply(const group_create_evaluator::operation_type& o)
   { try {
      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
         for_id = get_next_vote_id(p, vote_id_type::group);
         against_id = get_next_vote_id(p, vote_id_type::group);
      });
   
      return d.create<group_object>([&](group_object& w) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.customs = o.customs;
         w.admins = o.admins;
         w.application = o.application;
         w.vote_for = for_id;
         w.vote_against = against_id;
      }).id;
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result group_update_evaluator::do_evaluate(const group_update_evaluator::operation_type& o)
   { try {
      return void_result();
   } FC_CAPTURE_AND_RETHROW( (o) ) }

   void_result group_update_evaluator::do_apply(const group_update_evaluator::operation_type& o)
   { try {

      database& d = db();
      vote_id_type for_id, against_id;
      d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
          for_id = get_next_vote_id(p, vote_id_type::group);
          against_id = get_next_vote_id(p, vote_id_type::group);
      });

      d.modify( d.get(o.group), [&]( group_object& w ) {
         w.owner = o.owner;
         w.name = o.name;
         w.short_name = o.short_name;
         w.customs = o.customs;
         w.admins = o.admins;
         w.vote_for = for_id; // TODO:: what is?
         w.vote_against = against_id; // TODO:: what is?
      });

      return void_result();

   } FC_CAPTURE_AND_RETHROW( (o) ) }

} } // graphene::chain
