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
	}
	
	public void initialize()
	{
		Log.d("gaurav", "MFInAppPurchaseManager.initialize");
		
        // compute your public key and store it in base64EncodedPublicKey
		mPurchaseInterfaceListeners = new ArrayList<IAPPurchaseInterface>();
		mQueryInterfaceListeners = new ArrayList<IAPQueryInterface>();
		
        mHelper = new IabHelper(mContext, MFConstants.base64EncodedPublicKey);
        mHelper.enableDebugLogging(true);
        mHelper.startSetup(this);
	}
	
	public void addPurchaseListener(IAPPurchaseInterface listener)
	{
		mPurchaseInterfaceListeners.add(listener);
	}
	
	public void addQueryListener(IAPQueryInterface listener)
	{
		mQueryInterfaceListeners.add(listener);
	}

	/**
	 * Query the service for available in-app purchase items.  This should
	 * be done in a separate thread given that it's a network request.
	 */
	public void queryInAppItems()
	{		
		Log.d("gaurav", "MFInAppPurchaseManager.queryInAppItems");
		
		ArrayList<String> skuList = new ArrayList<String>();

		skuList.add(MFGameConstants.IAP_COINS_FIRST);
		skuList.add(MFGameConstants.IAP_COINS_SECOND);
		skuList.add(MFGameConstants.IAP_COINS_THIRD);
		skuList.add(MFGameConstants.IAP_COINS_FOURTH);
		skuList.add(MFGameConstants.IAP_REMOVE_ADS);
				
		mHelper.queryInventoryAsync(true, skuList, this);
	}
	
	public void purchaseItem(String pid)
	{
		MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_STARTED, pid);
	
		mHelper.launchPurchaseFlow(mContext, pid, 0, this);
	}
	
	public void consumeItem(Purchase purchase)
	{
		MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_CONSUME_STARTED, purchase.getSku());
		
		mHelper.consumeAsync(purchase, this);
	}
	
	/**
	 * Called after IAB has been setup.  Now query for all the SKU information.
	 */
	@Override
	public void onIabSetupFinished(IabResult result) 
	{
		Log.d("gaurav", "MFInAppPurchaseManager.onIabSetupFinished, result = " + result);
		
		if (result.isSuccess())
		{
			mIsConnectedWithServer = true;
		}
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
		Log.d("gaurav", "MFInAppPurchaseManager.onQueryInventoryFinished, result = " + result);
		if (result.isFailure()) 
		{
			Log.d("gaurav", "result.isFailure");
			// handle error
			MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_QUERY_FAILED, MFAnalytics.ANALYTICS_VALUE_IAP_QUERY_FAILED_RESULT_FAILURE, result.getResponse());
			
			for (IAPQueryInterface listener: mQueryInterfaceListeners)
			{
				listener.onQueryFinished(false);
			}
			return;
		}
		
		for (int i = 0; i < pidArray.length; i++)
		{
			SkuDetails skuDetails = inv.getSkuDetails(pidArray[i]);
			if (skuDetails == null)
			{
				//handle error.  Let user know.
				MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_QUERY_FAILED, MFAnalytics.ANALYTICS_VALUE_IAP_QUERY_FAILED_SKU_NULL, i);
				
				for (IAPQueryInterface listener: mQueryInterfaceListeners)
				{
					listener.onQueryFinished(false);
				}
				return;
			}
			String price = inv.getSkuDetails(pidArray[i]).getPrice();
			String name = inv.getSkuDetails(pidArray[i]).getTitle();
			String description = inv.getSkuDetails(pidArray[i]).getDescription();
			boolean isProvisioned = inv.hasPurchase(pidArray[i]);
			if (isProvisioned)
			{
				//* for consumable items such as coins, make sure they are consumed if they were provisioned by the user *//
				consumeItem(inv.getPurchase(pidArray[i]));
			}

			addInAppProduct(pidArray[i], name, description, price, "tbd", isProvisioned);
		}
		
		
		mIsSynchronizedWithServer = true;
		for (IAPQueryInterface listener: mQueryInterfaceListeners)
		{
			listener.onQueryFinished(true);
		}
	}

	@Override
	public void onIabPurchaseFinished(IabResult result, Purchase info) 
	{
		Log.d("gaurav", "MFInAppPurchaseManager.onIabPurchaseFinished, result = " + result);
		if (result.isFailure()) 
		{
			String sku = mContext.getResources().getString(R.string.store_indeterminate_sku_string);
			if (info != null)
			{
				sku = info.getSku();
			}
			if (result.getResponse() == IabHelper.IABHELPER_USER_CANCELLED) //user cancelled the purchase
			{
				MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_CANCELLED, sku, result.getResponse());
			}
			else //the purchase failed for some other reason
			{
				MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_FAILED, sku, result.getResponse());
			}
			
			//successfully purchased.  Update the UI to reflect the changes
			for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
			{
				listener.onPurchaseFinished(info, sku, false);
			}
			
			//some failure purchased.  Update the UI to reflect the changes
			return;
		}
		
		MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_COMPLETED, info.getSku());
		
		//successfully purchased.  Update the UI to reflect the changes
		for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
		{
			listener.onPurchaseFinished(info, info.getSku(), true);
		}
		
		//update the provisioning status
		updateInAppProduct(info.getSku(), true);
	}
	
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
			MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_CONSUME_FAILED, purchase.getSku(), result.getResponse());
			
			for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
			{
				listener.onConsumeFinished(purchase.getSku(), false);
			}
		}
		else
		{
			MFAnalytics.trackEvent(mContext, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_CONSUME_COMPLETED, purchase.getSku());
			
			for (IAPPurchaseInterface listener: mPurchaseInterfaceListeners)
			{
				listener.onConsumeFinished(purchase.getSku(), true);
			}
		}
	}
	
	public boolean isConnected()
	{
		return mIsConnectedWithServer;
	}
	
	public boolean isSynchronized()
	{
		return mIsSynchronizedWithServer;
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
	
	/**
	 * Implement this interface t listen to IAP query callbacks
	 * @author anukrity
	 *
	 */
	interface IAPQueryInterface
	{
		void onQueryFinished(boolean status);
	}
	
	private static MFInAppPurchaseManager sIAPManager = null;
	private boolean mIsSynchronizedWithServer = false; //query of IAP items was successful
	private boolean mIsConnectedWithServer = false; //setup IAB successful
	
	private Bundle mSkuDetails; //details of the SKU
	//private QuerySKUDetailsTask mQuerySkuDetailsTask;
	
	//private IInAppBillingService mService;
	
	Activity mContext;
	private IabHelper mHelper;
	private ArrayList<IAPPurchaseInterface> mPurchaseInterfaceListeners;
	private ArrayList<IAPQueryInterface> mQueryInterfaceListeners;
	
	private native void addInAppProduct(String id, String name, String description, String price, String priceCode, boolean isProvisioned);
	private native void updateInAppProduct(String id, boolean isProvisioned);
	private native void clearInAppProducts();
	public native String[] getProductDetails(String id); //return 4 strings, for name, description, price and currency code
	public native boolean getProductProvisioned(String id);

	private String pidArray[] = {MFGameConstants.IAP_COINS_FIRST,
			MFGameConstants.IAP_COINS_SECOND,
			MFGameConstants.IAP_COINS_THIRD,
			MFGameConstants.IAP_COINS_FOURTH,
			MFGameConstants.IAP_REMOVE_ADS
	};

	
};