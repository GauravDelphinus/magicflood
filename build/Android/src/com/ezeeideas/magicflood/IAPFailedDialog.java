package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class IAPFailedDialog extends GameDialogType1 {

	public IAPFailedDialog(Context context, int type, int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_iap_failed_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_iap_failed_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView positiveButtonTV = (TextView) findViewById(R.id.dialog_iap_failed_positive_button_id);
		positiveButtonTV.setTypeface(MFUtils.getTextTypeface(context));
		
		switch (type)
		{
		case TYPE_PURCHASE_FAILED:
			titleTV.setText(context.getResources().getString(R.string.dialog_iap_failed_purchase_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_iap_failed_purchase_text));
			break;
		case TYPE_CONSUME_FAILED:
			titleTV.setText(context.getResources().getString(R.string.dialog_iap_failed_consume_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_iap_failed_consume_text));
			break;
		case TYPE_QUERY_FAILED:
			titleTV.setText(context.getResources().getString(R.string.dialog_iap_failed_query_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_iap_failed_query_text));
			break;
		}
		
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_iap_failed);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
	
	public static final int TYPE_PURCHASE_FAILED = 1;
	public static final int TYPE_CONSUME_FAILED = 2;
	public static final int TYPE_QUERY_FAILED = 3;
}
