#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    /**
     * @brief group object contains the details of a blockchain group. See @ref groups for details.
     */
    class group_object : public abstract_object<group_object>
    {
    public:
        static const uint8_t    space_id = protocol_ids;
        static const uint8_t    type_id  = group_object_type;

        /// ID of the account which owns this group
        account_id_type         owner;
        /// IDs of the admin accounts
        vector<account_id_type> admins;
        /// Human-readable name for the group
        string                  name;
        /// Short name for the group
        string                  short_name;
        /// Phone of group
        string                  phone;
        /// Address of group
        string                  address;
        /// Custom fields of group
        string                  customs;

        /// Voting ID which represents approval of this group
        vote_id_type            vote_for;
        /// Voting ID which represents disapproval of this group
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
    group_object,
    indexed_by<
        ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
        ordered_unique< tag<by_name>, member<group_object, string, &group_object::short_name> >,
        ordered_unique< tag<by_vote_for>, member< group_object, vote_id_type, &group_object::vote_for > >,
        ordered_unique< tag<by_vote_against>, member< group_object, vote_id_type, &group_object::vote_against > >
    >
    > group_object_multi_index_type;

    using group_index = generic_index<group_object, group_object_multi_index_type>;

} } // graphene::chain

FC_REFLECT_DERIVED( graphene::chain::group_object, (graphene::db::object),
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
