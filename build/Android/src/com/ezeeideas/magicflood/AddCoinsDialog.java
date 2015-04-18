package com.ezeeideas.magicflood;

import android.content.Context;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class AddCoinsDialog extends GameDialogType5 implements MFInAppPurchaseManager.IAPQueryInterface {

	public AddCoinsDialog(Context context, int shortfall, int clientdata, MFInAppPurchaseManager iapManager, int numCoinsFirst, int numCoinsSecond, int numCoinsThird, int numCoinsFourth) 
	{
		super(context, clientdata);
		mContext = context;
		
		mNumCoinsFirst = numCoinsFirst;
		mNumCoinsSecond = numCoinsSecond;
		mNumCoinsThird = numCoinsThird;
		mNumCoinsFourth = numCoinsFourth;
		
		setupViews(shortfall);
		
		postSetupViews();
		
		mIAPManager = iapManager;
		refreshViews();
		
		Log.d("gaurav", "AddCoinsDialog, IAPManager isConnected = " + mIAPManager.isConnected() + ", isSynchronized = " + mIAPManager.isSynchronized());
		
		if (mIAPManager.isConnected() && !mIAPManager.isSynchronized())
		{
			mErrorTextView.setVisibility(View.VISIBLE);
			
			mIAPManager.queryInAppItems();
			mIAPManager.addQueryListener(this);
		}
	}

	protected void setupViews(int shortfall) 
	{
		setContentView(R.layout.dialog_add_coins);
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_add_coins_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(mContext));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_add_coins_description_text_id);
		String text = null;
		if (shortfall == 0)
		{
			text = mContext.getResources().getString(R.string.dialog_add_coins_description_static);
		}
		else
		{
			text = String.format(mContext.getResources().getString(R.string.dialog_add_coins_description_dynamic), shortfall);
		}
		descriptionTV.setText(text);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(mContext));
		
		mErrorTextView = (TextView) findViewById(R.id.dialog_add_coins_error_text_id);
		mErrorTextView.setTypeface(MFUtils.getTextTypeface(mContext));
	}
	
	private void refreshViews()
	{	
		if (mIAPManager.isConnected() && mIAPManager.isSynchronized())
		{
			String addCoinsPriceList[] = new String[4];
			String details[] = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FIRST);
			addCoinsPriceList[0] = details[2];
			details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_SECOND);
			addCoinsPriceList[1] = details[2];
			details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_THIRD);
			addCoinsPriceList[2] = details[2];
			details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FOURTH);
			addCoinsPriceList[3] = details[2];
			
			AddCoinsProductLayout firstLayout = (AddCoinsProductLayout) mPositiveAction1View;
			firstLayout.setProperties(mNumCoinsFirst, addCoinsPriceList[0], R.drawable.ic_iap_coins_first);
			
			AddCoinsProductLayout secondLayout = (AddCoinsProductLayout) mPositiveAction2View;
			secondLayout.setProperties(mNumCoinsSecond, addCoinsPriceList[1], R.drawable.ic_iap_coins_second);
			
			AddCoinsProductLayout thirdLayout = (AddCoinsProductLayout) mPositiveAction3View;
			thirdLayout.setProperties(mNumCoinsThird, addCoinsPriceList[2], R.drawable.ic_iap_coins_third);
			
			AddCoinsProductLayout fourthLayout = (AddCoinsProductLayout) mPositiveAction4View;
			fourthLayout.setProperties(mNumCoinsFourth, addCoinsPriceList[3], R.drawable.ic_iap_coins_fourth);
			
			mErrorTextView.setVisibility(View.GONE);
		}
		else
		{
			AddCoinsProductLayout firstLayout = (AddCoinsProductLayout) mPositiveAction1View;
			firstLayout.setProperties(mNumCoinsFirst, "", R.drawable.ic_iap_coins_first);
			
			AddCoinsProductLayout secondLayout = (AddCoinsProductLayout) mPositiveAction2View;
			secondLayout.setProperties(mNumCoinsSecond, "", R.drawable.ic_iap_coins_second);
			
			AddCoinsProductLayout thirdLayout = (AddCoinsProductLayout) mPositiveAction3View;
			thirdLayout.setProperties(mNumCoinsThird, "", R.drawable.ic_iap_coins_third);
			
			AddCoinsProductLayout fourthLayout = (AddCoinsProductLayout) mPositiveAction4View;
			fourthLayout.setProperties(mNumCoinsFourth, "", R.drawable.ic_iap_coins_fourth);
			
			mErrorTextView.setVisibility(View.VISIBLE);
		}
	}

	@Override
	public void onQueryFinished(boolean status) {
		Log.d("gaurav", "AddCoinsDialog.onQueryFinished, status = " + status);
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
		mPositiveAction1View = findViewById(R.id.add_coins_first_product_id);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.add_coins_second_product_id);
	}

	@Override
	protected void setupPositiveAction3View() 
	{
		mPositiveAction3View = findViewById(R.id.add_coins_third_product_id);
	}
	
	@Override
	protected void setupPositiveAction4View() 
	{
		mPositiveAction4View = findViewById(R.id.add_coins_fourth_product_id);
	}
	
	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);		
	}
	
	MFInAppPurchaseManager mIAPManager;
	Context mContext;
	int mNumCoinsFirst, mNumCoinsSecond, mNumCoinsThird, mNumCoinsFourth;
	TextView mErrorTextView;
}
