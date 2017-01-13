/*
 * Ryan Welling and James Lundgren 
 * Date: 3/3/2015
 * 
 * This class completes the encoding for an .mpff AV codec in ffmpeg 
 * The structure is based off of the BMP image format encoder. 
 * 
 * Copyright (c) 2006, 2007 Michel Bardiaux
 * Copyright (c) 2009 Daniel Verkamp <daniel at drv.nu>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "libavutil/imgutils.h"
#include "libavutil/avassert.h"
#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"


/**
 *
 * Initializes the encoding of an image into the mpff 
 * format. Sets the number of bits used to represent a 
 * pixel bassed off of its original format
 */
static av_cold int mpff_encode_init(AVCodecContext *avctx){
  
  // Set the bits per sample based off of the original image format
  switch (avctx->pix_fmt) 
  {
    case AV_PIX_FMT_BGR24:
      avctx->bits_per_coded_sample = 24;
      break;
    default:
      av_log(avctx, AV_LOG_INFO, "unsupported pixel format\n");
      return AVERROR(EINVAL);
  }
  
  // Allocate memory for our new mpff file 
  avctx->coded_frame = av_frame_alloc();
  if (!avctx->coded_frame)
    return AVERROR(ENOMEM);
  
  return 0;
}

/**
 *
 * Where the encoding takes place. We need to supply the necessary 
 * information in the header so that the image can be decoded 
 * properly. After the header/information header are written, we 
 * can begin encoding the file as an mpff.
 *
 */
static int mpff_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *pict, int *got_packet)
{
    
  const AVFrame * const p = pict;
  int n_bytes_image, n_bytes_per_row, n_bytes, i, hsize, ret; // n was unused as is
  int pad_bytes_per_row; 
  int bit_count = avctx->bits_per_coded_sample;
  uint8_t *ptr, *buf;
  
  // 
  //    avctx->width = avctx->width/2;
  //    avctx->height = avctx->height/2;
  
  // Need to set pict_type and set picture as a key frame 
  avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
  avctx->coded_frame->key_frame = 1;
  
  
  // calculate how many bytes per row we need, what the padding will be to make
  // the image fall on an convenient memory boundary, and how many total bytes we 
  // need for the image
  n_bytes_per_row = ((int64_t)avctx->width * (int64_t)bit_count + 7LL) >> 3LL;
  pad_bytes_per_row = (4 - n_bytes_per_row) & 3;
  n_bytes_image = avctx->height * (n_bytes_per_row + pad_bytes_per_row);
  
  

#define SIZE_MPFFFILEHEADER 12
#define SIZE_MPFFINFOHEADER 26

  // Header size is fileheader + infoheader, total bytes is header + image size 
  hsize = SIZE_MPFFFILEHEADER + SIZE_MPFFINFOHEADER;
  n_bytes = n_bytes_image + hsize;
  
  // Allocate memory for the packets 
  if ((ret = ff_alloc_packet2(avctx, pkt, n_bytes)) < 0)
    return ret;

  // Point to the image data so we can add the file/info header to it 
  buf = pkt->data;
  
  /*------ Begin writing the header -------*/
 
  bytestream_put_byte(&buf, 'M');                   // MPFFFILEHEADER.bfType
  bytestream_put_byte(&buf, 'P');
  bytestream_put_byte(&buf, 'F');                   // MPFFFILEHEADER.bfType
  bytestream_put_byte(&buf, 'F');                   // do.
  bytestream_put_le32(&buf, n_bytes);               // MPFFFILEHEADER.bfSize
  //bytestream_put_le16(&buf, 0);                     // MPFFFILEHEADER.bfReserved1
  //bytestream_put_le16(&buf, 0);                     // MPFFFILEHEADER.bfReserved2
  bytestream_put_le32(&buf, hsize);                 // MPFFFILEHEADER.bfOffBits
  bytestream_put_le32(&buf, SIZE_MPFFINFOHEADER); // BITMAPINFOHEADER.biSize
  bytestream_put_le32(&buf, avctx->width);          // MPFFINFOHEADER.biWidth
  bytestream_put_le32(&buf, avctx->height);         // MPFFINFOHEADER.biHeight
  //bytestream_put_le16(&buf, 1);                     // MPFFINFOHEADER.biPlanes
  bytestream_put_le16(&buf, bit_count);             // MPFFINFOHEADER.biBitCount
  //bytestream_put_le32(&buf, compression);           // MPFFINFOHEADER.biCompression
  bytestream_put_le32(&buf, n_bytes_image);         // MPFFINFOHEADER.biSizeImage
  // bytestream_put_le32(&buf, 0);                     // MPFFINFOHEADER.biXPelsPerMeter
  // bytestream_put_le32(&buf, 0);                     // MPFFINFOHEADER.biYPelsPerMeter
  bytestream_put_le32(&buf, 0);                     // MPFFINFOHEADER.biClrUsed
  bytestream_put_le32(&buf, 0);                     // MPFFINFOHEADER.biClrImportant
   
  /*------ End of writing the header -------*/
  
  // BMP files are bottom-to-top so we start from the end...
  ptr = p->data[0] + (avctx->height - 1) * p->linesize[0];
  buf = pkt->data + hsize;

  // Loop through each row of the the picture and write it to the mpff file 
  for(i = 0; i < avctx->height; i++) {
    memcpy(buf, ptr, n_bytes_per_row);
    buf += n_bytes_per_row;
    memset(buf, 0, pad_bytes_per_row);
    buf += pad_bytes_per_row;
    ptr -= p->linesize[0]; // ... and go back
  }
  
  pkt->flags |= AV_PKT_FLAG_KEY;
  *got_packet = 1;
  return 0;
}


/**
 * 
 * Called when the encoding is done, frees the memory 
 * allocated in order to encode the image. 
 *
 */
static av_cold int mpff_encode_close(AVCodecContext *avctx)
{
  av_frame_free(&avctx->coded_frame);
  return 0;
}


AVCodec ff_mpff_encoder = {
  .name           = "mpff",
  .long_name      = NULL_IF_CONFIG_SMALL("MPFF (Windows and OS/2 bitmap)"),
  .type           = AVMEDIA_TYPE_VIDEO,
  .id             = AV_CODEC_ID_MPFF,
  .init           = mpff_encode_init,
  .encode2        = mpff_encode_frame,
  .close          = mpff_encode_close,
  .pix_fmts       = (const enum AVPixelFormat[]){
    AV_PIX_FMT_BGR24,
    AV_PIX_FMT_NONE
  },
};



