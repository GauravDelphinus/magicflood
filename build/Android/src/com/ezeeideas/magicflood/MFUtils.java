package com.ezeeideas.magicflood;

import java.util.Hashtable;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.res.Configuration;
import android.graphics.Typeface;



public class MFUtils
{

	public static class FontCache 
	{
		private static Hashtable<String, Typeface> fontCache = new Hashtable<String, Typeface>();

		public static Typeface get(String name, Context context) 
		{
			Typeface tf = fontCache.get(name);
			if(tf == null) 
			{
				try 
				{
					tf = Typeface.createFromAsset(context.getAssets(), name);
				}
				catch (Exception e) 
				{
					return null;
				}
				fontCache.put(name, tf);
			}
			return tf;
		}
	}
	
	public static Typeface getTextTypeface(Context context)
	{
		Typeface face = FontCache.get("ArchitectsDaughter.ttf", context);;
		return face;
	}
	/**
	 * Helper function that returns the current screen size category
	 * @param context
	 * @return
	 */
	public static String getSizeName(Context context) {
	    int screenLayout = context.getResources().getConfiguration().screenLayout;
	    screenLayout &= Configuration.SCREENLAYOUT_SIZE_MASK;

	    switch (screenLayout) {
	    case Configuration.SCREENLAYOUT_SIZE_SMALL:
	        return "small";
	    case Configuration.SCREENLAYOUT_SIZE_NORMAL:
	        return "normal";
	    case Configuration.SCREENLAYOUT_SIZE_LARGE:
	        return "large";
	    case 4: // Configuration.SCREENLAYOUT_SIZE_XLARGE is API >= 9
	        return "xlarge";
	    default:
	        return "undefined";
	    }
	}
	
	public static String getDensityName(Context context) {
	    float density = context.getResources().getDisplayMetrics().density;
	    if (density >= 4.0) {
	        return "xxxhdpi";
	    }
	    if (density >= 3.0) {
	        return "xxhdpi";
	    }
	    if (density >= 2.0) {
	        return "xhdpi";
	    }
	    if (density >= 1.5) {
	        return "hdpi";
	    }
	    if (density >= 1.0) {
	        return "mdpi";
	    }
	    return "ldpi";
	}
	
	public static int prefGetInt(Context context, String pref, int defaultValue)
	{
		SharedPreferences settings;
		settings = context.getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		int retVal = settings.getInt(pref, defaultValue);
		
		return retVal;		
	}
	
	public static void prefPutInt(Context context, String pref, int value)
	{
		SharedPreferences settings;
		settings = context.getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		
		Editor editor = settings.edit();
		editor.putInt(pref, value);
		editor.commit();
	}

}