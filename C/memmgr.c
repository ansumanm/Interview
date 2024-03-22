#include <stdio.h>
#include <stdlib.h>

/*
Memory manager.
Given a chunk of memory of length l, allocate and free fixed page size units.
Maintain a bit list using integers.

For example:
startAddress = 0
length = 32*4 = 256 bytes
pagesize = 4 bytes
number of pages = 64
Bit list length = 256/(4*32) = 2

0th page = 0 to 3 bytes
1th page = 4 to 7 bytes
...
32th page = 32*4 = 128th to 131th byte
33rd page = 33*4 = 132th to 135th byte

33rd bit = (33/32 = 1, 33 % 32 = 1) = 1st bit of allocatedBits[1]


*/
typedef struct memoryManager
{
  void *startAddress;
  int length;
  int pageSize;
  int numPages;
  // Pointer to a bit list. If a bit is 0, that page is free. If 1, it is allocated.
  int numBytes;
  int *allocatedBits;
#define intSize 32; // in bits

  int allocatedPagesCount;
  int freePagesCount;
} MemoryManager;

void memoryManagerInit(MemoryManager *memmgr, void *startAddress, int length, int pageSize)
{
  memmgr->startAddress = startAddress;
  memmgr->length = length;
  memmgr->pageSize = pageSize;
  memmgr->numPages = length / pageSize;

  // Each page's free/alloc status is managed by 1 bit.
  memmgr->numBytes = memmgr->numPages / intSize;
  memmgr->allocatedBits = malloc(memmgr->numBytes);

  memmgr->allocatedPagesCount = 0;
  memmgr->freePagesCount = memmgr->numPages;
}

void memoryManagerDump(MemoryManager *mmgr)
{
  printf("-------------- Memory manager dump --------------\n");
  printf("Start Address: %p \n", mmgr->startAddress);
  printf("Length: %d \n", mmgr->length);
  printf("PageSize: %d \n", mmgr->pageSize);
  printf("Number of pages: %d \n", mmgr->numPages);
  printf("Number of bytes for bitmap: %d \n", mmgr->numBytes);
  printf("Allocated pages count: %d \n", mmgr->allocatedPagesCount);
  printf("Free pages count: %d \n", mmgr->freePagesCount);
  printf("-------------- Bitmap dump --------------\n");
  for (int i = 0; i < mmgr->numBytes; i++)
  {
    printf("0x%x\n", mmgr->allocatedBits[i]);
  }
  printf("----------------------------\n");
}

#define BIT_IS_SET(x, n) ((x) & (1UL << (n)) ? 1 : 0)
#define BIT_CLEAR_POSITION(x) (__builtin_ffs(~(x)) - 1)
#define BIT_SET(x, n) ((x) |= (1UL << (n)))
#define BIT_CLEAR(x, n) ((x) &= ~(1UL << (n)))

// Returns One page
void *memoryManagerPageAlloc(MemoryManager *memmgr)
{
  // First find the first word which has a but free.
  int index = 0;
  int clear_bit_pos;
  int free_page_index;
  long int ret_address;

  while (memmgr->allocatedBits[index] == ~0)
  {
    index++;
    if (index == (memmgr->numBytes))
    {
      printf("Returning NULL....\n");
      return NULL;
    }
  }
  clear_bit_pos = BIT_CLEAR_POSITION(memmgr->allocatedBits[index]);

  // Assume that the managed memory is an array, where each element is of size page_size.
  // free_page_index is the index to that array. It will be used to compute the absolute address.
  free_page_index = index * intSize + clear_bit_pos;

  // Set the bit to indicate that the page is allocated.
  BIT_SET(memmgr->allocatedBits[index], clear_bit_pos);

  memmgr->allocatedPagesCount++;
  memmgr->freePagesCount--;

  return (char *)memmgr->startAddress + (memmgr->pageSize * free_page_index);
}

void memoryManagerPageFree(MemoryManager *memmgr, void *addr)
{
  // Identify the offset from the base address.
  int offset = (char *)addr - (char *)memmgr->startAddress;
  int page_index = offset / (memmgr->pageSize);

  int byteIndex = page_index / intSize;
  int bitIndex = page_index % intSize;

  // Clear the Bit
  BIT_CLEAR(memmgr->allocatedBits[byteIndex], bitIndex);

  memmgr->allocatedPagesCount--;
  memmgr->freePagesCount++;
}

int main()
{
  // Test the memory manager
  MemoryManager mmgr;
  int numPages;
  int pageSize;
  char *managedMemory;
  int *x[64];

  numPages = 64;
  pageSize = sizeof(int);
  managedMemory = malloc(numPages * pageSize);
  // Instantiate an object of Memory manager

  memoryManagerInit(&mmgr, managedMemory, (numPages * pageSize), pageSize);
  memoryManagerDump(&mmgr);

  for (int i = 0; i < 64; i++)
  {
    x[i] = memoryManagerPageAlloc(&mmgr);
    // printf("Allocated memory: %p\n", x[i]);
    // memoryManagerDump(&mmgr);
  }

  memoryManagerPageFree(&mmgr, x[10]);
  memoryManagerDump(&mmgr);

  x[10] = memoryManagerPageAlloc(&mmgr);
  memoryManagerDump(&mmgr);

  memoryManagerPageFree(&mmgr, x[32]);
  memoryManagerPageFree(&mmgr, x[33]);
  memoryManagerPageFree(&mmgr, x[34]);
  memoryManagerPageFree(&mmgr, x[35]);
  memoryManagerDump(&mmgr);

  x[32] = memoryManagerPageAlloc(&mmgr);
  memoryManagerDump(&mmgr);

  free(managedMemory);
  
  return 0;
}
