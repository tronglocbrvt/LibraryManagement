#include "readerManagement.h"

char *getNationalID()
{
	int flag = 0;
	char *idNa = new char();
	do
	{
		printf("Nhap CMND (9 so hoac 12 so): ");
		scanf("%s", idNa);
		int temp = getchar();
		
		if (strlen(idNa) != 9 && strlen(idNa) != 12)
		{
			printf("CMND khong hop le. Vui long nhap lai.\n");
			continue;
		}

		flag = 1; 
		for (int i = 0; i < strlen(idNa); i++)
		{
			if (!isNumber(idNa[i]))
			{
				flag = 0;
				printf("CMND khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);
	return idNa;
}
void printfReader(Readers reader){

	printf("Ma doc gia:\t\t%s\n", reader.ID);
	printf("Ho ten day du:\t\t%s\n", reader.Fullname);
	printf("CMND:\t\t%s\n", reader.NationID);
	printf("Ngay sinh:\t\t%d/ %d / %d\n", reader.Birthday.Date, reader.Birthday.Month, reader.Birthday.Year);
	printf("Gioi tinh:\t\t%s\n", (reader.Sex == 0 ? (char *)"Nu" : (char *)"Nam"));
	printf("Thu dien tu:\t\t%s\n", reader.Email);
	printf("Dia chi:\t\t%s\n", reader.Address);
	printf("Ngay lap the:\t\t%d/ %d / %d\n", reader.creatCard.Date, reader.creatCard.Month, reader.creatCard.Year);
	printf("Ngay het han:\t\t%d/ %d / %d\n", reader.expireCard.Date, reader.expireCard.Month, reader.expireCard.Year);

}

Readers setReaderInf(char *readerID){
	Readers reader;
	int temp;
 	// thêm mã đọc giả -- tự động
	strcpy(reader.ID, readerID);
	// thêm họ và tên
	printf("Nhap Ho va Ten: ");
	gets(reader.Fullname);

	printf("Nhap ngay thang nam sinh:\n");
	reader.Birthday = getDayFrmUser();

	strcpy(&reader.NationID, getNationalID());

	printf("Nhap dia chi: ");
	gets(reader.Address);

	do
	{
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &reader.Sex);
		temp = getchar();

		if (reader.Sex != 0 && reader.Sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
		else break;
	} while (1);

	printf("Nhap dia chi email / thu dien tu: ");
	gets(reader.Email);
	
	// ngày lập thẻ -- lấy ngày tạo tài khoản : hôm nay
	reader.creatCard = getToday();
	// ngày hết hạn là ngày tối đa được lập của thẻ, ngày tối đa là một hằng số
	reader.expireCard = getExpiredDay(reader.creatCard);
	//
	return reader;
}

bool editReaderInf(Readers *reader){

	switch(getNumberPressKey(printfEditReaderInf())){
		case 1:
			printf("Nhap Ho va Ten: ");
			gets(reader.Fullname);
			break;
		case 2:
			printf("Nhap moi CMND de sua:\n");
			strcpy(reader->NationID, getNationalID);
			break;
		case 3:
			printf("Nhap ngay thang nam sinh:\n");
			reader.Birthday = getDayFrmUser();
			break;
		case 4:
			do
			{
				printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
				scanf("%d", &reader.Sex);
				temp = getchar();

				if (reader.Sex != 0 && reader.Sex != 1)
					printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
				else break;
			} while (1);
			break;
		case 5:
			printf("Nhap dia chi email / thu dien tu: ");
			gets(reader.Email);
			break;
		case 6:
			printf("Nhap dia chi: ");
			gets(reader.Address);
			break;
		case 7:
			reader.expireCard = getExpiredDay(getToday());
			break;

	}
	return true;
}



