#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <stdbool.h>

#define DEFAULT_DELIMITER ";"

typedef enum station_type {
    STATION_HVB,
    STATION_HVA,
    STATION_LV,
    STATION_INVALID,
} StationType;

typedef enum consumer_type {
    CONSUMER_COMPANY,
    CONSUMER_INDIVIDUAL,
    CONSUMER_ALL,
    CONSUMER_INVALID,
} ConsumerType;

typedef struct application_settings {
    char *filename;
    char *delimiter;
    int power_plant;
    enum station_type station_type;
    enum consumer_type consumer_type;
} ApplicationSettings;

ApplicationSettings *parse_application_settings(int argc, char *argv[]);

void free_application_settings(ApplicationSettings *settings);

void print_application_settings(ApplicationSettings *settings);

StationType parse_station_type(char *type);

ConsumerType parse_consumer_type(char *type);

bool validate_application_settings(ApplicationSettings *settings);

#endif //APPLICATION_SETTINGS_H
