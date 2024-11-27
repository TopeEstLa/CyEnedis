#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include <result_generator.h>
#include <application_settings.h>

/**
 * @brief Write the results to a CSV file.
 * @param filename name of the file
 * @param results list of results
 * @param count row count
 */
void write_csv(char *filename, StationResult **results, int count);

#endif //CSV_OUTPUT_H
