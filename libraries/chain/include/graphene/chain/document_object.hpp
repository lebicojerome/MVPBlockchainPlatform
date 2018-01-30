#pragma once
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    /**
     * @brief document object contains the details of a blockchain document. See @ref documents for details.
     */

    class document_object : public abstract_object<document_object>
    {
    public:
        static const uint8_t     space_id = protocol_ids;
        static const uint8_t     type_id  = document_object_type;

        /// ID of the account which owns this document
        account_id_type          owner;
        institution_id_type      institution;

//        time_point_sec           issue_date;
//        time_point_sec           expiry_date;

//        string                   first_name;
//        string                   last_name;
//        string                   middle_name;

//        time_point_sec           birth_date;

//        string                   document_name;
//        string                   phone;
//        string                   email;

//        string                   identity_card_number;
//        string                   identity_card_type_name;

//        string                   text;

//        string                   public_custom;
//        string                   hidden_custom;

        string                   public_hash;

        optional<memo_endo>      admin_private_data;
        optional<memo_endo>      student_private_data;

        vector<account_id_type>  confirming_admins;
        vector<account_id_type>  confirmed_admins;

        uint8_t                  status;

        /// Voting ID which represents approval of this document
        vote_id_type             vote_for;
        /// Voting ID which represents disapproval of this document
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
    document_object,
    indexed_by<
        ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
//        ordered_unique< tag<by_name>, member<document_object, string, &document_object::short_name> >,
        ordered_unique< tag<by_vote_for>, member< document_object, vote_id_type, &document_object::vote_for > >,
        ordered_unique< tag<by_vote_against>, member< document_object, vote_id_type, &document_object::vote_against > >
    >
    > document_object_multi_index_type;

    using document_index = generic_index<document_object, document_object_multi_index_type>;

} } // graphene::chain

FC_REFLECT_DERIVED( graphene::chain::document_object, (graphene::db::object),
    (owner)
    (institution)
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
//    (document_name)
//    (phone)
//    (email)
//    (identity_card_number)
//    (identity_card_type_name)
//    (text)
//    (public_custom)
//    (hidden_custom)
    (public_hash)
    (admin_private_data)
    (student_private_data)
    (confirming_admins)
    (confirmed_admins)
    (status)
)
