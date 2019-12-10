#pragma once
#using <system.dll>
#include <math.h>
#include <iostream>
#include <ctime>
#include "fir.h"
#include "kalman.h"
#include "lms.h"
#include "generate.h"

namespace optimalfilters {

#define I 100
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Drawing::Drawing2D;
	//using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	double* input_signal = new double[I];

	/// <summary>
	/// —водка дл€ FormMain
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::RadioButton^  radioButton_sin;
	private: System::Windows::Forms::RadioButton^  radioButton_line;
	private: System::Windows::Forms::Button^  button_kalman;
	private: System::Windows::Forms::Button^  button_lms;
	private: System::Windows::Forms::Button^  button_fir;
	private: System::Windows::Forms::Button^  button_original;
	private: System::Windows::Forms::Button^  button_clear;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::RadioButton^  radioButton_sin_err;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::GroupBox^  groupBox_signal_type;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->radioButton_sin_err = (gcnew System::Windows::Forms::RadioButton());
			this->button_clear = (gcnew System::Windows::Forms::Button());
			this->radioButton_sin = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_line = (gcnew System::Windows::Forms::RadioButton());
			this->button_kalman = (gcnew System::Windows::Forms::Button());
			this->button_lms = (gcnew System::Windows::Forms::Button());
			this->button_fir = (gcnew System::Windows::Forms::Button());
			this->button_original = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox_signal_type = (gcnew System::Windows::Forms::GroupBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->groupBox_signal_type->SuspendLayout();
			this->SuspendLayout();
			// 
			// radioButton_sin_err
			// 
			this->radioButton_sin_err->AutoSize = true;
			this->radioButton_sin_err->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton_sin_err->Location = System::Drawing::Point(6, 81);
			this->radioButton_sin_err->Name = L"radioButton_sin_err";
			this->radioButton_sin_err->Size = System::Drawing::Size(116, 24);
			this->radioButton_sin_err->TabIndex = 7;
			this->radioButton_sin_err->TabStop = true;
			this->radioButton_sin_err->Text = L"Sine (error)";
			this->radioButton_sin_err->UseVisualStyleBackColor = true;
			// 
			// button_clear
			// 
			this->button_clear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button_clear->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_clear->Location = System::Drawing::Point(15, 415);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(191, 37);
			this->button_clear->TabIndex = 6;
			this->button_clear->Text = L"Clear chart";
			this->button_clear->UseVisualStyleBackColor = true;
			this->button_clear->Click += gcnew System::EventHandler(this, &FormMain::button_clear_Click);
			// 
			// radioButton_sin
			// 
			this->radioButton_sin->AutoSize = true;
			this->radioButton_sin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton_sin->Location = System::Drawing::Point(6, 54);
			this->radioButton_sin->Name = L"radioButton_sin";
			this->radioButton_sin->Size = System::Drawing::Size(157, 24);
			this->radioButton_sin->TabIndex = 5;
			this->radioButton_sin->Text = L"Sine (dispersion)";
			this->radioButton_sin->UseVisualStyleBackColor = true;
			// 
			// radioButton_line
			// 
			this->radioButton_line->AutoSize = true;
			this->radioButton_line->Checked = true;
			this->radioButton_line->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton_line->Location = System::Drawing::Point(6, 27);
			this->radioButton_line->Name = L"radioButton_line";
			this->radioButton_line->Size = System::Drawing::Size(62, 24);
			this->radioButton_line->TabIndex = 4;
			this->radioButton_line->TabStop = true;
			this->radioButton_line->Text = L"Line";
			this->radioButton_line->UseVisualStyleBackColor = true;
			// 
			// button_kalman
			// 
			this->button_kalman->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button_kalman->Enabled = false;
			this->button_kalman->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_kalman->Location = System::Drawing::Point(15, 346);
			this->button_kalman->Name = L"button_kalman";
			this->button_kalman->Size = System::Drawing::Size(191, 37);
			this->button_kalman->TabIndex = 3;
			this->button_kalman->Text = L"Kalman filter";
			this->button_kalman->UseVisualStyleBackColor = true;
			this->button_kalman->Click += gcnew System::EventHandler(this, &FormMain::button_kalman_Click);
			// 
			// button_lms
			// 
			this->button_lms->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button_lms->Enabled = false;
			this->button_lms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_lms->Location = System::Drawing::Point(15, 303);
			this->button_lms->Name = L"button_lms";
			this->button_lms->Size = System::Drawing::Size(191, 37);
			this->button_lms->TabIndex = 2;
			this->button_lms->Text = L"LMS filter";
			this->button_lms->UseVisualStyleBackColor = true;
			this->button_lms->Click += gcnew System::EventHandler(this, &FormMain::button_lms_Click);
			// 
			// button_fir
			// 
			this->button_fir->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button_fir->Enabled = false;
			this->button_fir->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_fir->Location = System::Drawing::Point(15, 260);
			this->button_fir->Name = L"button_fir";
			this->button_fir->Size = System::Drawing::Size(191, 37);
			this->button_fir->TabIndex = 1;
			this->button_fir->Text = L"FIR filter";
			this->button_fir->UseVisualStyleBackColor = true;
			this->button_fir->Click += gcnew System::EventHandler(this, &FormMain::button_fir_Click);
			// 
			// button_original
			// 
			this->button_original->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button_original->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_original->Location = System::Drawing::Point(15, 188);
			this->button_original->Name = L"button_original";
			this->button_original->Size = System::Drawing::Size(191, 37);
			this->button_original->TabIndex = 0;
			this->button_original->Text = L"Input signal";
			this->button_original->UseVisualStyleBackColor = true;
			this->button_original->Click += gcnew System::EventHandler(this, &FormMain::button_original_Click);
			// 
			// chart1
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			series2->Legend = L"Legend1";
			series2->Name = L"original";
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(809, 622);
			this->chart1->TabIndex = 1;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->chart1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->groupBox_signal_type);
			this->splitContainer1->Panel2->Controls->Add(this->button_clear);
			this->splitContainer1->Panel2->Controls->Add(this->button_original);
			this->splitContainer1->Panel2->Controls->Add(this->button_fir);
			this->splitContainer1->Panel2->Controls->Add(this->button_lms);
			this->splitContainer1->Panel2->Controls->Add(this->button_kalman);
			this->splitContainer1->Size = System::Drawing::Size(1035, 622);
			this->splitContainer1->SplitterDistance = 809;
			this->splitContainer1->TabIndex = 2;
			// 
			// groupBox_signal_type
			// 
			this->groupBox_signal_type->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox_signal_type->Controls->Add(this->radioButton_line);
			this->groupBox_signal_type->Controls->Add(this->radioButton_sin);
			this->groupBox_signal_type->Controls->Add(this->radioButton_sin_err);
			this->groupBox_signal_type->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->groupBox_signal_type->Location = System::Drawing::Point(15, 31);
			this->groupBox_signal_type->Name = L"groupBox_signal_type";
			this->groupBox_signal_type->Size = System::Drawing::Size(191, 121);
			this->groupBox_signal_type->TabIndex = 8;
			this->groupBox_signal_type->TabStop = false;
			this->groupBox_signal_type->Text = L"Signal type";
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1035, 622);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"FormMain";
			this->Text = L"Optimal filters";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->groupBox_signal_type->ResumeLayout(false);
			this->groupBox_signal_type->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_original_Click(System::Object^  sender, System::EventArgs^  e) {
		chart1->Series->Clear();
		chart1->Series->Add("original");
		chart1->Series["original"]->ChartType = SeriesChartType::Line;
		chart1->Series["original"]->Color = Color::Blue;
		if (radioButton_line->Checked) {
			generate_line(input_signal, I);
			for (int i = 0; i < I; i++) {
				chart1->Series["original"]->Points->AddXY(i, input_signal[i]);
			}
		}
		else if (radioButton_sin->Checked) {
			generate_sin_dis(input_signal, I);
			for (int i = 0; i < I; i++) {
				chart1->Series["original"]->Points->AddXY(i, input_signal[i]);
			}
		}
		else {
			generate_sin_err(input_signal, I);
			for (int i = 0; i < I; i++) {
				chart1->Series["original"]->Points->AddXY(i, input_signal[i]);
			}
		}
		button_fir->Enabled = true;
		button_kalman->Enabled = true;
		button_lms->Enabled = true;
	}

