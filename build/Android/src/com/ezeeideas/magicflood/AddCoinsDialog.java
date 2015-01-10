package com.ezeeideas.magicflood;

import android.content.Context;

public class AddCoinsDialog extends GameDialogType5 {

	public AddCoinsDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
		
		AddCoinsProductLayout firstLayout = (AddCoinsProductLayout) mPositiveAction1View;
		firstLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_FIRST, "$0.99", 
				context.getResources().getDimension(R.dimen.small_deal_text_size), R.drawable.ic_iap_coins_first);
		
		AddCoinsProductLayout secondLayout = (AddCoinsProductLayout) mPositiveAction2View;
		secondLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_SECOND, "$1.49", 
				context.getResources().getDimension(R.dimen.medium_deal_text_size), R.drawable.ic_iap_coins_second);
		
		AddCoinsProductLayout thirdLayout = (AddCoinsProductLayout) mPositiveAction3View;
		thirdLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_THIRD, "$2.99", 
				context.getResources().getDimension(R.dimen.large_deal_text_size), R.drawable.ic_iap_coins_third);
		
		AddCoinsProductLayout fourthLayout = (AddCoinsProductLayout) mPositiveAction4View;
		fourthLayout.setProperties(MFGameConstants.COINS_IAP_COUNT_FOURTH, "$4.99", 
				context.getResources().getDimension(R.dimen.very_large_deal_text_size), R.drawable.ic_iap_coins_fourth);
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
