#include <stdlib.h>
#include "MFGameActivityJNI.h"
#include "MFGridInterface.h"

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    createNewGrid
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_createNewGrid
  (JNIEnv *env, jobject thisObj, jint level)
{
	jlong gridHandle = createNewGrid(level);
	return gridHandle;
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    deleteGrid
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_deleteGrid
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	deleteGrid(handle);
}
	

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getGridSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getGridSize
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	return getGridSize(handle);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getStartPos
 * Signature: (J)[I
 */
JNIEXPORT jintArray JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getStartPos
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	int *startPosPtr = getStartPos(handle);
	jint outCArray[] = {startPosPtr[0], startPosPtr[1]};
	freeStartPos(handle, startPosPtr);

	jintArray startPosArray = env->NewIntArray(2);
	if (NULL == startPosArray)
	{
		return NULL;
	}

	env->SetIntArrayRegion(startPosArray, 0, 2, outCArray);
	return startPosArray;
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getMaxMoves
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getMaxMoves
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	return getMaxMoves(handle);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getCurrMove
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getCurrMove
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	return getCurrMove(handle);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    playMove
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_playMove
  (JNIEnv *env, jobject thisObj, jlong handle, jint color)
{
	return playMove(handle, color);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getGridData
 * Signature: (J)[I
 */
JNIEXPORT jintArray JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getGridData
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	int **gridData = getGridData(handle);
	if (gridData == NULL)
	{
		return NULL;
	}

	int gridSize = getGridSize(handle);
	jint *outCArray = (jint *) malloc (gridSize * gridSize * sizeof(jint));
	for (int i = 0; i < gridSize * gridSize; i++)
	{
		int x = i % gridSize;
		int y = i / gridSize;
		outCArray[i] = gridData[x][y];
	}
	freeGridData(handle, gridData);

	jintArray gridDataArray = env->NewIntArray(gridSize * gridSize);
	if (NULL == gridDataArray)
	{
		return NULL;
	}

	env->SetIntArrayRegion(gridDataArray, 0, gridSize * gridSize, outCArray);
	free(outCArray);

	return gridDataArray;
}
