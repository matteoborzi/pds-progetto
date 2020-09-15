#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <boost/test/unit_test.hpp>
#include "../common/Checksum.h"
#include <fstream>


BOOST_AUTO_TEST_SUITE( test_suite_checksum);


    BOOST_AUTO_TEST_CASE(test_checksum_1){
       std::ofstream file{"test_file.txt"};

       file<<"Sample content of a file"<<std::endl;
       file.close();

       std::string res{"A5E1E5973B1CB78B8398A4C334618ED9"};

       BOOST_CHECK_EQUAL(computeChecksum("test_file.txt"), res);

    }

    BOOST_AUTO_TEST_CASE(test_checksum_2){
        BOOST_CHECK_THROW(computeChecksum("NOT_EXISTING_FILE"), std::exception);

    }

    BOOST_AUTO_TEST_CASE(test_checksum_3){
        std::ofstream file{"test_file.txt", std::ios::trunc};


        file.close();

        std::string res{"D41D8CD98F00B204E9800998ECF8427E"};

        BOOST_CHECK_EQUAL(computeChecksum("test_file.txt"), res);

    }


BOOST_AUTO_TEST_SUITE_END();