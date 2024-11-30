#ifndef APPLICATION_TEST_H
#define APPLICATION_TEST_H

#include <string.h>
#include <assert.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <qsort.h>

int test_global();

ApplicationSettings* test_settings_parser();

StationNode* test_avl_build(ApplicationSettings* settings);

StationResult** test_output(StationNode* node, int* count);

StationResult** test_qsort(StationResult** result, int count);

#endif //APPLICATION_TEST_H