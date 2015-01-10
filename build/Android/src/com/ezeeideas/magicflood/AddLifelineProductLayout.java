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
		// TODO Auto-generated constructor stub
	}
	
	public AddLifelineProductLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
	}
	
	public void setProperties(int count, int imageId)
	{
		//set the iap product image
		ImageView productImage = (ImageView) findViewById(R.id.add_lifeline_product_image_id);
		productImage.setBackgroundResource(imageId);
		
		TextView tvDetail = (TextView) findViewById(R.id.add_lifeline_product_count_text_id);
		tvDetail.setText(Integer.toString(count));
	}
}