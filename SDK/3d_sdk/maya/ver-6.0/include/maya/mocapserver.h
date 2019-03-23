/*-
 ==========================================================================
 Copyright (C) Alias Systems Corp., and/or its licensors ("Alias").  
 All rights reserved.  These coded instructions, statements, computer  
 programs, and/or related material (collectively, the "Material")
 contain unpublished information proprietary to Alias, which is
 protected by Canadian and US federal copyright law and by international
 treaties. This Material may not be disclosed to third parties, or be copied
 or duplicated, in whole or in part, without the prior written consent of
 Alias.  ALIAS HEREBY DISCLAIMS ALL WARRANTIES RELATING TO THE MATERIAL,
 INCLUDING, WITHOUT LIMITATION, ANY AND ALL EXPRESS OR IMPLIED WARRANTIES OF
 NON-INFRINGEMENT, MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 IN NO EVENT SHALL ALIAS BE LIABLE FOR ANY DAMAGES WHATSOEVER, WHETHER DIRECT,
 INDIRECT, SPECIAL, OR PUNITIVE, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 OR OTHER TORTIOUS ACTION, OR IN EQUITY, ARISING OUT OF OR RELATED TO THE
 ACCESS TO, USE OF, OR RELIANCE UPON THE MATERIAL.
 ==========================================================================
*/

/*
 * mocapserver.h - Definitions for writing motion capture servers for
 *	         Maya
 *
 */

#if !defined(__CAPSERVER_H__)
#define __CAPSERVER_H__ 1

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef _WIN32
#define PROTOTYPES
#endif

/*
 * Use the high level "am i in the devkit" flag to control the rotation
 * order flag
 */
#define CAP_ROTATION_ORDER_MAYA 1
#define CAP_ROTATION_ORDER_KIN  0
#ifndef CAP_ROTATION_ORDER
#	ifdef MAYA_MOCAP_DEVKIT
#		define CAP_ROTATION_ORDER CAP_ROTATION_ORDER_MAYA
#	else
#		define CAP_ROTATION_ORDER CAP_ROTATION_ORDER_KIN
#	endif
#endif

/*
 * Define basic motion capture types
 */

typedef struct _CapChannel *CapChannel;	/* Opaque pointer to a channel */

typedef float CapPosition[3];	/* A 3D position */

typedef float CapQuaternion[4];	/* A quaternion */

typedef float CapMatrix[4][4];	/* A 4x4 matrix */

typedef float CapMatrix3[3][3];	/* A 3x3 matrix */

/*
 * Enumerated types
 */

typedef enum CapSeverity
{
  CAP_SEV_DEBUG,
  CAP_SEV_INFO,
  CAP_SEV_WARNING,
  CAP_SEV_ERROR,
  CAP_SEV_FATAL,
  _CAP_SEV_LAST
} CapSeverity;

/*
 * Note: don't change the order of these.  They match the
 * TrackUsage enum in track.h. (At least UNKNOWN through LENS do.)
 */
typedef enum CapChannelUsage
{
  CAP_USAGE_NONE = -1,
  CAP_USAGE_UNKNOWN,
  CAP_USAGE_POSITION,
  CAP_USAGE_ORIENTATION,
  CAP_USAGE_XPOS,
  CAP_USAGE_YPOS,
  CAP_USAGE_ZPOS,
  CAP_USAGE_XROT,
  CAP_USAGE_YROT,
  CAP_USAGE_ZROT,
  CAP_USAGE_XSCALE,
  CAP_USAGE_YSCALE,
  CAP_USAGE_ZSCALE,
  CAP_USAGE_SCALE,
  CAP_USAGE_ATTACH,
  CAP_USAGE_COUPLING,
  CAP_USAGE_FILEINTERP,
  CAP_USAGE_SHAPE,
  CAP_USAGE_WEIGHT,
  CAP_USAGE_HITHER,
  CAP_USAGE_YON,
  CAP_USAGE_LENS,
  CAP_USAGE_POS_ORIENT,
  _CAP_USAGE_LAST
} CapChannelUsage;

