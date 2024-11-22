#include <station.h>

#include <stdlib.h>

Station* create_station(int id, long capacity, long consumption, StationType type) {
    Station *station = malloc(sizeof(Station));
    station->id = id;
    station->capacity = capacity;
    station->consumption = consumption;
    station->type = type;
    return station;
}
