#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "geohash36.h"
#include <stdlib.h>

#define NUM_CHARACTERS_FOR_GEOHASH36    GEOHASH36_DEFAULT_NUM_CHARACTERS

int main()
{
   char geohash36_buffer[NUM_CHARACTERS_FOR_GEOHASH36 + 1];
   char geohash36_buffer_neighbor[NUM_CHARACTERS_FOR_GEOHASH36 + 1];

   double latitude = 51.504444;
   double longitude = -0.086666;
   double outLatitude = 0, outLongitude = 0;
   double lat_prec, long_prec;
   int sizeBuf;

   geohash36_getPrecisionInMeters(NUM_CHARACTERS_FOR_GEOHASH36, &lat_prec, &long_prec);

   printf("Using %d characters for Geohash-36, our precision is %lf x %lf square meters\n", NUM_CHARACTERS_FOR_GEOHASH36, lat_prec, long_prec);

   sizeBuf = geohash36_encode(latitude, longitude, geohash36_buffer, NUM_CHARACTERS_FOR_GEOHASH36);
   sizeBuf = MIN(sizeBuf, NUM_CHARACTERS_FOR_GEOHASH36);
   geohash36_buffer[sizeBuf] = 0;

   printf("Geohash-36 of (%lf, %lf) is: %s\n", latitude, longitude, geohash36_buffer);

   geohash36_decode(geohash36_buffer, sizeBuf, &outLatitude, &outLongitude);

   printf("The Lat/Long of %s is: (%lf, %lf)\n", geohash36_buffer, outLatitude, outLongitude);
   
   printf("Geohash36 neighbors:\n");
   
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_NORTHWEST));
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_NORTH));
   printf("%s\n", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_NORTHEAST));
   
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_WEST));
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_CENTER));
   printf("%s\n", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_EAST));
   
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_SOUTHWEST));
   printf("%s\t", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_SOUTH));
   printf("%s\n", geohash36_getNeighbor(geohash36_buffer, sizeBuf, geohash36_buffer_neighbor, GEO36_NEIGHBORS_DIR_SOUTHEAST));

   return 0;
}
