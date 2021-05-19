#ifndef TEST_UNIT_GENERAL_H
#define TEST_UNIT_GENERAL_H

#include "common.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QTime>

class test_unit_general
{
public:
    test_unit_general();
    void runtest_Hashing();
    void runTest_IndexManager();

private:
    void testIndexCreationAndSaving();
    void testIndexLoadingAndModif();

    QTextStream *out;
};

#endif // TEST_UNIT_GENERAL_H
