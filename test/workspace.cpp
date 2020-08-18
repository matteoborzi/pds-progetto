#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <boost/test/unit_test.hpp>
#include <filesystem>
#include "utils/filesystem.h"
#include "../server/Workspace/workspace_utils.h"


BOOST_AUTO_TEST_SUITE(test_suite_workspace)

    BOOST_AUTO_TEST_CASE(test_workspace_1) {
        deleteFolder("pippo");
        createFolderIfNotExist("pippo");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), "1");
    }

    BOOST_AUTO_TEST_CASE(test_workspace_2) {
        deleteFolder("pippo");
        createFolderIfNotExist("pippo");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), "1");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), "1");
    }

    BOOST_AUTO_TEST_CASE(test_workspace_3) {
        deleteFolder("pippo");
        createFolderIfNotExist("pippo");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), "1");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\other user"), "2");
    }

    BOOST_AUTO_TEST_CASE(test_workspace_4) {

        deleteFolder("pippo");
        createFolderIfNotExist("pippo");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), "1");

        BOOST_CHECK_EQUAL(computeServerPath("pippo", "newPC", "C:\\users\\roberto"), "1");
    }

    BOOST_AUTO_TEST_CASE(test_workspace_5) {
        BOOST_CHECK_THROW(computeServerPath("NOT_EXISTING_USER", "pc", "C:\\"), std::exception);
    }

    BOOST_AUTO_TEST_CASE(test_workspace_6){
        deleteFolder("./pippo/MyPC/1");

        BOOST_CHECK_THROW(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), std::exception);
    }

    BOOST_AUTO_TEST_CASE(test_workspace_7){
        std::filesystem::remove("./pippo/MyPC/mapping.txt");

        BOOST_CHECK_THROW(computeServerPath("pippo", "MyPC", "C:\\users\\roberto"), std::exception);
    }

BOOST_AUTO_TEST_SUITE_END()

