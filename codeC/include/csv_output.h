#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include <result_generator.h>
#include <application_settings.h>

#define FIST_MAX 10
#define LAST_MIN 10

/**
 * @brief Write the results to a CSV file.
 * @param consumerType type of consumer
 * @param filename name of the file
 * @param results list of results
 * @param count row count
 */
void write_csv(ConsumerType consumerType, char *filename, StationResult **results, int count);

/**
 * @brief Write the first 10 max and last 10 min results to a CSV file.
 * @param consumerType type of consumer
 * @param filename name of the file to write to
 * @param results list of results
 * @param count row count
 */
void write_min_max_csv(ConsumerType consumerType, char *filename, StationResult **results, int count);

#endif //CSV_OUTPUT_H
