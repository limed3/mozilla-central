/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "vad_unittest.h"

#include <stdlib.h>

#include "common_audio/signal_processing/include/signal_processing_library.h"
#include "gtest/gtest.h"
#include "typedefs.h"
#include "webrtc_vad.h"

VadTest::VadTest() {}

void VadTest::SetUp() {}

void VadTest::TearDown() {}

// Returns true if the rate and frame length combination is valid.
bool VadTest::ValidRatesAndFrameLengths(int16_t rate, int16_t frame_length) {
  if (rate == 8000) {
    if (frame_length == 80 || frame_length == 160 || frame_length == 240) {
      return true;
    }
    return false;
  } else if (rate == 16000) {
    if (frame_length == 160 || frame_length == 320 || frame_length == 480) {
      return true;
    }
    return false;
  }
  if (rate == 32000) {
    if (frame_length == 320 || frame_length == 640 || frame_length == 960) {
      return true;
    }
    return false;
  }

  return false;
}

namespace {

TEST_F(VadTest, ApiTest) {
  // This API test runs through the APIs for all possible valid and invalid
  // combinations.

  VadInst* handle = NULL;
  int16_t zeros[kMaxFrameLength] = { 0 };

  // Construct a speech signal that will trigger the VAD in all modes. It is
  // known that (i * i) will wrap around, but that doesn't matter in this case.
  int16_t speech[kMaxFrameLength];
  for (int16_t i = 0; i < kMaxFrameLength; i++) {
    speech[i] = (i * i);
  }

  // NULL instance tests
  EXPECT_EQ(-1, WebRtcVad_Create(NULL));
  EXPECT_EQ(-1, WebRtcVad_Init(NULL));
  EXPECT_EQ(-1, WebRtcVad_Assign(NULL, NULL));
  EXPECT_EQ(-1, WebRtcVad_Free(NULL));
  EXPECT_EQ(-1, WebRtcVad_set_mode(NULL, kModes[0]));
  EXPECT_EQ(-1, WebRtcVad_Process(NULL, kRates[0], speech, kFrameLengths[0]));

  // WebRtcVad_AssignSize() test.
  size_t handle_size_bytes = WebRtcVad_AssignSize();
  EXPECT_EQ(576u, handle_size_bytes);

  // WebRtcVad_Assign() tests.
  void* tmp_handle = malloc(handle_size_bytes);
  EXPECT_EQ(-1, WebRtcVad_Assign(NULL, &handle));
  EXPECT_EQ(-1, WebRtcVad_Assign(tmp_handle, NULL));
  EXPECT_EQ(0, WebRtcVad_Assign(tmp_handle, &handle));
  EXPECT_EQ(handle, tmp_handle);
  free(tmp_handle);

  // WebRtcVad_Create()
  ASSERT_EQ(0, WebRtcVad_Create(&handle));

  // Not initialized tests
  EXPECT_EQ(-1, WebRtcVad_Process(handle, kRates[0], speech, kFrameLengths[0]));
  EXPECT_EQ(-1, WebRtcVad_set_mode(handle, kModes[0]));

  // WebRtcVad_Init() test
  ASSERT_EQ(0, WebRtcVad_Init(handle));

  // WebRtcVad_set_mode() invalid modes tests. Tries smallest supported value
  // minus one and largest supported value plus one.
  EXPECT_EQ(-1, WebRtcVad_set_mode(handle,
                                   WebRtcSpl_MinValueW32(kModes,
                                                         kModesSize) - 1));
  EXPECT_EQ(-1, WebRtcVad_set_mode(handle,
                                   WebRtcSpl_MaxValueW32(kModes,
                                                         kModesSize) + 1));

  // WebRtcVad_Process() tests
  // NULL speech pointer
  EXPECT_EQ(-1, WebRtcVad_Process(handle, kRates[0], NULL, kFrameLengths[0]));
  // Invalid sampling rate
  EXPECT_EQ(-1, WebRtcVad_Process(handle, 9999, speech, kFrameLengths[0]));
  // All zeros as input should work
  EXPECT_EQ(0, WebRtcVad_Process(handle, kRates[0], zeros, kFrameLengths[0]));
  for (size_t k = 0; k < kModesSize; k++) {
    // Test valid modes
    EXPECT_EQ(0, WebRtcVad_set_mode(handle, kModes[k]));
    // Loop through sampling rate and frame length combinations
    for (size_t i = 0; i < kRatesSize; i++) {
      for (size_t j = 0; j < kFrameLengthsSize; j++) {
        if (ValidRatesAndFrameLengths(kRates[i], kFrameLengths[j])) {
          EXPECT_EQ(1, WebRtcVad_Process(handle,
                                         kRates[i],
                                         speech,
                                         kFrameLengths[j]));
        } else {
          EXPECT_EQ(-1, WebRtcVad_Process(handle,
                                          kRates[i],
                                          speech,
                                          kFrameLengths[j]));
        }
      }
    }
  }

  EXPECT_EQ(0, WebRtcVad_Free(handle));
}

// TODO(bjornv): Add a process test, run on file.

}  // namespace
