package com.example.mysmartcamera.views;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

import java.lang.ref.WeakReference;
import java.util.Iterator;

public class ProgressView extends View {

	/** 进度条 */
	private Paint mProgressPaint;
	/** 闪 */
	private Paint mActivePaint;
	/** 暂停/中断色块 */
	private Paint mPausePaint;
	/** 回删 */
	private Paint mRemovePaint;
	/** 三秒 */
	private Paint mThreePaint;
	/** 超时 */
	private boolean mStop, mProgressChanged;
	private boolean mActiveState = false;
	/** 最长时长 */
	private int mMaxDuration, mVLineWidth;
	private boolean isShowEnoughTime = false;
	private boolean mIsBack = false;

	public ProgressView(Context paramContext) {
		super(paramContext);
		init();
	}

	public ProgressView(Context paramContext, AttributeSet paramAttributeSet) {
		super(paramContext, paramAttributeSet);
		init();
	}

	public ProgressView(Context paramContext, AttributeSet paramAttributeSet,
                        int paramInt) {
		super(paramContext, paramAttributeSet, paramInt);
		init();
	}

	private void init() {
		mProgressPaint = new Paint();
		mActivePaint = new Paint();
		mPausePaint = new Paint();
		mRemovePaint = new Paint();
		mThreePaint = new Paint();

	}
}
