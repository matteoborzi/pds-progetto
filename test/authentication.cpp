//
// Created by Angelica on 08/08/2020.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <boost/test/unit_test.hpp>
#include "../server/authentication/authentication.h"
#include <thread>
#include <iostream>

BOOST_AUTO_TEST_SUITE( test_suite_authentication);


BOOST_AUTO_TEST_CASE(test_authentication_1){
    bool res = authenticate("pippo", "password");
    BOOST_CHECK(res == true);
}

    BOOST_AUTO_TEST_CASE(test_authentication_2){
        bool res = authenticate("pippo", "password1");
        BOOST_CHECK(res == false);
    }


BOOST_AUTO_TEST_SUITE_END();