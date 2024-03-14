#pragma once
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <msclr/marshal_cppstd.h>
#include <sstream>
#include <conio.h>
#include <assert.h>
#include <algorithm>

using namespace System::Runtime::InteropServices;
using namespace cv;
using namespace msclr::interop;
using namespace System::Data;
using namespace System::Drawing;
//static Mat img;
static Mat drawhistogram(Mat img)
{
	// draw histogram
	/// Separate the image in 3 places ( B, G and R )
	std::vector<Mat> bgr_planes;
	split(img, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 1024; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));//white, (0,0,0) is black

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);//blue
		line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);//green
		line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);//red
	}
	return histImage;
}

namespace homework10asvdf {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label9;
	protected:
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txt_xi_R;
	private: System::Windows::Forms::TextBox^ txt_xi_G;
	private: System::Windows::Forms::TextBox^ txt_xi_B;
	private: System::Windows::Forms::TextBox^ txt_max_w_R;
	private: System::Windows::Forms::TextBox^ txt_max_w_G;
	private: System::Windows::Forms::TextBox^ txt_max_Ga;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::TextBox^ txt_max_w_B;
	private: System::Windows::Forms::NumericUpDown^ UD_Sigma;
	private: System::Windows::Forms::NumericUpDown^ UD_mi;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::OpenFileDialog^ oFD;
	private: System::Windows::Forms::PictureBox^ out_hist_box;
	private: System::Windows::Forms::PictureBox^ out_img_box;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::PictureBox^ ori_hist_box;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::PictureBox^ ori_img_box;
	private: System::Windows::Forms::Button^ button1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txt_xi_R = (gcnew System::Windows::Forms::TextBox());
			this->txt_xi_G = (gcnew System::Windows::Forms::TextBox());
			this->txt_xi_B = (gcnew System::Windows::Forms::TextBox());
			this->txt_max_w_R = (gcnew System::Windows::Forms::TextBox());
			this->txt_max_w_G = (gcnew System::Windows::Forms::TextBox());
			this->txt_max_Ga = (gcnew System::Windows::Forms::TextBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txt_max_w_B = (gcnew System::Windows::Forms::TextBox());
			this->UD_Sigma = (gcnew System::Windows::Forms::NumericUpDown());
			this->UD_mi = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->oFD = (gcnew System::Windows::Forms::OpenFileDialog());
			this->out_hist_box = (gcnew System::Windows::Forms::PictureBox());
			this->out_img_box = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->ori_hist_box = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->ori_img_box = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UD_Sigma))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UD_mi))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->out_hist_box))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->out_img_box))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ori_hist_box))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ori_img_box))->BeginInit();
			this->SuspendLayout();
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(15, 270);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(33, 16);
			this->label9->TabIndex = 14;
			this->label9->Text = L"xi_R";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(15, 227);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(33, 16);
			this->label8->TabIndex = 13;
			this->label8->Text = L"xi_G";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(15, 188);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(32, 16);
			this->label7->TabIndex = 2;
			this->label7->Text = L"xi_B";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(15, 147);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(65, 16);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Max_w_R";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(15, 109);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 16);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Max_w_G";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(15, 69);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 16);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Max_w_B";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(73, 16);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Max_w_Ga";
			// 
			// txt_xi_R
			// 
			this->txt_xi_R->Location = System::Drawing::Point(94, 267);
			this->txt_xi_R->Name = L"txt_xi_R";
			this->txt_xi_R->Size = System::Drawing::Size(101, 22);
			this->txt_xi_R->TabIndex = 8;
			// 
			// txt_xi_G
			// 
			this->txt_xi_G->Location = System::Drawing::Point(94, 224);
			this->txt_xi_G->Name = L"txt_xi_G";
			this->txt_xi_G->Size = System::Drawing::Size(101, 22);
			this->txt_xi_G->TabIndex = 7;
			// 
			// txt_xi_B
			// 
			this->txt_xi_B->Location = System::Drawing::Point(94, 185);
			this->txt_xi_B->Name = L"txt_xi_B";
			this->txt_xi_B->Size = System::Drawing::Size(101, 22);
			this->txt_xi_B->TabIndex = 6;
			// 
			// txt_max_w_R
			// 
			this->txt_max_w_R->Location = System::Drawing::Point(94, 144);
			this->txt_max_w_R->Name = L"txt_max_w_R";
			this->txt_max_w_R->Size = System::Drawing::Size(101, 22);
			this->txt_max_w_R->TabIndex = 5;
			// 
			// txt_max_w_G
			// 
			this->txt_max_w_G->Location = System::Drawing::Point(94, 109);
			this->txt_max_w_G->Name = L"txt_max_w_G";
			this->txt_max_w_G->Size = System::Drawing::Size(101, 22);
			this->txt_max_w_G->TabIndex = 4;
			// 
			// txt_max_Ga
			// 
			this->txt_max_Ga->Location = System::Drawing::Point(94, 27);
			this->txt_max_Ga->Name = L"txt_max_Ga";
			this->txt_max_Ga->Size = System::Drawing::Size(101, 22);
			this->txt_max_Ga->TabIndex = 2;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label9);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->txt_xi_R);
			this->groupBox3->Controls->Add(this->txt_xi_G);
			this->groupBox3->Controls->Add(this->txt_xi_B);
			this->groupBox3->Controls->Add(this->txt_max_w_R);
			this->groupBox3->Controls->Add(this->txt_max_w_G);
			this->groupBox3->Controls->Add(this->txt_max_w_B);
			this->groupBox3->Controls->Add(this->txt_max_Ga);
			this->groupBox3->Location = System::Drawing::Point(30, 300);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 317);
			this->groupBox3->TabIndex = 8;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Compensation Weights";
			// 
			// txt_max_w_B
			// 
			this->txt_max_w_B->Location = System::Drawing::Point(94, 66);
			this->txt_max_w_B->Name = L"txt_max_w_B";
			this->txt_max_w_B->Size = System::Drawing::Size(101, 22);
			this->txt_max_w_B->TabIndex = 3;
			// 
			// UD_Sigma
			// 
			this->UD_Sigma->Location = System::Drawing::Point(143, 61);
			this->UD_Sigma->Name = L"UD_Sigma";
			this->UD_Sigma->Size = System::Drawing::Size(50, 22);
			this->UD_Sigma->TabIndex = 6;
			this->UD_Sigma->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32, 0, 0, 0 });
			// 
			// UD_mi
			// 
			this->UD_mi->Location = System::Drawing::Point(143, 22);
			this->UD_mi->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->UD_mi->Name = L"UD_mi";
			this->UD_mi->Size = System::Drawing::Size(50, 22);
			this->UD_mi->TabIndex = 2;
			this->UD_mi->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 127, 0, 0, 0 });
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 63);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(122, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Standard Deviation";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(101, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Mean Gaussian";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->UD_Sigma);
			this->groupBox4->Controls->Add(this->UD_mi);
			this->groupBox4->Controls->Add(this->label2);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Location = System::Drawing::Point(30, 194);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(200, 100);
			this->groupBox4->TabIndex = 6;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Gaussian Tenplate";
			// 
			// oFD
			// 
			this->oFD->FileName = L"oFD";
			// 
			// out_hist_box
			// 
			this->out_hist_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->out_hist_box->Location = System::Drawing::Point(395, 21);
			this->out_hist_box->Name = L"out_hist_box";
			this->out_hist_box->Size = System::Drawing::Size(692, 322);
			this->out_hist_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->out_hist_box->TabIndex = 1;
			this->out_hist_box->TabStop = false;
			// 
			// out_img_box
			// 
			this->out_img_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->out_img_box->Location = System::Drawing::Point(6, 21);
			this->out_img_box->Name = L"out_img_box";
			this->out_img_box->Size = System::Drawing::Size(383, 322);
			this->out_img_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->out_img_box->TabIndex = 0;
			this->out_img_box->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->out_hist_box);
			this->groupBox2->Controls->Add(this->out_img_box);
			this->groupBox2->Location = System::Drawing::Point(253, 392);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(1093, 349);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Output";
			// 
			// ori_hist_box
			// 
			this->ori_hist_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ori_hist_box->Location = System::Drawing::Point(395, 21);
			this->ori_hist_box->Name = L"ori_hist_box";
			this->ori_hist_box->Size = System::Drawing::Size(692, 322);
			this->ori_hist_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ori_hist_box->TabIndex = 1;
			this->ori_hist_box->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->ori_hist_box);
			this->groupBox1->Controls->Add(this->ori_img_box);
			this->groupBox1->Location = System::Drawing::Point(253, 37);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(1093, 349);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Original";
			// 
			// ori_img_box
			// 
			this->ori_img_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ori_img_box->Location = System::Drawing::Point(6, 21);
			this->ori_img_box->Name = L"ori_img_box";
			this->ori_img_box->Size = System::Drawing::Size(383, 322);
			this->ori_img_box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ori_img_box->TabIndex = 0;
			this->ori_img_box->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(23, 58);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(207, 102);
			this->button1->TabIndex = 4;
			this->button1->Text = L"ASVDF";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1364, 756);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UD_Sigma))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UD_mi))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->out_hist_box))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->out_img_box))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ori_hist_box))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ori_img_box))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		oFD->Filter = "Image Files|*.bmp; *.jpg; *.png; *.pgm|All Files (*.*)|*.*||";
		oFD->Title = "Select an image file";
		oFD->Multiselect = "True";

		int number_of_files;
		array <System::String^>^ filenames_src;

		if (oFD->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			filenames_src = oFD->FileNames;
			number_of_files = oFD->FileNames->Length;
		}

		int step = 0;

		while (step < number_of_files)
		{
			System::String^ OpenFileName;
			OpenFileName = filenames_src[step];
			OpenFileName = OpenFileName->Replace("\\", "\\\\");
			char* imgname;
			imgname = (char*)Marshal::StringToHGlobalAnsi(OpenFileName).ToPointer();

			Mat img = cv::imread(imgname);
			resize(img, img, cv::Size(128, 128));
			Mat img_src;
			
			img.convertTo(img_src, CV_32F);

			int m = img_src.rows;
			int n = img_src.cols;

			Mat b_channel = Mat_<float>(m, n);
			Mat g_channel = Mat_<float>(m, n);
			Mat r_channel = Mat_<float>(m, n);

			// Split image into R, G, B channel
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					b_channel.at<float>(cv::Point(i, j)) = img_src.at<Vec3f>(cv::Point(i, j))[0];
					g_channel.at<float>(cv::Point(i, j)) = img_src.at<Vec3f>(cv::Point(i, j))[1];
					r_channel.at<float>(cv::Point(i, j)) = img_src.at<Vec3f>(cv::Point(i, j))[2];
				}
			}
			// Compute Gaussian Matrix
			float mi = (float)UD_mi->Value;
			float sigma = (float)UD_Sigma->Value;

			Mat mat_Ga = Mat(m, n, CV_32F);
			randn(mat_Ga, mi, sqrt(sigma));

			// Perform DFT through R, G, B and Ga
			Mat b_padded, g_padded, r_padded, ga_padded;
			int m_padded = getOptimalDFTSize(img_src.rows);
			int n_padded = getOptimalDFTSize(img_src.cols);

			copyMakeBorder(b_channel, b_padded, 0, m_padded - m, 0, n_padded - n, BORDER_CONSTANT, Scalar::all(0));
			copyMakeBorder(g_channel, g_padded, 0, m_padded - m, 0, n_padded - n, BORDER_CONSTANT, Scalar::all(0));
			copyMakeBorder(r_channel, r_padded, 0, m_padded - m, 0, n_padded - n, BORDER_CONSTANT, Scalar::all(0));
			copyMakeBorder(mat_Ga, ga_padded, 0, m_padded - m, 0, n_padded - n, BORDER_CONSTANT, Scalar::all(0));

			Mat b_planes[] = { Mat_<float>(b_padded), Mat::zeros(b_padded.size(), CV_32F) };
			Mat g_planes[] = { Mat_<float>(g_padded), Mat::zeros(g_padded.size(), CV_32F) };
			Mat r_planes[] = { Mat_<float>(r_padded), Mat::zeros(r_padded.size(), CV_32F) };
			Mat ga_planes[] = { Mat_<float>(ga_padded), Mat::zeros(ga_padded.size(), CV_32F) };
						
			Mat complex_b, complex_g, complex_r, complex_ga;

			merge(b_planes, 2, complex_b);
			merge(g_planes, 2, complex_g);
			merge(r_planes, 2, complex_r);
			merge(ga_planes, 2, complex_ga);

			Mat b_dft, g_dft, r_dft, ga_dft;
			dft(complex_b, b_dft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
			dft(complex_g, g_dft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
			dft(complex_r, r_dft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
			dft(complex_ga, ga_dft, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);

			Mat b_dft_planes[] = { Mat::zeros(b_padded.size(), CV_32F), Mat::zeros(b_padded.size(), CV_32F) };
			Mat g_dft_planes[] = { Mat::zeros(g_padded.size(), CV_32F), Mat::zeros(g_padded.size(), CV_32F) };
			Mat r_dft_planes[] = { Mat::zeros(r_padded.size(), CV_32F), Mat::zeros(r_padded.size(), CV_32F) };
			Mat ga_dft_planes[] = { Mat::zeros(ga_padded.size(), CV_32F), Mat::zeros(ga_padded.size(), CV_32F) };

			split(b_dft, b_dft_planes);
			split(g_dft, g_dft_planes);
			split(r_dft, r_dft_planes);
			split(ga_dft, ga_dft_planes);
			
			Mat re_b = b_dft_planes[0], im_b = b_dft_planes[1];
			Mat re_g = g_dft_planes[0], im_g = g_dft_planes[1];
			Mat re_r = r_dft_planes[0], im_r = r_dft_planes[1];
			Mat re_ga = ga_dft_planes[0], im_ga = ga_dft_planes[1];

			Mat b_magnitude = Mat::zeros(b_padded.size(), CV_32F);
			Mat g_magnitude = Mat::zeros(g_padded.size(), CV_32F);
			Mat r_magnitude = Mat::zeros(r_padded.size(), CV_32F);
			Mat ga_magnitude = Mat::zeros(ga_padded.size(), CV_32F);

			magnitude(re_b, im_b, b_magnitude);
			magnitude(re_g, im_g, g_magnitude);
			magnitude(re_r, im_r, r_magnitude);
			magnitude(re_ga, im_ga, ga_magnitude);

			Mat b_phase = Mat::zeros(b_padded.size(), CV_32F);
			Mat g_phase = Mat::zeros(g_padded.size(), CV_32F);
			Mat r_phase = Mat::zeros(r_padded.size(), CV_32F);

			phase(re_b, im_b, b_phase);
			phase(re_g, im_g, g_phase);
			phase(re_r, im_r, r_phase);

			// Find the compensation weight 
			float mean_b = mean(b_magnitude).val[0];
			float mean_g = mean(g_magnitude).val[0];
			float mean_r = mean(r_magnitude).val[0];

			float max_temp = max(mean_b, mean_g);
			float max_mean = max(mean_r, max_temp);

			Mat w_ga, u_ga, vt_ga;
			SVD::compute(ga_magnitude,w_ga, u_ga, vt_ga, SVD::NO_UV);
			float max_w_ga = w_ga.at<float>(cv::Point(0, 0));
			txt_max_Ga->Text = max_w_ga.ToString(); txt_max_Ga->Refresh();

			Mat w_b, u_b, vt_b;
			SVD::compute(b_magnitude, w_b, u_b, vt_b, SVD::NO_UV);
			float max_w_b = w_b.at<float>(cv::Point(0, 0));
			txt_max_w_B->Text = max_w_b.ToString(); txt_max_w_B->Refresh();

			Mat w_g, u_g, vt_g;
			SVD::compute(g_magnitude, w_g, u_g, vt_g, SVD::NO_UV);
			float max_w_g = w_g.at<float>(cv::Point(0, 0));
			txt_max_w_G->Text = max_w_g.ToString(); txt_max_w_G->Refresh();

			Mat w_r, u_r, vt_r;
			SVD::compute(r_magnitude, w_r, u_r, vt_r, SVD::NO_UV);
			float max_w_r = w_r.at<float>(cv::Point(0, 0));
			txt_max_w_R->Text = max_w_r.ToString(); txt_max_w_R->Refresh();

			float xi_b = sqrt((max_mean / mean_b) * (max_w_ga / max_w_b));
			float xi_g = sqrt((max_mean / mean_g) * (max_w_ga / max_w_g));
			float xi_r = sqrt((max_mean / mean_r) * (max_w_ga / max_w_r));

			txt_xi_B->Text = xi_b.ToString(); txt_xi_B->Refresh();
			txt_xi_G->Text = xi_g.ToString(); txt_xi_G->Refresh();
			txt_xi_R->Text = xi_r.ToString(); txt_xi_R->Refresh();

			//Update the sigma of SVD
			Mat svd_w_b, svd_u_b, svd_vt_b;
			SVD::compute(b_magnitude, svd_w_b, svd_u_b, svd_vt_b, SVD::FULL_UV);
			for (int i = 0; i < svd_w_b.cols; i++)
			{
				for (int j = 0; j < svd_w_b.rows; j++)
				{
					svd_w_b.at<float>(cv::Point(i, j)) = xi_b * svd_w_b.at<float>(cv::Point(i, j));
				}
			}
			b_magnitude = svd_u_b * Mat::diag(svd_w_b) * svd_vt_b;

			Mat svd_w_g, svd_u_g, svd_vt_g;
			SVD::compute(g_magnitude, svd_w_g, svd_u_g, svd_vt_g, SVD::FULL_UV);
			for (int i = 0; i < svd_w_g.cols; i++)
			{
				for (int j = 0; j < svd_w_g.rows; j++)
				{
					svd_w_g.at<float>(cv::Point(i, j)) = xi_g * svd_w_g.at<float>(cv::Point(i, j));
				}
			}
			g_magnitude = svd_u_g * Mat::diag(svd_w_g) * svd_vt_g;

			Mat svd_w_r, svd_u_r, svd_vt_r;
			SVD::compute(r_magnitude, svd_w_r, svd_u_r, svd_vt_r, SVD::FULL_UV);
			for (int i = 0; i < svd_w_r.cols; i++)
			{
				for (int j = 0; j < svd_w_r.rows; j++)
				{
					svd_w_r.at<float>(cv::Point(i, j)) = xi_r * svd_w_r.at<float>(cv::Point(i, j));
				}
			}
			r_magnitude = svd_u_r * Mat::diag(svd_w_r) * svd_vt_r;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					b_dft_planes[0].at<float>(cv::Point(i, j))
						= b_magnitude.at<float>(cv::Point(i, j)) * cos(b_phase.at<float>(cv::Point(i, j)));
					b_dft_planes[1].at<float>(cv::Point(i, j))
						= b_magnitude.at<float>(cv::Point(i, j)) * sin(b_phase.at<float>(cv::Point(i, j)));

					g_dft_planes[0].at<float>(cv::Point(i, j))
						= g_magnitude.at<float>(cv::Point(i, j)) * cos(g_phase.at<float>(cv::Point(i, j)));
					g_dft_planes[1].at<float>(cv::Point(i, j))
						= g_magnitude.at<float>(cv::Point(i, j)) * sin(g_phase.at<float>(cv::Point(i, j)));

					r_dft_planes[0].at<float>(cv::Point(i, j))
						= r_magnitude.at<float>(cv::Point(i, j)) * cos(r_phase.at<float>(cv::Point(i, j)));
					r_dft_planes[1].at<float>(cv::Point(i, j))
						= r_magnitude.at<float>(cv::Point(i, j)) * sin(r_phase.at<float>(cv::Point(i, j)));
				}
			}

			merge(b_dft_planes, 2, b_dft);
			merge(g_dft_planes, 2, g_dft);
			merge(r_dft_planes, 2, r_dft);

			Mat b_idft, g_idft, r_idft;
			idft(b_dft, b_idft, DFT_INVERSE | DFT_REAL_OUTPUT);
			idft(g_dft, g_idft, DFT_INVERSE | DFT_REAL_OUTPUT);
			idft(r_dft, r_idft, DFT_INVERSE | DFT_REAL_OUTPUT);

			Mat dst = img_src;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					dst.at<Vec3f>(cv::Point(i, j))[0] = b_idft.at<float>(cv::Point(i, j));
					dst.at<Vec3f>(cv::Point(i, j))[1] = g_idft.at<float>(cv::Point(i, j));
					dst.at<Vec3f>(cv::Point(i, j))[2] = r_idft.at<float>(cv::Point(i, j));
				}
			}
			
			dst.convertTo(dst, CV_8UC3);
			cv::normalize(dst, dst, 0, 255, NORM_MINMAX);
			//cv::imshow("Original", img);
			//cv::imshow("Output", dst);
			Mat img_hist = drawhistogram(img);
			Mat dst_hist = drawhistogram(dst);
			//imwrite("ori_img_4.bmp", img);
			//imwrite("ori_hist_4.bmp", img_hist);
			//imwrite("asvdf_img_4.bmp", dst);
			//imwrite("asvdf_hist_4In.bmp", dst_hist);

			int row_s = (img.rows / 4) * 4;
			int col_s = (img.cols / 4) * 4;

			Mat img_s = Mat(row_s, col_s, img.type());
			resize(img, img_s, img_s.size(), 0, 0, INTER_LINEAR);
			ori_img_box->Image = gcnew
				System::Drawing::Bitmap(img_s.size().width, img_s.size().height, img_s.step,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)img_s.data);
			ori_img_box->Refresh();

			Mat dst_s = Mat(row_s, col_s, img.type());
			resize(dst, dst_s, dst_s.size(), 0, 0, INTER_LINEAR);
			out_img_box->Image = gcnew
				System::Drawing::Bitmap(dst_s.size().width, dst_s.size().height, dst_s.step,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)dst_s.data);
			out_img_box->Refresh();

			int row_h = (img_hist.rows / 4) * 4;
			int col_h = (img_hist.cols / 4) * 4;

			Mat ori_hist_s = Mat(row_h, col_h, img_hist.type());
			resize(img_hist, ori_hist_s, ori_hist_s.size(), 0, 0, INTER_LINEAR);
			ori_hist_box->Image = gcnew
				System::Drawing::Bitmap(ori_hist_s.size().width, ori_hist_s.size().height, ori_hist_s.step,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)ori_hist_s.data);
			ori_hist_box->Refresh();
			
			Mat asvd_hist_s = Mat(row_h, col_h, img_hist.type());
			resize(dst_hist, asvd_hist_s, asvd_hist_s.size(), 0, 0, INTER_LINEAR);
			out_hist_box->Image = gcnew
				System::Drawing::Bitmap(asvd_hist_s.size().width, asvd_hist_s.size().height, asvd_hist_s.step,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)asvd_hist_s.data);
			out_hist_box->Refresh();

			step++;
		}
		
		
	}
};
}