/*
 * Rotation order for converting Euler angles to quaternions
 */
typedef enum CapRotationOrder
{
  /*
   * these rotation orders are kept for backward compatibility
   * and define rotations compatible with Kinemation/TAV naming
   */
  CAP_ROT_XYZ_KIN,
  CAP_ROT_XZY_KIN,
  CAP_ROT_YXZ_KIN,
  CAP_ROT_YZX_KIN,
  CAP_ROT_ZXY_KIN,
  CAP_ROT_ZYX_KIN,

  /*
   * the following rotation order names are reversed from the
   * Kinemation/TAV set but are compatible with PA/Maya names
   */ 

  CAP_ROT_XYZ_MAYA = CAP_ROT_ZYX_KIN,
  CAP_ROT_XZY_MAYA = CAP_ROT_YZX_KIN,
  CAP_ROT_YXZ_MAYA = CAP_ROT_ZXY_KIN,
  CAP_ROT_YZX_MAYA = CAP_ROT_XZY_KIN,
  CAP_ROT_ZXY_MAYA = CAP_ROT_YXZ_KIN,
  CAP_ROT_ZYX_MAYA = CAP_ROT_XYZ_KIN

} CapRotationOrder;

/*
 * This allows us to neither break old code, nor have to rewrite the
 * the entire interface for a consistant "guard_string" implementation
 */
#if CAP_ROTATION_ORDER == CAP_ROTATION_ORDER_MAYA
#	define CAP_ROT_XYZ CAP_ROT_XYZ_MAYA
#	define CAP_ROT_XZY CAP_ROT_XZY_MAYA
#	define CAP_ROT_YXZ CAP_ROT_YXZ_MAYA
#	define CAP_ROT_YZX CAP_ROT_YZX_MAYA
#	define CAP_ROT_ZXY CAP_ROT_ZXY_MAYA
#	define CAP_ROT_ZYX CAP_ROT_ZYX_MAYA
#elif CAP_ROTATION_ORDER == CAP_ROTATION_ORDER_KIN
#	define CAP_ROT_XYZ CAP_ROT_XYZ_KIN
#	define CAP_ROT_XZY CAP_ROT_XZY_KIN
#	define CAP_ROT_YXZ CAP_ROT_YXZ_KIN
#	define CAP_ROT_YZX CAP_ROT_YZX_KIN
#	define CAP_ROT_ZXY CAP_ROT_ZXY_KIN
#	define CAP_ROT_ZYX CAP_ROT_ZYX_KIN
#else
	This compiler error indicates that you have not set a valid
	value for the symbol CAP_ROTATION_ORDER.
#endif

typedef enum CapCommand
{
  CAP_CMD_ERROR,
  CAP_CMD_AUTHORIZE,
  CAP_CMD_INIT,
  CAP_CMD_VERSION,
  CAP_CMD_INFO,
  CAP_CMD_DATA,
  CAP_CMD_START_RECORD,
  CAP_CMD_STOP_RECORD,
  CAP_CMD_CLOSE,
  CAP_CMD_QUIT,
  _CAP_CMD_LAST
} CapCommand;

/*
 * Figure out if we should use prototypes or not
 */

#if !defined(_PROTO)
#if defined(PROTOTYPES) || defined(FUNCPROTO) || defined(__STDC__) || defined(__EXTENSIONS__) || defined(__cplusplus)
#define _PROTO(x)	x
#else
#define _PROTO(x)	()
#endif
#endif // !defined(_PROTO)

/*
 * Capture library function declarations/prototypes
 */

int	CapWaitTimeout _PROTO((int fd, int msec));

