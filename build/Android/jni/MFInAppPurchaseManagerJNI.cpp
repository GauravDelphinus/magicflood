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
  (JNIEnv *env, jobject thisObj, jstring pid, jstring name, jstring description, jstring price, jstring priceCode, jboolean isProvisioned)
{
	const char *idStr = env->GetStringUTFChars(pid, 0);
	const char *nameStr = env->GetStringUTFChars(name, 0);
	const char *descriptionStr = env->GetStringUTFChars(description, 0);
	const char *priceStr = env->GetStringUTFChars(price, 0);
	const char *priceCodeStr = env->GetStringUTFChars(priceCode, 0);

	addInAppProduct(idStr, nameStr, descriptionStr, priceStr, priceCodeStr, (isProvisioned == JNI_TRUE));
	
	env->ReleaseStringUTFChars(pid, idStr);
	env->ReleaseStringUTFChars(name, nameStr);
	env->ReleaseStringUTFChars(description, descriptionStr);
	env->ReleaseStringUTFChars(price, priceStr);
	env->ReleaseStringUTFChars(priceCode, priceCodeStr);
}

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    updateInAppProduct
 * Signature: (Ljava/lang/String;Z)V
 */
extern "C" JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_updateInAppProduct
  (JNIEnv *env, jobject thisObj, jstring pid, jboolean isProvisioned)
{
	const char *idStr = env->GetStringUTFChars(pid, 0);

	updateInAppProduct(idStr, (isProvisioned == JNI_TRUE));
	
	env->ReleaseStringUTFChars(pid, idStr);
}

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    clearInAppProducts
 * Signature: ()V
 */
extern "C" JNIEXPORT void JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_clearInAppProducts
  (JNIEnv *env, jobject thisObj)
{
	clearInAppProducts();
}
