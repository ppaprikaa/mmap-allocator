# MMAP-Allocator

Simple library that provides memory page mmap allocation/deallocation and guarding memory pages functionality which I built for my own research purposes only.

Here's the example of usage:
```C++
MMapMemView view{};

MMapMemView pages = view.AllocatePages(1000000); 
// Please don't allocate one million pages

pages.ProtectPages(0, 1);
pages.Deallocate();
```