/*  ========== CapDaemonize ==========
 *
 *  SYNOPSIS
 *      Turn this process into a daemon
 *
 *  PARAMETERS
 *      None
 *
 *  DESCRIPTION
 *	This routine turns the current process into a daemon process.
 *	A daemon process runs in the background in its own process
 *	group with no controlling terminal.  Important signals are
 *	also handled correctly.
 *
 *  RETURN VALUE
 *      0 if no error occurred or -1 if there was a problem.
 *	if -1 is returned, errno is set appropriately.
 * 
 *  NOTES
 *	On Unix, this routine causes the process to make a lot of changes:
 *      o ALL files are closed (including stdin, stdout, and stderr).
 *      o The pid changes (done with fork()).
 *      o The parent pid changes to 1.
 *      o The trapped signals may change (SIGHUP is ignored)
 *      o The current directory changes to /.
 *      o The umask is cleared.
 */
int	CapDaemonize _PROTO((void));

/* ========== CapError ==========
 *
 *  SYNOPSIS
 *	Generate an error message at an appropriate place
 *
 *  PARAMETERS
 *	int	client_fd	File desc of socket to client
 *	CapSeverity severity	The severity of the error
 *	char	*pgm		The name of the program
 *	char	*fmt		A printf style format string
 *	...			Args for the format string as necessary
 *
 *  DESCRIPTION
 *	This routine generates an appropriately placed error message.
 *	If the client file descriptor is valid, the message is passed
 *	to the client.  Otherwise, if we are running as a daemon, the
 *	message is sent to syslog, else it is sent to stderr.
 *
 *  RETURN VALUE
 *      0 if no error occurred or -1 if there was a problem.
 *	if -1 is returned, errno is set appropriately.
 */
int	CapError _PROTO((int client_fd, CapSeverity sev, char *pgm,
			 char *fmt,...));
             
/*  ========== CapServe ==========
 *
 *  SYNOPSIS
 *	Create a socket, wait for a connection and return the file
 *	descriptor.  (This routine is unneeded if the server is
 *	being started by inetd.)
 *
 *  PARAMETERS
 *	char	*server		The server name
 *
 *  DESCRIPTION
 *	This routine takes a server name, creates the socket, and
 *	waits for a connection.  It then removes the original sockets
 *	and returns the connection to the client.
 *
 *	A server name takes one of two formats: either <host>:<port>
 *	or <path>.  The <host>:<port> format creates an Internet
 *	family socket on the LOCAL host (the <host> part is IGNORED)
 *	for the specified port.  The port can be an integer port number
 *	or a service name that can be found by getservbyname().
 *	The <path> format specifies a pathname to use as the address
 *	of a Unix family socket for local connections only.  If 
 *	<path> starts with a '/', it is taken to be an absolute path
 *	otherwise, the path is assumed to be relative to "/tmp/".
 *
 *  RETURN VALUE
 *      The file descriptor on which the client is connected or
 *	-1 if there was some error (errno will be set appropriately).
 */
int	CapServe _PROTO((char *server));

/*  ========== CapCreateInetSocket ==========
 *
 *  SYNOPSIS
 *	Create an internet socket and return its file descriptor
 *
 *  PARAMETERS
 *	char	*service	The service name in /etc/services
 *	short	def_port	The default port number if service does
 *				not work
 *
 *  DESCRIPTION
 *	This routine creates an internet socket and returns its file
 *	descriptor.  If service is not NULL, it is looked up in
 *	/etc/services to get the port number to use.  If it is NULL
 *	or the lookup fails, def_port is used instead.
 *
 *  RETURN VALUE
 *      0 if no error occurred or -1 if there was a problem.
 *	if -1 is returned, errno is set appropriately.
 */
int	CapCreateInetSocket _PROTO((char *service, short def_port));

