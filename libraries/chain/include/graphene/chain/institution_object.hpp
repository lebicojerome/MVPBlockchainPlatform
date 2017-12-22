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
#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

/**
  * @defgroup institution_types Implementations of the various institution types in the system
  *
  * The system has various institution types, which do different things with the money they are paid. These institution types
  * and their semantics are specified here.
  *
  * All institution types exist as a struct containing the data this institution needs to evaluate, as well as a method
  * pay_institution, which takes a pay amount and a non-const database reference, and applies the institution's specific pay
  * semantics to the institution_type struct and/or the database. Furthermore, all institution types have an initializer,
  * which is a struct containing the data needed to create that kind of institution.
  *
  * Each initializer type has a method, init, which takes a non-const database reference, a const reference to the
  * institution object being created, and a non-const reference to the specific *_institution_type object to initialize. The
  * init method creates any further objects, and initializes the institution_type object as necessary according to the
  * semantics of that particular institution type.
  *
  * To create a new institution type, define a my_new_institution_type struct with a pay_institution method which updates the
  * my_new_institution_type object and/or the database. Create a my_new_institution_type::initializer struct with an init
  * method and any data members necessary to create a new institution of this type. Reflect my_new_institution_type and
  * my_new_institution_type::initializer into FC's type system, and add them to @ref institution_type and @ref
  * institution_initializer respectively. Make sure the order of types in @ref institution_type and @ref institution_initializer
  * remains the same.
  * @{
  */
/**
 * @brief A institution who returns all of his pay to the reserve
 *
 * This institution type pays everything he receives back to the network's reserve funds pool.
 */
        struct refund_institution_type
        {
            /// Record of how much this institution has burned in his lifetime
            share_type total_burned;

            void pay_institution(share_type pay, database&);
        };

/**
 * @brief A institution who sends his pay to a vesting balance
 *
 * This institution type takes all of his pay and places it into a vesting balance
 */
        struct vesting_balance_institution_type
        {
            /// The balance this institution pays into
            vesting_balance_id_type balance;

            void pay_institution(share_type pay, database& db);
        };

/**
 * @brief A institution who permanently destroys all of his pay
 *
 * This institution sends all pay he receives to the null account.
 */
        struct burn_institution_type
        {
            /// Record of how much this institution has burned in his lifetime
            share_type total_burned;

            void pay_institution(share_type pay, database&);
        };
///@}

// The ordering of types in these two static variants MUST be the same.
        typedef static_variant<
        refund_institution_type,
        vesting_balance_institution_type,
        burn_institution_type
        > institution_type;


/**
 * @brief institution object contains the details of a blockchain institution. See @ref institutions for details.
 */
        class institution_object : public abstract_object<institution_object>
        {
        public:
            static const uint8_t space_id = protocol_ids;
            static const uint8_t type_id =  institution_object_type;

            /// ID of the account which owns this institution
            account_id_type institution_account;
            /// Time at which this institution begins receiving pay, if elected
//            time_point_sec work_begin_date;
            /// Time at which this institution will cease to receive pay. institution will be deleted at this time
//            time_point_sec work_end_date;
            /// Amount in CORE this institution will be paid each day
//            share_type daily_pay;
            /// ID of this institution's pay balance
            institution_type institution;
            /// Human-readable name for the institution
            string name;
            /// URL to a web page representing this institution
//            string url;

            /// Voting ID which represents approval of this institution
            vote_id_type vote_for;
            /// Voting ID which represents disapproval of this institution
            vote_id_type vote_against;

            uint64_t total_votes_for = 0;
            uint64_t total_votes_against = 0;

//            bool is_active(fc::time_point_sec now)const {
//                return now >= work_begin_date && now <= work_end_date;
//            }

            share_type approving_stake()const {
                return int64_t( total_votes_for ) - int64_t( total_votes_against );
            }
        };

        struct by_account;
        struct by_vote_for;
        struct by_vote_against;
        typedef multi_index_container<
        institution_object,
        indexed_by<
                ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >
        >
        > institution_object_multi_index_type;

        using institution_index = generic_index<institution_object, institution_object_multi_index_type>;

    } } // graphene::chain

FC_REFLECT( graphene::chain::refund_institution_type, (total_burned) )
FC_REFLECT( graphene::chain::vesting_balance_institution_type, (balance) )
FC_REFLECT( graphene::chain::burn_institution_type, (total_burned) )
FC_REFLECT_TYPENAME( graphene::chain::institution_type )
FC_REFLECT_DERIVED( graphene::chain::institution_object, (graphene::db::object),
(institution_account)
//        (work_begin_date)
//        (work_end_date)
//        (daily_pay)
        (institution)
        (vote_for)
        (vote_against)
        (total_votes_for)
        (total_votes_against)
        (name)
//        (url)
)
