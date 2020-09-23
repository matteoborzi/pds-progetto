#include <stdexcept>
#include "file_util.h"

std::string concatenatePath(const std::string& base,const std::string& relative){
    std::string abs;

    if(base=="/")
        return relative;
    if(base[base.size()-1] == '/' )
        throw std::runtime_error("Base path should not end with /. Check Configuration implementation");
    //TODO implement for base path containing \

    return base+relative;
}