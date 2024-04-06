///This file is automatically generated by CMakeLists.txt do not edit

#include "RPC/MethodList.h"

namespace RPC {
    std::map<std::string, std::function<Response(const Json::Value&)>> methods = {
        {"addressstats", Methods::addressstats},
        {"algostats", Methods::algostats},
        {"createoldstreamkey", Methods::createoldstreamkey},
        {"debugwaittimes", Methods::debugwaittimes},
        {"getaddressholdings", Methods::getaddressholdings},
        {"getaddresskyc", Methods::getaddresskyc},
        {"getassetdata", Methods::getassetdata},
        {"getassetholders", Methods::getassetholders},
        {"getassetindexes", Methods::getassetindexes},
        {"getdgbequivalent", Methods::getdgbequivalent},
        {"getdomainaddress", Methods::getdomainaddress},
        {"getexchangerates", Methods::getexchangerates},
        {"getipfscount", Methods::getipfscount},
        {"getoldstreamkey", Methods::getoldstreamkey},
        {"getpsp", Methods::getpsp},
        {"getrawtransaction", Methods::getrawtransaction},
        {"listaddresshistory", Methods::listaddresshistory},
        {"listassetissuances", Methods::listassetissuances},
        {"listassets", Methods::listassets},
        {"listunspent", Methods::listunspent},
        {"resyncmetadata", Methods::resyncmetadata},
        {"send", Methods::send},
        {"sendmany", Methods::sendmany},
        {"sendtoaddress", Methods::sendtoaddress},
        {"shutdown", Methods::shutdown},
        {"syncstate", Methods::syncstate},
        {"version", Methods::version},
    };
}