#ifndef _GEOHASH36_H_
#define _GEOHASH36_H_

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "string.h"
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

/*!
************************************************************************************************************************
* @brief Default codes to set which direction will used when we process neighbors.
 
(-1,-1)  (-1, 0)  (-1,+1)
( 0,-1)  ( 0, 0)  ( 0,+1)
(+1,-1)  (+1, 0)  (-1,+1)

(-1,-1) 0xFFFF -> Northwest
(-1, 0) 0xFF00 -> North
(-1,+1) 0xFF01 -> Northeast
( 0,-1) 0x00FF -> West
( 0, 0) 0x0000 -> Center
( 0,+1) 0x0001 -> East
(+1,-1) 0x01FF -> Southwest
(+1, 0) 0x0100 -> South
(+1,+1) 0xFF01 -> Southeast
************************************************************************************************************************
**/
#define GEO36_NEIGHBORS_DIR_NORTHWEST     0xFFFF
#define GEO36_NEIGHBORS_DIR_NORTH         0xFF00
#define GEO36_NEIGHBORS_DIR_NORTHEAST     0xFF01
#define GEO36_NEIGHBORS_DIR_WEST          0x00FF
#define GEO36_NEIGHBORS_DIR_CENTER        0x0000
#define GEO36_NEIGHBORS_DIR_EAST          0x0001
#define GEO36_NEIGHBORS_DIR_SOUTHWEST     0x01FF
#define GEO36_NEIGHBORS_DIR_SOUTH         0x0100
#define GEO36_NEIGHBORS_DIR_SOUTHEAST     0x0101

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

/*!
 ************************************************************************************************************************
 * @brief Gets a neighbor Geohash-36 given a input hash and a direction (north, northeast, etc).
 ************************************************************************************************************************
 * @param [in] buffer_: input buffer which contains a Geohash-36 string;
 * @param [in] bufferSize_: "buffer_" length;
 * @param [out] outBuffer_: pointer of string buffer which will receive the Geohash-36 neighbor;
 * @param [in] direction_: code to indicate the direction of neighbor. See header file to view expected codes.
 ************************************************************************************************************************
 * @return Initialize result code.
 * @retval outBuffer_  - Everything worked;
 * @retval NULL        - Fail to decode due invalid input.
 ************************************************************************************************************************
 **/
char * geohash36_getNeighbor(char * buffer_, int bufferSize_, char * outBuffer_, uint16_t direction_);

#endif // _GEOHASH36_H_
