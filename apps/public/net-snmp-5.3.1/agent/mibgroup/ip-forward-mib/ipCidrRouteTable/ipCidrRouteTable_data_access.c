/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.17 $ of : mfd-data-access.m2c,v $ 
 *
 * $Id: //BBN_Linux/Branch/Branch_for_SDK_Release_MultiChip_20111013/tclinux_phoenix/apps/public/net-snmp-5.3.1/agent/mibgroup/ip-forward-mib/ipCidrRouteTable/ipCidrRouteTable_data_access.c#1 $
 */
/*
 * standard Net-SNMP includes 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*
 * include our parent header 
 */
#include "ipCidrRouteTable.h"


#include "ipCidrRouteTable_data_access.h"


/** @ingroup interface 
 * @addtogroup data_access data_access: Routines to access data
 *
 * These routines are used to locate the data used to satisfy
 * requests.
 * 
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ipCidrRouteTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * IP-FORWARD-MIB::ipCidrRouteTable is subid 4 of ipForward.
 * Its status is Deprecated.
 * OID: .1.3.6.1.2.1.4.24.4, length: 9
 */

/**
 * initialization for ipCidrRouteTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param ipCidrRouteTable_reg
 *        Pointer to ipCidrRouteTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
ipCidrRouteTable_init_data(ipCidrRouteTable_registration *
                           ipCidrRouteTable_reg)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_init_data",
                "called\n"));

    /*
     * TODO:303:o: Initialize ipCidrRouteTable data.
     */

    return MFD_SUCCESS;
}                               /* ipCidrRouteTable_init_data */

/**
 * container overview
 *
 */

/**
 * container initialization
 *
 * @param container_ptr_ptr A pointer to a container pointer. If you
 *        create a custom container, use this parameter to return it
 *        to the MFD helper. If set to NULL, the MFD helper will
 *        allocate a container for you.
 * @param  cache A pointer to a cache structure. You can set the timeout
 *         and other cache flags using this pointer.
 *
 *  This function is called at startup to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases. If no custom
 *  container is allocated, the MFD code will create one for your.
 *
 *  This is also the place to set up cache behavior. The default, to
 *  simply set the cache timeout, will work well with the default
 *  container. If you are using a custom container, you may want to
 *  look at the cache helper documentation to see if there are any
 *  flags you want to set.
 *
 * @remark
 *  This would also be a good place to do any initialization needed
 *  for you data source. For example, opening a connection to another
 *  process that will supply the data, opening a database, etc.
 */
void
ipCidrRouteTable_container_init(netsnmp_container **container_ptr_ptr,
                                netsnmp_cache * cache)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_container_init",
                "called\n"));

    if (NULL == container_ptr_ptr) {
        snmp_log(LOG_ERR,
                 "bad container param to ipCidrRouteTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    if (NULL == cache) {
        snmp_log(LOG_ERR,
                 "bad cache param to ipCidrRouteTable_container_init\n");
        return;
    }

    /*
     * TODO:345:A: Set up ipCidrRouteTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = IPCIDRROUTETABLE_CACHE_TIMEOUT;    /* seconds */
}                               /* ipCidrRouteTable_container_init */

/**
 * check entry for update
 *
 */
static void
_snarf_route_entry(netsnmp_route_entry *route_entry,
                   netsnmp_container *container)
{
    ipCidrRouteTable_rowreq_ctx *rowreq_ctx;

    DEBUGTRACE;

    netsnmp_assert(NULL != route_entry);
    netsnmp_assert(NULL != container);

    /*
     * allocate an row context and set the index(es), then add it to
     * the container
     */
    rowreq_ctx = ipCidrRouteTable_allocate_rowreq_ctx(route_entry, NULL);
    if ((NULL != rowreq_ctx) &&
        (MFD_SUCCESS == ipCidrRouteTable_indexes_set
         (rowreq_ctx, *((u_long *) route_entry->rt_dest),
          route_entry->rt_mask, route_entry->rt_tos,
          *((u_long *) route_entry->rt_nexthop)))) {
        CONTAINER_INSERT(container, rowreq_ctx);
        rowreq_ctx->ipCidrRouteStatus = ROWSTATUS_ACTIVE;
    } else {
        if (rowreq_ctx) {
            snmp_log(LOG_ERR, "error setting index while loading "
                     "ipCidrRoute cache.\n");
            ipCidrRouteTable_release_rowreq_ctx(rowreq_ctx);
        } else
            netsnmp_access_route_entry_free(route_entry);
    }
}

