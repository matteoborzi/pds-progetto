//
// Created by Angelica on 27/07/2020.
//

#include "time_utils.h"

template <typename TP>
/**
 * Template function to convert a generic time to time_t
 * @tparam TP the format of the time passed as parameter
 * @param tp the time to convert
 * @return time as time_T
 */
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

/**
 * computes last edit time of a directory_entry
 * @param entry
 * @return laste edit time
 */
std::time_t last_edit_time(std::filesystem::directory_entry& entry){
    const std::chrono::time_point last = std::filesystem::last_write_time(entry);
    std::time_t last_time = to_time_t(last);
    return last_time;
}