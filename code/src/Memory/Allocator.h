#pragma once

#include "Core/Base.h"
#include "Core/Types.h"

namespace SbEngine{
    class PMath{
    public:
        static u8 AlignForwardAdjustment(void* pAddress, u8 alignment);
        static u8 AlignForwardAdjustmentHeader(void* pAddress, u8 alignment, size_t headerSize);
        static void* Subtract(void* pAddress, size_t value);
        static void* Add(void* pAddress, size_t value);
    };
}

namespace SbEngine{
    struct Block {
        size_t size;
        Block* pNextBlock;
    };
    struct AllocHeader {

        size_t size;
        u8 adjustment;
    };
}

namespace SbEngine{
    class Allocator {
    public:
        Allocator(size_t size);
        virtual ~Allocator();

        virtual void* Allocate(size_t size, u8 alignment) = 0;
        virtual void Free(void* p) = 0;
        virtual void* Reallocate(void* p, size_t newSize) = 0;

        void* GetStart() const {return _pStart;}
        size_t GetSize() const {return _totalSize;}
        size_t GetUsedMemory() const {return _usedMemory;}

    protected:
        void* _pStart;
        size_t _totalSize;
        size_t _usedMemory;
    };

    class FreelistAllocator : public Allocator {
    public:
        FreelistAllocator(size_t size);

        void* Allocate(size_t size, u8 alignment) override;
        void Free(void* pBlockPointer) override;
        void* Reallocate(void* pBlockPointer, size_t newSize) override;
    private:
        Block* _pFreeBlocks;
    };

    class PoolAllocator : public Allocator {
    public:
        PoolAllocator(size_t size, size_t blockSize);

        void* Allocate(size_t size, u8 alignment) override;
        void Free(void* p) override;
        void* Reallocate(void* p, size_t newSize) override;
    private:
        size_t _blockSize;
        Block* _pBlocks;
    };

    class StackAllocator : public Allocator {
    public:
        void* Allocate(size_t size, u8 alignment) override;
        void Free(void* p) override;
        void* Reallocate(void* p, size_t newSize) override;
    private:
    };

    /////////////////////////////////////////////////////////////////////////////

    // TODO: delete these size tests

    class TestClass{
        public: long oi;
    };
    class TestClass2{
    public: 
        int a;
        int b;
        int c;
    };
    class TestClass3{

    public: 
        long a;
        int b;
        SbEngine::u8 c;
        SbEngine::String d;
    };
}

