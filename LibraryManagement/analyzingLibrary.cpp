#include "analyzingLibrary.h"


// printf("1. Thống kê số lượng sách trong thư viện.\n");
// printf("2. Thống kê số lượng sách theo thể loại.\n");
// printf("3. Thống kê số lượng độc giả.\n");
// printf("4. Thống kê số lượng độc giả theo giới tính.\n");
// printf("5. Thống kê số sách đang được mượn.\n");
// printf("6. Thống kê danh sách độc giả bị trễ hạn.\n");







void runningAnalyzingForAdmin(){
	
}
void runningAnalyzingForExpert(){
	
}
void runningAnalyzingForManager(){
	
}

void runningAnalyzing(int typeAccount){
	switch(typeAccount){
		case 1: // admin
			runningAnalyzingForAdmin();
			break;
		case 2: // chuyên viên
			runningAnalyzingForExpert();
			break;
		default: // quản lý
			runningAnalyzingForManager();
			break;
	}
}