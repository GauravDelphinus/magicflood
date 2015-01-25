package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class HurdleSmasherInfoDialog extends GameDialogType1 {

	public HurdleSmasherInfoDialog(Context context, int type) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_hurdle_smasher_info_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_hurdle_smasher_info_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView positiveButtonTV = (TextView) findViewById(R.id.dialog_introduce_lifeline_positive_button_id);
		positiveButtonTV.setTypeface(MFUtils.getTextTypeface(context));
		
		switch (type)
		{
		case TYPE_TAP:
			titleTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_tap_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_tap_text));
			break;
		case TYPE_RETRY:
			titleTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_not_detected_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_not_detected_text));
			break;
		case TYPE_GIVING_UP:
			titleTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_tries_title_text));
			descriptionTV.setText(context.getResources().getString(R.string.dialog_hurdle_smasher_info_tries_text));
			break;
		}
		
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_hurdle_smasher_info);
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
	
	public static final int TYPE_TAP = 1;
	public static final int TYPE_RETRY = 2;
	public static final int TYPE_GIVING_UP = 3;
}
