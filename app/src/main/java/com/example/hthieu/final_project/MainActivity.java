package com.example.hthieu.final_project;

import android.graphics.Bitmap;
import android.media.Image;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.CvException;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfKeyPoint;
import org.opencv.features2d.DescriptorExtractor;
import org.opencv.features2d.DescriptorMatcher;
import org.opencv.features2d.FeatureDetector;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.logging.Logger;

public class MainActivity extends AppCompatActivity implements CameraBridgeViewBase.CvCameraViewListener2{

    private static final String TAG = "MainActivity";
    TextView result_text;
    static private Mat elep_mat, union_mat, eng_hall_mat;


    private CameraBridgeViewBase mOpenCvCameraView;
    static Mat mGray, mRgba;
    private Mat [] bufImgs = new Mat[1];
    private boolean isMatch;
    static int frame_h;
    static int frame_w;
    Button but;
    static boolean test_bool = false;
    static boolean isProcessing = false;
    static String file_path;
    static String file_elep;
    static String file_union;
    static String file_eng_hall;



    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("opencv_java3");
    }


    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                    Log.d(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                    break;
                default:
                    Log.d(TAG, "Fail to load Opencv");
                    super.onManagerConnected(status);
                    break;
            }
        }
    };



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        result_text = (TextView) findViewById(R.id.result_text);
        result_text.setText("Press Button");

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.camera_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);

        but = (Button) findViewById(R.id.button);
        but.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(!test_bool){
                    isProcessing = true;
                    test_bool = !test_bool;
                    onPause();
                }
                else{
                    if(!isProcessing) {
                        test_bool = !test_bool;
                        onResume();
                    }
                }
            }
        });


        file_elep = Environment.getExternalStorageDirectory().getAbsolutePath() +"/elephan.txt";
        file_union = Environment.getExternalStorageDirectory().getAbsolutePath() +"/union.txt";
        file_eng_hall = Environment.getExternalStorageDirectory().getAbsolutePath() +"/eng_hall.txt";

        preComputeDesc();
        long tStart = System.currentTimeMillis();

        elep_mat = loadMat(file_elep);
        union_mat = loadMat(file_union);
        eng_hall_mat = loadMat(file_eng_hall);



