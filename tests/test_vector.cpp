// provides main(); this line is required in only one .cpp file
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "types/vector.h"

#include <iostream>


TEST_CASE("Testing Vector3 implementation"){
    Vector3 a = Vector3(1.0f, 6.0f, -8.0f);
    Vector3 b = Vector3(4.0f, -2.0f, -1.0f);

    auto r = a.Cross(b);
    std::cout << "(" << r.x << ", " << r.y << ", " << r.z << ")" << std::endl;

    CHECK(r ==Vector3(-22.0f, -31.0f, -26.0f));
}