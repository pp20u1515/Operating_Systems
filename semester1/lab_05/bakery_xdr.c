/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "bakery.h"

bool_t
xdr_BakeryOrder (XDR *xdrs, BakeryOrder *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->order_num))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->pid))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->order_result))
		 return FALSE;
	return TRUE;
}
