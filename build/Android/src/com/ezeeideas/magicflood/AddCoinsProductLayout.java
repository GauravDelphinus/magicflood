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
		// TODO Auto-generated constructor stub
	}
	
	public AddCoinsProductLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
	}
	
	public void setProperties(int count, String price, float size, int imageId)
	{
		//set the iap product image
		ImageView productImage = (ImageView) findViewById(R.id.add_coins_product_image_id);
		productImage.setBackgroundResource(imageId);
		
		TextView tvDetail = (TextView) findViewById(R.id.add_coins_product_count_text_id);
		tvDetail.setText(Integer.toString(count));
		tvDetail.setTextSize(size);
		
		TextView tvPrice = (TextView) findViewById(R.id.add_coins_product_price_text_id);
		tvPrice.setText(price);
	}
}