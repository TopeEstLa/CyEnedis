#include <application_settings.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ApplicationSettings *parse_application_settings(int argc, char *argv[]) {
    ApplicationSettings *settings = malloc(sizeof(ApplicationSettings));
    if (settings == NULL) {
        return NULL;
    }

    if (argc < 4 || argc > 5) {
        return NULL;
    }

    settings->filename = malloc(strlen(argv[1]) + 1);
    if (settings->filename == NULL) {
        free_application_settings(settings);
        return NULL;
    }

    strcpy(settings->filename, argv[1]);

    settings->delimiter = DEFAULT_DELIMITER;

    StationType station_type = parse_station_type(argv[2]);
    if (station_type == STATION_INVALID) {
        free_application_settings(settings);
        return NULL;
    }

    settings->station_type = station_type;

    ConsumerType consumer_type = parse_consumer_type(argv[3]);
    if (consumer_type == CONSUMER_INVALID) {
        free_application_settings(settings);
        return NULL;
    }

    settings->consumer_type = consumer_type;

    if (argc == 5) {
        settings->power_plant = atoi(argv[4]);
    } else {
        settings->power_plant = -1;
    }

    return settings;
}

bool validate_application_settings(ApplicationSettings *settings) {
    if (settings->filename == NULL) {
        return false;
    }

    if (settings->station_type == STATION_INVALID) {
        return false;
    }

    if (settings->consumer_type == CONSUMER_INVALID) {
        return false;
    }

    if (settings->power_plant < -1) {
        return false;
    }

    if (settings->station_type == STATION_HVB &&
        (settings->consumer_type == CONSUMER_INDIVIDUAL || settings->consumer_type == CONSUMER_ALL)) {
        return false;
    }

    if (settings->station_type == STATION_HVA &&
        (settings->consumer_type == CONSUMER_COMPANY || settings->consumer_type == CONSUMER_ALL)) {
        return false;
    }

    return true;
}

void print_application_settings(ApplicationSettings *settings) {
    printf("Filename: %s\n", settings->filename);
    printf("Delimiter: %s\n", settings->delimiter);
    printf("Station type: %d\n", settings->station_type);
    printf("Consumer type: %d\n", settings->consumer_type);
    printf("Power plant: %d\n", settings->power_plant);
}

void free_application_settings(ApplicationSettings *settings) {
    free(settings->filename);
    free(settings);
}

StationType parse_station_type(char *type) {
    if (strcmp(type, "hvb") == 0) return STATION_HVB;
    if (strcmp(type, "hva") == 0) return STATION_HVA;
    if (strcmp(type, "lv") == 0) return STATION_LV;
    return STATION_INVALID;
}

ConsumerType parse_consumer_type(char *type) {
    if (strcmp(type, "comp") == 0) return CONSUMER_COMPANY;
    if (strcmp(type, "indiv") == 0) return CONSUMER_INDIVIDUAL;
    if (strcmp(type, "all") == 0) return CONSUMER_ALL;
    return CONSUMER_INVALID;
}

char *generate_output_filename(ApplicationSettings *settings) {
    char *filename = malloc(100 * sizeof(char));
    if (filename == NULL) return NULL;

    char *station_type;
    switch (settings->station_type) {
        case STATION_HVB:
            station_type = "hvb";
            break;
        case STATION_HVA:
            station_type = "hva";
            break;
        case STATION_LV:
            station_type = "lv";
            break;
        default:
            station_type = "UNKNOWN";
            break;
    }

    char *consumer_type;
    switch (settings->consumer_type) {
        case CONSUMER_INDIVIDUAL:
            consumer_type = "indiv";
            break;
        case CONSUMER_COMPANY:
            consumer_type = "comp";
            break;
        case CONSUMER_ALL:
            consumer_type = "all";
            break;
        default:
            consumer_type = "UNKNOWN";
            break;
    }

    if (settings->power_plant == -1) {
        sprintf(filename, "%s_%s.csv", station_type, consumer_type);
    } else {
        sprintf(filename, "%s_%s_%d.csv", station_type, consumer_type, settings->power_plant);
    }

    return filename;
}