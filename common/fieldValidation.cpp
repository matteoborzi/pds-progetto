#include <boost/locale/encoding_errors.hpp>
#include <boost/locale.hpp>
#include "fieldValidation.h"

bool validateFieldFormat(const std::string & field) {
    try{
        boost::locale::conv::to_utf<char>(field, "UTF-8", boost::locale::conv::stop);
    }catch(...){
        return false;
    }
    return true;
}
