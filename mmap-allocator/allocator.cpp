#include <mmap-allocator/allocator.hpp>
#include <mmap-allocator/mem-view.hpp>
#include <mmap-allocator/pagesize.hpp>
#include <sys/mman.h>

MMapMemView MMapMemView::AllocatePages(size_t pages, void *start_addr) {
    size_t size = PagesToBytes(pages);

    void *start = mmap(start_addr, size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (start == MAP_FAILED) {
        throw "Cannot allocate";
    }

    return MMapMemView{(char *)start, size};
}

size_t MMapMemView::PageSize() { return gears::PageSize(); }

size_t MMapMemView::PagesToBytes(size_t pages) { return pages * PageSize(); }

void MMapMemView::Deallocate() {
    if (start_ == nullptr) {
        return;
    }

    if (munmap((void *)start_, size_) == -1) {
        throw "Cannot deallocate pages";
    }
}

void MMapMemView::ProtectPages(size_t start_page, size_t pages) {
    int ret = mprotect((void *)(start_ + PagesToBytes(start_page)),
                       PagesToBytes(pages), PROT_NONE);

    if (ret == -1)
        throw "Cannot protect pages";
}

MMapMemView::MMapMemView(MMapMemView &&that) noexcept {
    start_ = that.start_;
    size_ = that.size_;
    that.Reset();
}

MMapMemView &MMapMemView::operator=(MMapMemView &&that) noexcept {
    Deallocate();
    start_ = that.start_;
    size_ = that.size_;
    that.Reset();
    return *this;
}

MutableMemView MMapMemView::Release() {
    MutableMemView view = MutableView();
    Reset();
    return view;
}

void MMapMemView::Reset() noexcept {
    start_ = nullptr;
    size_ = 0;
}
