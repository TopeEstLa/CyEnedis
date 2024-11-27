#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <stdbool.h>

#define DEFAULT_DELIMITER ";"

/**
 * Enum for the type of station used for filtering
 * STATION_HVB: High voltage bus station
 * STATION_HVA: High voltage area station
 * STATION_LV: Low voltage station
 */
typedef enum station_type {
    STATION_HVB,
    STATION_HVA,
    STATION_LV,
    STATION_INVALID,
} StationType;

/**
 * Enum for the type of consumer used for filtering
 * CONSUMER_COMPANY: Company consumer
 * CONSUMER_INDIVIDUAL: Individual consumer
 * CONSUMER_ALL: All consumers
 */
typedef enum consumer_type {
    CONSUMER_COMPANY,
    CONSUMER_INDIVIDUAL,
    CONSUMER_ALL,
    CONSUMER_INVALID,
} ConsumerType;

/**
 * @brief Structure for the application settings parsed from parameters (CLI)
 * @param filename: The name of the CSV file to read
 * @param delimiter: The delimiter used in the CSV file
 * @param power_plant: The id of the power plant to filter
 * @param station_type: The type of station to filter
 * @param consumer_type: The type of consumer to filter
 */
typedef struct application_settings {
    char *filename;
    char *delimiter;
    int power_plant;
    enum station_type station_type;
    enum consumer_type consumer_type;
} ApplicationSettings;

/**
 * @brief Parse the application settings from the command line arguments
 * ./projectC <filename> <station_type> <consumer_type> [power_plant]
 * PowerPlant is not necessary
 * @param argc argument count
 * @param argv argument values
 * @return Parsed application settings or NULL if an error occurred
 */
ApplicationSettings *parse_application_settings(int argc, char *argv[]);

/**
 * @brief Free the memory allocated for the application settings
 * @param settings The application settings to free
 */
void free_application_settings(ApplicationSettings *settings);

/**
 * @brief Print the application settings to the console
 * @param settings
 */
void print_application_settings(ApplicationSettings *settings);

/**
 * @brief Parse the station type from a string
 * @param type The string to parse
 * @return The parsed station type or INVALID if the string is invalid
 */
StationType parse_station_type(char *type);

/**
 * @brief Parse the consumer type from a string
 * @param type The string to parse
 * @return The parsed consumer type or INVALID if the string is invalid
 */
ConsumerType parse_consumer_type(char *type);

/**
 * @brief Check if the parsed application settings is valid
 * - filename is not NULL
 * - delimiter is not NULL
 * - station_type is not INVALID
 * - consumer_type is not INVALID
 * - Station is not HVB and consumer is INDIVIDUAL or ALL
 * - Station is not HVA and consumer is COMPANY or ALL
 * @param settings The application settings to validate
 * @return true if the settings are valid, false otherwise
 */
bool validate_application_settings(ApplicationSettings *settings);

/**
 * @brief Generate the output filename based on the application settings
 * @param settings The application settings
 * @return The generated filename or NULL if an error occurred
 */
char* generate_output_filename(ApplicationSettings* settings);

#endif //APPLICATION_SETTINGS_H