/*  ========== CapCreateUnixSocket ==========
 *
 *  SYNOPSIS
 *	Create a unix socket and return its file descriptor
 *
 *  PARAMETERS
 *	char	*name		The file name to create.  If the
 *				name does not contain a '/' then
 *				"/tmp/" is prepended.
 *
 *  DESCRIPTION
 *	This routine creates a unix socket and returns its file
 *	descriptor.  If name contains a '/' then use that name
 *	directly.  If it does not contain a '/' then "/tmp/" is
 *	prepended to the name.
 *
 *  RETURN VALUE
 *      0 if no error occurred or -1 if there was a problem.
 *	if -1 is returned, errno is set appropriately.
 */
int	CapCreateUnixSocket _PROTO((char *name));

/*  ========== CapUnlinkUnixSocket ==========
 *
 *  SYNOPSIS
 *	Unlinks a unix socket and return its file descriptor
 *
 *  PARAMETERS
 *	char	*name		The file name to create.
 *
 *  DESCRIPTION
 *	This routine unlinks a unix socket.
 *	If name contains a '/' then use that name
 *	directly.  If it does not contain a '/' then "/tmp/" is
 *	prepended to the name.
 */
void CapUnlinkUnixSocket(char *name);

/*  ========== CapGetCommand ==========
 *
 *  SYNOPSIS
 *	Wait for and return the next command from the client
 *
 *  PARAMETERS
 *	int	client_fd	The socket connection to the client
 *
 *  DESCRIPTION
 *	This routine will read and return the next command from
 *	the client.  Any additional data that is passed with the
 *	command will be saved in a static area for later querying.
 *
 *  RETURN VALUE
 *	A CapCommand value
 */
CapCommand CapGetCommand _PROTO((int client_fd));

/*  ========== CapGetAuthInfo ==========
 *
 *  SYNOPSIS
 *	Return the authorization info that is in the client_query_buf
 *
 *  PARAMETERS
 *	int	client_fd	The client connection
 *	char	*user		The remote user
 *	char	*host		The remote host
 *	char	*realhost	The remote host as looked up from
 *				the address of the client connection
 *
 *  DESCRIPTION
 *	This routine returns the authorization info that is available
 *	if the current command is CAP_CMD_AUTHORIZE.
 *
 *  RETURN VALUE
 *	0 if there is no error or -1 if the last command was not
 *	CAP_CMD_AUTHORIZE.
 */
int	CapGetAuthInfo _PROTO((int client_fd, char *ruser, char *rhost,
			       char *realrhost));

/*  ========== CapInitialize ==========
 *
 *  SYNOPSIS
 *	Initialize the communications link
 *
 *  PARAMETERS
 *	int	client_fd	The client file descriptor
 *
 *  DESCRIPTION
 *	Do the initial handshake with the client and determine
 *	if the two processes can speak the same protocol.
 *
 *  RETURN VALUE
 *	0 if there is no error or -1 if there was some error.
 */
int	CapInitialize _PROTO((int client_fd, char *name));

/*  ========== CapAuthorize ==========
 *
 *  SYNOPSIS
 *	Send authorization back to the client
 *
 *  PARAMETERS
 *	int	client_fd	The client file descriptor
 *	int	authorized	The authorization flag
 *
 *  DESCRIPTION
 *	Tell the client whether he is authorized to use this server
 *	or not.
 *
 *  RETURN VALUE
 *	-1 if there was an error.  0 if everything is Ok.
 */
int	CapAuthorize _PROTO((int client_fd, int authorized));

/*  ========== CapVersion ==========
 *
 *  SYNOPSIS
 *	Send server version info to the client
 *
 *  PARAMETERS
 *	int	client_fd	The client file descriptor
 *	char	*server_name	The name of the server
 *	char	*version	The version number of the server
 *	char	*description	A 1-line description of the server
 *
 *  DESCRIPTION
 *	Send the version information to the client.
 *
 *  RETURN VALUE
 *	0 if no error occurred or -1 if there was an error.
 */
int	CapVersion _PROTO((int client_fd, char *server_name,
			   char *server_version, char *description));

