#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    struct information_statistics
    {
        uint32_t    information_status_new = 0;
        uint32_t    information_status_ready = 0;
        uint32_t    information_status_published = 0;
        uint32_t    information_status_annul = 0;
        uint32_t    not_accept_count = 0;
    };

    /**
     * @brief information object contains the details of a blockchain information. See @ref informations for details.
     */
    class information_object : public abstract_object<information_object>
    {
    public:
        static const uint8_t     space_id = protocol_ids;
        static const uint8_t     type_id  = information_object_type;

        /// ID of the account which owns this information
        account_id_type          owner;
        group_id_type            group;

//        time_point_sec           issue_date;
//        time_point_sec           expiry_date;

//        string                   first_name;
//        string                   last_name;
//        string                   middle_name;

//        time_point_sec           birth_date;

//        string                   information_name;
//        string                   phone;
//        string                   email;

//        string                   identity_card_number;
//        string                   identity_card_type_name;

//        string                   text;

//        string                   public_custom;
//        string                   hidden_custom;

        string                   admin_private_data_hash;
        string                   student_private_data_hash;
        string                   public_hash;
        string                   custom_data;

//        optional<memo_endo>      admin_private_data;
//        optional<memo_endo>      student_private_data;

        vector<account_id_type>  confirming_admins;
        vector<account_id_type>  confirmed_admins;
        account_id_type          student_owner;

        uint8_t                  status;

        /// Voting ID which represents approval of this information
        vote_id_type             vote_for;
        /// Voting ID which represents disapproval of this information
        vote_id_type             vote_against;

        uint64_t                 total_votes_for = 0;
        uint64_t                 total_votes_against = 0;

        share_type approving_stake()const {
            return int64_t( total_votes_for ) - int64_t( total_votes_against );
        }
    };

    struct by_vote_for;
    struct by_vote_against;
    typedef multi_index_container<
    information_object,
    indexed_by<
        ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
//        ordered_unique< tag<by_name>, member<information_object, string, &information_object::short_name> >,
        ordered_unique< tag<by_vote_for>, member< information_object, vote_id_type, &information_object::vote_for > >,
        ordered_unique< tag<by_vote_against>, member< information_object, vote_id_type, &information_object::vote_against > >
    >
    > information_object_multi_index_type;

    using information_index = generic_index<information_object, information_object_multi_index_type>;

} } // graphene::chain

FC_REFLECT( graphene::chain::information_statistics,
    (information_status_new)
    (information_status_ready)
    (information_status_published)
    (information_status_annul)
    (not_accept_count)
)

FC_REFLECT_DERIVED( graphene::chain::information_object, (graphene::db::object),
    (owner)
    (group)
    (vote_for)
    (vote_against)
    (total_votes_for)
    (total_votes_against)
//    (issue_date)
//    (expiry_date)
//    (first_name)
//    (last_name)
//    (middle_name)
//    (birth_date)
//    (information_name)
//    (phone)
//    (email)
//    (identity_card_number)
//    (identity_card_type_name)
//    (text)
//    (public_custom)
//    (hidden_custom)
    (admin_private_data_hash)
    (student_private_data_hash)
    (public_hash)
    (custom_data)
    (confirming_admins)
    (confirmed_admins)
    (student_owner)
    (status)
)
