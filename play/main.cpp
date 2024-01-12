#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <mmap-allocator/allocator.hpp>
#include <string_view>

int main(int argc, char *argv[]) {
    MMapMemView view{};

    try {
        MMapMemView pages = view.AllocatePages(1000000);
        pages.ProtectPages(0, 1);
        std::string_view str = pages.ConstView().AsStringView();
        std::cout << str << std::endl;

        printf("%p\n", (void *)pages.Start());
        printf("%p\n", (void *)pages.End());
        printf("%ld\n", pages.End() - pages.Start());

        std::cin.get();
        pages.Deallocate();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "ERROR" << std::endl;
    }

    return EXIT_SUCCESS;
}