/*  ========== CapInfo ==========
 *
 *  SYNOPSIS
 *	Send channel info from the server to the client.
 *
 *  PARAMETERS
 *	int	client_fd	The client file descriptor
 *
 *  DESCRIPTION
 *	Send a description of the available data from to the client
 *
 *  RETURN VALUE
 *	0 if there was no error or -1 if there was.
 */
int	CapInfo _PROTO((int client_fd, float min_rate, float max_rate,
			float def_rate, size_t buf_size, int dynamic));

/*  ========== CapGetRequestedFrame ==========
 *
 *  SYNOPSIS
 *	Return the requested frame that is in the client_query_buf
 *
 *  PARAMETERS
 *	int	client_fd	The client connection
 *
 *  DESCRIPTION
 *	This routine returns the frame number that was passed from the
 *	client with the CAP_CMD_DATA command.
 *
 *  RETURN VALUE
 *	The frame number passed in the CAP_CMD_DATA command or -1 if
 *	there is some error.
 */
int	CapGetRequestedFrame _PROTO((int client_fd));

/*  ========== CapGetRequestedTime ==========
 *
 *  SYNOPSIS
 *	Return the requested time that is in the client_query_buf
 *
 *  PARAMETERS
 *	int	client_fd	The client connection
 *
 *  DESCRIPTION
 *	This routine returns the frame number that was passed from the
 *	client with the CAP_CMD_DATA command.
 *
 *  RETURN VALUE
 *	The frame number passed in the CAP_CMD_DATA command or -1.0 if
 *	there is some error.
 */
float	CapGetRequestedTime _PROTO((int client_fd));

/*  ========== CapData ==========
 *
 *  SYNOPSIS
 *	Send the data to a client
 *
 *  PARAMETERS
 *	int	   client_fd	The client file descriptor
 *
 *  DESCRIPTION
 *	This routine sends all the saved data to the client.
 *
 *  RETURN VALUE
 *	Returns -1 for an error or 0 for no error.  If there is an
 *	error, errno is set to an appropriate value.
 */
int	CapData _PROTO((int client_fd));

/*  ========== CapSetData ==========
 *
 *  SYNOPSIS
 *	Set the data for a channel
 *
 *  PARAMETERS
 *	CapChannel channel	The channel
 *	void	   *data	A pointer to the data
 *
  *  DESCRIPTION
 *	This routine saves the data for later sending to the client.
 *	The data passed in is assumed to match the data type of the
 *	channel.
 *
 *  RETURN VALUE
 *	Returns -1 for an error or 0 for no error.  If there is an
 *	error, errno is set to an appropriate value.
 */
int	CapSetData _PROTO((CapChannel channel, void *data));

/*  ========== CapStartRecord ==========
 *
 *  SYNOPSIS
 *	Start recording
 *
 *  PARAMETERS
 *	int	   client_fd	The client file descriptor
 *	int	   sample_rate	The samples per second
 *
 *  DESCRIPTION
 *	This routine allocates space for recorded data and
 *	tells the client what the sample rate will be
 *
 *  RETURN VALUE
 *	Returns -1 for an error or 0 for no error.  If there is an
 *	error, errno is set to an appropriate value.
 */
int	CapStartRecord _PROTO((int client_fd, float sample_rate,
			       size_t buf_size));
                   
int	CapRecord _PROTO((int client_fd, float time));

/*  ========== CapStopRecord ==========
 *
 *  SYNOPSIS
 *	Stop recording and send the recorded data to the client
 *
 *  PARAMETERS
 *	int	   client_fd	The client file descriptor
 *
 *  DESCRIPTION
 *	This routine transmits the recorded data to the client
 *
 *  RETURN VALUE
 *	Returns -1 for an error or 0 for no error.  If there is an
 *	error, errno is set to an appropriate value.
 */
int	CapStopRecord _PROTO((int client_fd));

