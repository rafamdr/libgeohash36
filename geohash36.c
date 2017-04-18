/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "geohash36.h"

/***********************************************************************************************************************
Defines/macros
***********************************************************************************************************************/

/*!
************************************************************************************************************************
* @brief Defines the side size of base36 matrix.
************************************************************************************************************************
**/
#define GEOHASH_MATRIX_SIDE                  6

/*!
************************************************************************************************************************
* @brief Defines the Earth radius in meters.
************************************************************************************************************************
**/
#ifndef EARTH_RADIUS_IN_METERS
#define EARTH_RADIUS_IN_METERS               6370000
#endif

/*!
************************************************************************************************************************
* @brief Defines PI constant.
************************************************************************************************************************
**/
#ifndef PI
#define PI                                   3.14159265358979323846f
#endif

/*!
************************************************************************************************************************
* @brief Macro to calculate the absolute value of a number.
************************************************************************************************************************
**/
#ifndef ABS
#define ABS(value)                           (((value) < 0) ? (-value) : (value))
#endif

/***********************************************************************************************************************
Typedefs/structs/unions
***********************************************************************************************************************/
typedef union
{
   uint8_t value;

   struct
   {
      uint8_t curr : 7;
      uint8_t next : 1;
   }info;

}hash_node_t;

/***********************************************************************************************************************
Constants
***********************************************************************************************************************/
const char base36[GEOHASH_MATRIX_SIDE][GEOHASH_MATRIX_SIDE] =
{
   '2', '3', '4', '5', '6', '7',
   '8', '9', 'b', 'B', 'C', 'd',
   'D', 'F', 'g', 'G', 'h', 'H',
   'j', 'J', 'K', 'l', 'L', 'M',
   'n', 'N', 'P', 'q', 'Q', 'r',
   'R', 't', 'T', 'V', 'W', 'X'
};
//----------------------------------------------------------------------------------------------------------------------

const uint8_t base36_inverse_hash[] =
{
   0x91, 0x15, 0xFF, 0xFF, 0x93, 0x18, 0x14, 0x00, 0x16, 0x00, 0x97, 0x1B, 0x99, 0x1D, 0xFF, 0xFF, 0x9A, 0x1F, 0x1C, 
   0x00, 0x1E, 0x00, 0xFF, 0xFF, 0x20, 0x00, 0xFF, 0xFF, 0x80, 0x21, 0x81, 0x22, 0x82, 0x23, 0x03, 0x00, 0x04, 0x00, 
   0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0xFF, 0xFF, 0x0B, 
   0x00, 0xFF, 0xFF, 0x09, 0x00, 0x8A, 0x0E, 0x8C, 0x10, 0xFF, 0xFF, 0x8D, 0x12, 0x0F, 0x00
};

/***********************************************************************************************************************
Internal functions
***********************************************************************************************************************/

/*!
************************************************************************************************************************
* @brief Calculates the potency of a number using multiplication
************************************************************************************************************************
* @param [in] base_: desired base value;
* @param [in] exp_: desired expoent.
************************************************************************************************************************
* @return Result of potency.
************************************************************************************************************************
**/
static int geohash36_fastPow(int base_, uint32_t exp_)
{
   int output = 1;

   if (exp_ == 0)
      output;

   while(exp_ > 0)
   {
      output *= base_;
      exp_--;
   }

   return output;
}

/*!
************************************************************************************************************************
* @brief Gets the line and column of Base36 table given a character
************************************************************************************************************************
* @param [in] c_: pointer of instance of lgps_filter_t used to control all;
* @param [out] line_: pointer to a integer which will store the line calculated;
* @param [out] col_: pointer to a integer which will store the column calculated.
************************************************************************************************************************
* @return None.
************************************************************************************************************************
**/
static void geohash36_charToIndexes(char c_, int * line_, int * col_)
{
   (*line_) = -1;
   (*col_) = -1;

   //for (int i = 0; i < GEOHASH_MATRIX_SIDE; i++)
   //{
   //   for (int j = 0; j < GEOHASH_MATRIX_SIDE; j++)
   //   {
   //      if (c_ == base36[i][j])
   //      {
   //         (*line_) = i;
   //         (*col_) = j;
   //         break;
   //      }
   //   }
   //}

   int possible_index = c_ % 36;

   hash_node_t * node_ptr = (hash_node_t *)(base36_inverse_hash + (possible_index << 1));

   if (node_ptr->value != 0xFF)
   {
      char temp = *(((char*)base36) + node_ptr->info.curr);

      if (temp == c_)
      {
         (*line_) = node_ptr->info.curr / GEOHASH_MATRIX_SIDE;
         (*col_) = node_ptr->info.curr % GEOHASH_MATRIX_SIDE;
      }
      else if(node_ptr->info.next)
      {
         node_ptr++;
         temp = *(((char*)base36) + node_ptr->info.curr);

         if (temp == c_)
         {
            (*line_) = node_ptr->info.curr / GEOHASH_MATRIX_SIDE;
            (*col_) = node_ptr->info.curr % GEOHASH_MATRIX_SIDE;
         }
      }
   }
}