//        for (int i = 0 ; i < 21; i++){
//            Mat temp = loadMat(file_path);
//        }
        long tEnd = System.currentTimeMillis();
        long tDelta = tEnd - tStart;
        double elapsedSeconds = tDelta / 1000.0;
        Toast.makeText(this, Double.toString(elapsedSeconds), Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mOpenCvCameraView != null) {
            mOpenCvCameraView.disableView();
        }
        if(test_bool) {
            try {
                Mat elephant_img = Utils.loadResource(this, R.drawable.elephant, CvType.CV_8UC1);//Highgui.CV_LOAD_IMAGE_COLOR);
              //  Mat elephan_desc = loadMat(file_path);
//                bufImgs[0] = loadMat(file_path);

//                callcheckImg(1);

//                isMatch = createImg(mGray.getNativeObjAddr(), elephant_img.getNativeObjAddr(), elephan_desc.getNativeObjAddr());


                int match_number;
                match_number = checkImg(mGray.getNativeObjAddr(), elep_mat.getNativeObjAddr(), union_mat.getNativeObjAddr(),eng_hall_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr()
                        ,elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr()
                        ,elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr()
                        ,elep_mat.getNativeObjAddr(),elep_mat.getNativeObjAddr());

                switch (match_number){
                    case 0 :    result_text.setText("Elephant!");
                                break;
                    case 2 :    result_text.setText("Union!!");
                                break;
                    case 1 :    result_text.setText("Engineering Hall");
                                break;
                    default:    result_text.setText("Not Found");
                                break;
                }



//                if (isMatch) {
//                    result_text.post(new Runnable() {
//                        public void run() {
//                            result_text.setText("Match Found");
//                        }
//                    });
//                } else {
//                    result_text.post(new Runnable() {
//                        public void run() {
//                            result_text.setText("Match Not Found");
//                        }
//                    });
//                }
                isProcessing = false;
            } catch (IOException e) {
                e.printStackTrace();
                isProcessing = false;
            }

            Toast.makeText(getBaseContext(), "Press Button to back to camera!", Toast.LENGTH_LONG).show();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }


    @Override
    public void onCameraViewStarted(int width, int height) {
        frame_h = height;
        frame_w = width;
        mRgba = new Mat(height,width, CvType.CV_8UC4);
        mGray = new Mat(height,width, CvType.CV_8UC1);
        Log.d(TAG, "height=" + Integer.toString(frame_h) + " width=" + Integer.toString(width));
    }



    @Override
    public void onCameraViewStopped() {
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        mGray = inputFrame.gray();
        mRgba = inputFrame.rgba();
        return mRgba;
    }



    public void preComputeDesc(){
        Mat elephan_desc = new Mat();
//        Mat beckman_desc = new Mat();
        Mat eng_hall_desc = new Mat();
        Mat union_desc = new Mat();
        Mat beckman_desc = new Mat();
        Mat eng_lib_desc = new Mat();
        Mat panda_exp_desc = new Mat();
        Mat csl_desc = new Mat();


        try {
            Mat img1 = Utils.loadResource(this, R.drawable.elephant, CvType.CV_8UC1);//Highgui.CV_LOAD_IMAGE_COLOR);
            getDesc( img1.getNativeObjAddr(), elephan_desc.getNativeObjAddr());

            Mat eng_hall = Utils.loadResource(this, R.drawable.eng_hall, CvType.CV_8UC1);//Highgui.CV_LOAD_IMAGE_COLOR);
//            Mat beckman = Utils.loadResource(this, R.drawable.beckman, CvType.CV_8UC1);//Highgui.CV_LOAD_IMAGE_COLOR);
            getDesc( eng_hall.getNativeObjAddr(), eng_hall_desc.getNativeObjAddr());

            Mat union = Utils.loadResource(this, R.drawable.union, CvType.CV_8UC1);//Highgui.CV_LOAD_IMAGE_COLOR);
            getDesc( union.getNativeObjAddr(), union_desc.getNativeObjAddr());


        } catch (IOException e) {
            e.printStackTrace();
        }




        saveMat(file_elep, elephan_desc);
        saveMat(file_union, eng_hall_desc);
        saveMat(file_eng_hall, union_desc);

        // saveMat(file_path, descriptors);
    }

    //http://stackoverflow.com/questions/26445747/is-there-a-way-of-storing-opencv-javacv-mat-objects-in-a-database
    public final void saveMat(String path, Mat mat) {
        File file = new File(path);

        try {
            int cols = mat.cols();
            byte[] data = new byte[(int) mat.total() * mat.channels()];
            mat.get(0, 0, data);
//            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(path))) {
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
                oos.writeObject(cols);
                oos.writeObject(data);
                oos.close();
            }
        } catch (IOException | ClassCastException ex) {
            System.err.println("ERROR: Could not save mat to file: " + path);
        }


       // Mat mat1 = loadMat(path);
    }

    public final Mat loadMat(String path) {
        try {
            int cols;
            byte[] data;
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(path))) {
                cols = (int) ois.readObject();
                data = (byte[]) ois.readObject();
            }
            Mat mat = new Mat(data.length / cols, cols, CvType.CV_8UC1);
            mat.put(0, 0, data);
            return mat;
        } catch (IOException | ClassNotFoundException | ClassCastException ex) {
            System.err.println("ERROR: Could not load mat from file: " + path);
        }
        return null;
    }



    private void save_img_to_file(){
        Bitmap bmp = null;
        try {
            bmp = Bitmap.createBitmap(mRgba.cols(), mRgba.rows(), Bitmap.Config.ARGB_8888);
            Utils.matToBitmap(mRgba, bmp);
        } catch (CvException e) {
            Log.d(TAG, e.getMessage());
        }

        //mRgba.release();

        FileOutputStream out = null;

        String filename = "frame.png";

        File sd = new File(Environment.getExternalStorageDirectory() + "/frames");
        Log.d(TAG,Environment.getExternalStorageDirectory() + "/frames" );
        boolean success = true;
        if (!sd.exists()) {
            success = sd.mkdir();
        }
        if (success) {
            File dest = new File(sd, filename);

            try {
                out = new FileOutputStream(dest);
                assert bmp != null;
                bmp.compress(Bitmap.CompressFormat.PNG, 100, out); // bmp is your Bitmap instance
                // PNG is a lossless format, the compression factor (100) is ignored

            } catch (Exception e) {
                e.printStackTrace();
                Log.d(TAG, e.getMessage());
            } finally {
                try {
                    if (out != null) {
                        out.close();
                        Log.d(TAG, "OK!!");
                    }
                } catch (IOException e) {
                    Log.d(TAG, e.getMessage() + "Error");
                    e.printStackTrace();
                }
            }
        }
    }

    public native String stringFromJNI();

    public native String validate(long matAddrGr, long matAddrRgba);

    public native int callcheckImg(int vec_num);

    public native int checkImg(long matAddrGr, long descAddr0, long descAddr1, long descAddr2, long descAddr3, long descAddr4,
                               long descAddr5, long descAddr6, long descAddr7, long descAddr8, long descAddr9, long descAddr10,
                               long descAddr11, long descAddr12, long descAddr13, long descAddr14,
                               long descAddr15, long descAddr16, long descAddr17, long descAddr18, long descAddr19, long descAddr20
                               );
    public native boolean createImg(long matAddrGr, long matAddrRBF, long descAddr);

    public native void getDesc(long addrImg, long addDesc);

}
