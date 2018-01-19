#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    /**
     * @brief institution object contains the details of a blockchain institution. See @ref institutions for details.
     */
    class institution_object : public abstract_object<institution_object>
    {
    public:
        static const uint8_t    space_id = protocol_ids;
        static const uint8_t    type_id  = institution_object_type;

        /// ID of the account which owns this institution
        account_id_type         owner;
        /// IDs of the admin accounts
        vector<account_id_type> admins;
        /// Human-readable name for the institution
        string                  name;
        /// Short name for the institution
        string                  short_name;
        /// Phone of institution
        string                  phone;
        /// Address of institution
        string                  address;
        /// Custom fields of institution
        string                  customs;

        /// Voting ID which represents approval of this institution
        vote_id_type            vote_for;
        /// Voting ID which represents disapproval of this institution
        vote_id_type            vote_against;

        uint64_t                total_votes_for = 0;
        uint64_t                total_votes_against = 0;

        share_type approving_stake()const {
            return int64_t( total_votes_for ) - int64_t( total_votes_against );
        }
    };

    struct by_vote_for;
    struct by_vote_against;
    typedef multi_index_container<
    institution_object,
    indexed_by<
        ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
        ordered_unique< tag<by_name>, member<institution_object, string, &institution_object::short_name> >,
        ordered_unique< tag<by_vote_for>, member< institution_object, vote_id_type, &institution_object::vote_for > >,
        ordered_unique< tag<by_vote_against>, member< institution_object, vote_id_type, &institution_object::vote_against > >
    >
    > institution_object_multi_index_type;

    using institution_index = generic_index<institution_object, institution_object_multi_index_type>;

} } // graphene::chain

FC_REFLECT_DERIVED( graphene::chain::institution_object, (graphene::db::object),
    (owner)
    (admins)
    (vote_for)
    (vote_against)
    (total_votes_for)
    (total_votes_against)
    (name)
    (short_name)
    (phone)
    (address)
    (customs)
)
