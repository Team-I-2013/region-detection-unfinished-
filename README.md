RGB値を分解
赤色が他の色より1.5倍以上あるピクセルを検出
Mat lab_img,img,img_Result, r_img, g_img,b_img;
		cvtColor(src_img, lab_img, CV_BGR2Lab);

		vector<Mat> planes;
		split(lab_img, planes);
		threshold(planes[2], r_img, 100, 255, THRESH_BINARY);
		img=10*planes[2]/planes[0];
		threshold(img, g_img,15, 255, THRESH_BINARY);
		img=10*planes[2]/planes[1];
		threshold(img, b_img, 15, 255., THRESH_BINARY);
		img=g_img+b_img;
		img_Result=img+r_img;
		
最も大きい領域の計算
		 vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		cv::findContours(img_Result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		int maxk = 0;
		double tmparea, maxarea = cv::contourArea(Mat(contours[0]));
		for ( size_t k = 1; k < contours.size(); k++) {
		 if ((tmparea = cv::contourArea(Mat(contours[k]))) > maxarea) {
			maxk = k; maxarea = tmparea;
		 }
		}
	
エラーが出ないし、カメラも読み込み中で動かない。
とりあえず現状のプログラムコード。
