#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <application_settings.h>
#include <avl.h>
#include <stdbool.h>

/**
 * @brief Structure for the parsed data from a CSV line. all value can be null or -1 if not present.
 * @param power_plant: The power plant id.
 * @param hvb_station: The high voltage bus station id.
 * @param hva_station: The high voltage area station id.
 * @param lv_station: The low voltage station id.
 * @param company: The company id.
 * @param individual: The individual id.
 * @param capacity: The capacity of the station.
 * @param load: The load of the station.
 */
typedef struct parsed_data {
    int power_plant;
    int hvb_station;
    int hva_station;
    int lv_station;
    int company;
    int individual;
    long capacity;
    long load;
} ParsedData;

/**
 * @brief Process the CSV file and return the root of the AVL tree.
 * @param settings The application settings.
 * @return the root of the AVL tree or NULL if an error occurred.
 */
StationNode* process_csv_file(ApplicationSettings* settings);

/**
 * @brief Parse a CSV line and return the parsed data.
 * @param settings The application settings.
 * @param line The CSV line to parse.
 * @return The parsed data or NULL if an error occurred.
 */
ParsedData* parse_csv_line(ApplicationSettings* settings, char* line);

/**
 * @brief Check if the station should be processed.
 * @param data The parsed data.
 * @param settings The application settings.
 * @return true if the station should be processed, false otherwise.
 */
bool should_process_station(ParsedData* data, ApplicationSettings* settings);

/**
 * @brief Check if the consumer should be processed.
 * @param data The parsed data.
 * @param settings The application settings.
 * @return true if the consumer should be processed, false otherwise.
 */
bool should_process_consumer(ParsedData* data, ApplicationSettings* settings);

/**
 * @brief Get the parent station of the consumer.
 * @param data The parsed data.
 * @param settings The application settings.
 * @return The parent station id or -1 if not found.
 */
int get_parent_station(ParsedData* data, ApplicationSettings* settings);



#endif //CSV_PARSER_H