/***********************************************************************************************************************
External functions
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
int geohash36_encode(double latitude_, double longitude_, char * outBuffer_, int numCharacters_)
{
   //(51.504444, -0.086666)  -->   bdrdC26BqH

   double lat[] = { -90.0,  90.0  };
   double lon[] = { -180.0, 180.0 };
   int latIdx = 0, longIdx = 0;
   double slice;
   int outbuffer_count = 0;

   while (numCharacters_ > 0)
   {
      slice = lon[0] - lon[1];
      slice = ABS(slice) / (double)GEOHASH_MATRIX_SIDE;

      for (int i = 0; i < GEOHASH_MATRIX_SIDE; i++)
      {
         double leftBoudary = (lon[0] + (i * slice));
         double rightBoudary = (lon[0] + ((i + 1) * slice));

         if ((longitude_ > leftBoudary) && (longitude_ <= rightBoudary))
         {
            longIdx = i;
            lon[0] = leftBoudary;
            lon[1] = rightBoudary;
            break;
         }
      }

      slice = lat[0] - lat[1];
      slice = ABS(slice) / (double)GEOHASH_MATRIX_SIDE;

      for (int i = 0; i < GEOHASH_MATRIX_SIDE; i++)
      {
         double leftBoudary = (lat[0] + (i * slice));
         double rightBoudary = (lat[0] + ((i + 1) * slice));

         if ((latitude_ > leftBoudary) && (latitude_ <= rightBoudary))
         {
            latIdx = GEOHASH_MATRIX_SIDE - 1 - i;
            lat[0] = leftBoudary;
            lat[1] = rightBoudary;
            break;
         }
      }

      outBuffer_[outbuffer_count++] = base36[latIdx][longIdx];
      latIdx = 0;
      longIdx = 0;
      numCharacters_--;
   }

   return outbuffer_count;
}

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
int geohash36_decode(char * buffer_, int bufferSize_, double * outLatitude_, double * outLongitude_)
{
   //bdrdC26BqH   ~~>   (51.504444, -0.086666)

   double lat[] = { -90.0,  90.0  };
   double lon[] = { -180.0, 180.0 };
   int latLine, longCol;
   double slice;

   for (int i = 0; i < bufferSize_; i++)
   {
      geohash36_charToIndexes(buffer_[i], &latLine, &longCol);

      if (latLine == -1)
         return -1;

      latLine = GEOHASH_MATRIX_SIDE - 1 - latLine;

      slice = lon[0] - lon[1];
      slice = (ABS(slice) / (double)GEOHASH_MATRIX_SIDE);
      lon[1] = lon[0] + (slice * (longCol + 1));
      lon[0] = lon[0] + (slice * longCol);
      
      slice = lat[0] - lat[1];
      slice = (ABS(slice) / (double)GEOHASH_MATRIX_SIDE);
      lat[1] = lat[0] + (slice * (latLine + 1));
      lat[0] = lat[0] + (slice * latLine);
   }

   (*outLatitude_) = (lat[1] + lat[0]) / 2;
   (*outLongitude_) = (lon[1] + lon[0]) / 2;

   return 0;
}

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
void geohash36_getPrecisionInMeters(int numCharacters_, double * lat_prec, double * long_prec)
{
   double one_grade_in_meters = (2 * PI * EARTH_RADIUS_IN_METERS) / 360;

   (*lat_prec) = (90 / (double)geohash36_fastPow(GEOHASH_MATRIX_SIDE, numCharacters_)) * one_grade_in_meters;
   (*long_prec) = (*lat_prec) * 2;
}