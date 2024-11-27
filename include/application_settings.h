#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

typedef struct application_settings {
    char *filename;
    char *delimiter;
    int power_plant;
    int station_type;
    int consumer_type;
} ApplicationSettings;

ApplicationSettings *parse_application_settings(int argc, char *argv[]);

#endif //APPLICATION_SETTINGS_H
