#ifndef APPLICATION_TEST_H
#define APPLICATION_TEST_H

#include <string.h>
#include <assert.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <qsort.h>

/**
 * @brief Launches all tests.
 * @return 0 if all tests pass, 1 otherwise.
 */
int test_global();

/**
 * @brief Tests the settings parser.
 * @return Default settings.
 */
ApplicationSettings *test_settings_parser();

/**
 * @brief Tests the CSV parser.
 * @param settings The application settings.
 * @return The parsed AVL.
 */
StationNode *test_avl_build(ApplicationSettings *settings);

/**
 * @brief Tests the AVL tree result.
 * @param node The AVL tree.
 * @param count The number of results.
 * @return The results.
 */
StationResult **test_output(StationNode *node, int *count);

/**
 * @brief Tests the quicksort.
 * @param result the non-sorted results.
 * @param count The number of results.
 * @return The sorted results.
 */
StationResult **test_qsort(StationResult **result, int count);

/**
 * @brief Check if we have -t argument.
 * @param argc size of argv.
 * @param argv arguments.
 * @return true if we have -t argument, false otherwise.
 */
bool as_test_argument(int argc, char *argv[]);

#endif //APPLICATION_TEST_H