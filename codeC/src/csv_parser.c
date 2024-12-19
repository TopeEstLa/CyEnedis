#include <csv_parser.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_parsed_data(ParsedData *parsedData) {
    printf("Parsed Data %d %d %d %d %d %d %lld %lld\n", parsedData->power_plant, parsedData->hvb_station,
           parsedData->hva_station, parsedData->lv_station, parsedData->company, parsedData->individual,
           parsedData->capacity, parsedData->load);
}

void strip_newline(char *str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

StationNode *process_csv_file(ApplicationSettings *settings) {
    FILE *file = fopen(settings->filename, "r");
    if (file == NULL) return NULL;

    int max_line_length = 3024;
    char line[max_line_length];
    StationNode *root = NULL;

    fgets(line, max_line_length, file);

    while (fgets(line, max_line_length, file)) {
        strip_newline(line);
        ParsedData *data = parse_csv_line(settings, line);
        if (data == NULL) {
            printf("Failed to parse line %s\n", line);
            continue;
        }

        if (should_process_station(data, settings)) {
            int station = get_parent_station(data, settings);
            root = insert_station_node(root, station, data->capacity, data->load);
            if (root == NULL) {
                fclose(file);
                free(data);
                return NULL;
            }
        }

        free(data);
    }

    if (root == NULL) {
        fclose(file);
        return NULL;
    }

    rewind(file);
    fgets(line, sizeof(line), file);

    while (fgets(line, max_line_length, file)) {
        strip_newline(line);
        ParsedData *data = parse_csv_line(settings, line);
        if (data == NULL) {
            printf("Failed to parse line %s\n", line);
            continue;
        }

        if (should_process_consumer(data, settings)) {
            int parent_station = get_parent_station(data, settings);
            if (parent_station == -1) {
                free(data);
                continue; //Normal if we need to check hvb station and we have a consumer hooked in a lv station we need to skip it
            }

            StationNode *node = get_station_node(root, parent_station);
            if (node == NULL) {
                // Normal if we are in the case of a specific power plant
                free(data);
                continue;
            }
            node->load += data->load;
        }

        free(data);
    }

    fclose(file);
    return root;
}

ParsedData *parse_csv_line(ApplicationSettings *settings, char *line) {
    ParsedData *data = malloc(sizeof(ParsedData));
    if (data == NULL) return NULL;

    char *token;
    int field = 0;

    token = strtok(line, settings->delimiter);

    while (token != NULL) {
        char *value;

        if (strcmp(token, "-") == 0) {
            value = NULL;
        } else {
            value = malloc(strlen(token) + 1);
            if (value == NULL) {
                free(data);
                return NULL;
            }

            strcpy(value, token);
        }

        int valueInt;
        long long valueLong;
        if (value != NULL) {
            valueInt = atol(value);
            valueLong = atoll(value);
        } else {
            valueInt = -1;
            valueLong = 0;
        }

        switch (field) {
            case 0:
                data->power_plant = valueInt;
                break;
            case 1:
                data->hvb_station = valueInt;
                break;
            case 2:
                data->hva_station = valueInt;
                break;
            case 3:
                data->lv_station = valueInt;
                break;
            case 4:
                data->company = valueInt;
                break;
            case 5:
                data->individual = valueInt;
                break;
            case 6:
                data->capacity = valueLong;
                break;
            case 7:
                data->load = valueLong;
                break;
            default:
                break;
        }

        free(value);
        token = strtok(NULL, settings->delimiter);
        field++;
    }

    return data;
}

bool should_process_station(ParsedData *data, ApplicationSettings *settings) {
    if (settings->power_plant != -1 && data->power_plant != settings->power_plant) return false;
    if (data->capacity <= 0) return false;

    switch (settings->station_type) {
        case STATION_HVB:
            return data->hvb_station != -1;
        case STATION_HVA:
            return data->hva_station != -1;
        case STATION_LV:
            return data->lv_station != -1;
        default:
            return false;
    }
}

bool should_process_consumer(ParsedData *data, ApplicationSettings *settings) {
    if (settings->power_plant != -1 && data->power_plant != settings->power_plant) return false;
    if (data->load == 0) return false;

    switch (settings->consumer_type) {
        case CONSUMER_COMPANY:
            return data->company != -1;
        case CONSUMER_INDIVIDUAL:
            return data->individual != -1;
        case CONSUMER_ALL:
            return data->company != -1 || data->individual != -1;
        default:
            return false;
    }
}

int get_parent_station(ParsedData *data, ApplicationSettings *settings) {
    switch (settings->station_type) {
        case STATION_HVB:
            return data->hvb_station;
        case STATION_HVA:
            return data->hva_station;
        case STATION_LV:
            return data->lv_station;
        default:
            return -1;
    }
}