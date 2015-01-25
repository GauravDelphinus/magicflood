#include <jni.h>
#include "MFNativeLog.h"
#include "MFIAPInterface.h"

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

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    getProductDetails
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
extern "C" JNIEXPORT jobjectArray JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_getProductDetails
  (JNIEnv *env, jobject thisObj, jstring pid)
{
	jobjectArray ret;  
	int i;  

	const char *idStr = env->GetStringUTFChars(pid, 0);
	char **detailsArray = getInAppProductDetails(idStr);
	if (detailsArray == NULL)
	{
		return NULL;
	}

	char *message[4]= {detailsArray[0],
			detailsArray[1],
			detailsArray[2],
			detailsArray[3]};  

	ret= (jobjectArray)env->NewObjectArray(4,  
			env->FindClass("java/lang/String"),  
			env->NewStringUTF(""));  

	for(i=0;i<4;i++) 
	{  
		env->SetObjectArrayElement(ret, i, env->NewStringUTF(message[i]));  
	}  

	for (i = 0; i < 4; i++)
	{
		free(detailsArray[i]);
	}
	free(detailsArray);
	return(ret); 
}

/*
 * Class:     com_ezeeideas_magicflood_MFInAppPurchaseManager
 * Method:    getProductProvisioned
 * Signature: (Ljava/lang/String;)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_com_ezeeideas_magicflood_MFInAppPurchaseManager_getProductProvisioned
  (JNIEnv *env, jobject thisObj, jstring pid)
{
	const char *idStr = env->GetStringUTFChars(pid, 0);

	bool isProvisioned = getInAppProductProvisioned(idStr);

	if (isProvisioned)
	{
		return JNI_TRUE;
	}

	return JNI_FALSE;
}
