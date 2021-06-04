#pragma once
#include <iostream>
#include <stdlib.h>

namespace NVector {

    template<class T>
    class TVector {

    private:
        size_t bufferSize;
        size_t bufferUsed;
        T* buffer;

    public:
        //Default constructor
        TVector(): bufferSize(0), bufferUsed(0), buffer(nullptr) {};

        //Constructor with known size
        TVector(size_t size) :TVector()
        {
            if (size < 0) {
                throw "Error: vector size is less then zero";
            }
            buffer = new T[size];
            bufferUsed = size;
            bufferSize = size;
        }

        //Constructor with initial value
        TVector(size_t size, const T& initial) : TVector() {
            if (size < 0) {
                throw "Error: vector size is less then zero";
            }

            bufferSize = size;
            bufferUsed = size;
            buffer = new T[size];

            for (size_t i = 0; i < size; ++i) {
                buffer[i] = initial;
            }
        }
        //Constructor based on another vector
        TVector(const TVector<T>& vector) : bufferSize(vector.capacity()), bufferUsed(vector.size()), buffer(new T[vector.size()]) {
            for (size_t i = 0; i < vector.size(); ++i) {
                buffer[i] = vector[i];
            }
        }
        //Destructor
        ~TVector() {
            delete[] buffer;

            bufferSize = 0;
            bufferUsed = 0;
            buffer = nullptr;
        }

        //Getters for end and begin
        T* Begin() {
            return buffer;
        }
        T* End() {
            if (buffer) {
                return buffer + bufferUsed;
            }
            return nullptr;
        }
        //Expected capacity
        size_t capacity() const {
            return bufferSize;
        }
        //Real size
        size_t size() const {
            return bufferUsed;
        }

        bool is_empty() const {
            return (bufferUsed == 0);
        }

        //Returns value of the last element and delete it from vector
        T pop_back() {
            if (bufferUsed == 1) {
                T to_return = buffer[0];
                delete[] buffer;
                buffer = nullptr;
                bufferSize = 0;
                bufferUsed = 0;
                return to_return;
            }
            else if (bufferUsed > 1) {
                T to_return = buffer[bufferUsed - 1];
                const size_t capacityMultiplier = 2;
                --bufferUsed;
                if (bufferUsed * 2 < bufferSize) {
                    bufferSize /= capacityMultiplier;
                    T* newBuffer = new T[bufferSize];
                    for (int i = 0; i < bufferUsed; ++i) {
                        newBuffer[i] = buffer[i];
                    }
                    delete[] buffer;
                    buffer = newBuffer;
                }
                return to_return;
            }
        }

        //Copy the vector
        void copy(TVector<T>& vector) {
            if (bufferUsed != vector.size()) {
                delete[] buffer;
                bufferUsed = vector.size();
                buffer = new T[bufferUsed];
            }
            bufferSize = vector.capacity();
            if (buffer) {
                for (size_t i = 0; i < bufferUsed; ++i) {
                    buffer[i] = vector[i];
                }
            }
        }
        //Add element to the end
        void push_back(const T& value) {
            if (bufferUsed < bufferSize) {
                buffer[bufferUsed] = value;
                ++bufferUsed;
                return;
            }

            const size_t Multiplier = 2;
            size_t newCapacity = 1;
            if (bufferSize != 0) {
                newCapacity = bufferSize * Multiplier;
            }

            T* newBuffer = new T[newCapacity];
            if (buffer) {
                for (size_t i = 0; i < bufferUsed; ++i) {
                    newBuffer[i] = buffer[i];
                }
                delete[] buffer;
            }

            buffer = newBuffer;
            bufferSize = newCapacity;
            ++bufferUsed;
            buffer[bufferUsed - 1] = value;
        }
        //Operator overload for getting value of exat element
        T& operator[](size_t idx) {
            if (idx > bufferUsed || idx < 0) {
                throw "Error: index out of bounds";
            }
            return buffer[idx];
        }
        T operator[](size_t idx) const {
            if (idx > bufferUsed || idx < 0) {
                throw "Error: index out of bounds";
            }
            return buffer[idx];
        }
        
    }; //Class TVector 

} // namespace NVector
