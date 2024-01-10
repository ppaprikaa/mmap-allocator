#include <mmap-allocator/pagesize.hpp>
#include <unistd.h>

namespace gears {
	class PageSizeDetector {
	public:
		PageSizeDetector() {
			page_size_ = DetectPageSize();
		}
		size_t GetPageSize() {
			return page_size_;
		}
	private:
		size_t DetectPageSize() {
			return sysconf(_SC_PAGESIZE);
		}
	private:
		size_t page_size_;
	};

	size_t PageSize() {
		static  PageSizeDetector detector;

		return detector.GetPageSize();
	}
}
