//
// Created by mctrivia on 31/03/24.
//

#include "AppMain.h"
#include "utils.h"
#include "BitcoinRpcServerMethods.h"
#include "gtest/gtest.h"
#include "../tests/RPCMethods.h"

using namespace std;


TEST_F(RPCMethodsTest, getassetholders) {
    ///rpc method we will be testing(if using as reference make sure you change value above and bellow this line)
    const std::string METHOD="getassetholders";
    bool result;

    //test invalid parameters throws an exception of type DigiByteException
    //0 parameters
    try {
        Json::Value params=Json::arrayValue;
        rpcMethods[METHOD](params);
        result=false;
    } catch (const DigiByteException& e) {
        result=true;
    } catch (...) {
        result=false;
    }
    EXPECT_TRUE(result);

    //test invalid parameters throws an exception of type DigiByteException
    //2 parameters
    try {
        Json::Value params=Json::arrayValue;
        params.append("bad1");
        params.append("bad2");
        rpcMethods[METHOD](params);
        result=false;
    } catch (const DigiByteException& e) {
        result=true;
    } catch (...) {
        result=false;
    }
    EXPECT_TRUE(result);

    //test invalid parameters throws an exception of type DigiByteException
    //1 parameter but wrong type
    try {
        Json::Value params=Json::arrayValue;
        params.append("La");
        rpcMethods[METHOD](params);
        result=false;
    } catch (const DigiByteException& e) {
        result=true;
    } catch (...) {
        result=false;
    }
    EXPECT_TRUE(result);

    //test asset that doesn't exist that hasn't been used
    try {
        Json::Value params=Json::arrayValue;
        params.append(50000);
        auto results=rpcMethods[METHOD](params);
        EXPECT_TRUE(results.isObject());
        EXPECT_TRUE(results.empty());
    } catch (...) {
        EXPECT_TRUE(false);
    }

    //test known good asset
    try {
        Json::Value params=Json::arrayValue;
        params.append(245);
        auto results=rpcMethods[METHOD](params);
        EXPECT_TRUE(results.isObject());
        EXPECT_EQ(results.size(),121);
        EXPECT_EQ(results["D5QATG7Avxk5awXBsiY4NouT4xvevNehGo"].asUInt64(),100);
        EXPECT_EQ(results["D614qmHiiVhRvZo5wwEDYW6QCRa2xEai4v"].asUInt64(),100);
        EXPECT_EQ(results["D6Do6rpN71ZvcM7AC7AcHBkRGwVGPfoVDm"].asUInt64(),100);
        EXPECT_EQ(results["D6KEibhniB61ngneh4VnhEsrNzDVZCGxZh"].asUInt64(),200);
        EXPECT_EQ(results["D6KeUxivhAo7jqGmJstC5mF2TtpxFJC3k9"].asUInt64(),50);
        EXPECT_EQ(results["D6Z6B775Fe7Lj8ngNBwUb4HMUD2DEa3qfb"].asUInt64(),5);
        EXPECT_EQ(results["D6iJTtPJ9hcovhGXHSQJ6RcAuhXhUBSLQN"].asUInt64(),1);
        EXPECT_EQ(results["D724Wc6ahsyQ53T2vHGJ8s7xUoeBBUwJ7b"].asUInt64(),17490005);
        EXPECT_EQ(results["dgb1qnttjkj90aef87a8p3drsh6lm90afvz98dcs5gh"].asUInt64(),99);
        EXPECT_EQ(results["dgb1qz0dvsvrp36fy6nm9gllkezemzxgncw5qy3j0c9"].asUInt64(),33);
    } catch (...) {
        EXPECT_TRUE(false);
    }
}