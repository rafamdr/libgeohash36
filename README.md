# libgeohash36

A pure C implementation of Geohash-36

---

**int geohash36_encode(double latitude_, double longitude_, char * outBuffer_, int numCharacters_);**

Encodes desired latitude/longitude in Geohash-36 representation with a desired length.

Example: 
```C
   const int num_chars = 10;
   char geohash36_buffer[num_chars + 1];
   double latitude = 51.504444;
   double longitude = -0.086666;
   
   geohash36_encode(latitude, longitude, geohash36_buffer, num_chars);
   
   //Output: geohash36_buffer = "bdrdC26BqH";
```
   
---
   
**int geohash36_decode(char * buffer_, int bufferSize_, double * outLatitude_, double * outLongitude_);**

Decodes a Geohash-36 string.

Example: 
```C
   const char geohash36_buffer[] = "bdrdC26BqH";
   int num_chars = sizeof(geohash36_buffer) - 1;
   double outLatitude = 0, outLongitude = 0;
   
   geohash36_decode(geohash36_buffer, num_chars, &outLatitude, &outLongitude);

   //Output: outLatitude = 51.504444; outLongitude = -0.086666;
```

---

**void geohash36_getPrecisionInMeters(int numCharacters_, double * lat_prec, double * long_prec);**

Gets the precision (in meters) for latitude and longitude, given the number of characters in Geohash-36.

Example:
```C
   int num_chars = 10
   double lat_prec, long_prec;
   
   geohash36_getPrecisionInMeters(num_chars, &lat_prec, &long_prec);
   
   //Output: lat_prec = 0.165480; long_prec = 0.330961;
```
