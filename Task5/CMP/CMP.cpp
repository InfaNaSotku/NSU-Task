#include"CMP.h"

void calc_prefix_function(vector<size_t>& prefix_func, const string& str) 
{
    const size_t str_length = str.size();

    prefix_func.clear();
    prefix_func.resize(str_length);
    if (0 == str_length)
    return;

    prefix_func[0] = 0;

    for (size_t current = 1; current < str_length; ++current)
    {
        size_t matched_prefix = current - 1;
        size_t candidate = prefix_func[matched_prefix];
        while (candidate != 0 && str[current] != str[candidate])
        {
            matched_prefix = prefix_func[matched_prefix] - 1;
            candidate = prefix_func[matched_prefix];
        }

        if (candidate == 0)
            prefix_func[current] = str[current] == str[0] ? 1 : 0;
        else
            prefix_func[current] = candidate + 1;
    }
}