#ifndef _GEOHASH36_H_
#define _GEOHASH36_H_

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "stdint.h"

/***********************************************************************************************************************
Defines/macros
***********************************************************************************************************************/

/*!
************************************************************************************************************************
* @brief Suggested number of characters in Geohash-46 (default).
************************************************************************************************************************
**/
#define GEOHASH36_DEFAULT_NUM_CHARACTERS     10

/*!
************************************************************************************************************************
* @brief Macro to get minimum between 2 values.
************************************************************************************************************************
**/
#ifndef MIN
#define MIN(a, b)                            (((a) < (b)) ? (a) : (b))
#endif

/***********************************************************************************************************************
Exported functions
***********************************************************************************************************************/

/*!
************************************************************************************************************************
* @brief Encodes desired latitude/longitude in Geohash-36 representation with a desired length.
************************************************************************************************************************
* @param [in] latitude_: latitude of position which will be encoded;
* @param [in] longitude_: longitude of position which will be encoded;
* @param [out] outBuffer_: pointer of string buffer which will receive the Geohash-36;
* @param [in] numCharacters_: desired Geohash-36 length.
************************************************************************************************************************
* @return Geohash-36 length.
************************************************************************************************************************
**/
int geohash36_encode(double latitude_, double longitude_, char * outBuffer_, int numCharacters_);

/*!
************************************************************************************************************************
* @brief Decodes a Geohash-36 string.
************************************************************************************************************************
* @param [in] buffer_: input buffer which contains a Geohash-36 string;
* @param [in] bufferSize_: "buffer_" length;
* @param [out] outLatitude_: pointer to latitude which will store the result of decoding;
* @param [out] outLongitude_: pointer to longitude which will store the result of decoding.
************************************************************************************************************************
* @return Initialize result code.
* @retval  0  - Everything worked;
* @retval -1  - Fail to decode due invalid input.
************************************************************************************************************************
**/
int geohash36_decode(char * buffer_, int bufferSize_, double * outLatitude_, double * outLongitude_);

/*!
************************************************************************************************************************
* @brief Gets the precision (in meters) for latitude and longitude, given the number of characters in Geohash-36
************************************************************************************************************************
* @param [in] numCharacters_: desired Geohash-36 length;
* @param [out] lat_prec: pointer to a integer which will store latitude precision in meters;
* @param [out] long_prec: pointer to a integer which will store longitude precision in meters.
************************************************************************************************************************
* @return None.
************************************************************************************************************************
**/
void geohash36_getPrecisionInMeters(int numCharacters_, double * lat_prec, double * long_prec);

#endif // _GEOHASH36_H_