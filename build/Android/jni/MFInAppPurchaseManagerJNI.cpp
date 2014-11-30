#include <jni.h>
#include "MFIAPInterface.h"

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    initializeInAppInterface
 * Signature: ()V
 */
extern "C" JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_initializeInAppInterface
  (JNIEnv *env, jobject thisObj)
{
	initializeInAppInterface();
}

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    addInAppProduct
 * Signature: (ILjava/lang/String;Ljava/lang/String;Z)V
 */
extern "C" JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_addInAppProduct
  (JNIEnv *env, jobject thisObj, jint pid, jstring name, jstring description, jboolean isProvisioned)
{
	const char *nameStr = env->GetStringUTFChars(name, 0);
	const char *descriptionStr = env->GetStringUTFChars(description, 0);

	addInAppProduct(pid, nameStr, descriptionStr, (isProvisioned == JNI_TRUE));
	
	env->ReleaseStringUTFChars(name, nameStr);
	env->ReleaseStringUTFChars(description, descriptionStr);
}

