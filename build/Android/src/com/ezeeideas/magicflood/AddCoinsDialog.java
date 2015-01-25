package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class AddCoinsDialog extends GameDialogType5 {

	public AddCoinsDialog(Context context, String priceList[], int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_add_coins_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_add_coins_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
		
		AddCoinsProductLayout firstLayout = (AddCoinsProductLayout) mPositiveAction1View;
		firstLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_FIRST, priceList[0], R.drawable.ic_iap_coins_first);
		
		AddCoinsProductLayout secondLayout = (AddCoinsProductLayout) mPositiveAction2View;
		secondLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_SECOND, priceList[1], R.drawable.ic_iap_coins_second);
		
		AddCoinsProductLayout thirdLayout = (AddCoinsProductLayout) mPositiveAction3View;
		thirdLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_THIRD, priceList[2], R.drawable.ic_iap_coins_third);
		
		AddCoinsProductLayout fourthLayout = (AddCoinsProductLayout) mPositiveAction4View;
		fourthLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_FOURTH, priceList[3], R.drawable.ic_iap_coins_fourth);
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_add_coins);
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
}
