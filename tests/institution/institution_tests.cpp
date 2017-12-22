/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <boost/test/unit_test.hpp>
#include <fc/crypto/openssl.hpp>
#include <openssl/rand.h>

#include <graphene/chain/institution_object.hpp>
#include <graphene/chain/match_object.hpp>
#include <graphene/chain/game_object.hpp>
#include "../common/database_fixture.hpp"
#include <graphene/utilities/tempdir.hpp>
#include <graphene/chain/asset_object.hpp>
#include <graphene/chain/is_authorized_asset.hpp>

#include <boost/algorithm/string/replace.hpp>

using namespace graphene::chain;

// defined if "bye" matches fix available
#define BYE_MATCHES_FIXED

#define RAND_MAX_MIN(MAX, MIN) (std::rand() % ((MAX) - (MIN) + 1) + (MIN))

BOOST_AUTO_TEST_SUITE(institution_tests)

// class performing operations necessary for creating institutions,
// having players join the institutions and playing institutions to completion.
class institutions_helper
{
public:

    institutions_helper(database_fixture& df) : df(df)
    {
        assets.insert(asset_id_type());
        current_asset_idx = 0;
        optional<account_id_type> dividend_account = get_asset_dividend_account(asset_id_type());
        if (dividend_account.valid())
            players.insert(*dividend_account);
    }

    const std::set<institution_id_type>& list_institutions()
    {
        return institutions;
    }

    std::map<account_id_type, std::map<asset_id_type, share_type>> list_players_balances()
    {
        std::map<account_id_type, std::map<asset_id_type, share_type>> result;
        for (account_id_type player_id: players)
        {
            for( asset_id_type asset_id: assets)
            {
                asset a = df.db.get_balance(player_id, asset_id);
                result[player_id][a.asset_id] = a.amount;
             }
        }
        return result;
    }

    std::map<account_id_type, std::map<asset_id_type, share_type>> get_players_fees()
    {
        return players_fees;
    }

    void reset_players_fees()
    {
        for (account_id_type player_id: players)
        {
            for( asset_id_type asset_id: assets)
            {
                players_fees[player_id][asset_id] = 0;
            }
        }
    }

    void create_asset(const account_id_type& issuer_account_id,
                      const string& symbol,
                      uint8_t precision,
                      asset_options& common,
                      const fc::ecc::private_key& sig_priv_key)
    {
        graphene::chain::database& db = df.db;
        const chain_parameters& params = db.get_global_properties().parameters;
        signed_transaction tx;
        asset_create_operation op;
        op.issuer = issuer_account_id;
        op.symbol = symbol;
        op.precision = precision;
        op.common_options = common;

        tx.operations = {op};
        for( auto& op : tx.operations )
            db.current_fee_schedule().set_fee(op);
        tx.validate();
        tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
        df.sign(tx, sig_priv_key);
        PUSH_TX(db, tx);

        assets.insert(asset_id_type(++current_asset_idx));
    }

    void update_dividend_asset(const asset_id_type asset_to_update_id,
                               dividend_asset_options new_options,
                               const fc::ecc::private_key& sig_priv_key)
    {
        graphene::chain::database& db = df.db;
        const chain_parameters& params = db.get_global_properties().parameters;
        signed_transaction tx;
        asset_update_dividend_operation update_op;

        update_op.issuer = asset_to_update_id(db).issuer;
        update_op.asset_to_update = asset_to_update_id;
        update_op.new_options = new_options;

        tx.operations = {update_op};
        for( auto& op : tx.operations )
           db.current_fee_schedule().set_fee(op);
        tx.validate();
        tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
        df.sign(tx, sig_priv_key);
        PUSH_TX(db, tx);

        optional<account_id_type> dividend_account = get_asset_dividend_account(asset_to_update_id);
        if (dividend_account.valid())
          players.insert(*dividend_account);
    }

