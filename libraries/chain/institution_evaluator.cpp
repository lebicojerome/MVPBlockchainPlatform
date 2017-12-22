/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <graphene/chain/database.hpp>
#include <graphene/chain/institution_evaluator.hpp>

#include <graphene/chain/account_object.hpp>
#include <graphene/chain/vesting_balance_object.hpp>
#include <graphene/chain/institution_object.hpp>

#include <graphene/chain/protocol/vote.hpp>

namespace graphene { namespace chain {

void_result institution_create_evaluator::do_evaluate(const institution_create_evaluator::operation_type& o)
{ try {
   database& d = db();

   FC_ASSERT(d.get(o.owner).is_lifetime_member());

   return void_result();
} FC_CAPTURE_AND_RETHROW( (o) ) }


struct institution_init_visitor
{
   typedef void result_type;

   institution_object& institution;
   database&      db;

   institution_init_visitor( institution_object& w, database& d ):institution(w),db(d){}

   result_type operator()( const vesting_balance_institution_initializer& i )const
   {
      vesting_balance_institution_type w;
       w.balance = db.create<vesting_balance_object>([&](vesting_balance_object& b) {
         b.owner = institution.institution_account;
         b.balance = asset(0);

         cdd_vesting_policy policy;
         policy.vesting_seconds = fc::days(i.pay_vesting_period_days).to_seconds();
         policy.coin_seconds_earned = 0;
         policy.coin_seconds_earned_last_update = db.head_block_time();
         b.policy = policy;
      }).id;
      institution.institution = w;
   }

   template<typename T>
   result_type operator()( const T& )const
   {
      // DO NOTHING FOR OTHER institutionS
   }
};





object_id_type institution_create_evaluator::do_apply(const institution_create_evaluator::operation_type& o)
{ try {
   database& d = db();
   vote_id_type for_id, against_id;
   d.modify(d.get_global_properties(), [&for_id, &against_id](global_property_object& p) {
      for_id = get_next_vote_id(p, vote_id_type::institution);
      against_id = get_next_vote_id(p, vote_id_type::institution);
   });

   return d.create<institution_object>([&](institution_object& w) {
      w.institution_account = o.owner;
      w.name = o.name;
      w.vote_for = for_id;
      w.vote_against = against_id;

//      w.institution.set_which(o.initializer.which());
//      o.initializer.visit( institution_init_visitor( w, d ) );
   }).id;
} FC_CAPTURE_AND_RETHROW( (o) ) }

void refund_institution_type::pay_institution(share_type pay, database& db)
{
   total_burned += pay;
   db.modify(db.get(asset_id_type()).dynamic_data(db), [pay](asset_dynamic_data_object& d) {
      d.current_supply -= pay;
   });
}

void vesting_balance_institution_type::pay_institution(share_type pay, database& db)
{
   db.modify(balance(db), [&](vesting_balance_object& b) {
      b.deposit(db.head_block_time(), asset(pay));
   });
}


void burn_institution_type::pay_institution(share_type pay, database& db)
{
   total_burned += pay;
   db.adjust_balance( GRAPHENE_NULL_ACCOUNT, pay );
}

} } // graphene::chain
