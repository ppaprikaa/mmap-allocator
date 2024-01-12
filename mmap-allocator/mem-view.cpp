#include <mmap-allocator/mem-view.hpp>

size_t ConstMemView::PageSize() { return gears::PageSize(); }

size_t MutableMemView::PageSize() { return gears::PageSize(); }
