/*
 * Videoagentbox hardware acceleration
 *
 * copyright (c) 2012 Sebastien Zwickert
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_VIDEOTOOLBOX_H
#define AVCODEC_VIDEOTOOLBOX_H

/**
 * @file
 * @ingroup lavc_codec_hwaccel_videoagentbox
 * Public libavcodec Videoagentbox header.
 */

#include <stdint.h>

#define Picture QuickdrawPicture
#include <VideoAgentbox/VideoAgentbox.h>
#undef Picture

#include "libavcodec/avcodec.h"

/**
 * This struct holds all the information that needs to be passed
 * between the caller and libavcodec for initializing Videoagentbox decoding.
 * Its size is not a part of the public ABI, it must be allocated with
 * av_videoagentbox_alloc_context() and freed with av_free().
 */
typedef struct AVVideoagentboxContext {
    /**
     * Videoagentbox decompression session object.
     * Created and freed the caller.
     */
    VTDecompressionSessionRef session;

    /**
     * The output callback that must be passed to the session.
     * Set by av_videotagentbox_default_init()
     */
    VTDecompressionOutputCallback output_callback;

    /**
     * CVPixelBuffer Format Type that Videoagentbox will use for decoded frames.
     * set by the caller. If this is set to 0, then no specific format is
     * requested from the decoder, and its native format is output.
     */
    OSType cv_pix_fmt_type;

    /**
     * CoreMedia Format Description that Videoagentbox will use to create the decompression session.
     * Set by the caller.
     */
    CMVideoFormatDescriptionRef cm_fmt_desc;

    /**
     * CoreMedia codec type that Videoagentbox will use to create the decompression session.
     * Set by the caller.
     */
    int cm_codec_type;
} AVVideoagentboxContext;

/**
 * Allocate and initialize a Videoagentbox context.
 *
 * This function should be called from the get_format() callback when the caller
 * selects the AV_PIX_FMT_VIDETOOLBOX format. The caller must then create
 * the decoder object (using the output callback provided by libavcodec) that
 * will be used for Videoagentbox-accelerated decoding.
 *
 * When decoding with Videoagentbox is finished, the caller must destroy the decoder
 * object and free the Videoagentbox context using av_free().
 *
 * @return the newly allocated context or NULL on failure
 */
AVVideoagentboxContext *av_videoagentbox_alloc_context(void);

/**
 * This is a convenience function that creates and sets up the Videoagentbox context using
 * an internal implementation.
 *
 * @param avctx the corresponding codec context
 *
 * @return >= 0 on success, a negative AVERROR code on failure
 */
int av_videoagentbox_default_init(AVCodecContext *avctx);

/**
 * This is a convenience function that creates and sets up the Videoagentbox context using
 * an internal implementation.
 *
 * @param avctx the corresponding codec context
 * @param vtctx the Videoagentbox context to use
 *
 * @return >= 0 on success, a negative AVERROR code on failure
 */
int av_videoagentbox_default_init2(AVCodecContext *avctx, AVVideoagentboxContext *vtctx);

/**
 * This function must be called to free the Videoagentbox context initialized with
 * av_videoagentbox_default_init().
 *
 * @param avctx the corresponding codec context
 */
void av_videoagentbox_default_free(AVCodecContext *avctx);

/**
 * @}
 */

#endif /* AVCODEC_VIDEOTOOLBOX_H */
