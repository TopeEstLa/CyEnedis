#include <application_test.h>

#include <string.h>
#include <assert.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <qsort.h>

int test_settings_parser() {
    //Testing normal case
    char *argv[] = {"test", "test.csv", "lv", "all"};
    ApplicationSettings *settings = parse_application_settings(4, argv);
    assert(settings != NULL);

    assert(strcmp(settings->filename, "test.csv") == 0);
    assert(strcmp(settings->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings->power_plant == -1);
    assert(settings->station_type == STATION_LV);
    assert(settings->consumer_type == CONSUMER_ALL);
    assert(validate_application_settings(settings));
    free_application_settings(settings);

    char* argv1[] = {"test", "test.csv", "hvb", "comp"};
    ApplicationSettings *settings1 = parse_application_settings(4, argv1);
    assert(settings1 != NULL);
    assert(strcmp(settings1->filename, "test.csv") == 0);
    assert(strcmp(settings1->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings1->power_plant == -1);
    assert(settings1->station_type == STATION_HVB);
    assert(settings1->consumer_type == CONSUMER_COMPANY);
    assert(validate_application_settings(settings1));

    free_application_settings(settings1);

    char *argv6[] = {"test", "test.csv", "hva", "indiv"};
    ApplicationSettings *settings6 = parse_application_settings(4, argv6);
    assert(settings6 != NULL);
    assert(strcmp(settings6->filename, "test.csv") == 0);
    assert(strcmp(settings6->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings6->power_plant == -1);
    assert(settings6->station_type == STATION_HVA);
    assert(settings6->consumer_type == CONSUMER_INDIVIDUAL);
    assert(!validate_application_settings(settings6));

    free_application_settings(settings6);

    //Testing special power plant case
    char *argv2[] = {"test", "test.csv", "lv", "all", "1"};
    ApplicationSettings *settings2 = parse_application_settings(5, argv2);
    assert(settings2 != NULL);
    assert(strcmp(settings2->filename, "test.csv") == 0);
    assert(strcmp(settings2->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings2->power_plant == 1);
    assert(settings2->station_type == STATION_LV);
    assert(settings2->consumer_type == CONSUMER_ALL);

    free_application_settings(settings2);

    //Testing invalid case
    char *argv3[] = {"test", "test.csv", "lv", "all", "1", "2"};
    ApplicationSettings *settings3 = parse_application_settings(6, argv3);
    assert(settings3 == NULL);

    char* argv4[] = {"test", "test.csv", "lv", "all", "a"};
    ApplicationSettings *settings4 = parse_application_settings(5, argv4);
    assert(settings4 == NULL);

    char* argv5[] = {"test.csv", "lv", "all", "1"};
    ApplicationSettings *settings5 = parse_application_settings(4, argv5);
    assert(settings5 == NULL);


    return 0;
}