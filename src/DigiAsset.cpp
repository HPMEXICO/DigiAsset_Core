//
// Created by mctrivia on 07/06/23.
//

#include "static_block.hpp"
#include "DigiAsset.h"
#include "BitIO.h"
#include "IPFS.h"
#include "KYC.h"
#include <cryptopp870/sha.h>
#include <cryptopp870/ripemd.h>
#include <iostream>
#include "Base58.h"
#include "Blob.h"

using namespace std;




/*
 ██████╗ ██████╗ ███╗   ██╗███████╗████████╗ █████╗ ███╗   ██╗████████╗███████╗
██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗████╗  ██║╚══██╔══╝██╔════╝
██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ███████║██╔██╗ ██║   ██║   ███████╗
██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██║██║╚██╗██║   ██║   ╚════██║
╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║██║ ╚████║   ██║   ███████║
 ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
 */

const string DigiAsset::standardVoteAddresses[] = {"D8LWk1fGksGDxZai17A5wQUVsRiV69Nk7J",
                                                   "DBJNvWeirccgeAdZn9gV5otheutdthzWxx",
                                                   "D9zaWjGHuVNB32G7Pf5BMmtvDifdoS3Wsq",
                                                   "DEKQEMFHTc1M8Gs4xvY6paZ5RKtE1cbqNp",
                                                   "D8jnQigMYwhrB6Zjs73deF5RKprUdX5uvd",
                                                   "DELKWiuSj86pMfDb7aDaAUhLYG8D7H6JVj",
                                                   "DHUg85Pbc6mDK3y7kaWmsqjRaWfRVGys2U",
                                                   "D9rxXUhaDxku4ZhdkLtyZzmmGG5ViUAYds",
                                                   "DNehqnpzLWnv7vTTxkbHsneajBEzGjvLo2",
                                                   "DAKiRnvVCfD4imp5A41tCeoZkezzkPXB4C",
                                                   "D69jwFMuawBkG1hii1muQESFrbZFenZrmL",
                                                   "D7PJqwFSLmCURDNnd5cc9Ham856GwDQ9zy",
                                                   "DFHa9HQ9BDHuDKmBPvPzBE5dsLm85prUd4",
                                                   "DAJMr7m4ZyaCRa9Y1o8pMaAPViBhSZTENs",
                                                   "DFXqwRzai3Khd3n1uRaYgZTq1BhAUhyu3m",
                                                   "DSTKiCYQqpvrXME3rEFeYEsH3dZHCPU8ez",
                                                   "DG1rJMg6zCMoiptWeEozxpuVWKGmZkiHTf",
                                                   "DRgWqHV6d7HSxYhA5bCMvtLhuS3kbRYKo3",
                                                   "DD9kssWTzT8s5fv4Xg3MthRNCT7RtawQSw",
                                                   "DLLYN7hv535nXzpvZv25ySG8GdsfYNk1Bx",
                                                   "DJQEaiT39GyJgCJK7noarscutoeWHXMLaM",
                                                   "DEkaR4NfvWx3bq1MBw2nTcTP2JEPxKyaBX",
                                                   "DN9vVGNYzbjqTGRRGXkjiGVTpuKRz1eYe3",
                                                   "D6kCF8PDhwdPzSg3xeUmrDzVK9eK3nuEJj",
                                                   "DR3F3WE78aJmHvyGA35NjkLLf5F9X8eKaz",
                                                   "DSMdwgWYbEpPNQJ2Hs9Y89JqNmQdiwhWaq",
                                                   "DGJCxLgqW2sbhomNZvsDGsjam8pnY2b7uA",
                                                   "DAaQuGSbvRQA2B7zzbrQ3SRRYC9qaQVZch",
                                                   "DJbcjvGf7wzQaAQQ9GpHP1menk6jHyCsW4",
                                                   "DC5vxafEZQeqpqDawTyDx7nBW81V6LfrE5",
                                                   "DKJhzwe5PzFQuUdrzJR9gUfkvk4jzvUrZU",
                                                   "DRX7r83LHBf1cWKnBoAd8q1iN6UP833kPx",
                                                   "DShw4ZaRmW9fyWnP3umEyZ9KyJHWR9v6BD",
                                                   "DK9zdFCv9yz3C7jVbnTbVCZgGAd8S1Xqxk",
                                                   "DG2Gv2aZRALtMkKtaJEQr75bFqsL3JbKmB",
                                                   "D9zt7Xb1RgBepPrrYSRPv6N6YCUcS5CRx6",
                                                   "DAgRoBgYaDx7g6JPRZyufvFQAQc4zdjaP1",
                                                   "DPLi14JkyEjkbWQMQGavBARN8xo4avmuMh",
                                                   "DU4mqG99gi77BcZoS8FaJEiHk5HRYXNEcb",
                                                   "D6QdquB54saxViwAfL9xKiwoXaFo7UU5ec",
                                                   "DStTMUY2U1XSLsdq9uuWgfQefPDkQJkGQC",
                                                   "DPUV7Htc7jBwhc9z5rqoDFmKW3y1fE8xwA",
                                                   "DEGatQLqYCD9BumaXAqTFRCYZ4vznhQXcY",
                                                   "DCL7fkgzSSQSLvDMXqiRdnR9qQx5MjK89t",
                                                   "DNxc93Q2rrCm92sVyrtKhCn5MMC5YtuXxK",
                                                   "DDtWWXHe9a4EPn2EawiTDzYjq8SEKKRS6J",
                                                   "DNr54LSpN6iAQda1QYqykqeU7j7TyLeCcA",
                                                   "DE6eJePsjMDrTdKoi8HAGbX6Sdwh4RGTP9",
                                                   "D5kY1eMcDfLZWznQFSjCQMUW8DiSoxhmuy",
                                                   "D6dSnsPqcLaVvcH1MSFRMUy5KyVbnDufiX"};