    optional<account_id_type> get_asset_dividend_account(const asset_id_type& asset_id)
    {
        graphene::chain::database& db = df.db;
        optional<account_id_type> result;
        const asset_object& asset_obj = asset_id(db);

        if (asset_obj.dividend_data_id.valid())
        {
           const asset_dividend_data_object& dividend_data = (*asset_obj.dividend_data_id)(db);
           result = dividend_data.dividend_distribution_account;
        }
        return result;
    }

//    const institution_id_type create_institution (const account_id_type& creator,
//                                                const fc::ecc::private_key& sig_priv_key,
//                                                asset buy_in,
//                                                uint32_t number_of_players = 2,
//                                                uint32_t time_per_commit_move = 3,
//                                                uint32_t time_per_reveal_move = 1,
//                                                uint32_t number_of_wins = 3,
//                                                int32_t registration_deadline = 3600,
//                                                uint32_t start_delay = 3,
//                                                uint32_t round_delay = 3,
//                                                bool insurance_enabled = false,
//                                                uint32_t number_of_gestures = 3,
//                                                uint32_t start_time = 0,
//                                                fc::optional<flat_set<account_id_type> > whitelist = fc::optional<flat_set<account_id_type> >()
//                                                )
//    {
//        if (current_institution_idx.valid())
//            current_institution_idx = *current_institution_idx + 1;
//        else
//            current_institution_idx = 0;
//
//        graphene::chain::database& db = df.db;
//        const chain_parameters& params = db.get_global_properties().parameters;
//        signed_transaction trx;
//        institution_options options;
//        institution_create_operation op;
//        rock_paper_scissors_game_options& game_options = options.game_options.get<rock_paper_scissors_game_options>();
//
//        game_options.number_of_gestures = number_of_gestures;
//        game_options.time_per_commit_move = time_per_commit_move;
//        game_options.time_per_reveal_move = time_per_reveal_move;
//        game_options.insurance_enabled = insurance_enabled;
//
//        options.registration_deadline = db.head_block_time() + fc::seconds(registration_deadline + *current_institution_idx);
//        options.buy_in = buy_in;
//        options.number_of_players = number_of_players;
//        if (start_delay)
//            options.start_delay = start_delay;
//        if (start_time)
//            options.start_time = db.head_block_time() + fc::seconds(start_time);
//        options.round_delay = round_delay;
//        options.number_of_wins = number_of_wins;
//        if (whitelist.valid())
//            options.whitelist = *whitelist;
//
//        op.creator = creator;
//        op.options = options;
//        trx.operations = {op};
//        for( auto& op : trx.operations )
//            db.current_fee_schedule().set_fee(op);
//        trx.validate();
//        trx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
//        df.sign(trx, sig_priv_key);
//        PUSH_TX(db, trx);
//
//        institution_id_type institution_id = institution_id_type(*current_institution_idx);
//        institutions.insert(institution_id);
//        return institution_id;
//    }
//
//    void join_institution(const institution_id_type & institution_id,
//                         const account_id_type& player_id,
//                         const account_id_type& payer_id,
//                         const fc::ecc::private_key& sig_priv_key,
//                         asset buy_in
//                         )
//    {
//        graphene::chain::database& db = df.db;
//        const chain_parameters& params = db.get_global_properties().parameters;
//        signed_transaction tx;
//        institution_join_operation op;
//
//        op.payer_account_id = payer_id;
//        op.buy_in = buy_in;
//        op.player_account_id = player_id;
//        op.institution_id = institution_id;
//        tx.operations = {op};
//        for( auto& op : tx.operations )
//            db.current_fee_schedule().set_fee(op);
//        tx.validate();
//        tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
//        df.sign(tx, sig_priv_key);
//        PUSH_TX(db, tx);
//
//        players.insert(player_id);
//        players_keys[player_id] = sig_priv_key;
//   }
//
//   void leave_institution(const institution_id_type & institution_id,
//                         const account_id_type& player_id,
//                         const account_id_type& canceling_account_id,
//                         const fc::ecc::private_key& sig_priv_key
//                        )
//   {
//       graphene::chain::database& db = df.db;
//       const chain_parameters& params = db.get_global_properties().parameters;
//       signed_transaction tx;
//       institution_leave_operation op;
//
//       op.canceling_account_id = canceling_account_id;
//       op.player_account_id = player_id;
//       op.institution_id = institution_id;
//       tx.operations = {op};
//       for( auto& op : tx.operations )
//           db.current_fee_schedule().set_fee(op);
//       tx.validate();
//       tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
//       df.sign(tx, sig_priv_key);
//       PUSH_TX(db, tx);
//
//       //players.erase(player_id);
//   }
//
//
//
//    // stolen from cli_wallet
//    void rps_throw(const game_id_type& game_id,
//                   const account_id_type& player_id,
//                   rock_paper_scissors_gesture gesture,
//                   const fc::ecc::private_key& sig_priv_key
//                   )
//    {
//
//       graphene::chain::database& db = df.db;
//       const chain_parameters& params = db.get_global_properties().parameters;
//
//       // check whether the gesture is appropriate for the game we're playing
//       game_object game_obj = game_id(db);
//       match_object match_obj = game_obj.match_id(db);
//       institution_object institution_obj = match_obj.institution_id(db);
//       rock_paper_scissors_game_options game_options = institution_obj.options.game_options.get<rock_paper_scissors_game_options>();
//       assert((int)gesture < game_options.number_of_gestures);
//
//       account_object player_account_obj = player_id(db);
//
//       // construct the complete throw, the commit, and reveal
//       rock_paper_scissors_throw full_throw;
//       rand_bytes((char*)&full_throw.nonce1, sizeof(full_throw.nonce1));
//       rand_bytes((char*)&full_throw.nonce2, sizeof(full_throw.nonce2));
//       full_throw.gesture = gesture;
//
//       rock_paper_scissors_throw_commit commit_throw;
//       commit_throw.nonce1 = full_throw.nonce1;
//       std::vector<char> full_throw_packed(fc::raw::pack(full_throw));
//       commit_throw.throw_hash = fc::sha256::hash(full_throw_packed.data(), full_throw_packed.size());
//
//       rock_paper_scissors_throw_reveal reveal_throw;
//       reveal_throw.nonce2 = full_throw.nonce2;
//       reveal_throw.gesture = full_throw.gesture;
//
//       // store off the reveal for applying after both players commit
//       committed_game_moves[commit_throw] = reveal_throw;
//
//       signed_transaction tx;
//       game_move_operation move_operation;
//       move_operation.game_id = game_id;
//       move_operation.player_account_id = player_account_obj.id;
//       move_operation.move = commit_throw;
//       tx.operations = {move_operation};
//       for( operation& op : tx.operations )
//       {
//           asset f = db.current_fee_schedule().set_fee(op);
//           players_fees[player_id][f.asset_id] -= f.amount;
//       }
//       tx.validate();
//       tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
//       df.sign(tx, sig_priv_key);
//       if (/*match_obj.match_winners.empty() &&*/ game_obj.get_state() == game_state::expecting_commit_moves) // checking again
//          PUSH_TX(db, tx);
//    }
//
//    // spaghetti programming
//    // walking through all institutions, matches and games and throwing random moves
//    // optionaly skip generting randomly selected moves
//    // every_move_is >= 0 : every game is tie
//    void play_games(unsigned skip_some_commits = 0, unsigned skip_some_reveals = 0, int every_move_is = -1)
//    {
//      //try
//      //{
//        graphene::chain::database& db = df.db;
//        const chain_parameters& params = db.get_global_properties().parameters;
//
//        for(const auto& institution_id: institutions)
//        {
//            const institution_object& institution = institution_id(db);
//            const institution_details_object& institution_details = institution.institution_details_id(db);
//            rock_paper_scissors_game_options game_options = institution.options.game_options.get<rock_paper_scissors_game_options>();
//            for(const auto& match_id: institution_details.matches)
//            {
//                const match_object& match = match_id(db);
//                for(const auto& game_id: match.games )
//                {
//                    const game_object& game = game_id(db);
//                    const rock_paper_scissors_game_details& rps_details = game.game_details.get<rock_paper_scissors_game_details>();
//                    if (game.get_state() == game_state::expecting_commit_moves)
//                    {
//                        for(const auto& player_id: game.players)
//                        {
//                            if ( players_keys.find(player_id) != players_keys.end())
//                            {
//                                if (!skip_some_commits || player_id.instance.value % skip_some_commits != game_id.instance.value % skip_some_commits)
//                                {
//                                    auto iter = std::find(game.players.begin(), game.players.end(), player_id);
//                                    unsigned player_index = std::distance(game.players.begin(), iter);
//                                    if (!rps_details.commit_moves.at(player_index))
//                                        rps_throw(game_id, player_id,
//                                                  (rock_paper_scissors_gesture) (every_move_is >= 0 ? every_move_is : (std::rand() % game_options.number_of_gestures)), players_keys[player_id]);
//                                }
//                            }
//                        }
//                    }
//                    else if (game.get_state() == game_state::expecting_reveal_moves)
//                    {
//                        for (unsigned i = 0; i < 2; ++i)
//                        {
//                           if (rps_details.commit_moves.at(i) &&
//                               !rps_details.reveal_moves.at(i))
//                           {
//                              const account_id_type& player_id = game.players[i];
//                              if (players_keys.find(player_id) != players_keys.end())
//                              {
//                                 {
//
//                                    auto iter = committed_game_moves.find(*rps_details.commit_moves.at(i));
//                                    if (iter != committed_game_moves.end())
//                                    {
//                                       if (!skip_some_reveals || player_id.instance.value % skip_some_reveals != game_id.instance.value % skip_some_reveals)
//                                       {
//                                           const rock_paper_scissors_throw_reveal& reveal = iter->second;
//
//                                           game_move_operation move_operation;
//                                           move_operation.game_id = game.id;
//                                           move_operation.player_account_id = player_id;
//                                           move_operation.move = reveal;
//
//                                           signed_transaction tx;
//                                           tx.operations = {move_operation};
//                                           for( auto& op : tx.operations )
//                                           {
//                                               asset f = db.current_fee_schedule().set_fee(op);
//                                               players_fees[player_id][f.asset_id] -= f.amount;
//                                           }
//                                           tx.validate();
//                                           tx.set_expiration(db.head_block_time() + fc::seconds( params.block_interval * (params.maintenance_skip_slots + 1) * 3));
//                                           df.sign(tx, players_keys[player_id]);
//                                           if (game.get_state() == game_state::expecting_reveal_moves) // check again
//                                               PUSH_TX(db, tx);
//                                       }
//                                    }
//                                 }
//                              }
//                           }
//                        }
//                    }
//                }
//            }
//        }
//      //}
//      //catch (fc::exception& e)
//      //{
//      //    edump((e.to_detail_string()));
//      //    throw;
//      //}
//    }

private:
    database_fixture& df;
    // index of last created institution
    fc::optional<uint64_t> current_institution_idx;
    // index of last asset
    uint64_t current_asset_idx;
    // assets : core and maybe others
    std::set<asset_id_type> assets;
    // institutions to be played
    std::set<institution_id_type> institutions;
    // all players registered in institutions
    std::set<account_id_type> players;
    // players' private keys
    std::map<account_id_type, fc::ecc::private_key> players_keys;
    // total charges for moves made by every player
    std::map<account_id_type, std::map<asset_id_type, share_type>> players_fees;
    // store of commits and reveals
//    std::map<rock_paper_scissors_throw_commit, rock_paper_scissors_throw_reveal> committed_game_moves;

    // taken from rand.cpp
    void rand_bytes(char* buf, int count)
    {
      fc::init_openssl();

      int result = RAND_bytes((unsigned char*)buf, count);
      if (result != 1)
        FC_THROW("Error calling OpenSSL's RAND_bytes(): ${code}", ("code", (uint32_t)ERR_get_error()));
    }
};

/// Expecting assertion

//  creating institution
