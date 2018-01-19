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
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         owner;

        time_point_sec          issue_date;
        time_point_sec          expiry_date;

        string                  first_name;
        string                  last_name;
        string                  middle_name;

        time_point_sec          birth_date;

        string                  document_name;
        string                  phone;
        string                  email;

        string                  identity_card_number;
        string                  identity_card_type_name;

        institution_id_type     institution;

        string                  text;

        string                  public_custom;
        string                  hidden_custom;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

        optional<memo_endo>     private_data;

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
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         owner;

        time_point_sec          issue_date;
        time_point_sec          expiry_date;

        string                  first_name;
        string                  last_name;
        string                  middle_name;

        time_point_sec          birth_date;

        string                  document_name;
        string                  phone;
        string                  email;

        string                  identity_card_number;
        string                  identity_card_type_name;

        document_id_type        document;
        institution_id_type     institution;

        string                  text;

        string                  public_custom;
        string                  hidden_custom;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

        optional<memo_endo>     private_data;

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
        account_id_type         owner;

        document_id_type        document;

        vector<account_id_type> confirmed_admins;
        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };

    struct document_publishing_operation : public base_operation // TODO::: del
    {
        struct fee_parameters_type {
            uint64_t fee = ENDO_DOCUMENT_PUBLISHED_FEE;
        };

        asset                         fee;
        account_id_type               owner;
        document_id_type              document;
        uint8_t                       status;
        asset                         amount;

        account_id_type               fee_payer()const { return owner; }
        void                          validate()const;
    };

    struct document_annuling_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                   fee;
        account_id_type         owner;
        document_id_type        document;
        uint8_t                 status;

        account_id_type         fee_payer()const { return owner; }
        void                    validate()const;
    };
} }

FC_REFLECT( graphene::chain::document_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_create_operation,
    (fee)
    (owner)
    (issue_date)
    (expiry_date)
    (first_name)
    (last_name)
    (middle_name)
    (birth_date)
    (document_name)
    (phone)
    (email)
    (identity_card_number)
    (identity_card_type_name)
    (institution)
    (text)
    (public_custom)
    (hidden_custom)
    (confirming_admins)
    (confirmed_admins)
    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::document_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_update_operation,
    (fee)
    (owner)
    (issue_date)
    (expiry_date)
    (first_name)
    (last_name)
    (middle_name)
    (birth_date)
    (document_name)
    (phone)
    (email)
    (identity_card_number)
    (identity_card_type_name)
    (document)
    (institution)
    (text)
    (public_custom)
    (hidden_custom)
    (confirming_admins)
    (confirmed_admins)
    (private_data)
    (status)
)

FC_REFLECT( graphene::chain::document_confirming_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_confirming_operation,
    (fee)
    (owner)
    (confirmed_admins)
    (document)
    (status)
)

FC_REFLECT( graphene::chain::document_publishing_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_publishing_operation,
    (fee)
    (owner)
    (document)
    (status)
    (amount)
)

FC_REFLECT( graphene::chain::document_annuling_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::document_annuling_operation,
    (fee)
    (owner)
    (document)
    (status)
)