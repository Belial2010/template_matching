#ifndef CONTROLDICT_H
#define CONTROLDICT_H

/* if true apply gaussian stencil to images ( main and templates) */
#define GAUSSIAN_FLAG 0
/* if true rotation and scaling will use bilinear interpolation, else nearest neighbour */
#define INTERPOLATE_FLAG 0
#define INTERPOLATE_CORR_FLAG 0

#define SHOW_FILTERS 1

#define FRAME_TARGET 1

#define _DEBUG 0

/* luminance correlation coef */
static const float _alpha_ = 0.8f;
/* chromaticy correlation coef */
static const float _beta_ = 0.2f;

/* CIRCULAR SAMPLING FILTER SETTINGS */
/* rate of scale sampling */
static const float scaling_step_delta = 0.1f;

static const unsigned int circle_start = 0;
static const unsigned int circle_step_delta = 3;
/* threshold for first grade candidate pixels */
static const float th1 = 0.95f;

/* RADIAL SAMPLING FILTER SETTINGS */
/* rate of angle sampling */
//static const unsigned int rotation_step_count = 72;
static const unsigned int rotation_step_count = 72;
static const float rotation_start = 0.f;
static const float rotation_end = 360.f; /* not including this value */
/* threshold for second grade candidate pixels */
//static const float th2 = 0.8f;
static const float th2 = 0.75f;

/* threshold for last filter */
//static const float th3 = 0.54f;
static const float th3 = 0.95f;

#endif // CONTROLDICT_H
