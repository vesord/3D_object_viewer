//
// Created by vesord on 10.07.2021.
//

#include "calculations.h"
#include <math.h>

/// TEST FUNCTION
void ComputeRotationOffsets(float *fXOffset, float *fYOffset)
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = (float)glfwGetTime();

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	*fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
	*fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}