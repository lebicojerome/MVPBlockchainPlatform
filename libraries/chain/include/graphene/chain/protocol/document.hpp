#pragma once
#include <graphene/chain/protocol/base.hpp>
#include <graphene/chain/protocol/memo.hpp>

namespace graphene { namespace chain {

    struct document_object_const
    {
        enum document_object_statuses
        {
            document_status_new        = 0x0,
            document_status_ready      = 0x1,
            document_status_published  = 0x2,
            document_status_annul      = 0x3
        };
    };

    /**
     * @brief Create a new document object
     * @ingroup operations
     */
    struct document_create_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t    fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
            uint32_t    price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
        };

        asset                   fee;
        account_id_type         owner;
        institution_id_type     institution;

//        time_point_sec          issue_date;
//        time_point_sec          expiry_date;

//        string                  first_name;
//        string                  last_name;
//        string                  middle_name;

//        time_point_sec          birth_date;

//        string                  document_name;
//        string                  phone;
//        string                  email;

//        string                  identity_card_number;
//        string                  identity_card_type_name;

//        string                  text;

//        string                  public_custom;
//        string                  hidden_custom;

        optional<memo_endo>     admin_private_data;
        optional<memo_endo>     student_private_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

//        optional<memo_endo>     private_data;

        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };

    /**
     * @brief Update an existing document
     * @ingroup operations
     */
    struct document_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t    fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
            uint32_t    price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
        };

        asset                   fee;
        account_id_type         owner;
        document_id_type        document;
        institution_id_type     institution;

//        time_point_sec          issue_date;
//        time_point_sec          expiry_date;

//        string                  first_name;
//        string                  last_name;
//        string                  middle_name;

//        time_point_sec          birth_date;

//        string                  document_name;
//        string                  phone;
//        string                  email;

//        string                  identity_card_number;
//        string                  identity_card_type_name;

//        string                  text;

//        string                  public_custom;
//        string                  hidden_custom;

        optional<memo_endo>     admin_private_data;
        optional<memo_endo>     student_private_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

//        optional<memo_endo>     private_data;

        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };

    struct document_confirming_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;

        document_id_type        document;

        vector<account_id_type> confirmed_admins;
        uint8_t                 status;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };

    struct document_annuling_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;
        document_id_type        document;
        uint8_t                 status;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };

    struct document_hash_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;
        document_id_type        document;
        string                  public_hash;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };
} }

FC_REFLECT( graphene::chain::document_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_create_operation,
    (fee)
    (owner)
    (institution)
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
    (admin_private_data)
    (student_private_data)
    (confirming_admins)
    (confirmed_admins)
//    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::document_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_update_operation,
    (fee)
    (owner)
    (document)
    (institution)
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
    (admin_private_data)
    (student_private_data)
    (confirming_admins)
    (confirmed_admins)
//    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::document_confirming_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_confirming_operation,
    (fee)
    (account)
    (confirmed_admins)
    (document)
    (status)
)

FC_REFLECT( graphene::chain::document_annuling_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_annuling_operation,
    (fee)
    (account)
    (document)
    (status)
)

FC_REFLECT( graphene::chain::document_hash_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_hash_update_operation,
    (fee)
    (account)
    (document)
    (public_hash)
)