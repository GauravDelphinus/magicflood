package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.ImageView;
import android.widget.TextView;

public class AddMovesDialog extends GameDialogType3 {

	public AddMovesDialog(Context context, int clientdata, int numCoins) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		ImageView iv = (ImageView) findViewById(R.id.dialog_add_lifeline_main_image_id);
		iv.setBackgroundResource(R.drawable.ic_add_moves);

		TextView tvTitle = (TextView) findViewById(R.id.dialog_add_lifeline_title_text_id);
		tvTitle.setText(context.getResources().getString(R.string.dialog_add_lifeline_moves_title_text));
		tvTitle.setTypeface(MFUtils.getTextTypeface(context));

		TextView tvDescription = (TextView) findViewById(R.id.dialog_add_lifeline_description_text_id);
		tvDescription.setText(context.getResources().getString(R.string.dialog_add_lifeline_moves_description_text));
		tvDescription.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView tvCoins = (TextView) findViewById(R.id.add_lifeline_product_count_text_id);
		String coinsRequired = String.format(context.getResources().getString(R.string.coins_required_text), numCoins);
		tvCoins.setText(coinsRequired);
		tvCoins.setTypeface(MFUtils.getTextTypeface(context));
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_add_moves);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.add_lifeline_button_id);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
}
