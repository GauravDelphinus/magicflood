package com.ezeeideas.magicflood;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.ezeeideas.magicflood.iabutil.IabHelper;
import com.ezeeideas.magicflood.iabutil.IabResult;
import com.ezeeideas.magicflood.iabutil.Inventory;
import com.ezeeideas.magicflood.iabutil.Purchase;
import com.ezeeideas.magicflood.iabutil.SkuDetails;

public class MFInAppPurchaseManager implements IabHelper.OnIabSetupFinishedListener, IabHelper.QueryInventoryFinishedListener, IabHelper.OnIabPurchaseFinishedListener, IabHelper.OnConsumeFinishedListener
{
	public MFInAppPurchaseManager(Activity context)
	{
		mContext = context;
		
		initialize();
		
		initializeInAppInterface();
	}
	
	public void initialize()
	{
		Log.d("gaurav", "MFInAppPurchaseManager.initialize called");
		String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAzFOa2G5Il745oc+Mk4p9acAN49yEaR1yu0b/quHdxQQRNwwKH4ZJWxRTv+O3n/3EhhzqCpYp3DI1rlX/fjIJKYDMpeTofrhW4ySq/PHIJcC5z2ZvXw233CtAP2Bn44OvTcNrd0At5+9TVscRncN033fB+Tk1iX9e3fcwImkynAdYD1Fk+VDW2dKG9t6p9q+sE/tf98iw1aLgHNj8Rn3Dxo79EkbwbAxGk3LqqKJZExDCMnM9N2fb0iWEm+5mYhC1AFevQxjO3i0OFrgTp+EwiHysECvcUa6soY+ZDhBr0jHTW4hvIwiYBl80s2UPtpEMVdGV1nWOKsQ7bt6ogUv68wIDAQAB";
        // compute your public key and store it in base64EncodedPublicKey
		
		mPurchaseInterfaceListeners = new ArrayList<IAPPurchaseInterface>();
		
        mHelper = new IabHelper(mContext, base64EncodedPublicKey);
        mHelper.enableDebugLogging(true);
        mHelper.startSetup(this);
        Log.d("gaurav", "at the end of initialize");
	}
	
	public void addPurchaseListener(IAPPurchaseInterface listener)
	{
		mPurchaseInterfaceListeners.add(listener);
	}

	/**
	 * Query the service for available in-app purchase items.  This should
	 * be done in a separate thread given that it's a network request.
	 */
	public void queryInAppItems()
	{
		Log.d("gaurav", "queryInAppItems");
		
		ArrayList<String> skuList = new ArrayList<String>();
		String testPrefix = "";
		if (MFGameConstants.testingMode)
		{
			testPrefix += "test_";
		}
		skuList.add(testPrefix + MFGameConstants.IAP_ALACARTE_HURDLE_1);
		skuList.add(testPrefix + MFGameConstants.IAP_ALACARTE_HURDLE_2);
		skuList.add(testPrefix + MFGameConstants.IAP_ALACARTE_HURDLE_3);
		skuList.add(testPrefix + MFGameConstants.IAP_ALACARTE_HURDLE_4);
		skuList.add(testPrefix + MFGameConstants.IAP_ALACARTE_HURDLE_5);
		skuList.add(testPrefix + MFGameConstants.IAP_COMBO_HURDLES_1);
		skuList.add(testPrefix + MFGameConstants.IAP_COMBO_HURDLES_2);
		skuList.add(testPrefix + MFGameConstants.IAP_COMBO_HURDLES_3);
		skuList.add(testPrefix + MFGameConstants.IAP_COMBO_HURDLES_4);
		skuList.add(testPrefix + MFGameConstants.IAP_REMOVE_ADS);
				
		mHelper.queryInventoryAsync(true, skuList, this);
		Log.d("gaurav", "called queryInventoryAsync");
	}
	
	public void purchaseItem(String pid)
	{
		MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_STORE, MFAnalytics.ANALYTICS_ACTION_IAP_STARTED, pid);
		
