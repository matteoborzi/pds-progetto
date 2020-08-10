//
// Created by Angelica on 07/08/2020.
//


#include <boost/test/unit_test.hpp>
#include "../client/job/Job.h"

BOOST_AUTO_TEST_SUITE( test_suite_job )

BOOST_AUTO_TEST_CASE( test_job_1 ){
    Job job{"/root/folder1", ADD_FILE, true};


    BOOST_CHECK_EQUAL(job.getAct(), ADD_FILE);
    BOOST_CHECK_EQUAL(job.getPath(), "/root/folder1");
    BOOST_CHECK_EQUAL(job.getIsFile(), true);
}

BOOST_AUTO_TEST_CASE( test_job_2 ){
    Job job{"/root/folder1", ADD_DIRECTORY, false};
    BOOST_CHECK_EQUAL(job.getAct(), ADD_DIRECTORY);
    job.setAct(UPDATE);
    BOOST_CHECK_EQUAL(job.getAct(), UPDATE);
}

BOOST_AUTO_TEST_CASE(test_job_3){
        Job job{"/root/folder1", ADD_FILE, true};
        Job job2{"/root/folder1", ADD_DIRECTORY, false};
        BOOST_CHECK(job != job2);

        Job job3{"/root/folder1", ADD_FILE, true};
        BOOST_CHECK(job == job3);
}

BOOST_AUTO_TEST_CASE(test_job_4){
    BOOST_CHECK_THROW(
        Job job("/root/folder1", ADD_FILE, false), std::logic_error);
}

BOOST_AUTO_TEST_CASE(test_job_5){
        BOOST_CHECK_THROW(
                Job job("/root/folder1", ADD_DIRECTORY, true), std::logic_error);
}

BOOST_AUTO_TEST_CASE(test_job_6){
        Job job("/root/folder1", ADD_DIRECTORY, false);
        BOOST_CHECK_THROW(
                job.setAct(ADD_FILE), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
