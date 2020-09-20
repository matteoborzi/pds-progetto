#include <stdexcept>
#include "file_utils.h"

std::string concatenatePath(const std::string& base,const std::string& relative){
    std::string abs;

    if(base=="/")
        return relative;
    if(base.compare(base.size()-1,1,"/") == 0 )
        throw std::runtime_error("Base path should not end with /. Check Configuration implementation");
    //TODO implement for base path containing \

    return base+relative;
}