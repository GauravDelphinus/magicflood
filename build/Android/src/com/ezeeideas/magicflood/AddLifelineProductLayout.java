package com.ezeeideas.magicflood;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class AddLifelineProductLayout extends LinearLayout
{
	public AddLifelineProductLayout(Context context) 
	{
		super(context);
		mContext = context;
		// TODO Auto-generated constructor stub
	}
	
	public AddLifelineProductLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		mContext = context;
	}
	
	public void setProperties(int imageId, int coins1, int coins2)
	{
		//set the iap product image
		ImageView productImage = (ImageView) findViewById(R.id.add_lifeline_image1_id);
		productImage.setBackgroundResource(imageId);
		
		productImage = (ImageView) findViewById(R.id.add_lifeline_image2_id);
		productImage.setBackgroundResource(imageId);
		
		TextView tvDetail = (TextView) findViewById(R.id.add_lifeline_product_count1_text_id);
		String coinsRequired = String.format(getResources().getString(R.string.coins_required_text), coins1);
		tvDetail.setText(coinsRequired);
		tvDetail.setTypeface(MFUtils.getTextTypeface(mContext));
		
		tvDetail = (TextView) findViewById(R.id.add_lifeline_product_count2_text_id);
		coinsRequired = String.format(getResources().getString(R.string.coins_required_text), coins2);
		tvDetail.setText(coinsRequired);
		tvDetail.setTypeface(MFUtils.getTextTypeface(mContext));
		
		TextView multiplierText = (TextView) findViewById(R.id.text_multiplier1_id);
		multiplierText.setTypeface(MFUtils.getTextTypeface(mContext));
		multiplierText = (TextView) findViewById(R.id.text_multiplier2_id);
		multiplierText.setTypeface(MFUtils.getTextTypeface(mContext));
	}
	
	private Context mContext;
}