/*  ========== CapCreateChannel ==========
 *
 *  SYNOPSIS
 *	Create a new channel and add it to the channel hierarchy
 *
 *  PARAMETERS
 *	char       *name	The new channel's name
 *	CapChannelUsage usage	How the channel's data is to be used
 *	int	    data_type	The type of the channel (1, 3, 4, 6, or 7)
 *
 *  DESCRIPTION
 *	This routine creates a new channel in the channel hierarchy
 *	and returns a handle to the new channel.
 *
 *  RETURN VALUE
 *	The handle for the newly created handle or NULL if there was
 *	some error.
 */
CapChannel CapCreateChannel _PROTO((char *name, CapChannelUsage usage,
				    int data_type));
                    
/*  ========== CapGetRequestedRecordRate ==========
 *
 *  SYNOPSIS
 *	Return the record sample rate provided by the client
 *
 *  PARAMETERS
 *	int	client_fd	The client connection
 *
 *  DESCRIPTION
 *	This routine returns the sample rate that was passed from the
 *	client with the CAP_CMD_START_RECORD command.
 *
 *  RETURN VALUE
 *	The sample rate passed in the CAP_CMD_START_RECORD command or -1.0 if
 *	there is some error.
 */
float	CapGetRequestedRecordRate _PROTO((int client_fd));

/*  ========== CapGetRequestedRecordSize ==========
 *
 *  SYNOPSIS
 *	Return the record buffer size provided by the client
 *
 *  PARAMETERS
 *	int	client_fd	The client connection
 *
 *  DESCRIPTION
 *	This routine returns the buffer size that was passed from the
 *	client with the CAP_CMD_START_RECORD command.
 *
 *  RETURN VALUE
 *	The buffer size passed in the CAP_CMD_START_RECORD command or 1 if
 *	there is some error.
 */
int	CapGetRequestedRecordSize _PROTO((int client_fd));

#define EXPAND_ERROR_BUF 256

/*
 *  ========== CapExpandFilename ==========
 *
 *  SYNOPSIS
 *	Expand any environment variables or ~[user] in a filepath
 *
 *  PARAMETERS
 *	char *in_name		the incoming path
 *	char *out_name		the outgoing path  - the caller
 *				must ensure that out_name points to
 *				enough space to hold the expanded result
 *				(MAXPATHLEN, defined in sys/param.h).
 *
 *  DESCRIPTION
 *	CapExpandFilename does the following:
 *	1.  On Unix, look for a ~[username] at the start of in_name,
 *	    which is expanded to the login directory for that user.
 *	2.  Expand any environment variables.  They can be
 *	    anywhere in the in_name, are started with a $, and
 *	    ended with a / or end-of-string.
 *
 *  RETURN VALUE
 *	a pointer to out_name on success
 *	
 *	If the routine fails, the routine returns NULL and
 *	the global string CapExpandErrorMsg contains
 *	the reason for failure. 
 */
extern char   CapExpandErrorMsg[EXPAND_ERROR_BUF];
char   *CapExpandFilename _PROTO((const char *in_name, char *out_name));

/*************************************/
/*          Math functions           */
/*************************************/

/*  ========== CapQuat2Euler ==========
 *
 *  SYNOPSIS
 *	Convert a quaternion to Euler angles.
 *
 *  PARAMETERS
 *	CapRotationOrder	 order	The order of rotations
 *	CapQuaternion		 q      The quaternion
 *	float               *x	The x-rotation
 *	float               *y	The y-rotation
 *	float               *z	The z-rotation
 *
 *  DESCRIPTION
 *	This routine converts a quaternion to Euler angles.
 *
 *	The quaternion is assumed to be a unit quaternion stored
 *	in w, x, y, z order.
 */
void	CapQuat2Euler _PROTO((CapRotationOrder order, CapQuaternion q,
			      float *x, float *y, float *z));
                  
