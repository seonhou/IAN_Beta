#pragma once

int getRow(ifstream& ifile){

	/*
	�־��� ������ �� �پ� �����鼭 ���๮��(\n)�� ���� ������ row�� ���� 1�� ������Ų��.
	*/

	int row = 0;	// �� ��
	char line; // �� �پ� �о �ӽ÷� ������ ����

	// ���� �����͸� ������ ���� ��ġ�� �̵�
	ifile.clear();
	ifile.seekg(0, ios::beg);

	if (ifile.is_open())	// ������ ������ ���
	{
		while (ifile.get(line)){
			// ���� ���ڸ� ������ ��
			if (line == '\n'){
				/* 
				���� ���ڸ� ������ �� �� ���� ���ڸ� �����Ѵ�.
				�������ڰ� ���� ���ڰ� �ƴ� ��쿡�� ī��Ʈ�ϰ�
				�������ڰ� ���� ������ ��� ī��Ʈ ���� �ʴ´�.
				*/
				
				ifile.get(line);	
				if (line != '\n')	
					row++;			
			}
		}
		row++;	// ������ �� ó��
	}
	return row;
}

int getColumn(ifstream& ifile){

	char ch;
	int count = 1;
	int check_blank = 0;

	// ���� �����͸� ������ ���� ��ġ�� �̵�
	ifile.clear();
	ifile.seekg(0, ios::beg);

	if(ifile.is_open()){
		while (ifile.get(ch)){
			if(ch == '\t'){
				check_blank = 1;
			}
			else if(ch == ' '){
				check_blank = 1;
			}
			else if (ch == '\n'){
				break;
			}
			else{
				if(check_blank == 1){
					count = count + 1;
					check_blank = 0;
				}
			}
		}
	}
	return count;
}