		Log.d("gaurav", "calling mHelper.launchPurchaseFlow with pid = [" + pid + "]");
		String testPrefix = "";
		if (MFGameConstants.testingMode)
		{
			testPrefix = "test_";
		}
		mHelper.launchPurchaseFlow(mContext, testPrefix + pid, 0, this);
	}
	
	public void consumeItem(Purchase purchase)
	{
		mHelper.consumeAsync(purchase, this);
	}
	
	/**
	 * Called after IAB has been setup.  Now query for all the SKU information.
	 */
	@Override
	public void onIabSetupFinished(IabResult result) 
	{
		Log.d("gaurav", "onIabSetupFinished, result = " + result);
		queryInAppItems();
		
	}
	
	/**
	 * Called in onDestroy of parent activity.
	 */
	public void unbind()
	{
		   if (mHelper != null) mHelper.dispose();
		   mHelper = null;
	}
	
	
	@Override
	public void onQueryInventoryFinished(IabResult result, Inventory inv) //for provisioning status
	{
		Log.d("gaurav", "onQueryInventoryFinished called for SKU details, result = " + result);
		if (result.isFailure()) 
		{
			// handle error
			return;
		}

		String testPrefix = "";
		if (MFGameConstants.testingMode)
		{
			testPrefix += "test_";
		}
		
		Log.d("gaurav", "pidArray.length = " + pidArray.length);
		for (int i = 0; i < pidArray.length; i++)
		{
			SkuDetails skuDetails = inv.getSkuDetails(testPrefix + pidArray[i]);
			Log.d("gaurav", "skuDetails = [" + skuDetails + "]");
			//if (skuDetails != null)
			{
				String price = inv.getSkuDetails(testPrefix + pidArray[i]).getPrice();
				String name = inv.getSkuDetails(testPrefix + pidArray[i]).getTitle();
				String description = inv.getSkuDetails(testPrefix + pidArray[i]).getDescription();
				boolean isProvisioned = inv.hasPurchase(testPrefix + pidArray[i]);
				if (isProvisioned)
				{
					mIsAnythingProvisioned = true;
				}
				
				Log.d("gaurav", "i = " + i + ", calling addInAppProduct for [" + pidArray[i] + "] with name [" + name + "], description [" + description + "], price [" + price + "], isProvisioned [" + isProvisioned + "]");
				addInAppProduct(pidArray[i], name, description, price, "tbd", isProvisioned);
						 
				//Log.d("gaurav", "i = " + i + ", calling updateInAppProduct for [" + pidArray[i] + "] with [" + isProvisioned + "]");
				//updateInAppProduct(pidArray[i], isProvisioned);
				Log.d("gaurav","after calling addInAppProduct");
			}
		}
		
		Log.d("gaurav", "called at the end of onQueryInventoryFinished");
		mIsSynchronizedWithServer = true;
	}

	@Override
	public void onIabPurchaseFinished(IabResult result, Purchase info) 
	{
		if (result.isFailure()) 
		{
			String sku = mContext.getResources().getString(R.string.store_indeterminate_sku_string);
			if (info != null)
			{
				sku = info.getSku();
			}
			if (result.getResponse() == IabHelper.IABHELPER_USER_CANCELLED) //user cancelled the purchase
			{
				MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_STORE, MFAnalytics.ANALYTICS_ACTION_IAP_CANCELLED, sku, result.getResponse());
			}
			else //the purchase failed for some other reason
			{
				MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_STORE, MFAnalytics.ANALYTICS_ACTION_IAP_FAILED, sku, result.getResponse());
			}
			
			Log.d("gaurav", "Error purchasing: " + result + ", info = " + info + ", mPurchaseInterfaceListeners = " + mPurchaseInterfaceListeners);
			//some failure purchased.  Update the UI to reflect the changes
			return;
		}
		
		MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_STORE, MFAnalytics.ANALYTICS_ACTION_IAP_COMPLETED, info.getSku());
		
		Log.d("gaurav", "purchase successful, pid = [" + info.getSku() + "]");
		//successfully purchased.  Update the UI to reflect the changes
		for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
		{
			Log.d("gaurav", "calling onPurchaseFinished on each listener");
			listener.onPurchaseFinished(info, info.getSku(), true);
		}
		
		//update the provisioning status
		updateInAppProduct(info.getSku(), true);
	}
	
	public boolean isSynchronized()
	{
		return mIsSynchronizedWithServer;
	}
	
	public boolean isAnyIAPProvisioned()
	{
		return mIsAnythingProvisioned;
	}
	
	/**
	 * Implement this interface to listen to purchase completed callbacks.
	 * @author anukrity
	 *
	 */
	interface IAPPurchaseInterface
	{
		void onPurchaseFinished(Purchase purchase, String pid, boolean status);
		void onConsumeFinished(String pid, boolean status);
	}
	
	private static MFInAppPurchaseManager sIAPManager = null;
	private boolean mIsSynchronizedWithServer = false;
	private boolean mIsAnythingProvisioned = false;
	private Bundle mSkuDetails; //details of the SKU
	//private QuerySKUDetailsTask mQuerySkuDetailsTask;
	
	//private IInAppBillingService mService;
	
	Activity mContext;
	private IabHelper mHelper;
	private ArrayList<IAPPurchaseInterface> mPurchaseInterfaceListeners;
	
	private native void initializeInAppInterface();
	private native void addInAppProduct(String id, String name, String description, String price, String priceCode, boolean isProvisioned);
	private native void updateInAppProduct(String id, boolean isProvisioned);
	private native void clearInAppProducts();
	public native String[] getProductDetails(String id); //return 4 strings, for name, description, price and currency code
	public native boolean getProductProvisioned(String id);

	private String pidArray[] = {MFGameConstants.IAP_ALACARTE_HURDLE_1,
			MFGameConstants.IAP_ALACARTE_HURDLE_2,
			MFGameConstants.IAP_ALACARTE_HURDLE_3,
			MFGameConstants.IAP_ALACARTE_HURDLE_4,
			MFGameConstants.IAP_ALACARTE_HURDLE_5,
			MFGameConstants.IAP_COMBO_HURDLES_1,
			MFGameConstants.IAP_COMBO_HURDLES_2,
			MFGameConstants.IAP_COMBO_HURDLES_3,
			MFGameConstants.IAP_COMBO_HURDLES_4,
			MFGameConstants.IAP_REMOVE_ADS
	};

	public boolean handleActivityResult(int requestCode, int resultCode,
			Intent data) {
		return mHelper.handleActivityResult(requestCode, resultCode, data);
	}

	@Override
	public void onConsumeFinished(Purchase purchase, IabResult result) 
	{
		if (result.isFailure())
		{
			//failure in consumption
		}
		else
		{
			for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
			{
				Log.d("gaurav", "calling onPurchaseFinished on each listener");
				listener.onConsumeFinished(purchase.getSku(), true);
			}
		}
	}
};