const ExchangeRate DigiAsset::standardExchangeRates[] = {
        {
                .address =  "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =    0,
                .name =     "CAD"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   1,
                .name =    "USD"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   2,
                .name =    "EUR"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   3,
                .name =    "GBP"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   4,
                .name =    "AUD"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   5,
                .name =    "JPY"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   6,
                .name =    "CNY"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   7,
                .name =    "TRY"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   8,
                .name =    "BRL"
        },
        {
                .address = "dgb1qunxh378eltj2jrwza5sj9grvu5xud43vqvudwh",
                .index =   9,
                .name =    "CHF"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   0,
                .name =    "BTC"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   1,
                .name =    "ETH"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   2,
                .name =    "LTC"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   3,
                .name =    "DCR"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   4,
                .name =    "ZIL"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   5,
                .name =    "RVN"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   6,
                .name =    "XVG"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   7,
                .name =    "RDD"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   8,
                .name =    "NXS"
        },
        {
                .address = "dgb1qlk3hldeynl3prqw259u8gv0jh7w5nwppxlvt3v",
                .index =   9,
                .name =    "POT"
        }
};


/*
██╗  ██╗███████╗██╗     ██████╗ ███████╗██████╗ ███████╗
██║  ██║██╔════╝██║     ██╔══██╗██╔════╝██╔══██╗██╔════╝
███████║█████╗  ██║     ██████╔╝█████╗  ██████╔╝███████╗
██╔══██║██╔══╝  ██║     ██╔═══╝ ██╔══╝  ██╔══██╗╚════██║
██║  ██║███████╗███████╗██║     ███████╗██║  ██║███████║
╚═╝  ╚═╝╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝
 */

/**
 * Takes binary data stored in a string and hashes it twice.  First with sha256 then with ripemd160
 */
