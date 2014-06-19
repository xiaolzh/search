g++ -g -c -o MemoryBlock.o MemoryBlock.cpp
g++ -g -c -o MemoryPool.o MemoryPool.cpp
g++ -g -c -o example.o example.cpp
g++ -g -o example MemoryBlock.o MemoryPool.o example.o

