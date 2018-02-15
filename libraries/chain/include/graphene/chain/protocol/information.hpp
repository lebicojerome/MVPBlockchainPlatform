#pragma once
#include <graphene/chain/protocol/base.hpp>
#include <graphene/chain/protocol/memo.hpp>

namespace graphene { namespace chain {

    struct information_object_const
    {
        enum information_object_statuses
        {
            information_status_new        = 0x0,
            information_status_ready      = 0x1,
            information_status_published  = 0x2,
            information_status_annul      = 0x3
        };
    };

    /**
     * @brief Create a new information object
     * @ingroup operations
     */
    struct information_create_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t    fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
            uint32_t    price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
        };

        asset                   fee;
        account_id_type         owner;
        group_id_type     group;

//        time_point_sec          issue_date;
//        time_point_sec          expiry_date;

//        string                  first_name;
//        string                  last_name;
//        string                  middle_name;

//        time_point_sec          birth_date;

//        string                  information_name;
//        string                  phone;
//        string                  email;

//        string                  identity_card_number;
//        string                  identity_card_type_name;

//        string                  text;

//        string                  public_custom;
//        string                  hidden_custom;

        string                  admin_private_data_hash;
        string                  student_private_data_hash;
        string                  custom_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

//        optional<memo_endo>     private_data;

        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };

    /**
     * @brief Update an existing information
     * @ingroup operations
     */
    struct information_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t    fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
            uint32_t    price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
        };

        asset                   fee;
        account_id_type         owner;
        information_id_type        information;
        group_id_type     group;

//        time_point_sec          issue_date;
//        time_point_sec          expiry_date;

//        string                  first_name;
//        string                  last_name;
//        string                  middle_name;

//        time_point_sec          birth_date;

//        string                  information_name;
//        string                  phone;
//        string                  email;

//        string                  identity_card_number;
//        string                  identity_card_type_name;

//        string                  text;

//        string                  public_custom;
//        string                  hidden_custom;

        string                  admin_private_data_hash;
        string                  student_private_data_hash;
        string                  custom_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

//        optional<memo_endo>     private_data;

        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };

    struct information_confirming_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;

        information_id_type        information;

        vector<account_id_type> confirmed_admins;
        uint8_t                 status;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };

    struct information_annuling_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;
        information_id_type        information;
        uint8_t                 status;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };

    struct information_hash_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;
        information_id_type        information;
        string                  public_hash;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };

    struct information_binding_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         account;
        account_id_type         student;
        information_id_type        information;

        account_id_type         fee_payer()const { return account; }
        void                    validate()const;
    };
} }

FC_REFLECT( graphene::chain::information_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_create_operation,
    (fee)
    (owner)
    (group)
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
    (custom_data)
    (confirming_admins)
    (confirmed_admins)
//    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::information_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_update_operation,
    (fee)
    (owner)
    (information)
    (group)
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
    (custom_data)
    (confirming_admins)
    (confirmed_admins)
//    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::information_confirming_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_confirming_operation,
    (fee)
    (account)
    (confirmed_admins)
    (information)
    (status)
)

FC_REFLECT( graphene::chain::information_annuling_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_annuling_operation,
    (fee)
    (account)
    (information)
    (status)
)

FC_REFLECT( graphene::chain::information_hash_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_hash_update_operation,
    (fee)
    (account)
    (information)
    (public_hash)
)

FC_REFLECT( graphene::chain::information_binding_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_binding_operation,
    (fee)
    (account)
    (student)
    (information)
)