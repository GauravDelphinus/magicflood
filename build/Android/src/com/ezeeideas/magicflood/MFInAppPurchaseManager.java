package com.ezeeideas.magicflood;

import java.util.ArrayList;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;

import com.android.vending.billing.IInAppBillingService;

public class MFInAppPurchaseManager implements ServiceConnection
{
	public MFInAppPurchaseManager()
	{
		
	}
	
	public static MFInAppPurchaseManager create()
	{
		if (sIAPManager == null)
		{
			sIAPManager = new MFInAppPurchaseManager();
		}
		
		return sIAPManager;
		/*
		sIAPManager.initializeInAppInterface();
		
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_1, "First A-la-carte Item", "My very first IAP", true);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_2, "Second A-la-carte item", "My very second IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_3, "Third A-la-carte item", "My very third IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_4, "Fourth A-la-carte item", "My very fourth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_5, "Fifth A-la-carte item", "My very fifth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_6, "Sixth A-la-carte item", "My very sixth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_1, "Combo: 5 Hurdles!", "My very seventh IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_2, "Combo: 10 Hurdles!", "My very eighth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_3, "Combo: 25 Hurdles!", "My very ninth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_4, "Combo: 50 Hurdles!", "My very tenth IAP", false);
		*/
	}
	
	@Override
	public void onServiceConnected(ComponentName arg0, IBinder service) 
	{
		mService = IInAppBillingService.Stub.asInterface(service);
	}

	@Override
	public void onServiceDisconnected(ComponentName arg0) 
	{
		mService = null;		
	}
	
	public boolean isServiceConnected()
	{
		return (mService != null);
	}
	
	/**
	 * Query the service for available in-app purchase items.  This should
	 * be done in a separate thread given that it's a network request.
	 */
	public void queryInAppItems()
	{
		mQuerySkuDetailsTask = new QuerySKUDetailsTask();
		mQuerySkuDetailsTask.execute(0);
	}
	
	private class QuerySKUDetailsTask extends AsyncTask<Integer, Integer, Boolean>
	{
		protected Boolean doInBackground(Integer... args)
		{
			ArrayList<String> skuList = new ArrayList<String> ();
			
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_1);
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_2);
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_3);
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_4);
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_5);
			skuList.add(MFGameConstants.IAP_ALACARTE_HURDLE_6);
			skuList.add(MFGameConstants.IAP_COMBO_HURDLES_1);
			skuList.add(MFGameConstants.IAP_COMBO_HURDLES_2);
			skuList.add(MFGameConstants.IAP_COMBO_HURDLES_3);
			skuList.add(MFGameConstants.IAP_COMBO_HURDLES_4);
			skuList.add(MFGameConstants.IAP_REMOVE_ADS);
			
			Bundle querySkus = new Bundle();
			querySkus.putStringArrayList(MFGameConstants.IAP_QUERY_SKUS_KEY, skuList);
			
			try {
				mSkuDetails = mService.getSkuDetails(3, MFGameConstants.PACKAGE_NAME, "inapp", querySkus);
			} catch (RemoteException e) {
				return false;
			}
			int response = mSkuDetails.getInt("RESPONSE_CODE");
			if (response == MFGameConstants.BILLING_RESPONSE_RESULT_OK)
			{
				return true;
			}
			
			return false;
		}
		protected void onProgressUpdate(Integer... args)
		{
			
		}
		protected void onPostExecute(Boolean result)
		{
			if (result == true)
			{
				ArrayList<String> responseList = mSkuDetails.getStringArrayList("DETAILS_LIST");

				
				//add the in-app products
				for (String thisResponse : responseList) 
				{
					JSONObject object;
					try {
						object = new JSONObject(thisResponse);
						String pid = object.getString(MFGameConstants.IAP_PRODUCT_ID);
						String price = object.getString(MFGameConstants.IAP_PRODUCT_PRICE);
						String name = object.getString(MFGameConstants.IAP_PRODUCT_TITLE);
						String description = object.getString(MFGameConstants.IAP_PRODUCT_DESCRIPTION);
						String currencyCode = object.getString(MFGameConstants.IAP_PRODUCT_PRICE_CURRENCY_CODE);
						
						//Add this product to the list in the C++ side
						addInAppProduct(pid, name, description, price, currencyCode, false);
					} catch (JSONException e) {
						//something went wrong, so we can't claim we're done synchronizing the iap status
						mIsSynchronizedWithServer = false;
					}
				}
				
				//now update the provisioning status
				Bundle ownedItems = null;
				try {
					ownedItems = mService.getPurchases(3, MFGameConstants.PACKAGE_NAME, "inapp", null);
				} catch (RemoteException e1) {
					//something went wrong, so we can't claim we're done synchronizing the iap status
					mIsSynchronizedWithServer = false;
				}
				
				int response = ownedItems.getInt("RESPONSE_CODE");
				if (response == MFGameConstants.BILLING_RESPONSE_RESULT_OK) {
				   ArrayList<String> ownedSkus =
				      ownedItems.getStringArrayList("INAPP_PURCHASE_ITEM_LIST");
				   ArrayList<String>  purchaseDataList =
				      ownedItems.getStringArrayList("INAPP_PURCHASE_DATA_LIST");
				   ArrayList<String>  signatureList =
				      ownedItems.getStringArrayList("INAPP_DATA_SIGNATURE");
				    
				   for (int i = 0; i < purchaseDataList.size(); ++i) 
				   {
				      String purchaseData = purchaseDataList.get(i);
				  
				      JSONObject object;
				      try {
				    	  object = new JSONObject(purchaseData);
				    	  String pid = object.getString(MFGameConstants.IAP_PRODUCT_ID);
				    	  String purchaseState = object.getString(MFGameConstants.IAP_PURCHASE_STATE);
				    	  boolean provisioned = false;
				    	  if (Integer.getInteger(purchaseState) == 0)
				    	  {
				    		  //purchased!
				    		  provisioned = true;
				    	  }

				    	  //update the provisioning status in the C++ code
				    	  updateInAppProduct(pid, provisioned);
				      } catch (JSONException e) {
				    	  //something went wrong, so we can't claim we're done synchronizing the iap status
				    	  mIsSynchronizedWithServer = false;
				      }
				   } 
				}
				
				//we're now synchronized the iap status in the C++ code
				mIsSynchronizedWithServer = true;
			}
		}
	}
	
	private static MFInAppPurchaseManager sIAPManager = null;
	private boolean mIsSynchronizedWithServer = false;
	private Bundle mSkuDetails; //details of the SKU
	private QuerySKUDetailsTask mQuerySkuDetailsTask;
	
	private IInAppBillingService mService;
	
	private native void initializeInAppInterface();
	private native void addInAppProduct(String id, String name, String description, String price, String priceCode, boolean isProvisioned);
	private native void updateInAppProduct(String id, boolean isProvisioned);
};