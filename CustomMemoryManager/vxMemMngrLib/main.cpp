#include "vx_mem_mngr.h"
#include "componenttests.h"

using namespace  vx_mm;

void trial_one();

void lcl_initialize()
{
    vx_mm::vx_managed_memory::initialize(vx_mm::mem_req_stratergy::ms_greedy);
    vx_mm::vx_managed_memory::initialize(vx_mm::mem_req_stratergy::ms_lite);
    vx_mm::vx_managed_memory::initialize(vx_mm::mem_req_stratergy::ms_normal);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    lcl_initialize();
    trial_one();

    std::cout << "\n\n";
    
#ifdef _MSC_VER
	getchar();
#endif

    return 0;
}

void trial_one()
{
    ComponentTests test;

    //test.test_vx_page1();
    //std::cout << "\n=======================\n";

    test.test_vx_page2();
}
