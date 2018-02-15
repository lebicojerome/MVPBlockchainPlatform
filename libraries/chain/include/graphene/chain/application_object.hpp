#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    /**
     * @brief application object contains the details of a blockchain application. See @ref applications for details.
     */
    class application_object : public abstract_object<application_object>
    {
    public:
        static const uint8_t    space_id = protocol_ids;
        static const uint8_t    type_id  = application_object_type;

        /// ID of the account which owns this application
        account_id_type         owner;
        /// IDs of the admin accounts
        vector<account_id_type> admins;
        /// Human-readable name for the application
        string                  name;
        /// Short name for the application
        string                  short_name;
        /// Custom fields of application
        string                  customs;

        /// Voting ID which represents approval of this application
        vote_id_type            vote_for;
        /// Voting ID which represents disapproval of this application
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
    application_object,
    indexed_by<
        ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
        ordered_unique< tag<by_name>, member<application_object, string, &application_object::short_name> >,
        ordered_unique< tag<by_vote_for>, member< application_object, vote_id_type, &application_object::vote_for > >,
        ordered_unique< tag<by_vote_against>, member< application_object, vote_id_type, &application_object::vote_against > >
    >
    > application_object_multi_index_type;

    using application_index = generic_index<application_object, application_object_multi_index_type>;

} } // graphene::chain

FC_REFLECT_DERIVED( graphene::chain::application_object, (graphene::db::object),
    (owner)
    (admins)
    (vote_for)
    (vote_against)
    (total_votes_for)
    (total_votes_against)
    (name)
    (short_name)
    (customs)
)
