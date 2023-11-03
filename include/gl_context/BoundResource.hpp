#pragma once

#include <stdexcept>


// Limitation: this implementation only allows for single thread, one bind per all gl contexts.
// fix me!b
template<typename T>
struct BoundResource {
    static int bound;

    BoundResource() {
        if(bound > 0) {
            throw std::logic_error("Another resource of this type is currently bound");
        }
        ++bound;
    }
    ~BoundResource() { --bound; }

    BoundResource(const BoundResource&) = delete;
    BoundResource(BoundResource&&) { ++bound; }
    BoundResource& operator=(const BoundResource&) = delete;
    BoundResource& operator=(BoundResource&&) { ++bound; }

    operator bool() { return true; }
};
