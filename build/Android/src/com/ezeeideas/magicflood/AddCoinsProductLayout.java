package com.ezeeideas.magicflood;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class AddCoinsProductLayout extends LinearLayout
{
	public AddCoinsProductLayout(Context context) 
	{
		super(context);
		mContext = context;
	}
	
	public AddCoinsProductLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		mContext = context;
	}
	
	public void setProperties(int count, String price, int imageId)
	{
		//set the iap product image
		ImageView productImage = (ImageView) findViewById(R.id.add_coins_product_image_id);
		productImage.setBackgroundResource(imageId);
		
		TextView tvDetail = (TextView) findViewById(R.id.add_coins_product_count_text_id);
		String coinsText = String.format(getResources().getString(R.string.coins_required_text), count);
		tvDetail.setText(coinsText);
		tvDetail.setTypeface(MFUtils.getTextTypeface(mContext));
		
		TextView tvPrice = (TextView) findViewById(R.id.add_coins_product_price_text_id);
		tvPrice.setText(price);
		tvPrice.setTypeface(MFUtils.getTextTypeface(mContext));
	}
	
	private Context mContext;
}