void DigiAsset::insertSRHash(vector<uint8_t> dataToHash, vector<uint8_t>& result, size_t startIndex) {
    //do sha256
    CryptoPP::byte abDigest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(abDigest, reinterpret_cast<const CryptoPP::byte*>(dataToHash.data()),
                                       dataToHash.size());

    //do ripemd160
    CryptoPP::byte abDigest2[CryptoPP::RIPEMD160::DIGESTSIZE];
    CryptoPP::RIPEMD160().CalculateDigest(abDigest2, abDigest, CryptoPP::SHA256::DIGESTSIZE);

    //add to assetId
    for (size_t i = 0; i < CryptoPP::RIPEMD160::DIGESTSIZE; i++) {
        result[i + startIndex] = abDigest2[i];
    }
}

/**
 * Takes binary data stored in a string and hashes it twice.  First with sha256 then with ripemd160
 */
void DigiAsset::insertSRHash(const std::string& dataToHash, vector<uint8_t>& result, size_t startIndex) {
    auto* hashData = (CryptoPP::byte*) dataToHash.c_str();

    //do sha256
    CryptoPP::byte abDigest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(abDigest, hashData, dataToHash.length());

    //do ripemd160
    CryptoPP::byte abDigest2[CryptoPP::RIPEMD160::DIGESTSIZE];
    CryptoPP::RIPEMD160().CalculateDigest(abDigest2, abDigest, CryptoPP::SHA256::DIGESTSIZE);

    //add to assetId
    for (size_t i = 0; i < CryptoPP::RIPEMD160::DIGESTSIZE; i++) {
        result[i + startIndex] = abDigest2[i];
    }
}

/**
 * Calculates a valid script pub key for all existing locked assets as of block 17000000 but not necessarily valid for all future blocks
 * it does not matter that future blocks may calculate wrong answer as long as everyone uses this formula.
 */
