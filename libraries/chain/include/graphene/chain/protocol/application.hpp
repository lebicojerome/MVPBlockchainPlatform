#pragma once
#include <graphene/chain/protocol/base.hpp>

namespace graphene { namespace chain {

    /**
     * @brief Create a new application object
     * @ingroup operations
     */
    struct application_create_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                       fee;
        account_id_type             owner;

        string                      name;
        string                      short_name;
        string                      customs;
        vector<account_id_type>     admins;

        account_id_type   fee_payer()const { return owner; }
        void              validate()const;
    };

    /**
     * @brief Update an existing application
     * @ingroup operations
     */
    struct application_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                       fee;
        account_id_type             owner;

        string                      name;
        string                      short_name;
        string                      customs;
        vector<account_id_type>     admins;

        application_id_type         application;

        account_id_type   fee_payer()const { return owner; }
        void              validate()const;
    };
} }

FC_REFLECT( graphene::chain::application_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::application_create_operation,
    (fee)
    (owner)
    (name)
    (short_name)
    (customs)
    (admins)
)

FC_REFLECT( graphene::chain::application_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::application_update_operation,
    (fee)
    (owner)
    (name)
    (short_name)
    (customs)
    (application)
    (admins)
)