package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.ImageView;
import android.widget.TextView;

public class AddBridgeDialog extends GameDialogType4 {

	public AddBridgeDialog(Context context, int clientdata, int numCoins1, int numCoins2) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		AddLifelineProductLayout layout = (AddLifelineProductLayout) findViewById(R.id.add_lifeline_layout_id);
		layout.setProperties(R.drawable.ic_bridge, numCoins1, numCoins2);

		ImageView iv = (ImageView) findViewById(R.id.dialog_add_lifeline_main_image_id);
		iv.setBackgroundResource(R.drawable.ic_add_bridge);

		TextView tvTitle = (TextView) findViewById(R.id.dialog_add_lifeline_title_text_id);
		tvTitle.setText(context.getResources().getString(R.string.dialog_add_lifeline_bridge_title_text));
		tvTitle.setTypeface(MFUtils.getTextTypeface(context));

		TextView tvDescription = (TextView) findViewById(R.id.dialog_add_lifeline_description_text_id);
		tvDescription.setText(context.getResources().getString(R.string.dialog_add_lifeline_bridge_description_text));
		tvDescription.setTypeface(MFUtils.getTextTypeface(context));
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_add_lifeline);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.add_lifeline1_button_id);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.add_lifeline2_button_id);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
}
