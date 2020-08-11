#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Angelica on 07/08/2020.
//

#include <boost/test/unit_test.hpp>
#include "../client/job/Job.h"
#include "../client/job/JobQueue.h"
#include <thread>
#include <iostream>

struct fixture{
    fixture():jq(){};
    ~fixture()=default;
    JobQueue jq;
};

BOOST_FIXTURE_TEST_SUITE(test_suite_jobqueue, fixture)

BOOST_AUTO_TEST_CASE( test_jobqueue_1, * boost::unit_test::timeout(5) ) {
    Job job{"/root/folder1", ADD_DIRECTORY, false};
    std::thread t([&job](JobQueue &jq)->void {
        sleep(1);
        jq.add(job);
    }, std::ref(jq));
    Job j = jq.getLastAndSetSent();
    t.join();
    BOOST_CHECK(j == job);
}

    BOOST_AUTO_TEST_CASE( test_jobqueue_2, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", ADD_FILE, true};
        Job job2{"/root/folder1", ADD_DIRECTORY, false};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job job3{"/root/folder1", ADD_DIRECTORY, false};
        BOOST_CHECK_THROW(jq.add(job3), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_3, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", DELETE, true};
        Job job2{"/root/folder1", ADD_DIRECTORY, false};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_4, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", CANCELLED, true};
        Job job2{"/root/folder1", ADD_DIRECTORY, false};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_5, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", DELETE, true};
        Job job2{"/root/folder1", UPDATE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_THROW(jq.add(job2), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_6, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", UPDATE, true};
        Job job2{"/root/folder1", ADD_FILE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_THROW(jq.add(job2), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_7, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", UPDATE, true};
        Job job2{"/root/folder1", UPDATE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK(j.getAct() == UPDATE );
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_8, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", ADD_FILE, true};
        Job job2{"/root/folder1", DELETE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job job3{"/root/folder1", ADD_DIRECTORY, false};
        std::thread t([&job3](JobQueue &jq)->void {
            jq.add(job3);
        }, std::ref(jq));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK_EQUAL(j.getAct(), ADD_DIRECTORY );
        t.join();
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_9, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", CANCELLED, true};
        Job job2{"/root/folder1", UPDATE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK(j.getAct() == UPDATE );
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_10, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", ADD_FILE, true};
        Job job2{"/root/folder1", UPDATE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK(j.getAct() == ADD_FILE );
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_11, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", DELETE, true};
        Job job2{"/root/folder1", ADD_FILE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        BOOST_CHECK_NO_THROW(jq.add(job2));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK(j.getAct() == UPDATE );
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_12, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", ADD_FILE, true};
        BOOST_CHECK_NO_THROW(jq.add(job));
        Job j = jq.getLastAndSetSent();
        std::string path = "/root/folder2";
        BOOST_CHECK_THROW(jq.setConcluded(path), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE( test_jobqueue_13, * boost::unit_test::timeout(5) ) {
        Job job{"/root/folder1", ADD_FILE, true};
        std::atomic<int> flag = 0;
        BOOST_CHECK_NO_THROW(jq.add(job));
        Job j = jq.getLastAndSetSent();
        BOOST_CHECK(j == job);
        Job job3{"/root/folder1", ADD_DIRECTORY, false};
        std::thread t([&job3, &flag](JobQueue &jq)->void {
            while(!flag);
            jq.add(job3);
        }, std::ref(jq));
        std::string path = "/root/folder1";
        BOOST_CHECK_NO_THROW(jq.setConcluded(path));
        flag = 1;
        j = jq.getLastAndSetSent();
        BOOST_CHECK(j == job3);
        t.join();
    }


BOOST_AUTO_TEST_SUITE_END()
