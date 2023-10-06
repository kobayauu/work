
/*
 * The following structures are PRIVATE starting with CUPS 1.6/macOS 10.8.
 * Please use the new accessor functions available in CUPS 1.6 and later, as
 * these definitions will be moved to a private header file in a future release.
 *
 * Define _IPP_PRIVATE_STRUCTURES to 1 to cause the private IPP structures to be
 * exposed in CUPS 1.6.  This happens automatically on macOS when compiling for
 * a deployment target of 10.7 or earlier.
 *
 * Define _IPP_PRIVATE_STRUCTURES to 0 to prevent the private IPP structures
 * from being exposed.  This is useful when migrating existing code to the new
 * accessors.
 */

#  ifdef _IPP_PRIVATE_STRUCTURES
     /* Somebody has overridden the value */
#  elif defined(_CUPS_SOURCE) || defined(_CUPS_IPP_PRIVATE_H_)
     /* Building CUPS */
#    define _IPP_PRIVATE_STRUCTURES 1
#  elif defined(__APPLE__)
#    if defined(MAC_OS_X_VERSION_10_8) && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8
       /* Building for 10.7 and earlier */
#      define _IPP_PRIVATE_STRUCTURES 1
#    elif !defined(MAC_OS_X_VERSION_10_8)
       /* Building for 10.7 and earlier */
#      define _IPP_PRIVATE_STRUCTURES 1
#    endif /* MAC_OS_X_VERSION_10_8 && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8 */
#  else
#    define _IPP_PRIVATE_STRUCTURES 0
#  endif /* _CUPS_SOURCE || _CUPS_IPP_PRIVATE_H_ */

#  if _IPP_PRIVATE_STRUCTURES
typedef union _ipp_request_u		/**** Request Header ****/
{
  struct				/* Any Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    int		op_status;		/* Operation ID or status code*/
    int		request_id;		/* Request ID */
  }		any;

  struct				/* Operation Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_op_t	operation_id;		/* Operation ID */
    int		request_id;		/* Request ID */
  }		op;

  struct				/* Status Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		status;

  /**** New in CUPS 1.1.19 ****/
  struct				/* Event Header @since CUPS 1.1.19/macOS 10.3@ */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		event;
} _ipp_request_t;

/**** New in CUPS 1.1.19 ****/

typedef union _ipp_value_u		/**** Attribute Value ****/
{
  int		integer;		/* Integer/enumerated value */

  char		boolean;		/* Boolean value */

  ipp_uchar_t	date[11];		/* Date/time value */

  struct
  {
    int		xres,			/* Horizontal resolution */
		yres;			/* Vertical resolution */
    ipp_res_t	units;			/* Resolution units */
  }		resolution;		/* Resolution value */

  struct
  {
    int		lower,			/* Lower value */
		upper;			/* Upper value */
  }		range;			/* Range of integers value */

  struct
  {
    char	*language;		/* Language code */
    char	*text;			/* String */
  }		string;			/* String with language value */

  struct
  {
    int		length;			/* Length of attribute */
    void	*data;			/* Data in attribute */
  }		unknown;		/* Unknown attribute type */

/**** New in CUPS 1.1.19 ****/
  ipp_t		*collection;		/* Collection value @since CUPS 1.1.19/macOS 10.3@ */
} _ipp_value_t;
typedef _ipp_value_t ipp_value_t;	/**** Convenience typedef that will be removed @private@ ****/

struct _ipp_attribute_s			/**** IPP attribute ****/
{
  ipp_attribute_t *next;		/* Next attribute in list */
  ipp_tag_t	group_tag,		/* Job/Printer/Operation group tag */
		value_tag;		/* What type of value is it? */
  char		*name;			/* Name of attribute */
  int		num_values;		/* Number of values */
  _ipp_value_t	values[1];		/* Values */
};

struct _ipp_s				/**** IPP Request/Response/Notification ****/
{
  ipp_state_t		state;		/* State of request */
  _ipp_request_t	request;	/* Request header */
  ipp_attribute_t	*attrs;		/* Attributes */
  ipp_attribute_t	*last;		/* Last attribute in list */
  ipp_attribute_t	*current;	/* Current attribute (for read/write) */
  ipp_tag_t		curtag;		/* Current attribute group tag */

/**** New in CUPS 1.2 ****/
  ipp_attribute_t	*prev;		/* Previous attribute (for read) @since CUPS 1.2/macOS 10.5@ */

/**** New in CUPS 1.4.4 ****/
  int			use;		/* Use count @since CUPS 1.4.4/macOS 10.6.?@ */
/**** New in CUPS 2.0 ****/
  int			atend,		/* At end of list? */
			curindex;	/* Current attribute index for hierarchical search */
};
#  endif /* _IPP_PRIVATE_STRUCTURES */
