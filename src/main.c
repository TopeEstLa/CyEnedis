#include <stdio.h>

#include <application_settings.h>
#include <csv_parser.h>


int main(int argc, char *argv[]) {
    ApplicationSettings *settings = parse_application_settings(argc, argv);
    if (settings == NULL) {
        printf("Invalid settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        return 1;
    }

    if (!validate_application_settings(settings)) {
        printf("Invalid settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        free_application_settings(settings);
        return 1;
    }

    print_application_settings(settings);
    StationNode* node = process_csv_file(settings);
    if (node == NULL) {
        printf("Error processing file\n");
        free_application_settings(settings);
        return 1;
    }

    pretty_print_avl(node, 0);


    return 0;
}
