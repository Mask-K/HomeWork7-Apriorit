#include "MyGuard.h"
#include "Deletors.h"
#include "MySmartPtrs.h"


void testMyGuard(){
    MyGuard guard("D:\\test.txt", //write here YOUR path
                  GENERIC_WRITE,
                  FILE_SHARE_READ,
                  nullptr,
                  CREATE_NEW,
                  FILE_ATTRIBUTE_NORMAL,
                  nullptr);

    std::string strText = "Hello Apriorit!";
    DWORD bytesWritten;
    WriteFile(
            guard,
            strText.c_str(),
            strText.size(),
            &bytesWritten,
            nullptr);
    std::cout << "Check the file in your computer\n";
}

void testSmartPtrs(){
    SharedPointer<int> p1(new int(5));
    std::cout << "First shared ptr created\n";
    std::cout << "Count for p1: " << p1.use_count() << std::endl;
    auto p2 = p1;
    std::cout << "Second shared ptr created using copy constructor\n";
    std::cout << "Count for p1: " << p1.use_count() << std::endl;
    std::cout << "Count for p2: " << p2.use_count() << std::endl;

    {
        auto p3(std::move(p2));
        std::cout << "Third shared ptr created using move constructor with p2\n";
        std::cout << "Count for p3: " << p3.use_count() << std::endl;
    }
    std::cout << "The third is now out of visibility scope\n";
    std::cout << "Count for p1: " << p1.use_count() << std::endl;

    WeakPointer<int> wp = p1;
    std::cout << "Weak ptr created using copy constructor with p1\n";
    std::cout << "Count for p1: " << p1.use_count() << std::endl;
    std::cout << "Count for wp: " << wp.use_count() << std::endl;

    std::cout << "Check if weak ptr expired " << wp.expired() << std::endl;

    SharedPointer<int> p4(wp);
    std::cout << "New shared ptr created using copy constructor with weak ptr\n";
    std::cout << "Count for p1: " << p1.use_count() << std::endl;
    std::cout << "Count for p4: " << p4.use_count() << std::endl;

    std::cout << "Reset p4\n";
    p4.reset();
    std::cout << "Count for p1: " << p1.use_count() << std::endl;
    std::cout << "Count for wp: " << wp.use_count() << std::endl;

    auto p5 = wp.lock();
    std::cout << "New shared ptr created using weak ptr lock method\n";
    std::cout << "Count for wp: " << wp.use_count() << std::endl;
    std::cout << "Count for p5: " << p1.use_count() << std::endl;

    p1.reset();
    p5.reset();

    std::cout << "Reseted all available shared ptrs\n";
    std::cout << "Count for wp: " << wp.use_count() << std::endl;

    std::cout << "New shared ptr created using weak ptr lock method\n";
    auto p6 = wp.lock();
    std::cout << "Count for p6: " << p1.use_count() << std::endl;
}








int main(){
    try{
        //Task 1
        testMyGuard();
        std::cout << std::endl;
        //Task 2
        labdaDeleter();
        fDeleter();
        pDeleter();
        std::cout << std::endl;
        //Task3
        testSmartPtrs();

    }
    catch(const std::exception& e){
        std::cerr << e.what();
    }




    return 0;
}
