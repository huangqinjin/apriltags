#ifndef TAGDETECTOR_H
#define TAGDETECTOR_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include "AprilTags/TagDetection.h"
#include "AprilTags/TagFamily.h"
#include "AprilTags/FloatImage.h"

namespace AprilTags {

class TagDetector {
public:
	
	const TagFamily thisTagFamily;

	//! Constructor
  // note: TagFamily is instantiated here from TagCodes
	TagDetector(const TagCodes& tagCodes, int blackBorder = 1) : thisTagFamily(tagCodes, blackBorder) {}
    TagDetector(const TagFamily& tagFamily) : thisTagFamily(tagFamily) {}
	
	std::vector<TagDetection> extractTags(const cv::Mat& image);
	
};

} // namespace

#endif
