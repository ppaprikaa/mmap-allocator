#pragma once

#include <sys/mman.h>

#include <mmap-allocator/mem-view.hpp>

class MMapMemView {
	public:
		MMapMemView() {
			Reset();
		}

		~MMapMemView() {
			Deallocate();
		}

		static MMapMemView AllocatePages(size_t pages, void *start = nullptr) ;
		static size_t PageSize();
		static size_t PagesToBytes(size_t pages);

		void Deallocate();
		void ProtectPages(size_t start_page, size_t pages);
	
		MMapMemView(MMapMemView&& that) noexcept;
		MMapMemView& operator=(MMapMemView&& that) noexcept;
		
		const char* Start() const noexcept {
			return start_;
		}

		const char* End() const noexcept {
			return start_ + size_;
		}

		ConstMemView ConstView() const noexcept {
			return {(char*)start_, size_};
		}

		MutableMemView MutableView() const noexcept {
			return {(char*)start_, size_};
		}

		MutableMemView Release();
		
		bool HasSpace() const noexcept {
			return size_ > 0;
		}

		bool IsValid() const noexcept {
			return start_ != nullptr;
		}
	private:
		void Reset() noexcept;
		MMapMemView(char* start, size_t size) : start_(start), size_(size) {}
	private:
		const char* start_;
		size_t size_;
};