vector<uint8_t> DigiAsset::calcSimpleScriptPubKey(const vin_t& vinData) {
    if (vinData.scriptSig.hex.empty()) {
        //dgb1 address
        //return 0014 + ripmd160(sha256(vinData.txwitness.end()))
        vector<uint8_t> result{0x00, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        Blob lastPart{vinData.txinwitness.back()};
        insertSRHash(lastPart.vector(), result, 2);
        return result;
    }

    //find last value in scriptSig
    BitIO scriptSig = BitIO::makeHexString(vinData.scriptSig.hex);
    size_t parts = 0;
    vector<uint8_t> lastPart;
    while (scriptSig.getNumberOfBitLeft() > 0) {
        if (scriptSig.getBitcoinDataHeader() == -2) {
            parts++;
            lastPart = scriptSig.getBitcoinData();
        }
    }

    if (vinData.txinwitness.empty() && (parts < 3)) {
        //D address
        //return 76a914 + ripmd160(sha256( last value in vinData.scriptSig.hex )) + 88ac
        vector<uint8_t> result{0x76, 0xa9, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x88,
                               0xac};
        insertSRHash(lastPart, result, 3);
        return result;
    }

    //S.. address
    //return a914 + ripmd160(sha256( last value in vinData.scriptSig.hex )) + 87
    vector<uint8_t> result{0xa9, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x87};
    insertSRHash(lastPart, result, 2);
    return result;
}

std::string DigiAsset::calculateAssetId(const vin_t& firstVin, uint8_t issuanceFlags) const {
    vector<uint8_t> assetIdBinary(28);
    //get header
    const uint16_t headerOptions[] = {0x2e37, 0x2e6b, 0x2e4e, 0, 0x20ce, 0x2102, 0x20e4, 0};

    uint16_t header = headerOptions[(issuanceFlags & 0x1c)
            >> 2];   //gets the assetId header based on lock status and aggregation
    assetIdBinary[0] = header >> 8;
    assetIdBinary[1] = header & 0xff;

    //add data hash
    if (_locked) {
        //locked assets use the ascii txid and output number as there hash data
        insertSRHash(firstVin.txid + ":" + to_string(firstVin.n), assetIdBinary, 2);
    } else {
        //unlocked use simplified script pub key
        insertSRHash(calcSimpleScriptPubKey(firstVin), assetIdBinary, 2);
    }

    //add footer
    assetIdBinary[22] = 0;
    assetIdBinary[23] = issuanceFlags >> 5;

    //create check footer(first 4 bytes of double sha256)
    CryptoPP::byte abDigest3[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::byte abDigest4[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(abDigest3, assetIdBinary.data(), 24);
    CryptoPP::SHA256().CalculateDigest(abDigest4, abDigest3, CryptoPP::SHA256::DIGESTSIZE);
    for (size_t i = 0; i < 4; i++) {
        assetIdBinary[24 + i] = abDigest4[i];
    }

    //convert to base 58
    return Base58::encode(assetIdBinary);
}


/*
██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗ ██████╗ ██████╗
██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗
██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝
██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║   ██║██╔══██╗
╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║
 ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
 */


DigiAsset::DigiAsset(const getrawtransaction_t& txData, unsigned int height, unsigned char version,
                     unsigned char opcode, BitIO& opReturnData) {
    if (!processIssuance(txData, height, version, opcode, opReturnData)) throw DigiAsset::exceptionInvalidIssuance();
}


DigiAsset::DigiAsset(uint64_t assetIndex, const string& assetId, const string& cid, const KYC& issuer,
                     const DigiAssetRules& rules,
                     unsigned int heightCreated, unsigned int heightUpdated, bool bad, uint64_t amount) {
    //store variables
    _assetIndex = assetIndex;
    _assetId = assetId;
    _cid = cid;
    _issuer = issuer;
    _rules = rules;
    _heightCreated = heightCreated;
    _heightUpdated = heightUpdated;
    _bad = bad;
    _count = amount;
    _existingAsset = true;
    _enableWrite = false;

    //compute flags
    _locked = (assetId.c_str()[0] == 'L');
    switch (assetId.c_str()[1]) {
        case 'a':
            _aggregation = AGGREGABLE;
            break;
        case 'd':
            _aggregation = DISTINCT;
            break;
        case 'h':
            _aggregation = HYBRID;
            break;
        default:
            throw out_of_range("invalid assetId");
    }
    _divisibility = Base58::decode(assetId)[23];
}


/*
██████╗ ██████╗  ██████╗  ██████╗███████╗███████╗███████╗
██╔══██╗██╔══██╗██╔═══██╗██╔════╝██╔════╝██╔════╝██╔════╝
██████╔╝██████╔╝██║   ██║██║     █████╗  ███████╗███████╗
██╔═══╝ ██╔══██╗██║   ██║██║     ██╔══╝  ╚════██║╚════██║
██║     ██║  ██║╚██████╔╝╚██████╗███████╗███████║███████║
╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝╚══════╝╚══════╝╚══════╝
 */


bool DigiAsset::processIssuance(const getrawtransaction_t& txData, unsigned int height, unsigned char version,
                                unsigned char opcode, BitIO& opReturnData) {

    Database* db = Database::GetInstance();
    _existingAsset = true;
    try {
        //for now assume this is first issuance of asset we will correct later if not
        _heightCreated = height;
        _heightUpdated = height;

        //if version<3 & opcode 1 or 2 skip the sha1 data since it is useless
        if ((version < 3) && (opcode < 3)) opReturnData.movePositionBy(160);

        //get metadata hash if it exists
        BitIO metadataHash;
        if ((opcode == 1) || (opcode == 3) || (opcode == 4)) metadataHash = opReturnData.copyBits(256);
        if (opcode == 2) {
            //meta data hash encoded in
            BitIO multiSigData = BitIO::makeHexString(txData.vout[0].scriptPubKey.hex);
            multiSigData.getBitcoinDataHeader();    //number of signers needed
            multiSigData.getBitcoinData();          //hash of first signers key
            metadataHash = multiSigData.copyBitcoinData();//sha256 of meta data
        }

        //calculate cid
        if (metadataHash.getLength() == 256) {
            metadataHash.movePositionToBeginning();
            _cid = IPFS::sha256ToCID(metadataHash);
        }

        //get amount of assets to create
        _count = opReturnData.getFixedPrecision();

        //get issuance flags
        size_t rulesStart = opReturnData.getPosition();
        if (opReturnData.getLength() - 8 < rulesStart) return false;  //data missing
        opReturnData.movePositionTo(opReturnData.getLength() - 8); //set to 8th last bit
        unsigned char issuanceFlags = opReturnData.getBits(8);
        _divisibility = issuanceFlags >> 5;
        _locked = ((issuanceFlags & 0x10) > 0);
        _aggregation = (issuanceFlags & 0x0c) >> 2;
        if (_aggregation == 3) return false;  //invalid header type
        opReturnData.movePositionTo(rulesStart);         //put pointer back

        //fix amount if version 1
        if (version == 1) {
            _count /= BitIO::pow10(_divisibility);
        }

        //check counts are valid
        if ((_locked) && (_count == 0)) return false;    //not assets possible to create
        if ((_aggregation != AGGREGABLE) && (_count == 0)) return false;    //not assets possible to create
        if (_count > (uint64_t) 18014398509481983) return false; //invalid amount

        //special cases for locked assets
        if (_locked) _rules.lock(); //can't rewrite rules if locked

        //get the rules
        _rules = DigiAssetRules(txData, opReturnData, _cid, opcode);

        //calculate assetId
        _assetId = calculateAssetId(txData.vin[0], issuanceFlags);

        //check if this is update or issuance
        if ((!_locked) && (isAggregable())) { //these types never update
            _heightCreated = db->getAssetHeightCreated(_assetId, height, _assetIndex);
        }

        //if unlocked check for conflicting rules
        handleRulesConflict();

        //lookup KYC state
        string issuer = db->getSendingAddress(txData.vin[0].txid, txData.vin[0].n);
        _issuer = db->getAddressKYC(issuer);
        return true;

    } catch (const out_of_range& e) {
        return false;
    }
}

/**
 * If an asset is unlocked then rules included with the issuance may or may not be ignored in favour of older rules that exist.
 * Criteria to decide what rules should be used.  Do in order and stop when 1 is valid
 * 1) If locked then always use rules encoded with asset
 * 2) If no older rules exist than use the rules encoded with the asset
 * 3) If no new rules included use old rules(there must be old rules to get past step 2)
 * 4) If old rule was rewritable than use the new rule
 * 5) Use the old rules
 */
void DigiAsset::handleRulesConflict() {
    //check if possible to have old rules
    if (_locked) return;    //not possible to have conflicts
    if (_aggregation != AGGREGABLE) return;    //not possible to have conflicts

    //lookup old rules
    Database* db = Database::GetInstance();
    DigiAssetRules oldRules = db->getRules(_assetId);
    if (oldRules.empty()) return; //no old rules exist

    //check if rules should be rewound
    if (!oldRules.isRewritable() || _rules.empty()) {
        //if rules where not rewritable or no rules where set this time use the old rules(to remove rules when creating an asset you need to use rules op code but than not include any rules) if non rules op code is used than this means don't change to save space
        _rules = oldRules;
    }
}

/**
 * Allows checking if 2 assets are the same type
 * @param rhs
 * @return
 */
bool DigiAsset::operator==(const DigiAsset& rhs) const {
    return (_assetIndex == rhs._assetIndex);
}

bool DigiAsset::operator!=(const DigiAsset& rhs) const {
    return (_assetIndex != rhs._assetIndex);
}

void DigiAsset::removeCount(uint64_t count) {
    if (count > _count) throw out_of_range("Can't remove more than have");
    _count -= count;
}

void DigiAsset::setCount(uint64_t count) {
    _count = count;
}

void DigiAsset::addCount(uint64_t count) {
    _count += count;
}

uint64_t DigiAsset::getCount() const {
    return _count;
}

std::string DigiAsset::getStrCount() const {
    string result = to_string(_count);                                       //convert to string
    int neededDecimals = _divisibility + 1 - result.length();
    if (neededDecimals > 0) result.insert(0, neededDecimals, '0');        //pad start so at least 1 zero before decimal
    result.insert(result.length() - _divisibility, 1, '.');                 //add decimal point
    return result;
}

uint8_t DigiAsset::getDecimals() const {
    return _divisibility;
}

/**
 * Calculates the CID based on a sha256
 * returns empty if there is no meta data
 */
std::string DigiAsset::getCID() const {
    return _cid;
}

uint64_t DigiAsset::getAssetIndex() const {
    return _assetIndex;
}

void DigiAsset::setAssetIndex(uint64_t assetIndex) {
    if (_assetIndex != 0) throw exceptionWriteProtected();
    _assetIndex = assetIndex;
}

bool DigiAsset::isHybrid() const {
    return (_aggregation == HYBRID);
}

bool DigiAsset::isAggregable() const {
    return (_aggregation == AGGREGABLE);
}

bool DigiAsset::isDistinct() const {
    return (_aggregation == DISTINCT);
}

bool DigiAsset::isLocked() const {
    return _locked;
}

std::string DigiAsset::getAssetId() const {
    return _assetId;
}

KYC DigiAsset::getIssuer() const {
    return _issuer;
}

DigiAssetRules DigiAsset::getRules() const {
    return _rules;
}

unsigned int DigiAsset::getHeightCreated() const {
    return _heightCreated;
}

unsigned int DigiAsset::getHeightUpdated() const {
    return _heightUpdated;
}

uint64_t DigiAsset::getExpiry() const {
    return _rules.getExpiry();
}

bool DigiAsset::isBad() const {
    return _bad;
}

void DigiAsset::setOwned() {
    if (isLocked()) return;
    _enableWrite = true;
}

void DigiAsset::setRules(const DigiAssetRules& rules) {
    if (!_enableWrite) throw exceptionWriteProtected();                 //need to mark you own the asset
    if (!_rules.isRewritable()) throw exceptionWriteProtected();        //not possible to change
    _rules = rules;
}

void DigiAsset::checkRulesPass(const vector<AssetUTXO>& inputs, const vector<AssetUTXO>& outputs, unsigned int height,
                               uint64_t time) const {
    //if no rules than no need to check if they were followed
    if (_rules.empty()) return;
    Database* db = Database::GetInstance();

    //make list of changes
    map<string, int64_t> changes;

    //subtract any assets we spent
    for (const AssetUTXO& input: inputs) {
        for (const DigiAsset& asset: input.assets) {
            if (asset.getAssetIndex() == _assetIndex) {
                changes[input.address] -= asset.getCount();
            }
        }
    }

    //add any assets we received
    for (const AssetUTXO& output: outputs) {
        for (const DigiAsset& asset: output.assets) {
            if (asset.getAssetIndex() == _assetIndex) {
                changes[output.address] += asset.getCount();
            }
        }
    }

    //rules don't apply if consolidation transaction or pure burn so check if assets actually moved anywhere
    bool consolidation = true;
    for (const auto& change: changes) {//[address,change]
        if (change.second > 0) consolidation = false;
    }
    if (consolidation) return;

    //check signer rules
    if (_rules.getRequiredSignerWeight() > 0) {
        vector<Signer> signers = _rules.getSigners();
        uint64_t totalWeight = 0;
        for (const Signer& signer: signers) {
            bool wasSigned = false;
            for (const AssetUTXO& utxo: inputs) {
                if (signer.address == utxo.address) {
                    wasSigned = true;
                    break;
                }
            }
            if (wasSigned) totalWeight += signer.weight;
        }
        if (totalWeight < _rules.getRequiredSignerWeight()) throw exceptionRuleFailed("Signers");
    }

    //check royalties rule
    if (_rules.getIfRequiresRoyalty()) {
        //get the exchange rate
        uint64_t exchangeRate = floor(db->getAcceptedExchangeRate(_rules.getRoyaltyCurrency(), height));

        //get the number of new recipients(assume 1 is change if more than 1 output)
        size_t count = -1;
        for (const AssetUTXO& utxo: outputs) {
            for (const DigiAsset& asset: utxo.assets) {
                if (asset.getAssetIndex() == _assetIndex) {
                    count++;
                    break;
                }
            }
        }
        if (count < 1) count = 1;

        //check that royalty was paid
        vector<Royalty> royalties = _rules.getRoyalties();
        for (const Royalty& royalty: royalties) {
            uint64_t minAccepted = (count * royalty.amount * exchangeRate / 100000000) -
                                   1;//in case of rounding error minimum accepted is 1 sat lower
            bool paid = false;
            for (const AssetUTXO& utxo: outputs) {
                if ((utxo.address == royalty.address) && (utxo.digibyte >= minAccepted)) {
                    paid = true;
                    break;
                }
            }
            if (!paid) throw exceptionRuleFailed("Royalty");
        }
    }

    //check kyc rules
    if (_rules.getIfGeoFenced()) {
        for (const auto& change: changes) {
            if (change.second <= 0) {
                continue;
            }                                             //didn't receive so don't check
            KYC addressData = db->getAddressKYC(change.first);                   //gets the addresses KYC data
            if (
                    (!addressData.valid(height)) ||
                    (!_rules.getIfCountryAllowedToReceive(addressData.getCountry()))
                    ) {
                throw exceptionRuleFailed("KYC");
            }       //throw if not valid
        }
    }

    //check expiry rules
    if (_rules.getIfExpired(height, time)) throw exceptionRuleFailed("Expiry");

    //check vote rules
    if (_rules.getIfVoteRestricted()) {
        for (const auto& change: changes) {
            if (change.second <= 0) continue;
            if (!_rules.getIfValidVoteAddress(change.first)) throw exceptionRuleFailed("Vote");
        }
    }

    //check deflate rules
    if (_rules.getRequiredBurn() > 0) {
        //count how many assets have been burned
        int64_t burns = 0;
        for (const auto& change: changes) {
            burns -= change.second;//negative so a negative change results in positive numbers
        }
        //negative numbers is not possible at this point
        if ((uint64_t) burns < _rules.getRequiredBurn()) throw exceptionRuleFailed("Deflation");
    }
}


Value DigiAsset::toJSON(bool simplified) const {
    Json::Value result(Json::objectValue);

    // Simplified
    result["assetIndex"] = getAssetIndex();
    result["assetId"] = getAssetId();
    result["cid"] = getCID();
    result["count"] = getCount();
    result["decimals"] = getDecimals();

    if (simplified) return result;

    // Include meta data
    if (!_cid.empty()) {
        try {
            IPFS* ipfs = IPFS::GetInstance();
            string metadata = ipfs->callOnDownloadSync(_cid, "", DIGIASSET_JSON_IPFS_MAX_WAIT);
            Json::Value metadataValue;
            Json::Reader reader;
            bool parsingSuccessful = reader.parse(metadata, metadataValue);
            if (!parsingSuccessful) {
                result["ipfs"] = "Metadata is corrupt";
            } else {
                result["ipfs"] = metadataValue;
            }
        } catch (const IPFS::exception& e) {
            result["ipfs"] = "Metadata could not be found";
        }
    }

    // Rules
    DigiAssetRules rules = getRules();
    if (!rules.empty()) {
        result["rules"] = rules.toJSON();
    }

    // Issuer
    Json::Value kycObj(Json::objectValue);
    kycObj["address"] = _issuer.getAddress();
    if (_issuer.valid()) {
        kycObj["country"] = _issuer.getCountry();
        string name = _issuer.getName();
        if (!name.empty()) {
            kycObj["name"] = name;
        } else {
            string hash = _issuer.getHash();
            kycObj["hash"] = hash;
        }
    }
    result["issuer"] = kycObj;

    return result;
}