/**
 * container shutdown
 *
 * @param container_ptr A pointer to the container.
 *
 *  This function is called at shutdown to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases.
 *
 *  This function is called before ipCidrRouteTable_container_free().
 *
 * @remark
 *  This would also be a good place to do any cleanup needed
 *  for you data source. For example, closing a connection to another
 *  process that supplied the data, closing a database, etc.
 */
void
ipCidrRouteTable_container_shutdown(netsnmp_container *container_ptr)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_container_shutdown", "called\n"));

    if (NULL == container_ptr) {
        snmp_log(LOG_ERR,
                 "bad params to ipCidrRouteTable_container_shutdown\n");
        return;
    }

}                               /* ipCidrRouteTable_container_shutdown */

/**
 * load initial data
 *
 * TODO:350:M: Implement ipCidrRouteTable data load
 * This function will also be called by the cache helper to load
 * the container again (after the container free function has been
 * called to free the previous contents).
 *
 * @param container container to which items should be inserted
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_RESOURCE_UNAVAILABLE : Can't access data source
 * @retval MFD_ERROR                : other error.
 *
 *  This function is called to load the index(es) (and data, optionally)
 *  for the every row in the data set.
 *
 * @remark
 *  While loading the data, the only important thing is the indexes.
 *  If access to your data is cheap/fast (e.g. you have a pointer to a
 *  structure in memory), it would make sense to update the data here.
 *  If, however, the accessing the data invovles more work (e.g. parsing
 *  some other existing data, or peforming calculations to derive the data),
 *  then you can limit yourself to setting the indexes and saving any
 *  information you will need later. Then use the saved information in
 *  ipCidrRouteTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
ipCidrRouteTable_container_load(netsnmp_container *container)
{
    netsnmp_container *route_container;

    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_cache_load",
                "called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the ipCidrRouteTable container.
     * loop over your ipCidrRouteTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    route_container =
        netsnmp_access_route_container_load(NULL,
                                            NETSNMP_ACCESS_ROUTE_LOAD_IPV4_ONLY);

    if (NULL == route_container)
        return MFD_RESOURCE_UNAVAILABLE;        /* msg already logged */

    /*
     * we just got a fresh copy of route data. snarf data
     */
    CONTAINER_FOR_EACH(route_container,
                       (netsnmp_container_obj_func *) _snarf_route_entry,
                       container);

    /*
     * free the container. we've either claimed each ifentry, or released it,
     * so the dal function doesn't need to clear the container.
     */
    netsnmp_access_route_container_free(route_container,
                                        NETSNMP_ACCESS_ROUTE_FREE_DONT_CLEAR);

    DEBUGMSGT(("verbose:ipCidrRouteTable:ipCidrRouteTable_cache_load",
               "%d records\n", CONTAINER_SIZE(container)));

    return MFD_SUCCESS;
}                               /* ipCidrRouteTable_container_load */

/**
 * container clean up
 *
 * @param container container with all current items
 *
 *  This optional callback is called prior to all
 *  item's being removed from the container. If you
 *  need to do any processing before that, do it here.
 *
 * @note
 *  The MFD helper will take care of releasing all the row contexts.
 *
 */
