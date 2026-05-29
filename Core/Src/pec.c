/*! \file ******************************************************************
 *
 * \brief PEC calculation.
 *
 *  This file implements the PEC computation over a specified buffer range. It follows
 *  a minimum memory approach.
 *
 ***************************************************************************/

#include	"pec.h"

/** PEC computation.
*
*   This function computes a PEC over a specified buffer. The PEC is a CRC
*   polynomial defined by C(x) = x8 + x2 + x1 + 1. See section 7.4.2
*   of the SMBUS specification.
*
*   \note This is a minimum memory approach. A look up table is faster.
*
@param 		*bptr	Pointer to buffer
@param		len		Number of characters to include in the computation
@return 	PEC as a uint8_t
*/
uint8_t pec_Compute( uint8_t const *bptr, uint16_t len ) {

	uint8_t pec;

	pec = 0;

	while ( len-- )
	{
		pec = pec_Update( pec, *bptr );
		++bptr;
	};
	return pec;
}


/** PEC update.
*
*    This function updates the PEC using the passed PEC and the new datum.
*    The PEC is a CRC polynomial defined by C(x) = x8 + x2 + x1 + 1.
*    See section 7.4.2 of the SMBUS specification.
*
*   \note This is a minimum memory approach. A look up table is faster.
*
@param 		pec		Current PEC
@param		datum	Byte to update the PEC with
@return 	The PEC as a uint8_t.
*/
uint8_t pec_Update( uint8_t pec, uint8_t datum ) {
	uint8_t i;

	pec ^= datum;
	for ( i = 0; i < 8; ++i )
	{
		if ( pec & 0x80 )
		{
			pec <<= 1;      /* Modified at the suggestion of Lint from */
			pec ^= 0x07;    /* pec = (pec << 1) ^ 0x07; */
		}
		else
		{
			pec <<= 1;
		}
	}
	return pec;
}
