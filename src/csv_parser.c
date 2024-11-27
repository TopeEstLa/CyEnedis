#include <csv_parser.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_parsed_data(ParsedData* parsedData) {
    printf("Parsed Data %d %d %d %d %d %d %ld %ld\n", parsedData->power_plant, parsedData->hvb_station, parsedData->hva_station, parsedData->lv_station, parsedData->company, parsedData->individual, parsedData->capacity, parsedData->load);
}

StationNode* process_csv_file(ApplicationSettings* settings) {
    FILE *file = fopen(settings->filename, "r");
    if (file == NULL) return NULL;

    char line[3024];
    StationNode *root = NULL;

    fgets(line, sizeof(line), file);

    while (fgets(line, 1024, file)) {
        ParsedData *data = parse_csv_line(settings, line);
        if (data == NULL) continue;

        if (should_process_station(data, settings)) {
            int station = get_parent_station(data, settings);
            root = insert_station_node(root, station, data->capacity, data->load);
            if (root == NULL) { // TODO: Handle error
                fclose(file);
                return NULL;
            }
        }

        free(data);
    }

    rewind(file);
    fgets(line, sizeof(line), file);

    while (fgets(line, 1024, file)) {
        ParsedData *data = parse_csv_line(settings, line);
        if (data == NULL) continue;

        if (should_process_consumer(data, settings)) {
            int parent_station = get_parent_station(data, settings);
            if (parent_station == -1) continue; //TODO: Handle error
            StationNode* node = get_station_node(root, parent_station);
            if (node == NULL) continue; //TODO: Handle error
            node->load += data->load;
        }

        free(data);
    }

    fclose(file);
    return root;
}

ParsedData* parse_csv_line(ApplicationSettings* settings, char* line) {
    ParsedData *data = malloc(sizeof(ParsedData));
    if (data == NULL) return NULL;

    char *token = strtok(line, settings->delimiter);
    int field = 0;

    while (token != NULL && field < 8) {
        char* value = strcmp(token, "-") == 0 ? NULL : strdup(token);

        long valueInt;
        if (value != NULL) {
            valueInt = atol(value);
        } else {
            valueInt = -1;
        }

        switch (field) {
            case 0: data->power_plant = valueInt; break;
            case 1: data->hvb_station = valueInt; break;
            case 2: data->hva_station = valueInt; break;
            case 3: data->lv_station = valueInt; break;
            case 4: data->company = valueInt; break;
            case 5: data->individual = valueInt; break;
            case 6: data->capacity = valueInt; break;
            case 7: data->load = valueInt; break;
        }

        free(value);
        token = strtok(NULL, settings->delimiter);
        field++;
    }

    print_parsed_data(data);
    return data;
}

bool should_process_station(ParsedData* data, ApplicationSettings* settings) {
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

bool should_process_consumer(ParsedData* data, ApplicationSettings* settings) {
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

int get_parent_station(ParsedData* data, ApplicationSettings* settings) {
    switch (settings->station_type) {
        case STATION_HVB: return data->hvb_station;
        case STATION_HVA: return data->hva_station;
        case STATION_LV: return data->lv_station;
        default: return -1;
    }
}