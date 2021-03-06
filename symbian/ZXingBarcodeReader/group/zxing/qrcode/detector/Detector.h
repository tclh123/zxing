#ifndef __DETECTOR_H__
#define __DETECTOR_H__

/*
 *  Detector.h
 *  zxing
 *
 *  Created by Christian Brunschen on 14/05/2008.
 *  Copyright 2008 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/common/Counted.h>
#include <zxing/common/DetectorResult.h>
#include <zxing/common/BitMatrix.h>
#include <zxing/qrcode/detector/AlignmentPattern.h>
#include <zxing/common/PerspectiveTransform.h>

namespace zxing {
namespace qrcode {

class Detector : public Counted {
private:
  Ref<BitMatrix> image_;

protected:
  Ref<BitMatrix> getImage();

  static Ref<BitMatrix> sampleGrid(Ref<BitMatrix> image, int dimension, Ref<PerspectiveTransform>);
  static int computeDimension(Ref<ResultPoint> topLeft, Ref<ResultPoint> topRight, Ref<ResultPoint> bottomLeft,
                              float moduleSize);
  float calculateModuleSize(Ref<ResultPoint> topLeft, Ref<ResultPoint> topRight, Ref<ResultPoint> bottomLeft);
  float calculateModuleSizeOneWay(Ref<ResultPoint> pattern, Ref<ResultPoint> otherPattern);
  float sizeOfBlackWhiteBlackRunBothWays(int fromX, int fromY, int toX, int toY);
  float sizeOfBlackWhiteBlackRun(int fromX, int fromY, int toX, int toY);
  Ref<AlignmentPattern> findAlignmentInRegion(float overallEstModuleSize, int estAlignmentX, int estAlignmentY,
      float allowanceFactor);
public:

  virtual Ref<PerspectiveTransform> createTransform(Ref<ResultPoint> topLeft, Ref<ResultPoint> topRight, Ref <
      ResultPoint > bottomLeft, Ref<ResultPoint> alignmentPattern, int dimension);

  Detector(Ref<BitMatrix> image);
  Ref<DetectorResult> detect();
};
}
}

#endif // __DETECTOR_H__
