/*! \file ******************************************************************
 *
 * \brief pec.h.
 *
 ***************************************************************************/

#ifndef PEC_H_
#define PEC_H_

#include <stdint.h>

uint8_t pec_Compute( uint8_t const *bptr, uint16_t len );
uint8_t pec_Update( uint8_t pec, uint8_t datum );

#endif /* PEC_H_ */
