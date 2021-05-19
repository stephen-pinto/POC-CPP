#include "componenttests.h"
using namespace vx_types;
using namespace std;
//using namespace vx_mm;

ComponentTests::ComponentTests()
{

}

void ComponentTests::test_vx_page1()
{
    pvx_page_ls lspg = new vx_page_ls(1024);

    char* ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    cout << "\nUsed size :  " << lspg->used_size();
    cout << "\nTotal size : " << lspg->size();

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)lspg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    /*
        ptr = (char*)lspg->allocate(100);
        memcpy(ptr, "This is a sample string", 100);
        cout << "\n" << ptr;
    */

    cout << "\nUsed size :  " << lspg->used_size();
    cout << "\nTotal size : " << lspg->size();
}

void ComponentTests::test_vx_page2()
{
    pvx_page_mngd mgdpg =new vx_page_mngd(1024);

    char* ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;
    mgdpg->release(ptr);

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;
    mgdpg->release(ptr);

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;
    mgdpg->release(ptr);

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;
    mgdpg->release(ptr);

    cout << "\nUsed size :  " << mgdpg->used_size();
    cout << "\nTotal size : " << mgdpg->size();

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;
    mgdpg->release(ptr);

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    ptr = (char*)mgdpg->allocate(100);
    memcpy(ptr, "This is a sample string", 100);
    cout << "\n" << ptr;

    /*
        ptr = (char*)lspg->allocate(100);
        memcpy(ptr, "This is a sample string", 100);
        cout << "\n" << ptr;
    */

    cout << "\nUsed size :  " << mgdpg->used_size();
    cout << "\nTotal size : " << mgdpg->size();
}
