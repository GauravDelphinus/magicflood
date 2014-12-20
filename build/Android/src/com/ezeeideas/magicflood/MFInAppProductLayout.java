package com.ezeeideas.magicflood;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MFInAppProductLayout extends LinearLayout
{
	public MFInAppProductLayout(Context context) 
	{
		super(context);
		// TODO Auto-generated constructor stub
	}
	
	public MFInAppProductLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
	}
	
	public void setProperties(String title, String price, boolean isProvisioned, boolean isFree, int imageId)
	{
		//set the iap product image
		ImageView productImage = (ImageView) findViewById(R.id.image_iap_pic_id);
		productImage.setBackgroundResource(imageId);
		
		setProperties(title, price, isProvisioned, isFree);
	}
	
	public void setProperties(String title, String price, boolean isProvisioned, boolean isFree)
	{
		TextView tvDetail = (TextView) findViewById(R.id.textview_iap_detail_id);
		tvDetail.setText(title);
		
		TextView tvPrice = (TextView) findViewById(R.id.textview_price_id);
		ImageView imageView = (ImageView) findViewById(R.id.image_iap_status_id);
		
		if (isFree) //set free text if the product is free
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setBackgroundResource(R.drawable.background_iap_provisioned);
			
			tvPrice.setText(getResources().getText(R.string.store_iap_free_text));
		}
		else if (isProvisioned)
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setBackgroundResource(R.drawable.background_iap_provisioned);
			
			//already provisioned, so don't show the price
			tvPrice.setText(getResources().getText(R.string.store_iap_provisioned_text));
		}
		else
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setBackgroundResource(R.drawable.background_iap_not_provisioned);
			
			//set the price
			tvPrice.setText(price);
		}
		
	}
	
	public void updatedProvisioningStatus(boolean isProvisioned)
	{
		ImageView imageView = (ImageView) findViewById(R.id.image_iap_status_id);
		if (isProvisioned)
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setBackgroundResource(R.drawable.background_iap_provisioned);
		}
		else
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setBackgroundResource(R.drawable.background_iap_not_provisioned);
		}
	}
}