/*  ========== CapEuler2Quat ==========
 *
 *  SYNOPSIS
 *	Convert Euler angles to a quaternion
 *
 *  PARAMETERS
 *	CapRotationOrder    order	The rotation order
 *	float               x	The x-rotation in radians
 *	float               y	The y-rotation in radians
 *	float               z	The z-rotation in radians
 *	CapQuaternion       q	The quaternion
 *
 *  DESCRIPTION
 *	This routine converts the Euler angles (in the given order)
 *	to a quaternion.
 */
void	CapEuler2Quat _PROTO((CapRotationOrder order, float x, float y,
			      float z, CapQuaternion q));

/*  ========== CapQuat2Matrix ==========
 *
 *  SYNOPSIS
 *	Convert a quaternion to a 4x4 matrix
 *
 *  PARAMETERS
 *	CapQuaternion       q	The quaternion
 *	CapMatrix           m	The matrix
 *
 *  DESCRIPTION
 *	This routine converts a quaternion to a matrix.
 */
void	CapQuat2Matrix _PROTO((CapQuaternion q, CapMatrix m));

/*  ========== CapMatrix2Quat ==========
 *
 *  SYNOPSIS
 *	Convert (the orientation part of) a 4x4 matrix to a quaternion
 *
 *  PARAMETERS
 *	CapMatrix           m	The matrix
 *	CapQuaternion       q	The quaternion
 *
 *  DESCRIPTION
 *	This routine takes the upper-left 3x3 submatrix from a 4x4 and
 *	converts it to a quaternion.
 */
 void	CapMatrix2Quat _PROTO((CapMatrix m, CapQuaternion q));

/*  ========== CapQuat2Matrix3 ==========
 *
 *  SYNOPSIS
 *	Convert a quaternion to a 3x3 matrix
 *
 *  PARAMETERS
 *	CapQuaternion       q	The quaternion
 *	CapMatrix3          m	The matrix
 *
 *  DESCRIPTION
 *	This routine converts a quaternion to a 3x3 matrix.
 */
void	CapQuat2Matrix3 _PROTO((CapQuaternion q, CapMatrix3 m));

/*  ========== CapMatrix32Quat ==========
 *
 *  SYNOPSIS
 *	Convert a 3x3 matrix to a quaternion
 *
 *  PARAMETERS
 *	CapMatrix3          m	The 3x3 matrix
 *	CapQuaternion       q	The quaternion
 *
 *  DESCRIPTION
 *	This routine converts a 3x3 rotation matrix to a quaternion.
 */
void	CapMatrix32Quat _PROTO((CapMatrix3 m, CapQuaternion q));

/*  ========== CapQuatMult ==========
 *
 *  SYNOPSIS
 *	Multiply 2 quaternions
 *
 *  PARAMETERS
 *	CapQuaternion		 q1	A quaternion
 *	CapQuaternion		 q2	A quaternion
 *	CapQuaternion		 q0	The result
 *
 *  DESCRIPTION
 *	This routine creates a composite quaternion that is equivalent
 *	to rotating by q2, then q1.
 */
void	CapQuatMult _PROTO((CapQuaternion q1, CapQuaternion q2,
			    CapQuaternion q0));

/*  ========== CapQuatRotate ==========
 *
 *  SYNOPSIS
 *	Rotate a vector by a quaternion
 *
 *  PARAMETERS
 *	CapQuaternion	  q		The quaternion
 *	CapPosition	  p		The point
 *	CapPosition	  r		The result
 *
 *  DESCRIPTION
 *	This routine rotates the point p by the quaternion q and stores
 *	the result in r.
 *
 *  NOTES
 *	This assumes that the quaternion q is normalized
 */
void	CapQuatRotate _PROTO((CapQuaternion q, CapPosition p,
			      CapPosition r));

