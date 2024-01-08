#include <cstdio>
#include <string>
#include <vector>

struct lesson{
    std::string name;
    float start;
    float end;
};

lesson opt_time(std::vector<lesson> scheldue){
    float min = 24;
    lesson res;
    for (auto& c: scheldue) {
        if (c.end< min){
            min = c.end;
            res = c;
        }
    }
    return res;
}

bool is_exists(std::vector<lesson> res, lesson t) {
    for (auto& c: res)
        if (c.name == t.name) return true;
    return false;
}

int main () {
    std::vector<lesson> scheldue{
        {"art", 9, 10},
        {"eng", 4.30, 10.30},
        {"math", 10, 11},
        {"cs", 10.30, 11.30},
        {"music", 11, 12}};

    lesson opt = opt_time(scheldue);
    std::vector<lesson> res;
    res.push_back(opt);
    for (auto& c: scheldue){
        if (!is_exists(res, c)) {
            if (c.start >= opt.end){
                opt = c;
                res.push_back(opt);
            }
        }
    }

    for (auto& r: res)
        printf("%s: %0.2f:%0.2f\n", r.name.c_str(), r.start, r.end);
    

    return 0;
}
