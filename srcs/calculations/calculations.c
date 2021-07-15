#include "scop.h"
#include <math.h>
#include <string.h>

void stationary_offset(t_mat4f *model_to_cam) {
	memset(model_to_cam, 0, sizeof(*model_to_cam));

	// Identity matrix
	model_to_cam->x.x = 1.f;
	model_to_cam->y.y = 1.f;
	model_to_cam->z.z = 1.f;
	model_to_cam->w.w = 1.f;

	// Stationary offset
	model_to_cam->w.x = 0.f;
	model_to_cam->w.y = 0.f;
	model_to_cam->w.z = -100.f;
}

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

//void OvalOffset(float elapsedTime) {
//	const float loopDuration = 3.f;
//	const float scale = 3.141592f * 2.f / loopDuration;
//
//	float curTimeInLoop = fmodf(elapsedTime, loopDuration);
//
//	memset(modelToCameraMatrix, 0, sizeof(float) * 16);
//
//	// Identity matrix
//	modelToCameraMatrix[0] = 1.f;
//	modelToCameraMatrix[5] = 1.f;
//	modelToCameraMatrix[10] = 1.f;
//	modelToCameraMatrix[15] = 1.f;
//
//	modelToCameraMatrix[12] = cosf(curTimeInLoop * scale) * 4.f;
//	modelToCameraMatrix[13] = sinf(curTimeInLoop * scale) * 6.f;
//	modelToCameraMatrix[14] = -20.f;
//}
//
//void BottomCircleOffset(float elapsedTime) {
//	const float loopDuration = 12.f;
//	const float scale = 3.141592f * 2.f / loopDuration;
//
//	float curTimeInLoop = fmodf(elapsedTime, loopDuration);
//
//	memset(modelToCameraMatrix, 0, sizeof(float) * 16);
//
//	// Identity matrix
//	modelToCameraMatrix[0] = 1.f;
//	modelToCameraMatrix[5] = 1.f;
//	modelToCameraMatrix[10] = 1.f;
//	modelToCameraMatrix[15] = 1.f;
//
//	modelToCameraMatrix[12] = cosf(curTimeInLoop * scale) * 5.f;
//	modelToCameraMatrix[13] = -3.5f;
//	modelToCameraMatrix[14] = sinf(curTimeInLoop * scale) * 6.f - 20.f;
//}