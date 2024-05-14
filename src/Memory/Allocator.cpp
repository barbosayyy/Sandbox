#include "Allocator.h"

#include <cassert>
#include "../Core/Debug.h"

using namespace Sandbox;

Allocator::Allocator(size_t size){
    _pStart = new byte[size];
    _totalSize = size;
    _usedMemory = 0;
}

Allocator::~Allocator(){
    assert(_usedMemory == 0);
    _pStart = nullptr;
    _totalSize = 0;
}

FreelistAllocator::FreelistAllocator(size_t size) : Allocator(size), _pFreeBlocks((Block*)_pStart){
    assert(size >= sizeof(Block));
    _pFreeBlocks->size = size;
    _pFreeBlocks->pNextBlock = nullptr;
}

// Creates one big block, big block will be divided into smaller blocks as the allocator is used.
// Empty blocks with adjacent empty blocks should be merged to create larger empty blocks.
// Should be defragmented periodically.

void* FreelistAllocator::Allocate(size_t size, u8 alignment){
    Block* pPreviousBlock {nullptr};
    Block* pBlock = _pFreeBlocks;

    u8 adjustment = PMath::AlignForwardAdjustmentHeader(pBlock, alignment, sizeof(AllocHeader));
    size_t totalBlockSize = size + adjustment;

    // This needs improvement

    while(pBlock != nullptr){
        // Check for large enough block
        if(pBlock->size < totalBlockSize){
            pPreviousBlock = pBlock;
            pBlock = pBlock->pNextBlock;
            continue;
        }
        static_assert(sizeof(AllocHeader) >= sizeof(Block), "Allocation Header must be at least as large as the size of the free block");

        // Check if allocation is possible
        if(pBlock->size - totalBlockSize <= sizeof(AllocHeader)){
            totalBlockSize = pBlock->size;
            if(pPreviousBlock != nullptr){
                pPreviousBlock->pNextBlock = pBlock->pNextBlock;
            }
            else{
                pBlock = pBlock->pNextBlock;
            }
        }
        // New block with remaining size
        else{
            Block* pNewBlock = (Block*)(reinterpret_cast<uintptr_t>(pBlock) + reinterpret_cast<uintptr_t>(totalBlockSize));
            pNewBlock->size = pBlock->size - totalBlockSize;
            pNewBlock->pNextBlock = pBlock->pNextBlock;
            if(pPreviousBlock != nullptr && pPreviousBlock->pNextBlock != nullptr)
                pPreviousBlock->pNextBlock = pNewBlock;
            else
                _pFreeBlocks = pNewBlock;
        }
        
        uintptr_t pAllocBlockAddress = (uintptr_t)pBlock + adjustment;
        AllocHeader* pHeader = (AllocHeader*)(pAllocBlockAddress - sizeof(AllocHeader));
        pHeader->size = totalBlockSize;
        pHeader->adjustment = adjustment;
        _usedMemory += totalBlockSize;

        return (void*)pAllocBlockAddress;
    }
    Logger::Trace(LogLevel::ERROR, "Memory Allocator: Failed to get Object pointer");

    return nullptr;
}

void FreelistAllocator::Free(void* pBlockPointer){
    assert(pBlockPointer != nullptr);
    AllocHeader* pHeader = (AllocHeader*)PMath::Subtract(pBlockPointer, sizeof(AllocHeader));
    void* pFullBlockStart = PMath::Subtract(pBlockPointer, pHeader->adjustment);
    size_t totalBlockSize = pHeader->size;
    void* pFullBlockEnd = PMath::Add(pFullBlockStart, totalBlockSize);
    Block* pPreviousFreeBlock {nullptr};
    Block* pFreeBlocks {_pFreeBlocks};
    
    // Find next free block with enough size
    while(pFreeBlocks != nullptr) {
        if( (uintPointer)pFreeBlocks >= (uintPointer)pFullBlockEnd ) 
            break; 
        pPreviousFreeBlock = pFreeBlocks; 
        pFreeBlocks = pFreeBlocks->pNextBlock;
    }

    if(pPreviousFreeBlock == nullptr){
        pPreviousFreeBlock = (Block*)pFullBlockStart;
        pPreviousFreeBlock->size = totalBlockSize;
        pPreviousFreeBlock->pNextBlock = pFreeBlocks;
        pFreeBlocks = pPreviousFreeBlock;
    }   
    else if((uintPointer)pPreviousFreeBlock + pPreviousFreeBlock->size == (uintPointer)pFullBlockStart){
        pPreviousFreeBlock->size = totalBlockSize;
    }
    else{
        Block* temp = (Block*)pFullBlockStart;
        temp->size = totalBlockSize;
        temp->pNextBlock = pPreviousFreeBlock->pNextBlock;
        pPreviousFreeBlock->pNextBlock = temp;
        pPreviousFreeBlock = temp;
    }

    if(pFreeBlocks != nullptr && (uintPointer)pFreeBlocks == (uintPointer)pFullBlockEnd){
        pPreviousFreeBlock->size += pFreeBlocks->size;
        pPreviousFreeBlock->pNextBlock = pFreeBlocks->pNextBlock;
    }

    _usedMemory -= totalBlockSize;
}

/*
* WIP
*/
void* FreelistAllocator::Reallocate(void* p, size_t newSize){
    return p;
}

// TODO: relocate

// Returns adjustment required to align address to next power 2 alignment boundary - Object address alignment should be equal to its largest data type
uint8_t PMath::AlignForwardAdjustment(void* pAddress, uint8_t alignment){
    uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(pAddress) & static_cast<uintptr_t>(alignment-1));

    if(adjustment == 0)
        return 0;

    return adjustment;
}

// Align address with given alignment and introduces a header before the address for metadata 
uint8_t PMath::AlignForwardAdjustmentHeader(void* pAddress, uint8_t alignment, size_t headerSize){
    uint8_t adjustment = PMath::AlignForwardAdjustment(pAddress, alignment);
    uint8_t requiredSize = headerSize;

    if(adjustment < requiredSize){
        requiredSize -= adjustment;
        adjustment += alignment * (requiredSize/alignment);

        if(requiredSize % alignment > 0)
            adjustment += alignment;
    }
    return adjustment;
}

void* PMath::Subtract(void* pAddress, size_t value)
{
    return static_cast<u8*>(pAddress) - value;
}

void* PMath::Add(void* pAddress, size_t value)
{
    return static_cast<u8*>(pAddress) + value;
}