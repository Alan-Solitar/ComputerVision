#pragma once

#ifndef COMPUTER_VISION_BINARY_IMAGE_H_
#define COMPUTER_VISION_BINARY_IMAGE_H_

#include "Image.h"
using namespace ComputerVisionProjects;

	class BinaryImage :public Image
	{

	public:
		size_t threshold;
		void ConvertToBinary(size_t thresholdVar)
		{
			threshold = thresholdVar;
			for (int i = 0; i < num_rows_; ++i) {
				for (int j = 0; j < num_columns_; ++j) {
					if (GetPixel(i, j) > threshold)
						SetPixel(i, j, 1);
					else
						SetPixel(i, j, 0);
				}
			}

		}

	};


#endif
