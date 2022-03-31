#pragma once

int getRow(ifstream& ifile){

	/*
	주어진 파일을 한 줄씩 읽으면서 개행문자(\n)를 만날 때마다 row의 값을 1씩 증가시킨다.
	*/

	int row = 0;	// 행 수
	char line; // 한 줄씩 읽어서 임시로 저장할 공간

	// 파일 포인터를 파일의 시작 위치로 이동
	ifile.clear();
	ifile.seekg(0, ios::beg);

	if (ifile.is_open())	// 파일이 열렸을 경우
	{
		while (ifile.get(line)){
			// 개행 문자를 만났을 때
			if (line == '\n'){
				/* 
				개행 문자를 만났을 때 그 다음 문자를 조사한다.
				다음문자가 개행 문자가 아닌 경우에만 카운트하고
				다음문자가 개행 문자인 경우 카운트 하지 않는다.
				*/
				
				ifile.get(line);	
				if (line != '\n')	
					row++;			
			}
		}
		row++;	// 마지막 줄 처리
	}
	return row;
}

int getColumn(ifstream& ifile){

	char ch;
	int count = 1;
	int check_blank = 0;

	// 파일 포인터를 파일의 시작 위치로 이동
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