#ifndef GETCAMDEVICE_H
#define GETCAMDEVICE_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <libv4l2.h>
#include <iostream>

#define N_CAMERAS 1

// Can onlyh do MJPG at this point.
#define MJPG
// which IO method is in use.
enum io_method
  {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
  };

// a data structure to keep track of buffer allocation.
typedef struct buffer
{
  unsigned char   *start;
  size_t  length;
}
  BUFFER;

// a data structure to keep track of cameras
typedef struct camera
{
  int id;
  char *dev_name;
  int fd;
  BUFFER *buffers;
  unsigned int n_buffers;
  enum io_method io;
  struct v4l2_format fmt;
  struct timeval current_time;
  struct timeval last_time;
  long int usec_diff;
  int n_frames;
}
  CAMERA;

// packet types
#define ACC_GYRO_TEMP 2
#define IMAGE_JPG 3

unsigned int packet_count = 0;
unsigned int frame_count = 0;

int skipped_first_frame = 0;

typedef struct packet_header
{
  unsigned int header_size; // what size is the header
  unsigned int version; // what version of software are we assuming?
  unsigned int packet_type; // what kind of packet is this?
  unsigned int channel; // what is this data stream?
  unsigned int n_data_bytes; // number of bytes of data in packet after header
  unsigned int n_bytes; // how big is this object in total?
  unsigned int n_packets; // how many UDP packets is this object broken into?
  unsigned int packet_index; // which packet is this?
  unsigned int byte_index; // which byte does this packet start at.
  unsigned int packet_count; // how many packets so far.
  unsigned int usec_diff; // interval between last frame and this one.
  unsigned int blank0; // Handle compiler differences.
  unsigned int blank1; //
  unsigned int blank2; //
  struct timeval time_stamp; // time stamp of frame.
}
  HEADER;

/**********************************************************************/
/**********************************************************************/
// Globals
/**********************************************************************/
/**********************************************************************/

CAMERA camera[ N_CAMERAS ];

// info to send a packet
//char *remote_ip_address;
//struct sockaddr_in remote_addr, my_addr;
//int addr_len = sizeof( remote_addr );
//int sockfd;

/**********************************************************************/
/**********************************************************************/
// Utilities
/**********************************************************************/
/********************************************************************/

void err(char *s)
{
    perror(s);
    exit(1);
}
static void errno_exit(const char *s)
{
  fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
  exit(EXIT_FAILURE);
}


static void close_device( CAMERA *pcam )
{
        if ( -1 == close( pcam->fd ) )
      errno_exit("close");

        pcam->fd = -1;
}

/**********************************************************************/

static int open_device( CAMERA *pcam )
{
  struct stat st;

  if ( -1 == stat( pcam->dev_name, &st ) )
    {
      fprintf(stderr, "Cannot identify '%s': %d, %s\n",
          pcam->dev_name, errno, strerror(errno) );
      return 2;
      //exit(EXIT_FAILURE);
    }

  if (!S_ISCHR(st.st_mode))
    {
      fprintf( stderr, "%s is no device\n", pcam->dev_name );
      return 3;
      //exit(EXIT_FAILURE);
    }

  // fd = open(pcam->dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);
  // try blocking DQBUF
  pcam->fd = open(pcam->dev_name, O_RDWR /* required */ /* | O_NONBLOCK */, 0);

  if (-1 == pcam->fd)
    {
      fprintf(stderr, "Cannot open '%s': %d, %s\n",
          pcam->dev_name, errno, strerror(errno));
      return 4;
      //exit(EXIT_FAILURE);
    }
  return 1;
}

static int xioctl(int fh, int request, void *arg)
{
  int r;

  do
    {
      r = ioctl(fh, request, arg);
    }
  while (-1 == r && EINTR == errno);

  return r;
}


std::string  get_cameraName(int camId )
{
    struct v4l2_capability cap = {0};
    char vpath[11] ="/dev/video";
     char ch = (char) (camId%10)+48;
    vpath[10] = (char) (camId%10)+48;
      char  *mymessage;
       char  *camName;

    camera[camId].id = camId;
    camera[camId].fd = -1;
    camera[camId].buffers = NULL;
    camera[camId].n_buffers = 0;
    camera[camId].io = IO_METHOD_MMAP;
    camera[camId].dev_name = (char *) "xxx";
    camera[camId].n_frames = 0;
    camera[camId].dev_name = (char *) "/dev/video0";

    if ( camId >= 1 )
      camera[1].dev_name = (char *) "/dev/video1";
    if ( camId > 2 )
      camera[2].dev_name = (char *) "/dev/video2";
    if ( camId > 3 )
      camera[3].dev_name = (char *) "/dev/video3";
    if ( camId > 4 )
      camera[4].dev_name = (char *) "/dev/video4";
    if ( camId > 5 )
      camera[5].dev_name = (char *) "/dev/video5";
    if ( camId > 6 )
      camera[6].dev_name = (char *) "/dev/video6";
    if ( camId > 7 )
      camera[7].dev_name = (char *) "/dev/video7";
    if ( camId > 8 )
      camera[8].dev_name = (char *) "/dev/video8";

    //printf( "\n\nCamera: %d %s\n", camera[camId].id, camera[camId].dev_name );

     if(open_device(&camera[camId]) > 1)
    {
         const char *msg ="Camera not found";
         mymessage = ( char *) malloc(sizeof(char)* (strlen((const char *) msg)));
         memcpy((void*)mymessage,(void*)msg,strlen((const char *) msg));

         return mymessage;
     }




    if (-1 == xioctl( camera[camId].fd, VIDIOC_QUERYCAP, &cap))
      {
        if (EINVAL == errno)
      {
        fprintf( stderr, "%s is not a V4L2 device\n", camera[camId].dev_name );
        exit(EXIT_FAILURE);
      }
        else
      {
        errno_exit( "VIDIOC_QUERYCAP" );
      }
      }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
      {
        fprintf(stderr, "%s is not a video capture device\n",
            camera[camId].dev_name);
        exit(EXIT_FAILURE);
      }

    printf( "\ndriver: %s\n", cap.driver );
    printf( "card: %s\n", cap.card );
    printf( "bus_info: %s\n", cap.bus_info );
    printf ("version: %u.%u.%u\n",
        (cap.version >> 16) & 0xFF,
        (cap.version >> 8) & 0xFF,
        cap.version & 0xFF);
    printf("%s\n", cap.card);
    close_device(&camera[camId]);

    char *cam;
   mymessage = ( char *) malloc(sizeof(char)* (strlen((const char *) cap.card)));
   memcpy((void*)mymessage,(void*)cap.card,strlen((const char *) cap.card));
   auto x1 = [&](){ int i=0; for(i =0; i< strlen((const char*)mymessage);i++ ) {  if( mymessage[i] ==':') { break; }  }  return i; };
   int x = x1();
   cam = ( char *) malloc(sizeof(char)* ( strlen((const char *) cap.card)-x ));
   strncpy((char *)cam,(const char *)mymessage+x+2,strlen((const char*)mymessage));
   std::string usbCamnm {cam};
   free(mymessage);

   return  usbCamnm;
    //return  cap.card;
}


#endif // GETCAMDEVICE_H
