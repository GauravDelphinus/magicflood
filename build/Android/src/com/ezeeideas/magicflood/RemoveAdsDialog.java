package com.ezeeideas.magicflood;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class RemoveAdsDialog extends GameDialogType3 implements MFInAppPurchaseManager.IAPQueryInterface
{
	public RemoveAdsDialog(Activity context, int clientdata, MFInAppPurchaseManager iapManager) 
	{
		super(context, clientdata);
		mContext = context;

		setupViews();
		
		postSetupViews();

		mIAPManager = iapManager;
		Log.d("gaurav", "RemoveAdsDialog, iapManager = " + iapManager);
		refreshViews();
		
		if (mIAPManager.isConnected() && !mIAPManager.isSynchronized())
		{
			mErrorTextView.setVisibility(View.VISIBLE);
			
			mIAPManager.queryInAppItems();
			mIAPManager.addQueryListener(this);
		}
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_remove_ads);
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_remove_ads_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(mContext));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_remove_ads_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(mContext));
		
		mErrorTextView = (TextView) findViewById(R.id.dialog_remove_ads_error_text_id);
		mErrorTextView.setTypeface(MFUtils.getTextTypeface(mContext));
	}

	private void refreshViews()
	{
		if (mIAPManager.isConnected() && mIAPManager.isSynchronized())
		{
			String detailsArray[];
	        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_REMOVE_ADS);
	        
			TextView tv = (TextView) findViewById(R.id.remove_ads_price_text_id);
			String text = String.format(mContext.getResources().getString(R.string.remove_ads_price_text), detailsArray[2]);
			tv.setText(text);
			tv.setTypeface(MFUtils.getTextTypeface(mContext));
			
			mErrorTextView.setVisibility(View.GONE);
		}
		else
		{
			mErrorTextView.setVisibility(View.VISIBLE);
		}
	}
	
	@Override
	public void onQueryFinished(boolean status) {
		refreshViews();
		
	}
	
	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.remove_ads_button_id);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
	
	MFInAppPurchaseManager mIAPManager;
	Context mContext;
	TextView mErrorTextView;
}