void
ipCidrRouteTable_container_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_container_free",
                "called\n"));

    /*
     * TODO:380:M: Free ipCidrRouteTable container data.
     */
}                               /* ipCidrRouteTable_container_free */

/**
 * prepare row for processing.
 *
 *  When the agent has located the row for a request, this function is
 *  called to prepare the row for processing. If you fully populated
 *  the data context during the index setup phase, you may not need to
 *  do anything.
 *
 * @param rowreq_ctx pointer to a context.
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 */
int
ipCidrRouteTable_row_prep(ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_row_prep",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
}                               /* ipCidrRouteTable_row_prep */

/*
 * TODO:420:r: Implement ipCidrRouteTable index validation.
 */
/*---------------------------------------------------------------------
 * IP-FORWARD-MIB::ipCidrRouteEntry.ipCidrRouteDest
 * ipCidrRouteDest is subid 1 of ipCidrRouteEntry.
 * Its status is Deprecated, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.4.24.4.1.1
 * Description:
The destination IP address of this route. 

                This object may not take a Multicast (Class D) address 
                value. 

                Any assignment (implicit or otherwise) of an instance  
                of this object to a value x must be rejected if the  
                bitwise logical-AND of x with the value of the  
                corresponding instance of the ipCidrRouteMask object is  
                not equal to x.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is IPADDR (based on perltype IPADDR)
 * The net-snmp type is ASN_IPADDRESS. The C type decl is u_long (u_long)
 */
/**
 * check validity of ipCidrRouteDest index portion
 *
 * @retval MFD_SUCCESS   : the incoming value is legal
 * @retval MFD_ERROR     : the incoming value is NOT legal
 *
 * @note this is not the place to do any checks for the sanity
 *       of multiple indexes. Those types of checks should be done in the
 *       ipCidrRouteTable_validate_index() function.
 *
 * @note Also keep in mind that if the index refers to a row in this or
 *       some other table, you can't check for that row here to make
 *       decisions, since that row might not be created yet, but may
 *       be created during the processing this request. If you have
 *       such checks, they should be done in the check_dependencies
 *       function, because any new/deleted/changed rows should be
 *       available then.
 *
 * The following checks have already been done for you:
 *
 * If there a no other checks you need to do, simply return MFD_SUCCESS.
 */
int
ipCidrRouteDest_check_index(ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteDest_check_index",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:426:M: |-> Check ipCidrRouteTable index ipCidrRouteDest.
     * check that index value in the table context is legal.
     * (rowreq_ctx->tbl_index.ipCidrRouteDest)
     */

    return MFD_SUCCESS;         /* ipCidrRouteDest index ok */
}                               /* ipCidrRouteDest_check_index */

/*---------------------------------------------------------------------
 * IP-FORWARD-MIB::ipCidrRouteEntry.ipCidrRouteMask
 * ipCidrRouteMask is subid 2 of ipCidrRouteEntry.
 * Its status is Deprecated, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.4.24.4.1.2
 * Description:
Indicate the mask to be logical-ANDed with the  
                destination address before being compared to the value  
                in the ipCidrRouteDest field.  For those systems that  
                do not support arbitrary subnet masks, an agent  
                constructs the value of the ipCidrRouteMask by  
                reference to the IP Address Class. 

                Any assignment (implicit or otherwise) of an instance  
                of this object to a value x must be rejected if the  
                bitwise logical-AND of x with the value of the  
                corresponding instance of the ipCidrRouteDest object is  


                not equal to ipCidrRouteDest.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is IPADDR (based on perltype IPADDR)
 * The net-snmp type is ASN_IPADDRESS. The C type decl is u_long (u_long)
 */
