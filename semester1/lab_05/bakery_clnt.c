/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "bakery.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

struct BakeryOrder *
getorder_1(struct BakeryOrder *argp, CLIENT *clnt)
{
	static struct BakeryOrder clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, GetOrder,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) argp,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct BakeryOrder *
waitinqueue_1(struct BakeryOrder *argp, CLIENT *clnt)
{
	static struct BakeryOrder clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, WaitInQueue,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) argp,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

struct BakeryOrder *
processbakeryresult_1(struct BakeryOrder *argp, CLIENT *clnt)
{
	static struct BakeryOrder clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ProcessBakeryResult,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) argp,
		(xdrproc_t) xdr_BakeryOrder, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
