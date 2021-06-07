#ifndef ASSIGNMENT4_TOMBSTONES_H
#define ASSIGNMENT4_TOMBSTONES_H

#include <iostream>
#include <cassert>

template<class T>
class Pointer {
private:
    int *refCount;
    T *ptr;

    void releaseCount() {
        if (ptr != nullptr) {
            --(*refCount);
            if ((*refCount) == 0) {
                delete ptr;
                ptr = nullptr;
                delete refCount;
                refCount = nullptr;
            }
        }
    }

public:
    Pointer<T>() {// default constructor
        ptr = new T;
        refCount = new int;
        *refCount = 1;
    }

    Pointer<T>(Pointer<T> &pointer) {// copy constructor
        if (*this != pointer) {
            ptr = pointer.ptr;
            refCount = pointer.refCount;
            if (ptr != nullptr) {
                ++(*refCount);
            }
        }
    }

    explicit Pointer<T>(T *_ptr) { // bootstrapping constructor
        ptr = _ptr;
        refCount = new int;
        if (ptr != nullptr) {
            *refCount = 1;
        } else {
            *refCount = 0;
        }

    }

// argument should always be a call to new
    ~Pointer<T>() {// destructor
        if (refCount != nullptr) {
            --(*refCount);
            if (*refCount == 0) {
                if (ptr != nullptr) {
                    delete ptr;
                    ptr = nullptr;
                }
                delete refCount;
                refCount = nullptr;
            }
        }
    }


    T &operator*() const {// dereferencing
        if (ptr != nullptr) {
            return *ptr;
        } else {
            std::cout << "Dangling pointer dereferenced!\nExit!\n";
            exit(0);
        }
    }

    T *operator->() const {// field dereferencing
        if (ptr != nullptr) {
            return ptr;
        } else {
            std::cout << "Dangling pointer dereferenced!\nExit!\n";
            exit(0);
        }
    }

    Pointer<T> &operator=(const Pointer<T> &pointer) {// assignment
        if (ptr == pointer.ptr) {
            return *this;
        }
        releaseCount();
        ptr = pointer.ptr;
        refCount = pointer.refCount;
        if (ptr != nullptr) {
            ++(*refCount);
        }
        return *this;
    }

    Pointer<T> &operator=(T *_ptr) {// assignment
        if (ptr == _ptr) {
            return *this;
        }
        releaseCount();
        ptr = _ptr;
        refCount = new int;
        if (ptr != nullptr) {
            *(refCount) = 1;
        } else {
            *(refCount) = 0;
        }
        return *this;
    }

    friend void free(Pointer<T> &pointer) {// delete pointed-at object
        if (pointer.refCount !=nullptr) {
            --(*pointer.refCount);
            if (*pointer.refCount == 0) {
                if (pointer.ptr != nullptr) {
                    delete pointer.ptr;
                    pointer.ptr = nullptr;
                }
                delete pointer.refCount;
                pointer.refCount = nullptr;
            }
        }
    }

// This is essentially the inverse of the new inside the call to
// the bootstrapping constructor. It should delete the pointed-to
// object (which should in turn call its destructor).
// equality comparisons:
    bool operator==(const Pointer<T> &pointer) const {
        return ptr == pointer.ptr;
    }

    bool operator!=(const Pointer<T> &pointer) const {
        return ptr != pointer.ptr;
    }

    bool operator==(const int n) const {
        return ptr == nullptr && n == 0;
    }

// true iff Pointer is null and int is zero
    bool operator!=(const int n) const {
        return !(ptr == nullptr && n == 0);
    }
// false iff Pointer is null and int is zero
};


#endif 
