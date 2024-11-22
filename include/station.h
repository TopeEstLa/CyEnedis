#ifndef STATION_H
#define STATION_H

/**
 * @brief Enum for the type of the station or consumer.
 */
typedef enum station_type {
    POWER_STATION,
    HV_B_STATION,
    HV_A_STATION,
    LV_STATION,
    COMPANY_CONSUMER,
    INDIVIDUAL_CONSUMER
} StationType;

/**
 * @brief Struct for the station or consumer.
 * @param id The id of the station or consumer.
 * @param capacity The capacity of the station if it is a station.
 * @param consumption The consumption of the consumer if it is a consumer.
 * @param type The type of the station or consumer.
 */
typedef struct station {
    int id;
    long capacity, consumption;
    enum station_type type;
} Station;

/**
 * @brief Create a station struct with the given parameters.
 * @param id The id of the station.
 * @param capacity The capacity of the station.
 * @param consumption The consumption of the station.
 * @param type The type of the station.
 * @return The created station.
 */
Station* create_station(int id, long capacity, long consumption, StationType type);

#endif //STATION_H