/**
 * check validity of ipCidrRouteMask index portion
 *
 * @retval MFD_SUCCESS   : the incoming value is legal
 * @retval MFD_ERROR     : the incoming value is NOT legal
 *
 * @note this is not the place to do any checks for the sanity
 *       of multiple indexes. Those types of checks should be done in the
 *       ipCidrRouteTable_validate_index() function.
 *
 * @note Also keep in mind that if the index refers to a row in this or
 *       some other table, you can't check for that row here to make
 *       decisions, since that row might not be created yet, but may
 *       be created during the processing this request. If you have
 *       such checks, they should be done in the check_dependencies
 *       function, because any new/deleted/changed rows should be
 *       available then.
 *
 * The following checks have already been done for you:
 *
 * If there a no other checks you need to do, simply return MFD_SUCCESS.
 */
int
ipCidrRouteMask_check_index(ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteMask_check_index",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:426:M: |-> Check ipCidrRouteTable index ipCidrRouteMask.
     * check that index value in the table context is legal.
     * (rowreq_ctx->tbl_index.ipCidrRouteMask)
     */

    return MFD_SUCCESS;         /* ipCidrRouteMask index ok */
}                               /* ipCidrRouteMask_check_index */

/*---------------------------------------------------------------------
 * IP-FORWARD-MIB::ipCidrRouteEntry.ipCidrRouteTos
 * ipCidrRouteTos is subid 3 of ipCidrRouteEntry.
 * Its status is Deprecated, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.4.24.4.1.3
 * Description:
The policy specifier is the IP TOS Field.  The encoding 
                of IP TOS is as specified by the following convention. 
                Zero indicates the default path if no more specific 
                policy applies. 

                +-----+-----+-----+-----+-----+-----+-----+-----+ 
                |                 |                       |     | 
                |   PRECEDENCE    |    TYPE OF SERVICE    |  0  | 
                |                 |                       |     | 
                +-----+-----+-----+-----+-----+-----+-----+-----+ 

                             IP TOS                IP TOS 
                   Field     Policy      Field     Policy 
                   Contents    Code      Contents    Code 
                   0 0 0 0  ==>   0      0 0 0 1  ==>   2 
                   0 0 1 0  ==>   4      0 0 1 1  ==>   6 
                   0 1 0 0  ==>   8      0 1 0 1  ==>  10 
                   0 1 1 0  ==>  12      0 1 1 1  ==>  14 
                   1 0 0 0  ==>  16      1 0 0 1  ==>  18 
                   1 0 1 0  ==>  20      1 0 1 1  ==>  22 
                   1 1 0 0  ==>  24      1 1 0 1  ==>  26 
                   1 1 1 0  ==>  28      1 1 1 1  ==>  30
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   0
 *   settable   0
 *
 * Ranges:  0 - 2147483647;
 *
 * Its syntax is INTEGER32 (based on perltype INTEGER32)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
 */
/**
 * check validity of ipCidrRouteTos index portion
 *
 * @retval MFD_SUCCESS   : the incoming value is legal
 * @retval MFD_ERROR     : the incoming value is NOT legal
 *
 * @note this is not the place to do any checks for the sanity
 *       of multiple indexes. Those types of checks should be done in the
 *       ipCidrRouteTable_validate_index() function.
 *
 * @note Also keep in mind that if the index refers to a row in this or
 *       some other table, you can't check for that row here to make
 *       decisions, since that row might not be created yet, but may
 *       be created during the processing this request. If you have
 *       such checks, they should be done in the check_dependencies
 *       function, because any new/deleted/changed rows should be
 *       available then.
 *
 * The following checks have already been done for you:
 *    The value is in (one of) the range set(s):  0 - 2147483647
 *
 * If there a no other checks you need to do, simply return MFD_SUCCESS.
 */
int
ipCidrRouteTos_check_index(ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTos_check_index",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:426:M: |-> Check ipCidrRouteTable index ipCidrRouteTos.
     * check that index value in the table context is legal.
     * (rowreq_ctx->tbl_index.ipCidrRouteTos)
     */

    return MFD_SUCCESS;         /* ipCidrRouteTos index ok */
}                               /* ipCidrRouteTos_check_index */