/*  ========== CapQuatMagnitude ==========
 *
 *  SYNOPSIS
 *	Return the magnitude of a quaternion
 *
 *  PARAMETERS
 *	CapQuaternion		 q	The quaternion
 *
 *  RETURN VALUE
 *	The magnitude of the quaternion.
 *
 *  DESCRIPTION
 *	This routine returns the magnitude of a quaternion.
 */
float	CapQuatMagnitude _PROTO((CapQuaternion q));

/*  ========== CapQuatNormalize ==========
 *
 *  SYNOPSIS
 *	Normalize the quaternion
 *
 *  PARAMETERS
 *	CapQuaternion     q		The quaternion
 *
 *  DESCRIPTION
 *	This routine normalizes a quaternion in place.
 */
void	CapQuatNormalize _PROTO((CapQuaternion q, CapQuaternion qn));

/*  ========== CapQuatInvert ==========
 *
 *  SYNOPSIS
 *	Invert a quaternion
 *
 *  PARAMETERS
 *	CapQuaternion     q		The quaternion
 *	CapQuaternion     qi		The inverse quaternion
 *
 *  DESCRIPTION
 *	This routine returns the invers of a quaternion.  The quaternion
 *	does not have to be normalized.
 */
void	CapQuatInvert _PROTO((CapQuaternion q, CapQuaternion qi));

/*  ========== CapEuler2Matrix ==========
 *
 *  SYNOPSIS
 *	Convert Euler angles to a matrix
 *
 *  PARAMETERS
 *	CapRotationOrder  order		The rotation order
 *	float		  x		The x-rotation
 *	float		  y		The y-rotation
 *	float		  z		The z-rotation
 *	CapMatrix	  m		The matrix
 *
 *  DESCRIPTION
 *	This routine converts the Euler angles (in the given order)
 *	to a matrix.
 */
void	CapEuler2Matrix _PROTO((CapRotationOrder order, float x, float y,
				float z, CapMatrix m));
                
/*  ========== CapEuler2Matrix3 ==========
 *
 *  SYNOPSIS
 *	Convert Euler angles to a 3x3 matrix
 *
 *  PARAMETERS
 *	CapRotationOrder  order		The rotation order
 *	float		  x		The x-rotation
 *	float		  y		The y-rotation
 *	float		  z		The z-rotation
 *	CapMatrix3	  m		The 3x3 matrix
 *
 *  DESCRIPTION
 *	This routine converts the Euler angles (in the given order)
 *	to a 3x3 matrix.
 */
void	CapEuler2Matrix3 _PROTO((CapRotationOrder order, float x, float y,
				 float z, CapMatrix3 m));

/*  ========== CapMatrix2Euler ==========
 *
 *  SYNOPSIS
 *	Convert a matrix to Euler angles.
 *
 *  PARAMETERS
 *	CapRotationOrder	 ord	The order of rotations
 *	CapMatrix		 m	The matrix
 *	float			*x	The x-rotation
 *	float			*y	The y-rotation
 *	float			*z	The z-rotation
 *
 *  DESCRIPTION
 *	This routine converts a matrix to Euler angles.
 */
void	CapMatrix2Euler _PROTO((CapRotationOrder ord, CapMatrix m,
				float *x, float *y, float *z));

/*  ========== CapMatrix32Euler ==========
 *
 *  SYNOPSIS
 *	Convert a 3x3 matrix to Euler angles.
 *
 *  PARAMETERS
 *	CapRotationOrder	 ord	The order of rotations
 *	CapMatrix3		 m	The 3x3 matrix
 *	float			*x	The x-rotation
 *	float			*y	The y-rotation
 *	float			*z	The z-rotation
 *
 *  DESCRIPTION
 *	This routine converts a matrix to Euler angles.
 */
void	CapMatrix32Euler _PROTO((CapRotationOrder ord, CapMatrix3 m,
				 float *x, float *y, float *z));

#if defined(__cplusplus)
}
#endif

#endif /* __CAPSERVER_H__ */
