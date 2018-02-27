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

    struct information_relation {
        application_id_type application_id;
        information_id_type information_id;
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
        group_id_type           group;

        string                  admin_private_data_hash;
        string                  student_private_data_hash;
        string                  custom_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

        vector<information_relation>  parent_information_relations;

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

        string                  admin_private_data_hash;
        string                  student_private_data_hash;
        string                  custom_data;

        vector<account_id_type> confirming_admins;
        vector<account_id_type> confirmed_admins;

        vector<information_relation>  parent_information_relations;

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

FC_REFLECT( graphene::chain::information_relation,
    (application_id)
    (information_id)
)

FC_REFLECT( graphene::chain::information_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_create_operation,
    (fee)
    (owner)
    (group)
    (admin_private_data_hash)
    (student_private_data_hash)
    (custom_data)
    (confirming_admins)
    (confirmed_admins)
    (parent_information_relations)
    (status)
)

FC_REFLECT( graphene::chain::information_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::information_update_operation,
    (fee)
    (owner)
    (information)
    (group)
    (admin_private_data_hash)
    (student_private_data_hash)
    (custom_data)
    (confirming_admins)
    (confirmed_admins)
    (parent_information_relations)
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