private: System::Void button_fir_Click(System::Object^  sender, System::EventArgs^  e) {
	double* filtered_fir = new double[I];
	fir(input_signal, filtered_fir, I);
	chart1->Series->Add("FIR");
	chart1->Series["FIR"]->ChartType = SeriesChartType::Line;
	chart1->Series["FIR"]->Color = Color::Green;
	for (int i = 0; i < I; i++) {
		chart1->Series["FIR"]->Points->AddXY(i, filtered_fir[i]);
	}
}

private: System::Void button_lms_Click(System::Object^  sender, System::EventArgs^  e) {
	double* filtered_lms = new double[I];
	lms(input_signal, filtered_lms, I);
	chart1->Series->Add("LMS");
	chart1->Series["LMS"]->ChartType = SeriesChartType::Line;
	chart1->Series["LMS"]->Color = Color::Violet;
	for (int i = 0; i < I; i++) {
		chart1->Series["LMS"]->Points->AddXY(i, filtered_lms[i]);
	}
}

private: System::Void button_kalman_Click(System::Object^  sender, System::EventArgs^  e) {
	double* filtered_kalman = new double[I];

	double F = 1; //factor of real value to previous real value
	double Q = 2; // measurement noise
	double H = 1; // factor of measured value to real value
	double R = 10; // environment noise

	Kalman_filter* kalman = new Kalman_filter(Q, R, F, H);   // parameters of the filter

	kalman->set_state(input_signal[0], 0.25);        // set the start value of State and Covariance

	for (int i = 0; i < I; i++) {               // 
		kalman->correct(input_signal[i]);             // using the kalman filter
		filtered_kalman[i] = kalman->state;     //
	}
	chart1->Series->Add("kalman");
	chart1->Series["kalman"]->ChartType = SeriesChartType::Line;
	chart1->Series["kalman"]->Color = Color::Red;
	for (int i = 0; i < I; i++) {
		chart1->Series["kalman"]->Points->AddXY(i, filtered_kalman[i]);
	}	
}
private: System::Void button_clear_Click(System::Object^  sender, System::EventArgs^  e) {
	chart1->Series->Clear();
	button_fir->Enabled = false;
	button_kalman->Enabled = false;
	button_lms->Enabled = false;
}
};
}
