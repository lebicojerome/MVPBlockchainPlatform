#pragma once
#include <graphene/chain/protocol/base.hpp>

namespace graphene { namespace chain {

    /**
     * @brief Create a new institution object
     * @ingroup operations
     */
    struct institution_create_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                       fee;
        account_id_type             owner;

        string                      name;
        string                      short_name;
        string                      phone;
        string                      address;
        string                      customs;
        vector<account_id_type>     admins;

        account_id_type   fee_payer()const { return owner; }
        void              validate()const;
    };

    /**
     * @brief Update an existing institution
     * @ingroup operations
     */
    struct institution_update_operation : public base_operation
    {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        asset                       fee;
        account_id_type             owner;

        string                      name;
        string                      short_name;
        string                      phone;
        string                      address;
        string                      customs;
        vector<account_id_type>     admins;

        institution_id_type         institution;

        account_id_type   fee_payer()const { return owner; }
        void              validate()const;
    };
} }

FC_REFLECT( graphene::chain::institution_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::institution_create_operation,
    (fee)
    (owner)
    (name)
    (short_name)
    (phone)
    (address)
    (customs)
    (admins)
)

FC_REFLECT( graphene::chain::institution_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( graphene::chain::institution_update_operation,
    (fee)
    (owner)
    (name)
    (short_name)
    (phone)
    (address)
    (customs)
    (institution)
    (admins)
)