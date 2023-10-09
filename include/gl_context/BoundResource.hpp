#pragma once

#include <stdexcept>

template<typename T>
struct BoundResource {
    static bool bound;
    BoundResource() {
        if(bound) {
            throw std::logic_error("Another resource of this type is currently bound");
        }
        bound = true;
    }
    ~BoundResource() {
        bound = false;
    }

    BoundResource(const BoundResource&) = delete;
    BoundResource(BoundResource&&) = delete;
    BoundResource& operator=(const BoundResource&) = delete;
    BoundResource& operator=(BoundResource&&) = delete;
};
