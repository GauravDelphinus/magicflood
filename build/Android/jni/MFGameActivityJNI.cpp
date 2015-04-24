#include <stdlib.h>
#include "MFGameActivityJNI.h"
#include "MFGridInterface.h"
#include "MFGlobalInterface.h"

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
 * Method:    getNumLevels
 * Signature: ()J
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumLevels
  (JNIEnv *env, jobject thisObj)
{
	return getNumLevels();
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
	int **startPosPtr = getStartPos(handle);
	if (startPosPtr == NULL)
	{
		return NULL;
	}

	int numStartPos = getNumStartPos(handle);
	jint *outCArray = (jint *) malloc (2 * numStartPos * sizeof(jint));
	for (int i = 0; i < numStartPos; i++)
	{
		outCArray[2 * i] = startPosPtr[i][0];
		outCArray[2 * i + 1] = startPosPtr[i][1];
	}
	freeStartPos(handle, startPosPtr);

	jintArray startPosArray = env->NewIntArray(2 * numStartPos);
	if (NULL == startPosArray)
	{
		return NULL;
	}

	env->SetIntArrayRegion(startPosArray, 0, 2 * numStartPos, outCArray);
	free(outCArray);

	return startPosArray;
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumStartPos
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumStartPos
  (JNIEnv *env, jobject thisObj, jlong handle)
{
	return getNumStartPos(handle);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    addStartPos
 * Signature: (J)V
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_addStartPos
  (JNIEnv *env, jobject thisObj, jlong handle, jint x, jint y)
{
	return addStartPos(handle, x, y);
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
 * Method:    setMaxMoves
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_setMaxMoves
  (JNIEnv *env, jobject thisObj, jlong handle, jint maxMoves)
{
	setMaxMoves(handle, maxMoves);
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
JNIEXPORT jintArray JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_playMove
  (JNIEnv *env, jobject thisObj, jlong handle, jint color)
{
	int *resultPtr = playMove(handle, color);
	jint outCArray[] = {resultPtr[0], resultPtr[1]};
	freePlayMove(handle, resultPtr);

	jintArray resultArray = env->NewIntArray(2);
	if (NULL == resultArray)
	{
		return NULL;
	}

	env->SetIntArrayRegion(resultArray, 0, 2, outCArray);
	return resultArray;
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

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    smashHurdle
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_smashHurdle
  (JNIEnv *env, jobject thisObj, jlong handle, jint x, jint y)
{
	return smashHurdle(handle, x, y);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    setCoins
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_setCoins
  (JNIEnv *env, jobject thisObj, jint coins)
{
	setCoins(coins);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getCoins
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getCoins
  (JNIEnv *env, jobject thisObj)
{
	return getCoins();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsIAPFirst
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsIAPFirst
  (JNIEnv *env, jobject thisObj)
{
	return getNumCoinsIAPFirst();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsIAPSecond
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsIAPSecond
  (JNIEnv *env, jobject thisObj)
{
	return getNumCoinsIAPSecond();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsIAPThird
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsIAPThird
  (JNIEnv *env, jobject thisObj)
{
	return getNumCoinsIAPThird();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsIAPFourth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsIAPFourth
  (JNIEnv *env, jobject thisObj)
{
	return getNumCoinsIAPFourth();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsForMoves
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsForMoves
  (JNIEnv *env, jobject thisObj)
{
	return getNumCoinsForMoves();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsForStar
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsForStar
  (JNIEnv *env, jobject thisObj, jint numStars)
{
	return getNumCoinsForStar(numStars);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsForHurdleSmasher
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsForHurdleSmasher
  (JNIEnv *env, jobject thisObj, jint numSmashers)
{
	return getNumCoinsForHurdleSmasher(numSmashers);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsForBridge
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsForBridge
  (JNIEnv *env, jobject thisObj, jint numBridges)
{
	return getNumCoinsForBridge(numBridges);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getMinLevelToAddStars
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getMinLevelToAddStars
  (JNIEnv *env, jobject thisObj)
{
	return getMinLevelToAddStars();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getMinLevelToAddHurdleSmasher
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getMinLevelToAddHurdleSmasher
  (JNIEnv *env, jobject thisObj)
{
	return getMinLevelToAddHurdleSmasher();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getMinLevelToAddBridge
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getMinLevelToAddBridge
  (JNIEnv *env, jobject thisObj)
{
	return getMinLevelToAddBridge();
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    getNumCoinsForSuccessfulGame
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_getNumCoinsForSuccessfulGame
  (JNIEnv *env, jobject thisObj, jint currMove, jint maxMoves)
{
	return getNumCoinsForSuccessfulGame(currMove, maxMoves);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    isBridgeEndpointValid
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_isBridgeEndpointValid
  (JNIEnv *env, jobject thisObj, jlong handle, jint row, jint col)
{
	return isBridgeEndpointValid(handle, row, col);
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    checkBridgeValid
 * Signature: (JIIII)[I
 */
JNIEXPORT jintArray JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_checkBridgeValid
  (JNIEnv *env, jobject thisObj, jlong handle, jint startrow, jint startcol, jint endrow, jint endcol)
{
	
	int **bridgeExtremesPtr = checkBridgeValid(handle, startrow, startcol, endrow, endcol);
	if (bridgeExtremesPtr == NULL)
	{
		return NULL;
	}

	jint *outCArray = (jint *) malloc (2 * 2 * sizeof(jint));
	for (int i = 0; i < 2; i++)
	{
		outCArray[2 * i] = bridgeExtremesPtr[i][0];
		outCArray[2 * i + 1] = bridgeExtremesPtr[i][1];
	}
	freeBridgeExtremes(handle, bridgeExtremesPtr);

	jintArray bridgeExtremesArray = env->NewIntArray(2 * 2);
	if (NULL == bridgeExtremesArray)
	{
		return NULL;
	}

	env->SetIntArrayRegion(bridgeExtremesArray, 0, 2 * 2, outCArray);
	free(outCArray);

	return bridgeExtremesArray;
}

/*
 * Class:     com_ezeeideas_magicflood_MFGameActivity
 * Method:    buildBridge
 * Signature: (JIIII)V
 */
JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFGameActivity_buildBridge
  (JNIEnv *env, jobject thisObj, jlong handle, jint startrow, jint startcol, jint endrow, jint endcol)
{
	buildBridge(handle, startrow, startcol, endrow, endcol);
}