/*---------------------------------------------------------------------
 * IP-FORWARD-MIB::ipCidrRouteEntry.ipCidrRouteNextHop
 * ipCidrRouteNextHop is subid 4 of ipCidrRouteEntry.
 * Its status is Deprecated, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.4.24.4.1.4
 * Description:
On remote routes, the address of the next system en  
                route; Otherwise, 0.0.0.0.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is IPADDR (based on perltype IPADDR)
 * The net-snmp type is ASN_IPADDRESS. The C type decl is u_long (u_long)
 */
/**
 * check validity of ipCidrRouteNextHop index portion
 *
 * @retval MFD_SUCCESS   : the incoming value is legal
 * @retval MFD_ERROR     : the incoming value is NOT legal
 *
 * @note this is not the place to do any checks for the sanity
 *       of multiple indexes. Those types of checks should be done in the
 *       ipCidrRouteTable_validate_index() function.
 *
 * @note Also keep in mind that if the index refers to a row in this or
 *       some other table, you can't check for that row here to make
 *       decisions, since that row might not be created yet, but may
 *       be created during the processing this request. If you have
 *       such checks, they should be done in the check_dependencies
 *       function, because any new/deleted/changed rows should be
 *       available then.
 *
 * The following checks have already been done for you:
 *
 * If there a no other checks you need to do, simply return MFD_SUCCESS.
 */
int
ipCidrRouteNextHop_check_index(ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteNextHop_check_index",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:426:M: |-> Check ipCidrRouteTable index ipCidrRouteNextHop.
     * check that index value in the table context is legal.
     * (rowreq_ctx->tbl_index.ipCidrRouteNextHop)
     */

    return MFD_SUCCESS;         /* ipCidrRouteNextHop index ok */
}                               /* ipCidrRouteNextHop_check_index */

/**
 * verify specified index is valid.
 *
 * This check is independent of whether or not the values specified for
 * the columns of the new row are valid. Column values and row consistency
 * will be checked later. At this point, only the index values should be
 * checked.
 *
 * All of the individual index validation functions have been called, so this
 * is the place to make sure they are valid as a whole when combined. If
 * you only have one index, then you probably don't need to do anything else
 * here.
 * 
 * @note Keep in mind that if the indexes refer to a row in this or
 *       some other table, you can't check for that row here to make
 *       decisions, since that row might not be created yet, but may
 *       be created during the processing this request. If you have
 *       such checks, they should be done in the check_dependencies
 *       function, because any new/deleted/changed rows should be
 *       available then.
 *
 *
 * @param ipCidrRouteTable_reg
 *        Pointer to the user registration data
 * @param rowreq_ctx
 *        Pointer to the users context.
 * @retval MFD_SUCCESS            : success
 * @retval MFD_CANNOT_CREATE_NOW  : index not valid right now
 * @retval MFD_CANNOT_CREATE_EVER : index never valid
 */
int
ipCidrRouteTable_validate_index(ipCidrRouteTable_registration *
                                ipCidrRouteTable_reg,
                                ipCidrRouteTable_rowreq_ctx * rowreq_ctx)
{
    int             rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteTable_validate_index",
                "called\n"));

    /** we should have a non-NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:430:M: |-> Validate potential ipCidrRouteTable index.
     */
    if (1) {
        snmp_log(LOG_WARNING, "invalid index for a new row in the "
                 "ipCidrRouteTable table.\n");
        /*
         * determine failure type.
         *
         * If the index could not ever be created, return MFD_NOT_EVER
         * If the index can not be created under the present circumstances
         * (even though it could be created under other circumstances),
         * return MFD_NOT_NOW.
         */
        if (0) {
            return MFD_CANNOT_CREATE_EVER;
        } else {
            return MFD_CANNOT_CREATE_NOW;
        }
    }

    return rc;
}                               /* ipCidrRouteTable_validate_index */

/** @} */
