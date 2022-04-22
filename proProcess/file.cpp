#include"file.h"
#define GRAM_CREATE_POSI 79

MFile::MFile(string filename):MFile() {
		set_file_path(filename);
	}
	/*

	���ܣ���ȡ���ŵĴ�С
	*/
	unsigned long long MFile::get_token_size()
	{
		return token.size();
	}

	MFile::MFile()
	{
		flag = false; curLine = 1; 
	}

	inline bool MFile::set_file_path(string filePath)
	{
		ifstream input(filePath);

		try {
			if (!input) {
				throw  FileError(filePath);
			}
		}
		catch (FileError& e) {
			e.showExceptionInform();
			return false;
			flag = false;
		}
		this->filePath = filePath;
		this->fileDir = split_file_dir(filePath);
		this->filename = split_file_name(filePath);
		this->savefilePath = fileDir+"\\" + filename + ".lex";
		flag = true;
		return true;

	}
	/*
	����:void
	���ܣ��ع�һ����Ԫ��token������
	�����void

	*/
	void MFile::roll_back()
	{
		if (lineFeed) {
			list<string>temp;
			temp.push_back(rellback);
			token.push_front(temp);
			curLine--;
			return;
		}
		else {
			list<list<string>>::iterator iter = token.begin();
			iter->push_front(rellback);
		}
	}
	void MFile::roll_back(int val)
	{
		if (lineFeed) {
			list<string>temp;
			for (int i = 0; i < val; i++) {
				string temp2 = rellbackStack.top();
				rellbackStack.pop();
				temp.push_back(temp2);
			}
			temp.push_back(rellback);
			token.push_front(temp);
			curLine--;
			return;
		}
		else {
			list<list<string>>::iterator iter = token.begin();
			for (int i = 0; i < val; i++) {
				string temp2 = rellbackStack.top();
				rellbackStack.pop();
				iter->push_front(temp2);
			}	
		}
	}
	/*
	���룺void
	���ܣ���token�����л�ȡһ����Ԫ��С��ֵ,����tokenɾ����������
	�����string
	*/
	string MFile::get_token()
	{
		string str;
		if (token.empty() || !flag)return ENTER;//����Ϊ�գ�����EOF
		rellback = "";
		if (((token.front()).size() <= 0) ||
			((token.front()).size() <= 1 && (token.front().front() == ""))) {
			token.pop_front();
			curLine++;
			lineFeed = true;
			return "";
		}
		list<list<string>>::iterator begin;
		begin = token.begin();
		list<string>::iterator iter;
		iter = (*begin).begin();
		str = *iter;
		begin->pop_front();
		rellback = str;
		rellbackStack.push(str);
		lineFeed = false;
		return str;
	}

	string MFile::get_file()
	{
		return filename;
	}

	string MFile::split_file_name(string fullPath)
	{
		string fileName = "";
		int index1 = fullPath.find_last_of('\\');
		int index2 = fullPath.find_last_of('.');
		fileName = fullPath.substr(index1 + 1, index2 - index1-1);
		return fileName;
	}
	unsigned long long MFile::get_cur_line()
	{
		return curLine;
	}
	string MFile::split_file_dir(string fullPath)
	{
		string filePath = "";
		bool flag = true;
		for (int i = fullPath.length() - 1; i >= 0; i--) {
			filePath = fullPath[i] + filePath;
			if (fullPath[i] == 92 && flag) {
				filePath = "";
				flag = !flag;
			}
			//else if (fullPath[i] == 92)break;
		}
		return filePath;
	}
	string MFile::split_file_dir(char* fullPath)
	{
		string filePath = "";
		int i;
		for (i = 0; fullPath[i] != '\0'; i++)
			filePath = fullPath[i];
		return split_file_dir(filePath);
	}
	string MFile::split_file_name(char* fullPath)
	{
		string filePath = "";
		int i;
		for (i = 0; fullPath[i] != '\0'; i++)
			filePath = fullPath[i];
		return split_file_name(filePath);
	}

	string MFile::remove_tabs_and_lineComments(string str)
	{
		string temp = "";
		bool flag = false;
		int index = str.find("#include", 0);
		if (index != -1) {
			return "";
		}
			for (int i = 0; i < str.size(); i++)
				if (str[i] == '\t')
					continue;
				else {
					if (str[i] == '"')flag = !flag;
					else if ((!flag) && ((str[i] == '/') && (i + 1 < str.size()) && (str[i + 1] == '/')))break;
					temp += str[i];
				}
		
		return temp;
	}

	list<list<string>>& MFile::remove_blank(list<list<string>>& token)
	{
		for (list<list<string>>::iterator iterBegin = token.begin(),
			iterEnd = token.end(); iterBegin != iterEnd;) {
			
			for (list<string>::iterator iter2Begin = (*iterBegin).begin(),
				iter2End = (*iterBegin).end(); iter2Begin != iter2End; ) {
				if ((*iter2Begin) == " "||(*iter2Begin)=="") {
					list<string>::iterator temp = iter2Begin;
					iter2Begin++;
					(*iterBegin).erase(temp);
				}
				else iter2Begin++;
			}
			if ((*iterBegin).size() == 0) {
				list<list<string>>::iterator temp = iterBegin;
				iterBegin++;
				token.erase(temp);
			}
			else  iterBegin++;
		}
		return token;
	}


	bool MFile::read_file()
	{
		fstream file(filePath, ios::in);
		string str, temp;
		list<string>ls;//������ʱ�б�
		int i;
		int lastIndex;//��һ���±�
		try {
			if (!file)throw FileError(filePath);
		}
		catch (FileError& error) {
			error.showExceptionInform();
			return false;
		}
		char tempCharacter[FILE_LINE_MAX_NUMBER];
		bool commentsFlag = false;
		list<string>saveList;
		while (!file.eof()) {	//�����ļ����ݵ�saveList
			file.getline(tempCharacter, FILE_LINE_MAX_NUMBER);
			string temp = tempCharacter;
			string tempStr = remove_tabs_and_lineComments(temp);
			if (tempStr == "")continue;
			int commentIndexBegin = tempStr.find("/*");
			int commentIndexEnd = tempStr.find("*/");
			if (commentIndexBegin != -1) {
				if (commentIndexEnd != -1) {
					tempStr = tempStr.substr(0, commentIndexBegin) +
						tempStr.substr(commentIndexEnd, tempStr.length() - commentIndexEnd);
				}
				else {
					commentsFlag = true;
					tempStr = tempStr.substr(0, commentIndexBegin);
				}
			}
			else if (commentsFlag == true && commentIndexEnd == -1) {
				continue;
			}
			else if (commentIndexEnd != -1) {
				commentsFlag = false;
				tempStr = tempStr.substr(commentIndexEnd + 2, tempStr.length() - commentIndexEnd - 2);
			}
			saveList.push_back(tempStr);
		}
		save_file(saveList);
		while (!saveList.empty()) {//��ȡ�ļ����������
			str.clear();
			ls.clear();
			lastIndex = 0;//��Ϊ��
			str = saveList.front();//������
			saveList.pop_front();
			if (str != "") {	//��Ϊ�س�
				bool flag = false;//���ű�ʶ ��
				for (i = 0; i < str.length(); i++) {	//���Ϊ������������߼������
					if (str[i] == '"')flag = !flag;
					if (flag == true)continue; //�������ݲ����д���
					if (str[i] == ',' || str[i] == '+' || str[i] == '-' || str[i] == '*' ||
						str[i] == '/' || str[i] == '<' || str[i] == '>' || str[i] == '=' ||
						str[i] == ')' || str[i] == '(' || str[i] == ' ' || str[i] == ';' ||
						str[i] == '{' || str[i] == '}' || str[i] == ':'	|| str[i] == '[' ||
						str[i] == ']') {
						if (lastIndex != i) {			//�ȱ����������������һ�������
							temp = str.substr(lastIndex, i - lastIndex);
							ls.push_back(temp);
						}
						if ((i + 1 < str.length()) &&
							(str[i] == '<' || (str[i] == '>' && str[i + 1] != '>')) &&
							(str[i + 1] == '>' || str[i + 1] == '=')) {
							temp.clear();
							temp.push_back(str[i]);
							temp.push_back(str[i + 1]);
							ls.push_back(temp);
							lastIndex = i + 2;
							i++;
						}
						else {
							temp = str[i];	//���������
							ls.push_back(temp);
							lastIndex = i + 1;
						}
					}
					else if (str[i] == ' ') {
						temp = str.substr(lastIndex, i - lastIndex);
						ls.push_back(temp);
						lastIndex = i + 1;
					}
				}
				if (lastIndex < str.length()) {		//����һ������
					temp = str.substr(lastIndex, str.length() - lastIndex);
					ls.push_back(temp);
				}
				ls.push_back("\n");
				token.push_back(ls);
				ls.clear();
			}
			else {
				ls.push_back("");
				token.push_back(ls);
			}

		}
		file.close();
		flag = true;
		token = remove_blank(token);
		save_token_file(token);
		return true;
	}

	string& MFile::get_filename()
	{
		return this->filename;
	}

	string& MFile::get_fileDir()
	{
		return this->fileDir;
	}


	/*
	���룺void
	���ܣ���ȡ�ļ��е����ݵ�token�����У��ļ���ȡ�ɹ�����true��ʧ�ܷ���false
	���:bool
	*/

	bool MFile::save_file(list<string>& vec)
	{
		ofstream outFile(savefilePath);
		try {
			if (!outFile) {
				throw  FileError(savefilePath);
			}
		}
		catch (FileError& e) {
			e.showExceptionInform();
			return false;
		//	flag = false;
		}
		list<string>::iterator end = vec.end();
		for (list<string>::iterator begin = vec.begin(); begin != end; begin++) {
			if ((*begin).length() == 0)continue;
			outFile.write((*begin).c_str(), (*begin).length());
			outFile.write("\n", 2);
		}
		outFile.close();
		return true;
	}

	

