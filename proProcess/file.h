#pragma once
#ifndef _FILE_
#define _CRT_SECURE_NO_WARNINGS
#define _FILE_
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<list>
#include<string>
#include<Windows.h>
#include<direct.h>
#include<stack>
#include"myException.h"
#define CHARACTER_MAX 257
#define READ_MAX 10
#define ENTER ""

#define FILE_LINE_MAX_NUMBER 1024
#define SYMBOL_SIZE 15
#define KEYWORD_TABLE 53
	using namespace std;
//	extern enum Gram;
	//using FilePtr = FILE*;
	class MFile //���ļ�����
	{
	public:
		unsigned long long get_cur_line();//��ȡ��ǰ��
		static string split_file_dir(string fullPath);//��ȡ�ļ�·��
		static string split_file_dir(char* fullPath);
		static string split_file_name(string fullPath);//��ȡ�ļ���
		static string split_file_name(char* fullPath);
		static string remove_tabs_and_lineComments(string str);
		static list<list<string>>& remove_blank(list<list<string>>& token);
		 bool save_file(list<string>& vec);
		 bool save_token_file(list<list<string>>& token);
		
		 vector<string>& get_removed_text();
		 MFile(string filePath);
		/*���ܣ���ȡ���ŵĴ�С*/
		unsigned long long get_token_size();//��ȡ���Ŵ�С
		MFile() ;
		bool set_file_path(string filePath);//�����ļ� ��
		void roll_back();//�ع�
		void roll_back(int val);
		virtual string get_token();//��ȡ����
		string get_file();//��ȡ�ļ���
		bool get_flag() { return flag; }
		bool read_file();
		string& get_filename();
		string& get_fileDir();
		vector<string> get_tokenVec();
	protected:
		bool flag;//����ļ��Ƿ�ɹ��� 
		//��ȡ�ļ�
		unsigned long long curLine;//��ǰ�洢���ŵ��±�
	//	virtual	bool read_file() = 0;//��ȡ�ļ�
		string rellback;//�ع�ֵ
		list<list<string>>token;//�洢����
		vector<string>vec;
		stack<string>rellbackStack;
		std::string filename,fileDir,filePath,savefilePath;//�ļ���
		bool lineFeed;//���з�
	};


#endif


