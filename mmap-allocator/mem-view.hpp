#pragma once

#include <cstddef>
#include <string_view>

#include <mmap-allocator/pagesize.hpp>

class ConstMemView {
  public:
    ConstMemView(const char *start, size_t size) : start_(start), size_(size) {}
    ConstMemView() : ConstMemView(nullptr, 0){};

    static size_t PageSize();

    static ConstMemView Empty() { return ConstMemView(); }

    const char *Start() const noexcept { return start_; }

    size_t Size() const noexcept { return size_; }

    const char *End() const noexcept { return start_ + size_; }

    const size_t Pages() const noexcept { return Size() / PageSize(); }

    std::string_view AsStringView() { return {start_, size_}; }

  private:
    const char *start_;
    size_t size_;
};

class MutableMemView {
  public:
    MutableMemView(char *start, size_t size)
        : initial_(start), start_(start), size_(size) {}
    MutableMemView() : MutableMemView(nullptr, 0) {}

    static size_t PageSize();

    static MutableMemView Empty() { return MutableMemView(); }

    char *Initial() const noexcept { return initial_; }

    char *Start() const noexcept { return start_; }

    size_t Size() const noexcept { return size_; }

    char *End() const noexcept { return start_ + size_; }

    char *Back() const noexcept { return End() - 1; }

    size_t Pages() const noexcept { return Size() / PageSize(); }

    bool HasSpace() const noexcept { return size_ > 0; }

    bool IsValid() const noexcept { return start_ != nullptr; }

    void MoveForward(size_t offset) noexcept {
        if (offset > size_)
            return;
        start_ += offset;
        size_ -= offset;
    }

    void MoveBackward(size_t offset) noexcept {
        if (start_ - offset < initial_)
            return;
        start_ -= offset;
        size_ += offset;
    }

    void operator+=(size_t offset) noexcept { MoveForward(offset); }

    void operator-=(size_t offset) noexcept { MoveBackward(offset); }

  private:
    char *initial_;
    char *start_;
    size_t size_;
};
