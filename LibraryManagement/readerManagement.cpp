#include "readerManagement.h"


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
 	// them ma doc gia
	strcpy(reader.ID, readerID);
	// them ho va ten
	printf("Nhap Ho va Ten: ");
	gets(reader.Fullname);

	do
	{
		printf("Nhap ngay sinh: ");
		scanf("%d", &reader.Birthday.Date);
		temp = getchar();

		printf("Nhap thang sinh: ");
		scanf("%d", &reader.Birthday.Month);
		temp = getchar();

		printf("Nhap nam sinh: ");
		scanf("%d", &reader.Birthday.Year);
		temp = getchar();

		if (!isPossibleDay(reader.Birthday.Date, reader.Birthday.Month, reader.Birthday.Year))
			printf("Ngay thang nam sinh khong hop le vui long nhap lai.\n");
		else break;
	} while (1);

	do
	{
		printf("Nhap CMND (9 so hoac 12 so): ");
		scanf("%s", &reader.NationID);
		temp = getchar();

		if (strlen(reader.NationID) != 9 && strlen(reader.NationID) != 12)
			printf("CMND khong hop le. Vui long nhap lai.\n");
		else break;
	} while (1);

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
	
	// ngay lap the
	reader.creatCard = getToday();
	// ngay het han tu co ham
	reader.expireCard = getExpiredDay(reader.creatCard);

	//
	return reader;
}
